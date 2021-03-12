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

global_demo = 0
glog = false

function app( ctx )
  --print ("starting task " .. ctx.name)
  
  local ev = eos.create_user_event("event_1")
  if ev == nil then
    print ("error")
    eos.error(ctx, "error")
    return
  end
  
  --eos.create_task(task_demo, "task_demo")
  

  while(1) do
    global_demo = global_demo+1
    if glog == true then 
      print("app is alive, global_demo = " .. global_demo)
    end
    --eos.post(ev, "message from task 1")
    eos.delay(ctx, 1000)
    
  end
end

function task_demo( ctx )
  --print ("starting task " .. ctx.name)
  
  eos_set_timer(ctx.task_id, 5, 1000)
  eos_set_timer(ctx.task_id, 6, 1500)
  
  local res,msg = eos.subscribe_event_by_name(ctx, "event_1")
  if res == false then
    print(msg)
  end
  
  res,msg = eos.subscribe_event_by_name(ctx, "EV_SYS_TIMER")
  if res == false then
    print(msg)
  end

  
  local t
  while(1) do
    local ev, arg = eos.wait_event(ctx)
    print("task_demo: event = " .. ev.name .. " msg = " .. arg)
  end
end





