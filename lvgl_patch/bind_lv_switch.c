
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
#include "lv_switch.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_switch_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_switch_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_switch_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_switch_on(lv_obj_t * sw, lv_anim_enable_t anim);
// ***********************************************

static int bind_lv_switch_on(lua_State *L)
{
  void * sw = lua_touserdata(L,1);
  int anim = lua_tointeger(L,2);

  lv_switch_on(sw, anim);

  return 0;
}


// ***********************************************
// * void lv_switch_off(lv_obj_t * sw, lv_anim_enable_t anim);
// ***********************************************

static int bind_lv_switch_off(lua_State *L)
{
  void * sw = lua_touserdata(L,1);
  int anim = lua_tointeger(L,2);

  lv_switch_off(sw, anim);

  return 0;
}


// ***********************************************
// * bool lv_switch_toggle(lv_obj_t * sw, lv_anim_enable_t anim);
// ***********************************************

static int bind_lv_switch_toggle(lua_State *L)
{
  void * sw = lua_touserdata(L,1);
  int anim = lua_tointeger(L,2);

  bool ret = lv_switch_toggle(sw, anim);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline void lv_switch_set_anim_time(lv_obj_t * sw, uint16_t anim_time){    lv_bar_set_anim_time(sw, anim_time);
// ***********************************************

static int bind_lv_switch_set_anim_time(lua_State *L)
{
  void * sw = lua_touserdata(L,1);
  int lv_bar_set_anim_time = lua_tointeger(L,2);

  lv_switch_set_anim_time(sw, lv_bar_set_anim_time);

  return 0;
}


// ***********************************************
// * static inline bool lv_switch_get_state(const lv_obj_t * sw){    return lv_bar_get_value(sw) == 1 ? true : false;
// ***********************************************

static int bind_lv_switch_get_state(lua_State *L)
{
  void * lv_bar_get_value = lua_touserdata(L,1);

  bool ret = lv_switch_get_state(lv_bar_get_value);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline uint16_t lv_switch_get_anim_time(const lv_obj_t * sw){    return lv_bar_get_anim_time(sw);
// ***********************************************

static int bind_lv_switch_get_anim_time(lua_State *L)
{
  void * lv_bar_get_anim_time = lua_touserdata(L,1);

  uint16_t ret = lv_switch_get_anim_time(lv_bar_get_anim_time);

  lua_pushinteger(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "switch_create", bind_lv_switch_create },
  { "switch_on", bind_lv_switch_on },
  { "switch_off", bind_lv_switch_off },
  { "switch_toggle", bind_lv_switch_toggle },
  { "switch_set_anim_time", bind_lv_switch_set_anim_time },
  { "switch_get_state", bind_lv_switch_get_state },
  { "switch_get_anim_time", bind_lv_switch_get_anim_time },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_switch__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
