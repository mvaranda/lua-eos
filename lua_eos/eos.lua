--/***************************************************************
-- *
-- *                 This code is part of LUA_EOS
-- *
-- * Copyrights 2021 - Varanda Labs Inc.
-- *
-- * License:
-- *   Creative Commons: CC BY-NC-SA 4.0
-- *   Attribution-NonCommercial-ShareAlike 4.0 International
-- *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
-- *
-- *   Note: for purchasing a commertial license contact:
-- *     m@varanda.ca
-- *
-- ***************************************************************
-- */

-- http://lua-users.org/wiki/LuaStyleGuide
-- check optimization: https://github.com/pallene-lang/pallene

function show(t)
  for k,v in pairs(t) do
    print(k,v)
    if type(v) == 'table' then
      show(v) -- recursive
    end
  end 
end


--function _eos_delay(t)
--  local x = 0
--  local y = 0
--  while (x < 100000) do
--    x = x + 1
--    while (y < t * 50000) do
--      y = y + 1
--    end
--  end
--end

local function getfenv(fn)
  local i = 1
  while true do
    local name, val = debug.getupvalue(fn, i)
    if name == "_ENV" then
      return val
    elseif not name then
      break
    end
    i = i + 1
  end
end

local function setfenv(fn, env)
  local i = 1
  while true do
    local name = debug.getupvalue(fn, i)
    if name == "_ENV" then
      debug.upvaluejoin(fn, i, (function()
        return env
      end), 1)
      break
    elseif not name then
      break
    end

    i = i + 1
  end

  return fn
end


eos = {}
local tasks = {}

-- the following id's must match with sys_events_t enumeration
EV_SYS_START_UP =  {id = 1,    name = "EV_SYS_START_UP",        pri = false}
EV_SYS_SHUT_DOWN = {id = 2,    name = "EV_SYS_SHUT_DOWN",       pri = false}
EV_SYS_TIMER =     {id = 3,    name = "EV_SYS_TIMER",           pri = false}

local events_list = {
  EV_SYS_START_UP, 
  EV_SYS_SHUT_DOWN
}

local user_event = 1000
local task_id_cnt = 1

local ST_YIELD = 1
local ST_WAIT_DELAY = 2
local ST_WAIT_EVENT = 3
local ST_ERROR = 4

-- ----------------------------
--
--      S C H E D U L E R
--
-- ----------------------------

local function scheduler()
  local success
  local args
  local fist_time = true
  local nat_ev
  
  while(1) do
    nat_ev = eod_read_event_table()
    
    for k,task in pairs(tasks) do
      
      if nat_ev ~= nil then
        for kk,ev in pairs(nat_ev) do
          -- check if timer 
          if ev.ev_id == EV_SYS_TIMER.id then
            
            if ev.task_id == task.task_id then
              -- if timer ID = 0 this is a delay
              if ev.timer_id == 0 then
                print("** EVENT IS EXPIRED DELAY.. change to YIELD state")
                task.state = ST_YIELD
              else
                print("** EVENT IS TIMER")
              
              end
            end
          else
            for kkk, sub in pairs(task.subscription) do
              if sub.id == ev.ev_id then
                -- TODO: add exception for timer as task id must also match
                table.insert(task.ev_q, {event=sub, arg=ev})
              end
            end
          end  
        end
      end
      
      success = true
      if task.state == ST_YIELD then
        success, args = coroutine.resume(task.co, task, "ID", "ARGS")
      elseif task.state ==  ST_WAIT_DELAY then
        -- do nothing
      elseif task.state ==  ST_WAIT_EVENT then
        if #task.ev_q > 0 then
          local e = table.remove(task.ev_q, 1)
          success, args = coroutine.resume(task.co, task, e.event, e.arg)
        end
      elseif task.state ==  ST_ERROR then
        -- TODO: remove task from the list
      else
        print("unexpected e.state = " .. task.state)
        return
      end
      
      if success == false then
        print("Error: " .. args)
        return
      end
      
    end
    
    --eos_delay(100)
    
    if fist_time then
      eos.post(EV_SYS_START_UP, "Starting up")
      fist_time = false
    end
    
    -- read events from native and dispatch them
    
  end
