
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

if EOS_PLATFORM == "SIMULATOR" then
  EOS_PATH = "../target_files/?.lua;"
else
  EOS_PATH = "/spiffs/?.lua;"
end
package.path = EOS_PATH

require "lvgl"
require "lv_disp"
require "lv_obj"
require "lv_btn"
require "lv_checkbox"
require "lv_label"
require "lv_linemeter"
require "lv_slider"
require "lv_style"
require "lv_color"
require "lv_switch"


--------
global_demo = 0
glog = false
g_user_event_1 = nil


-- -------- Variables and callback for button 1 -----
btn_1 = nil
label_1 = nil
btn_1_cnt = 1

local function btn_1_cb (obj, ev)
  if ev == LV_EVENT_PRESSED then
    lv.label_set_text(label_1, "Button " .. tostring(btn_1_cnt))
    btn_1_cnt = btn_1_cnt + 1
    eos.post(g_user_event_1, "user event sent by btn_1_cb")
  end
end

-- -------- Variables and callback for button 2 -----
btn_2 = nil
label_2 = nil
btn_2_cnt = 1

local function btn_2_cb (obj, ev)
  if ev == LV_EVENT_PRESSED then
    lv.label_set_text(label_2, "Button " .. tostring(btn_2_cnt))
    btn_2_cnt = btn_2_cnt + 1
    eos.post(g_user_event_1, "user event sent by btn_2_cb")
  end
end

------------- callback for slider -----
function slider_handler (obj, ev)
 local v = lv.slider_get_value(obj)
 lv.linemeter_set_value(lmeter, v)
end

-- ---------- Init UI -------------
local function init_ui()
  btn_1 = lv.btn_create(lv.scr_act(), 0)
  lv.obj_set_pos(btn_1, 30, 10)
  lv.obj_set_size(btn_1, 120, 50)
  label_1 = lv.label_create(btn_1, 0)
  lv.label_set_text(label_1, "Button")
  lv.obj_set_event_cb(btn_1, btn_1_cb)
  
  btn_2 = lv.btn_create(lv.scr_act(), 0)
  lv.obj_set_pos(btn_2, 170, 10)
  lv.obj_set_size(btn_2, 120, 50)
  label_2 = lv.label_create(btn_2, 0)
  lv.label_set_text(label_2, "Button")
  lv.obj_set_event_cb(btn_2, btn_2_cb)

  lmeter = lv.linemeter_create(lv.scr_act(), 0)
  lv.linemeter_set_range(lmeter, 0, 100)
  lv.linemeter_set_value(lmeter, 80)
  lv.linemeter_set_scale(lmeter, 240, 10)
  lv.obj_set_size(lmeter, 100, 100)
  lv.obj_align(lmeter, 0, 0, 0, 70)

  slider = lv.slider_create(lv.scr_act(), 0)
  lv.obj_align(slider, 0, 0, 0, 0)
  lv.slider_set_range(slider, 0, 100)
  lv.obj_set_event_cb(slider, slider_handler)
end

-- ----------- dome: new task demo receiving user defined event ----------
function task_test_user_event_1( ctx )  
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

-- -------------- Main App for simulator ------------
function app_default(ctx)
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
  
  init_ui()

  while(1) do
    local ev, arg = eos.wait_event(ctx)
    lvgl_dispatch(ev, arg) -- lvgl_dispatch returns true if event was LVGL
                           -- it can be used in "elseif then" chain

  end

end
--------


function app_kalunga( ctx )

  init_ui()

  while(1) do
    global_demo = global_demo+1
    if glog == true then 
      print("app is alive, global_demo = " .. global_demo)
    end

    eos.delay(ctx, 1000)
    btn_1_cnt = btn_1_cnt + 1
    lv.label_set_text(label_1, "Button " .. btn_1_cnt)
    if (btn_1_cnt % 2) > 0 then
      btn_2_cnt = btn_2_cnt + 1
      lv.label_set_text(label_2, "Button " .. btn_2_cnt)
    end
      
  end
end

function app(ctx)
  if EOS_PLATFORM == "SIMULATOR" or EOS_PLATFORM == "NSCREEN32" then
    app_default(ctx)
  else
    app_kalunga(ctx)
  end
end
