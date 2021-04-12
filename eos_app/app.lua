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
g_user_event_1 = nil
g_user_event_2 = nil

local EOS_PATH = "../lua_eos/?.lua;"
package.path = EOS_PATH

require "lvgl"



-- -------- Variables and callback for button 1 -----
local btn_1
local label_1
local btn_1_cnt = 1

local function btn_1_cb (obj, ev)
  if ev == LV_EVENT_PRESSED then
    lv_label_set_text(label_1, "Button " .. tostring(btn_1_cnt))
    btn_1_cnt = btn_1_cnt + 1
    eos.post(g_user_event_1, "user event sent by btn_1_cb")
  end
end

-- -------- Variables and callback for button 2 -----
local btn_2
local label_2
local btn_2_cnt = 1

local function btn_2_cb (obj, ev)
  if ev == LV_EVENT_PRESSED then
    lv_label_set_text(label_2, "Button " .. tostring(btn_2_cnt))
    btn_2_cnt = btn_2_cnt + 1
    eos.post(g_user_event_1, "user event sent by btn_2_cb")
  end
end

function task_test_user_event_1( ctx )  
  --local res,msg = eos.subscribe_event_by_name(ctx, "g_user_event_1")
  local res,msg = eos.subscribe_event(ctx, g_user_event_1)
  if res == false then
    print(msg)
    return
  end
  while(1) do
    local ev, arg = eos.wait_event(ctx)
    print("task_demo: event = " .. ev.name .. ", msg = " .. arg)
  end
end

-- -------------- Main App ------------
function app(ctx)
  -- creat user event
  g_user_event_1 = eos.create_user_event("user_event_1")
  if g_user_event_1 == nil then
    print("could not create user event")
  end
  
  eos.create_task(task_test_user_event_1, "task_test_user_event_1")

  ok, msg = eos.subscribe_event_by_name(ctx, "EV_SYS_LVGL")
  if ok == false then
    print(msg)
  end
  
  btn_1 = lv_btn_create(lv_scr_act(), 0)
  lv_obj_set_pos(btn_1, 10, 10)
  lv_obj_set_size(btn_1, 120, 50)
  label_1 = lv_label_create(btn_1, 0)
  lv_label_set_text(label_1, "Button")
  lv_obj_set_event_cb(btn_1, btn_1_cb)

  btn_2 = lv_btn_create(lv_scr_act(), 0)
  lv_obj_set_pos(btn_2, 150, 10)
  lv_obj_set_size(btn_2, 120, 50)
  label_2 = lv_label_create(btn_2, 0)
  lv_label_set_text(label_2, "Button")
  lv_obj_set_event_cb(btn_2, btn_2_cb)

  while(1) do
    local ev, arg = eos.wait_event(ctx)
    lvgl_dispatch(ev, arg) -- lvgl_dispatch returns true if event was LVGL
                           -- it can be used in "elseif then" chain

  end

end

function _app( ctx )
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





