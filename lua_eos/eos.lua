
-- http://lua-users.org/wiki/LuaStyleGuide
function show(t) for k,v in pairs(t) do print(k .. " =  ".. v) end end

function _eos_delay(t)
  local x = 0
  local y = 0
  while (x < 100000) do
    x = x + 1
    while (y < t * 50000) do
      y = y + 1
    end
  end
end

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

-- comment out the following line for eos
eos_delay = _eos_delay

schd = {}
local tasks = {}
local user_events = {}

local user_event = 1000

local ST_YIELD = 1
local ST_WAIT_DELAY = 2
local ST_WAIT_EVENT = 3
local ST_ERROR = 4

local function scheduler()
  local success
  local args
  while(1) do
    for k,v in pairs(tasks) do
      
      success = true
      if v.state == ST_YIELD then
        success, args = coroutine.resume(v.co, v, "ID", "ARGS")
      elseif v.state ==  ST_WAIT_DELAY then
        print("WAIT_DELAY not implemeneted")
        return
      elseif v.state ==  ST_WAIT_EVENT then
        if #v.ev_q > 0 then
          local e = table.remove(v.ev_q, 1)
          
        end
      else
        print("unexpected e.state = " .. v.state)
        return
      end
      
      if success == false then
        print("Error: " .. args)
        return
      end
      eos_delay(1000)
    end
  end
end

function schd.create_user_event(name, high_priority)
  local p = false
  if high_priority ~= nil then
    p = high_priority
  end
  local ev = {}
  ev.id = user_event
  ev.name = name
  ev.pri = high_priority
  user_event = user_event + 1
  table.insert(user_events, ev)
  return ev
end

function schd.subscribe_event(ctx, event)
  -- chech if event already subscribed
  for k,v in pairs(ctx.ev_q) do
    if event.id == v.id then
      print("event already subscribed")
      return
    end
  end
  table.insert(ctx.ev_q, event)
end

function schd.subscribe_event_by_name(ctx, name)
  for k,v in pairs(user_events) do
    if name == v.name then
      schd.subscribe_event(ctx, v)
      return true
    end
  end
  return false, "could not find event " .. name
end


function schd.create_task(task_func, name)
  local e = {}
  e["co"] = coroutine.create(task_func)
  e["name"] = name
  e["state"] = ST_YIELD
  e["subscription"] = {}
  e["ev_q"] = {} -- entries have "ev_id" and "table_values"
  table.insert(tasks, e)
end

function schd.scheduler()
  scheduler()
end

function schd.yield()
  coroutine.yield()
end



function task1( ctx )
  print ("starting task " .. ctx.name)
  
  local ev = schd.create_user_event("event_1")
  
  local x = 10
  while(1) do
    print("task1, x = " .. x)
    x=x+1
    schd.yield()
  end
end

function task2( ctx )
  print ("starting task " .. ctx.name)
  
  local res,msg = schd.subscribe_event_by_name(ctx, "event_1")
  if res == false then
    print(msg)
  end
  
  local y = 1
  while(1) do
    print("task2, y = " .. y)
    y=y+1
    schd.yield()
  end
end

schd.create_task(task1, "task1")
schd.create_task(task2, "task2")
schd.scheduler()




