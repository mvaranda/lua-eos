
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
#include "lv_bar.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_bar_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_bar_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_bar_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_bar_set_value(lv_obj_t * bar, int16_t value, lv_anim_enable_t anim);
// ***********************************************

static int bind_lv_bar_set_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);
  int value = lua_tointeger(L,2);
  int anim = lua_tointeger(L,3);

  lv_bar_set_value(bar, value, anim);

  return 0;
}


// ***********************************************
// * void lv_bar_set_start_value(lv_obj_t * bar, int16_t start_value, lv_anim_enable_t anim);
// ***********************************************

static int bind_lv_bar_set_start_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);
  int start_value = lua_tointeger(L,2);
  int anim = lua_tointeger(L,3);

  lv_bar_set_start_value(bar, start_value, anim);

  return 0;
}


// ***********************************************
// * void lv_bar_set_range(lv_obj_t * bar, int16_t min, int16_t max);
// ***********************************************

static int bind_lv_bar_set_range(lua_State *L)
{
  void * bar = lua_touserdata(L,1);
  int min = lua_tointeger(L,2);
  int max = lua_tointeger(L,3);

  lv_bar_set_range(bar, min, max);

  return 0;
}


// ***********************************************
// * void lv_bar_set_type(lv_obj_t * bar, lv_bar_type_t type);
// ***********************************************

static int bind_lv_bar_set_type(lua_State *L)
{
  void * bar = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);

  lv_bar_set_type(bar, type);

  return 0;
}


// ***********************************************
// * void lv_bar_set_anim_time(lv_obj_t * bar, uint16_t anim_time);
// ***********************************************

static int bind_lv_bar_set_anim_time(lua_State *L)
{
  void * bar = lua_touserdata(L,1);
  int anim_time = lua_tointeger(L,2);

  lv_bar_set_anim_time(bar, anim_time);

  return 0;
}


// ***********************************************
// * int16_t lv_bar_get_value(const lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  int16_t ret = lv_bar_get_value(bar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_bar_get_start_value(const lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_start_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  int16_t ret = lv_bar_get_start_value(bar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_bar_get_min_value(const lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_min_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  int16_t ret = lv_bar_get_min_value(bar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_bar_get_max_value(const lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_max_value(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  int16_t ret = lv_bar_get_max_value(bar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_bar_type_t lv_bar_get_type(lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_type(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  lv_bar_type_t ret = lv_bar_get_type(bar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_bar_get_anim_time(const lv_obj_t * bar);
// ***********************************************

static int bind_lv_bar_get_anim_time(lua_State *L)
{
  void * bar = lua_touserdata(L,1);

  uint16_t ret = lv_bar_get_anim_time(bar);

  lua_pushinteger(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "bar_create", bind_lv_bar_create },
  { "bar_set_value", bind_lv_bar_set_value },
  { "bar_set_start_value", bind_lv_bar_set_start_value },
  { "bar_set_range", bind_lv_bar_set_range },
  { "bar_set_type", bind_lv_bar_set_type },
  { "bar_set_anim_time", bind_lv_bar_set_anim_time },
  { "bar_get_value", bind_lv_bar_get_value },
  { "bar_get_start_value", bind_lv_bar_get_start_value },
  { "bar_get_min_value", bind_lv_bar_get_min_value },
  { "bar_get_max_value", bind_lv_bar_get_max_value },
  { "bar_get_type", bind_lv_bar_get_type },
  { "bar_get_anim_time", bind_lv_bar_get_anim_time },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_bar__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
