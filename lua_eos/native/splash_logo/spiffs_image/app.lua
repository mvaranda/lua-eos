
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
glog = true

function app( ctx )
  print ("starting task " .. ctx.name)
  
--  local ev = eos.create_user_event("event_1")
--  if ev == nil then
--    print ("error")
--    eos.error(ctx, "error")
--    return
--  end
  
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
