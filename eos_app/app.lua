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


function app( ctx )
  print ("starting task " .. ctx.name)
  
  local ev = eos.create_user_event("event_1")
  if ev == nil then
    print ("error")
    eos.error(ctx, "error")
    return
  end
  
  eos.create_task(task_demo, "task_demo")
  
  local x = 10
  while(1) do
    print("app is alive, x = " .. x)
    x=x+1
    eos.post(ev, "message from task 1")
    eos.delay(ctx, 2000)
    
  end
end

function task_demo( ctx )
  print ("starting task " .. ctx.name)
  
  eos_set_timer(ctx.task_id, 5, 1000)
  eos_set_timer(ctx.task_id, 6, 1500)
  
  res,msg = eos.subscribe_event_by_name(ctx, "event_1")
  if res == false then
    print(msg)
  end
  
  local t
  while(1) do
    local ev, arg = eos.wait_event(ctx)
    print("task_demo: event = " .. ev.name .. " msg = " .. arg)
  end
end





