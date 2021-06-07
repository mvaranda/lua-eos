
 /*
 ###############################################################
 #
 #                 This code is part of LUA_EOS
 #
 # Copyrights 2021 - Varanda Labs Inc.
 #
 # License:
 #   Creative Commons: CC BY-NC-SA 4.0
 #   Attribution-NonCommercial-ShareAlike 4.0 International
 #   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 #
 #   Note: for purchasing a commertial license contact:
 #     m@varanda.ca
 #
 ###############################################################
*/

#include "log.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"
#include "lv_keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_keyboard_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_keyboard_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_keyboard_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_keyboard_set_textarea(lv_obj_t * kb, lv_obj_t * ta);
// ***********************************************

static int bind_lv_keyboard_set_textarea(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  void * ta = lua_touserdata(L,2);

  lv_keyboard_set_textarea(kb, ta);

  return 0;
}


// ***********************************************
// * void lv_keyboard_set_mode(lv_obj_t * kb, lv_keyboard_mode_t mode);
// ***********************************************

static int bind_lv_keyboard_set_mode(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  int mode = lua_tointeger(L,2);

  lv_keyboard_set_mode(kb, mode);

  return 0;
}


// ***********************************************
// * void lv_keyboard_set_cursor_manage(lv_obj_t * kb, bool en);
// ***********************************************

static int bind_lv_keyboard_set_cursor_manage(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_keyboard_set_cursor_manage(kb, en);

  return 0;
}


// ***********************************************
// * void lv_keyboard_set_map(lv_obj_t * kb, lv_keyboard_mode_t mode, const char * map[]);
// ***********************************************

static int bind_lv_keyboard_set_map(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  int mode = lua_tointeger(L,2);
  const char * map = lua_tostring(L,3);

  lv_keyboard_set_map(kb, mode, map); // REPAIR

  return 0;
}


// ***********************************************
// * void lv_keyboard_set_ctrl_map(lv_obj_t * kb, lv_keyboard_mode_t mode, const lv_btnmatrix_ctrl_t ctrl_map[]);
// ***********************************************

static int bind_lv_keyboard_set_ctrl_map(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  int mode = lua_tointeger(L,2);
  const lv_btnmatrix_ctrl_t * ctrl_map = lua_touserdata(L,3);

  lv_keyboard_set_ctrl_map(kb, mode, ctrl_map); // REPAIR

  return 0;
}


// ***********************************************
// * lv_obj_t * lv_keyboard_get_textarea(const lv_obj_t * kb);
// ***********************************************

static int bind_lv_keyboard_get_textarea(lua_State *L)
{
  void * kb = lua_touserdata(L,1);

  lv_obj_t * ret = lv_keyboard_get_textarea(kb);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_keyboard_mode_t lv_keyboard_get_mode(const lv_obj_t * kb);
// ***********************************************

static int bind_lv_keyboard_get_mode(lua_State *L)
{
  void * kb = lua_touserdata(L,1);

  lv_keyboard_mode_t ret = lv_keyboard_get_mode(kb);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_keyboard_get_cursor_manage(const lv_obj_t * kb);
// ***********************************************

static int bind_lv_keyboard_get_cursor_manage(lua_State *L)
{
  void * kb = lua_touserdata(L,1);

  bool ret = lv_keyboard_get_cursor_manage(kb);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline const char ** lv_keyboard_get_map_array(const lv_obj_t * kb){    return lv_btnmatrix_get_map_array(kb);
// ***********************************************

static int bind_lv_keyboard_get_map_array(lua_State *L)
{
  void * lv_btnmatrix_get_map_array = lua_touserdata(L,1);

  const char ** ret = lv_keyboard_get_map_array(lv_btnmatrix_get_map_array);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * void lv_keyboard_def_event_cb(lv_obj_t * kb, lv_event_t event);
// ***********************************************

static int bind_lv_keyboard_def_event_cb(lua_State *L)
{
  void * kb = lua_touserdata(L,1);
  int event = lua_tointeger(L,2);

  lv_keyboard_def_event_cb(kb, event);

  return 0;
}



static const luaL_Reg binding_names [] = {
  { "keyboard_create", bind_lv_keyboard_create },
  { "keyboard_set_textarea", bind_lv_keyboard_set_textarea },
  { "keyboard_set_mode", bind_lv_keyboard_set_mode },
  { "keyboard_set_cursor_manage", bind_lv_keyboard_set_cursor_manage },
  { "keyboard_set_map", bind_lv_keyboard_set_map },
  { "keyboard_set_ctrl_map", bind_lv_keyboard_set_ctrl_map },
  { "keyboard_get_textarea", bind_lv_keyboard_get_textarea },
  { "keyboard_get_mode", bind_lv_keyboard_get_mode },
  { "keyboard_get_cursor_manage", bind_lv_keyboard_get_cursor_manage },
  { "keyboard_get_map_array", bind_lv_keyboard_get_map_array },
  { "keyboard_def_event_cb", bind_lv_keyboard_def_event_cb },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_keyboard__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
