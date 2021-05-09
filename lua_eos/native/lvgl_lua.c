/***************************************************************
 *
 *                 This code is part of LUA_EOS
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include "log.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"
#include "lualib.h"


#ifdef __cplusplus
extern "C" {
#endif

//----------- prototypes ----------


// bindings

typedef lv_obj_t * (*create_func_prototype_t) (lv_obj_t *parent, const lv_obj_t *copy);

typedef struct create_func_st {
    uint32_t                    id;
    create_func_prototype_t     func;
} create_func_t;

static const create_func_t create_func_info[] = {
  { 0, lv_obj_create },             // { name = "lv_obj_create",           func_id = 0 },
  { 1, lv_label_create },           // { name = "lv_lable_create",         func_id = 1 },
  { 2, lv_btn_create },             // { name = "lv_btn_create",           func_id = 2 },
  { 3, NULL}
};

#define CREATE_FUNC_INFO_LEN ((sizeof(create_func_info) / sizeof(create_func_t)) - 1)

static int bind_lv_create(lua_State *L)
{
    int32_t func_id = (uint32_t) lua_tointeger(L,1);
    void * par = lua_touserdata(L,2);
    void * copy = lua_touserdata(L,3);

    if (func_id >= CREATE_FUNC_INFO_LEN || func_id < 0) {
        LOG_E("bind_lv_create: invalid func_id %d", func_id);
        lua_pushnil(L);
        return 1;
    }
    //LOG("bind_lv_create:  func_id = %d\r\n", func_id);
    create_func_prototype_t f = create_func_info[func_id].func;

    lv_obj_t * obj = f(par, (const lv_obj_t *) copy);
    // LOG("bind_lv_create creted: 0x%x\r\n", (unsigned int) obj);
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}



static int bind_lv_scr_act(lua_State *L)
{
    void * obj = lv_scr_act();
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

static int bind_lv_obj_set_pos(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    short x = (short) lua_tointeger(L,2);
    short y = (short) lua_tointeger(L,3);
    lv_obj_set_pos(obj, x, y);
    return 0;
}

static int bind_lv_obj_set_size(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    short x =  (short) lua_tointeger(L,2);
    short y =  (short) lua_tointeger(L,3);
    lv_obj_set_size(obj, x, y);
    return 0;
}

static int bind_lv_label_set_text(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    const char * txt = lua_tostring(L,2);
    lv_label_set_text(obj, txt);
    return 0;
}

static void cb_event_push_lvgl (lua_State *L, ev_queue_item_t * item_ptr)
{
  lua_pushstring(L, "ev_id");                      // Key
  lua_pushinteger(L, item_ptr->event_id);    // value
  lua_settable(L, -3);

  //--------- arg table ----------
  lua_pushstring(L, "arg");
  lua_newtable(L);
  // field 1
  lua_pushstring(L, "obj");                      // Key
  lua_pushlightuserdata(L, item_ptr->item.lvgl_item.obj);    // value
  lua_settable(L, -3);

  // field 2
  lua_pushstring(L, "lvgl_event");                        // Key
  lua_pushinteger(L, item_ptr->item.lvgl_item.lv_event);   // value
  lua_settable(L, -3);


  lua_settable(L, -3);
  //-------------------------------

}

static void lv_cb(lv_obj_t * obj, lv_event_t event)
{

    ev_queue_item_t ev_item;
    memset(&ev_item, 0, sizeof(ev_item));
    ev_item.event_id = EV_SYS_LVGL;
    ev_item.cb_event_push = (void *) cb_event_push_lvgl;
    ev_item.item.lvgl_item.obj = obj;
    ev_item.item.lvgl_item.lv_event = event;
    // LOG("add EV_SYS_LVGL event %d", event);
    add_event_to_queue(&ev_item);

}

#define LV_LIB_NAME "lv"
#define LV_OBJECTS  "lv_objs"

void lv_append_lib_funcs(lua_State *L, luaL_Reg * reg)
{
  lua_getglobal(L, LV_LIB_NAME);
  if ( ! lua_istable(L, -1)) {
    // create table to store all lv functions and variables
    luaL_newlib (L, reg);
    lua_setglobal(L, LV_LIB_NAME);

    return;
  }
  luaL_setfuncs(L, reg, 0);
}

extern lua_State * get_lua_state(void);

void lv_append_obj(void * obj)
{
  lua_State * L = get_lua_state();
  if ( ! L) {
      LOG("L not available");
      return;
  }

  lua_getglobal(L, LV_OBJECTS);

  if ( ! lua_istable(L, -1)) {
    // create a table to track objects to forward events
    lua_newtable(L);
    lua_pushstring(L, "dummy_key");
    lua_pushstring(L, "dummy_val");
    lua_settable(L, -3);
    lua_setglobal(L, LV_OBJECTS);
    LOG("lv_objs created\r\n");
    lua_getglobal(L, LV_OBJECTS); // to top again
  }

  lua_pushstring(L, "dummy");
  lua_setfield( L, -2, obj );
}

static int bind_lv_obj_set_event_cb (lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    lv_obj_set_event_cb(obj, lv_cb);
    return 0;
}

void lvgl_lua_init(lua_State *L)
{
//    lua_pushcfunction(L, bind_lv_create);
//    lua_setglobal(L, "bind_lv_create");

//    lua_pushcfunction(L, bind_lv_scr_act);
//    lua_setglobal(L, "lv_scr_act");

//    lua_pushcfunction(L, bind_lv_obj_set_pos);
//    lua_setglobal(L, "lv_obj_set_pos");

//    lua_pushcfunction(L, bind_lv_obj_set_size);
//    lua_setglobal(L, "lv_obj_set_size");

//    lua_pushcfunction(L, bind_lv_label_set_text);
//    lua_setglobal(L, "lv_label_set_text");

    lua_pushcfunction(L, bind_lv_obj_set_event_cb);
    lua_setglobal(L, "bind_lv_obj_set_event_cb");


}


#ifdef __cplusplus
extern }
#endif



