
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


-- lv object table. each entry has a table with the following fields:
-- native obj handle (type userdata) are the indexes
--   ["children"]: table with children objects (use to delete/clean operations)
--      children table: each entry points to an object
--   ["callback"]: callback ID use for finding cb
local objects = lv_objs

--function lv_obj_set_event_cb(obj, func)
--  lv_objs[obj] = func -- ["callback"] = func
--  bind_lv_obj_set_event_cb(obj)
--end

function lv.obj_set_event_cb(obj, func)
  lv_objs[obj] = func -- ["callback"] = func
  bind_lv_obj_set_event_cb(obj)
end

function lvgl_dispatch(ev, arg)
  if ev.id ~= EV_SYS_LVGL.id then
    return false
  end
  local obj = arg.obj
  lv_objs[obj](obj, arg.lvgl_event)
  return true
end







