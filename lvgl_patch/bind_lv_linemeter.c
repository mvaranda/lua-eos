
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
#include "lv_linemeter.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_linemeter_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_linemeter_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_linemeter_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_linemeter_set_value(lv_obj_t * lmeter, int32_t value);
// ***********************************************

static int bind_lv_linemeter_set_value(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  int value = lua_tointeger(L,2);

  lv_linemeter_set_value(lmeter, value);

  return 0;
}


// ***********************************************
// * void lv_linemeter_set_range(lv_obj_t * lmeter, int32_t min, int32_t max);
// ***********************************************

static int bind_lv_linemeter_set_range(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  int min = lua_tointeger(L,2);
  int max = lua_tointeger(L,3);

  lv_linemeter_set_range(lmeter, min, max);

  return 0;
}


// ***********************************************
// * void lv_linemeter_set_scale(lv_obj_t * lmeter, uint16_t angle, uint16_t line_cnt);
// ***********************************************

static int bind_lv_linemeter_set_scale(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  int angle = lua_tointeger(L,2);
  int line_cnt = lua_tointeger(L,3);

  lv_linemeter_set_scale(lmeter, angle, line_cnt);

  return 0;
}


// ***********************************************
// * void lv_linemeter_set_angle_offset(lv_obj_t * lmeter, uint16_t angle);
// ***********************************************

static int bind_lv_linemeter_set_angle_offset(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  int angle = lua_tointeger(L,2);

  lv_linemeter_set_angle_offset(lmeter, angle);

  return 0;
}


// ***********************************************
// * void lv_linemeter_set_mirror(lv_obj_t * lmeter, bool mirror);
// ***********************************************

static int bind_lv_linemeter_set_mirror(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  int mirror = lua_toboolean(L,2);

  lv_linemeter_set_mirror(lmeter, mirror);

  return 0;
}


// ***********************************************
// * int32_t lv_linemeter_get_value(const lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_value(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  int32_t ret = lv_linemeter_get_value(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int32_t lv_linemeter_get_min_value(const lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_min_value(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  int32_t ret = lv_linemeter_get_min_value(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int32_t lv_linemeter_get_max_value(const lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_max_value(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  int32_t ret = lv_linemeter_get_max_value(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_linemeter_get_line_count(const lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_line_count(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  uint16_t ret = lv_linemeter_get_line_count(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_linemeter_get_scale_angle(const lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_scale_angle(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  uint16_t ret = lv_linemeter_get_scale_angle(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_linemeter_get_angle_offset(lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_angle_offset(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  uint16_t ret = lv_linemeter_get_angle_offset(lmeter);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_linemeter_draw_scale(lv_obj_t * lmeter, const lv_area_t * clip_area, uint8_t part);
// ***********************************************

static int bind_lv_linemeter_draw_scale(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);
  void * clip_area = lua_touserdata(L,2);
  int part = lua_tointeger(L,3);

  lv_linemeter_draw_scale(lmeter, clip_area, part);

  return 0;
}


// ***********************************************
// * bool lv_linemeter_get_mirror(lv_obj_t * lmeter);
// ***********************************************

static int bind_lv_linemeter_get_mirror(lua_State *L)
{
  void * lmeter = lua_touserdata(L,1);

  bool ret = lv_linemeter_get_mirror(lmeter);

  lua_pushboolean(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "linemeter_create", bind_lv_linemeter_create },
  { "linemeter_set_value", bind_lv_linemeter_set_value },
  { "linemeter_set_range", bind_lv_linemeter_set_range },
  { "linemeter_set_scale", bind_lv_linemeter_set_scale },
  { "linemeter_set_angle_offset", bind_lv_linemeter_set_angle_offset },
  { "linemeter_set_mirror", bind_lv_linemeter_set_mirror },
  { "linemeter_get_value", bind_lv_linemeter_get_value },
  { "linemeter_get_min_value", bind_lv_linemeter_get_min_value },
  { "linemeter_get_max_value", bind_lv_linemeter_get_max_value },
  { "linemeter_get_line_count", bind_lv_linemeter_get_line_count },
  { "linemeter_get_scale_angle", bind_lv_linemeter_get_scale_angle },
  { "linemeter_get_angle_offset", bind_lv_linemeter_get_angle_offset },
  { "linemeter_draw_scale", bind_lv_linemeter_draw_scale },
  { "linemeter_get_mirror", bind_lv_linemeter_get_mirror },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg * reg);

int bind_lv_linemeter__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
}


#ifdef __cplusplus
  }
#endif
