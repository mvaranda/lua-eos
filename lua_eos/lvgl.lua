
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

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

create_factory()

--local f
--f = load("function test2() print(\"works\") end")
--f()
--M["test2"] = test2
--_G["test2"] = nil






