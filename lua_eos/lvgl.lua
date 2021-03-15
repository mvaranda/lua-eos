
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

LV_EVENT_PRESSED = 0 --             /**< The object has been pressed*/
LV_EVENT_PRESSING = 1  --            /**< The object is being pressed (called continuously while pressing)*/
LV_EVENT_PRESS_LOST = 2  --          /**< User is still pressing but slid cursor/finger off of the object */
LV_EVENT_SHORT_CLICKED = 3  --       /**< User pressed object for a short period of time, then released it. Not called if dragged. */
LV_EVENT_LONG_PRESSED = 4  --        /**< Object has been pressed for at least LV_INDEV_LONG_PRESS_TIME.  Not called if dragged.*/
LV_EVENT_LONG_PRESSED_REPEAT = 5  -- /**< Called after LV_INDEV_LONG_PRESS_TIME in every `LV_INDEV_LONG_PRESS_REP_TIME` ms.  Not called if dragged.*/
LV_EVENT_CLICKED = 6  --             /**< Called on release if not dragged (regardless to long press)*/
LV_EVENT_RELEASED =  7 --            /**< Called in every cases when the object has been released*/
LV_EVENT_DRAG_BEGIN = 8  --
LV_EVENT_DRAG_END = 9  --
LV_EVENT_DRAG_THROW_BEGIN = 10  --
LV_EVENT_GESTURE = 11  --           /**< The object has been gesture*/
LV_EVENT_KEY = 12  --
LV_EVENT_FOCUSED = 13  --
LV_EVENT_DEFOCUSED = 14  --
LV_EVENT_LEAVE = 15  --
LV_EVENT_VALUE_CHANGED = 16  --      /**< The object's value has changed (i.e. slider moved) */
LV_EVENT_INSERT = 17  --
LV_EVENT_REFRESH = 18  --
LV_EVENT_APPLY = 19  --  /**< "Ok" ,    "Apply" or similar specific button has clicked*/
LV_EVENT_CANCEL = 20  -- /**< "Close" ,    "Cancel" or similar specific button has clicked*/
LV_EVENT_DELETE = 21  -- /**< Object is being deleted */


-- lv object table. each entry has a table withthe following fields:
-- native obj handle (type userdata) are the indexes
--   ["children"]: table with children objects (use to delete/clean operations)
--      children table: each entry points to an object
--   ["callback"]: callback ID use for finding cb
local objects = {}

-- create ID's. It must match with create_func_id_t enumeration in lvgl_lua.c
local CREATE_OBJ_FACTORY_INFO = {
  { name = "lv_obj_create",           func_id = 0 },
  { name = "lv_label_create",         func_id = 1 },
  { name = "lv_btn_create",           func_id = 2 },
}

function add_obj(h)
  objects[h] = {}
end

local CREATE_OBJ_END = ", par, copy) if h ~= nil then add_obj(h) end return h end"
local function create_factory()
  local f,k,v
  for k,v in pairs(CREATE_OBJ_FACTORY_INFO) do
    f = load("function " .. v.name .. "(par, copy) local h = bind_lv_create( " .. v.func_id .. CREATE_OBJ_END)
    f()
  end
end

function lv_obj_set_event_cb(obj, func)
  objects[obj]["callback"] = func
  bind_lv_obj_set_event_cb(obj)
end

function lvgl_dispatch(obj, event)
  if objects[obj] ~= nil then
    if type(objects[obj].callback) == 'function' then
      objects[obj].callback(obj, event)
    end
  end
end


create_factory()

--local f
--f = load("function test2() print(\"works\") end")
--f()
--M["test2"] = test2
--_G["test2"] = nil






