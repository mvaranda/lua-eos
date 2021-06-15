
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
#include "lv_arc.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_arc_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_arc_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_arc_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_arc_set_start_angle(lv_obj_t * arc, uint16_t start);
// ***********************************************

static int bind_lv_arc_set_start_angle(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int start = lua_tointeger(L,2);

  lv_arc_set_start_angle(arc, start);

  return 0;
}


// ***********************************************
// * void lv_arc_set_end_angle(lv_obj_t * arc, uint16_t end);
// ***********************************************

static int bind_lv_arc_set_end_angle(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int end = lua_tointeger(L,2);

  lv_arc_set_end_angle(arc, end);

  return 0;
}


// ***********************************************
// * void lv_arc_set_angles(lv_obj_t * arc, uint16_t start, uint16_t end);
// ***********************************************

static int bind_lv_arc_set_angles(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int start = lua_tointeger(L,2);
  int end = lua_tointeger(L,3);

  lv_arc_set_angles(arc, start, end);

  return 0;
}


// ***********************************************
// * void lv_arc_set_bg_start_angle(lv_obj_t * arc, uint16_t start);
// ***********************************************

static int bind_lv_arc_set_bg_start_angle(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int start = lua_tointeger(L,2);

  lv_arc_set_bg_start_angle(arc, start);

  return 0;
}


// ***********************************************
// * void lv_arc_set_bg_end_angle(lv_obj_t * arc, uint16_t end);
// ***********************************************

static int bind_lv_arc_set_bg_end_angle(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int end = lua_tointeger(L,2);

  lv_arc_set_bg_end_angle(arc, end);

  return 0;
}


// ***********************************************
// * void lv_arc_set_bg_angles(lv_obj_t * arc, uint16_t start, uint16_t end);
// ***********************************************

static int bind_lv_arc_set_bg_angles(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int start = lua_tointeger(L,2);
  int end = lua_tointeger(L,3);

  lv_arc_set_bg_angles(arc, start, end);

  return 0;
}


// ***********************************************
// * void lv_arc_set_rotation(lv_obj_t * arc, uint16_t rotation_angle);
// ***********************************************

static int bind_lv_arc_set_rotation(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int rotation_angle = lua_tointeger(L,2);

  lv_arc_set_rotation(arc, rotation_angle);

  return 0;
}


// ***********************************************
// * void lv_arc_set_type(lv_obj_t * arc, lv_arc_type_t type);
// ***********************************************

static int bind_lv_arc_set_type(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);

  lv_arc_set_type(arc, type);

  return 0;
}


// ***********************************************
// * void lv_arc_set_value(lv_obj_t * arc, int16_t value);
// ***********************************************

static int bind_lv_arc_set_value(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int value = lua_tointeger(L,2);

  lv_arc_set_value(arc, value);

  return 0;
}


// ***********************************************
// * void lv_arc_set_range(lv_obj_t * arc, int16_t min, int16_t max);
// ***********************************************

static int bind_lv_arc_set_range(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int min = lua_tointeger(L,2);
  int max = lua_tointeger(L,3);

  lv_arc_set_range(arc, min, max);

  return 0;
}


// ***********************************************
// * void lv_arc_set_chg_rate(lv_obj_t * arc, uint16_t threshold);
// ***********************************************

static int bind_lv_arc_set_chg_rate(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int threshold = lua_tointeger(L,2);

  lv_arc_set_chg_rate(arc, threshold);

  return 0;
}


// ***********************************************
// * void lv_arc_set_adjustable(lv_obj_t * arc, bool adjustable);
// ***********************************************

static int bind_lv_arc_set_adjustable(lua_State *L)
{
  void * arc = lua_touserdata(L,1);
  int adjustable = lua_toboolean(L,2);

  lv_arc_set_adjustable(arc, adjustable);

  return 0;
}


// ***********************************************
// * uint16_t lv_arc_get_angle_start(lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_angle_start(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  uint16_t ret = lv_arc_get_angle_start(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_arc_get_angle_end(lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_angle_end(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  uint16_t ret = lv_arc_get_angle_end(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_arc_get_bg_angle_start(lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_bg_angle_start(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  uint16_t ret = lv_arc_get_bg_angle_start(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_arc_get_bg_angle_end(lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_bg_angle_end(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  uint16_t ret = lv_arc_get_bg_angle_end(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_arc_type_t lv_arc_get_type(const lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_type(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  lv_arc_type_t ret = lv_arc_get_type(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_arc_get_value(const lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_value(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  int16_t ret = lv_arc_get_value(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_arc_get_min_value(const lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_min_value(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  int16_t ret = lv_arc_get_min_value(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * int16_t lv_arc_get_max_value(const lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_max_value(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  int16_t ret = lv_arc_get_max_value(arc);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_arc_is_dragged(const lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_is_dragged(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  bool ret = lv_arc_is_dragged(arc);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_arc_get_adjustable(lv_obj_t * arc);
// ***********************************************

static int bind_lv_arc_get_adjustable(lua_State *L)
{
  void * arc = lua_touserdata(L,1);

  bool ret = lv_arc_get_adjustable(arc);

  lua_pushboolean(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "arc_create", bind_lv_arc_create },
  { "arc_set_start_angle", bind_lv_arc_set_start_angle },
  { "arc_set_end_angle", bind_lv_arc_set_end_angle },
  { "arc_set_angles", bind_lv_arc_set_angles },
  { "arc_set_bg_start_angle", bind_lv_arc_set_bg_start_angle },
  { "arc_set_bg_end_angle", bind_lv_arc_set_bg_end_angle },
  { "arc_set_bg_angles", bind_lv_arc_set_bg_angles },
  { "arc_set_rotation", bind_lv_arc_set_rotation },
  { "arc_set_type", bind_lv_arc_set_type },
  { "arc_set_value", bind_lv_arc_set_value },
  { "arc_set_range", bind_lv_arc_set_range },
  { "arc_set_chg_rate", bind_lv_arc_set_chg_rate },
  { "arc_set_adjustable", bind_lv_arc_set_adjustable },
  { "arc_get_angle_start", bind_lv_arc_get_angle_start },
  { "arc_get_angle_end", bind_lv_arc_get_angle_end },
  { "arc_get_bg_angle_start", bind_lv_arc_get_bg_angle_start },
  { "arc_get_bg_angle_end", bind_lv_arc_get_bg_angle_end },
  { "arc_get_type", bind_lv_arc_get_type },
  { "arc_get_value", bind_lv_arc_get_value },
  { "arc_get_min_value", bind_lv_arc_get_min_value },
  { "arc_get_max_value", bind_lv_arc_get_max_value },
  { "arc_is_dragged", bind_lv_arc_is_dragged },
  { "arc_get_adjustable", bind_lv_arc_get_adjustable },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_arc__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