end

function eos.delay(ctx, time)
  eos_set_timer(ctx.task_id, 0, time)
  ctx.state = ST_WAIT_DELAY
  local c, e, arg = coroutine.yield()
end

function eos.create_user_event(name, high_priority)
  local p = false
  for k,v in pairs(events_list) do
    if v.name == name then
      return nil, "event name already taken: " .. name
    end
  end
  if high_priority ~= nil then
    p = high_priority
  end
  local ev = { id = user_event,
               name = name,
               pri = high_priority
  }
  user_event = user_event + 1
  table.insert(events_list, ev)
  return ev
end

function eos.post(event, arg)
  for k,task in pairs(tasks) do
    for kk, e in pairs(task.subscription) do
      if e == event then
        table.insert(task.ev_q, {event=event, arg=arg})
      end
    end
  end
end

function eos.subscribe_event(ctx, event)
  -- chech if event already subscribed
  for k,v in pairs(ctx.subscription) do
    if event.id == v.id then
      print("event already subscribed")
      return
    end
  end
  table.insert(ctx.subscription, event)
  -- print("Subscribed: " .. event.name)
end

function eos.subscribe_event_by_name(ctx, name)
  for k,v in pairs(events_list) do
    if name == v.name then
      eos.subscribe_event(ctx, v)
      return true
    end
  end
  return false, "could not find event " .. name
end


function eos.create_task(task_func, name)
  local e = {}
  e["task_id"] = task_id_cnt
  task_id_cnt = task_id_cnt + 1
  e["co"] = coroutine.create(task_func)
  e["name"] = name
  e["state"] = ST_YIELD
  e["subscription"] = {}
  e["ev_q"] = {} -- entries have "ev_id" and "table_values"
  table.insert(tasks, e)
end

function eos.scheduler()
  scheduler()
end

function eos.wait_event(ctx)
  ctx.state = ST_WAIT_EVENT
  local c, e, arg = eos.yield()
  return e, arg
end

function eos.yield()
  local c, e, arg = coroutine.yield()
  return c,e,arg
end

function eos.error(ctx, msg)
  ctx.state = ST_ERROR
end

function task1( ctx )
  print ("starting task " .. ctx.name)
  
  local ev = eos.create_user_event("event_1")
  if ev == nil then
    print ("error")
    eos.error(ctx, "error")
    return
  end
  
  local x = 10
  while(1) do
    print("task1, x = " .. x)
    x=x+1
    if (x % 5) == 0 then
      eos.post(ev, "message from task 1")
    end
    --eos.yield()
    eos.delay(ctx, 200)
    
  end
end

function task3( ctx )
  print ("starting task " .. ctx.name)
  
  eos_set_timer(ctx.task_id, 5, 2000)
  eos_set_timer(ctx.task_id, 6, 2000)
  
  res,msg = eos.subscribe_event_by_name(ctx, "event_1")
  if res == false then
    print(msg)
  end
  
  local y = 1
  local t
  while(1) do
--    print("task2, y = " .. y)
--    y=y+1
--    eos.yield()
    local ev, arg = eos.wait_event(ctx)
    print("task3: event = ", ev.name, " msg = ", arg)
    

  end
end



function task2( ctx )
  print ("starting task " .. ctx.name)
  
  -- subscribe for events
  local res,msg = eos.subscribe_event_by_name(ctx, "EV_SYS_START_UP")
  if res == false then
    print(msg)
  end
  res,msg = eos.subscribe_event_by_name(ctx, "event_1")
  if res == false then
    print(msg)
  end

  eos.create_task(task3, "task3")
  
  local y = 1
  while(1) do
--    print("task2, y = " .. y)
--    y=y+1
--    eos.yield()
    local ev, arg = eos.wait_event(ctx)
    print("task2: event = ", ev.name, " msg = ", arg)
  end
end

eos.create_task(task1, "task1")
--eos.create_task(task2, "task2")
eos.scheduler()




