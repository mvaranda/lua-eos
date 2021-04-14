
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

local EOS_PATH = "/spiffs/?.lua;"
package.path = EOS_PATH
require "lvgl"

global_demo = 0
glog = false

local btn_1
local label_1
local btn_1_cnt = 1

local btn_2
local label_2
local btn_2_cnt = 1

local function init_ui()
  print("init_ui: in")
  btn_1 = lv_btn_create(lv_scr_act(), 0)
  lv_obj_set_pos(btn_1, 30, 10)
  lv_obj_set_size(btn_1, 120, 50)
  label_1 = lv_label_create(btn_1, 0)
  lv_label_set_text(label_1, "Button_A")
  
  btn_2 = lv_btn_create(lv_scr_act(), 0)
  lv_obj_set_pos(btn_2, 170, 10)
  lv_obj_set_size(btn_2, 120, 50)
  label_2 = lv_label_create(btn_2, 0)
  lv_label_set_text(label_2, "Button_B")
  print("init_ui: out")
end

function app( ctx )
--  print ("starting task " .. ctx.name)

  
--  local ev = eos.create_user_event("event_1")
--  if ev == nil then
--    print ("error")
--    eos.error(ctx, "error")
--    return
--  end
  
  --eos.create_task(task_demo, "task_demo")
  init_ui()

  while(1) do
    global_demo = global_demo+1
    if glog == true then 
      print("app is alive, global_demo = " .. global_demo)
    end
    --eos.post(ev, "message from task 1")
    eos.delay(ctx, 1000)
    btn_1_cnt = btn_1_cnt + 1
    lv_label_set_text(label_1, "Button " .. btn_1_cnt)
    if (btn_1_cnt % 2) > 0 then
      btn_2_cnt = btn_2_cnt + 1
      lv_label_set_text(label_2, "Button " .. btn_2_cnt)
    end
      
  end
end
