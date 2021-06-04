
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
#include "lv_checkbox.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_checkbox_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_checkbox_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_checkbox_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_checkbox_set_text(lv_obj_t * cb, const char * txt);
// ***********************************************

static int bind_lv_checkbox_set_text(lua_State *L)
{
  void * cb = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_checkbox_set_text(cb, txt);

  return 0;
}


// ***********************************************
// * void lv_checkbox_set_text_static(lv_obj_t * cb, const char * txt);
// ***********************************************

static int bind_lv_checkbox_set_text_static(lua_State *L)
{
  void * cb = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_checkbox_set_text_static(cb, txt);

  return 0;
}


// ***********************************************
// * void lv_checkbox_set_checked(lv_obj_t * cb, bool checked);
// ***********************************************

static int bind_lv_checkbox_set_checked(lua_State *L)
{
  void * cb = lua_touserdata(L,1);
  int checked = lua_toboolean(L,2);

  lv_checkbox_set_checked(cb, checked);

  return 0;
}


// ***********************************************
// * void lv_checkbox_set_disabled(lv_obj_t * cb);
// ***********************************************

static int bind_lv_checkbox_set_disabled(lua_State *L)
{
  void * cb = lua_touserdata(L,1);

  lv_checkbox_set_disabled(cb);

  return 0;
}


// ***********************************************
// * void lv_checkbox_set_state(lv_obj_t * cb, lv_btn_state_t state);
// ***********************************************

static int bind_lv_checkbox_set_state(lua_State *L)
{
  void * cb = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);

  lv_checkbox_set_state(cb, state);

  return 0;
}


// ***********************************************
// * const char * lv_checkbox_get_text(const lv_obj_t * cb);
// ***********************************************

static int bind_lv_checkbox_get_text(lua_State *L)
{
  void * cb = lua_touserdata(L,1);

  const char * ret = lv_checkbox_get_text(cb);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * static inline bool lv_checkbox_is_checked(const lv_obj_t * cb){    return lv_btn_get_state(cb) == LV_BTN_STATE_RELEASED ? false : true;
// ***********************************************

static int bind_lv_checkbox_is_checked(lua_State *L)
{
  void * lv_btn_get_state = lua_touserdata(L,1);

  bool ret = lv_checkbox_is_checked(lv_btn_get_state);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline bool lv_checkbox_is_inactive(const lv_obj_t * cb){    return lv_btn_get_state(cb) == LV_BTN_STATE_DISABLED ? true : false;
// ***********************************************

static int bind_lv_checkbox_is_inactive(lua_State *L)
{
  void * lv_btn_get_state = lua_touserdata(L,1);

  bool ret = lv_checkbox_is_inactive(lv_btn_get_state);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline lv_btn_state_t lv_checkbox_get_state(const lv_obj_t * cb){    return lv_btn_get_state(cb);
// ***********************************************

static int bind_lv_checkbox_get_state(lua_State *L)
{
  void * lv_btn_get_state = lua_touserdata(L,1);

  lv_btn_state_t ret = lv_checkbox_get_state(lv_btn_get_state);

  lua_pushinteger(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "checkbox_create", bind_lv_checkbox_create },
  { "checkbox_set_text", bind_lv_checkbox_set_text },
  { "checkbox_set_text_static", bind_lv_checkbox_set_text_static },
  { "checkbox_set_checked", bind_lv_checkbox_set_checked },
  { "checkbox_set_disabled", bind_lv_checkbox_set_disabled },
  { "checkbox_set_state", bind_lv_checkbox_set_state },
  { "checkbox_get_text", bind_lv_checkbox_get_text },
  { "checkbox_is_checked", bind_lv_checkbox_is_checked },
  { "checkbox_is_inactive", bind_lv_checkbox_is_inactive },
  { "checkbox_get_state", bind_lv_checkbox_get_state },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_checkbox__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
