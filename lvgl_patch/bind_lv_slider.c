
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
#include "lv_slider.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_slider_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_slider_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_slider_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * static inline void lv_slider_set_value(lv_obj_t * slider, int16_t value, lv_anim_enable_t anim){    lv_bar_set_value(slider, value, anim);
// ***********************************************

static int bind_lv_slider_set_value(lua_State *L)
{
  void * slider = lua_touserdata(L,1);
  int value = lua_tointeger(L,2);
  int lv_bar_set_value = lua_tointeger(L,3);

  lv_slider_set_value(slider, value, lv_bar_set_value);

  return 0;
}


// ***********************************************
// * static inline void lv_slider_set_left_value(lv_obj_t * slider, int16_t left_value, lv_anim_enable_t anim){    lv_bar_set_start_value(slider, left_value, anim);
// ***********************************************

static int bind_lv_slider_set_left_value(lua_State *L)
{
  void * slider = lua_touserdata(L,1);
  int left_value = lua_tointeger(L,2);
  int lv_bar_set_start_value = lua_tointeger(L,3);

  lv_slider_set_left_value(slider, left_value, lv_bar_set_start_value);

  return 0;
}


// ***********************************************
// * static inline void lv_slider_set_range(lv_obj_t * slider, int16_t min, int16_t max){    lv_bar_set_range(slider, min, max);
// ***********************************************

static int bind_lv_slider_set_range(lua_State *L)
{
  void * slider = lua_touserdata(L,1);
  int min = lua_tointeger(L,2);
  int lv_bar_set_range = lua_tointeger(L,3);

  lv_slider_set_range(slider, min, lv_bar_set_range);

  return 0;
}


// ***********************************************
// * static inline void lv_slider_set_anim_time(lv_obj_t * slider, uint16_t anim_time){    lv_bar_set_anim_time(slider, anim_time);
// ***********************************************

static int bind_lv_slider_set_anim_time(lua_State *L)
{
  void * slider = lua_touserdata(L,1);
  int lv_bar_set_anim_time = lua_tointeger(L,2);

  lv_slider_set_anim_time(slider, lv_bar_set_anim_time);

  return 0;
}


// ***********************************************
// * static inline void lv_slider_set_type(lv_obj_t * slider, lv_slider_type_t type){    if(type == LV_SLIDER_TYPE_NORMAL)        lv_bar_set_type(slider, LV_BAR_TYPE_NORMAL);
// ***********************************************

static int bind_lv_slider_set_type(lua_State *L)
{
  void * slider = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);

  lv_slider_set_type(slider, type);

  return 0;
}


// ***********************************************
// * int16_t lv_slider_get_value(const lv_obj_t * slider);
// ***********************************************

static int bind_lv_slider_get_value(lua_State *L)
{
  void * slider = lua_touserdata(L,1);

  int16_t ret = lv_slider_get_value(slider);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline int16_t lv_slider_get_left_value(const lv_obj_t * slider){    return lv_bar_get_start_value(slider);
// ***********************************************

static int bind_lv_slider_get_left_value(lua_State *L)
{
  void * lv_bar_get_start_value = lua_touserdata(L,1);

  int16_t ret = lv_slider_get_left_value(lv_bar_get_start_value);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline int16_t lv_slider_get_min_value(const lv_obj_t * slider){    return lv_bar_get_min_value(slider);
// ***********************************************

static int bind_lv_slider_get_min_value(lua_State *L)
{
  void * lv_bar_get_min_value = lua_touserdata(L,1);

  int16_t ret = lv_slider_get_min_value(lv_bar_get_min_value);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline int16_t lv_slider_get_max_value(const lv_obj_t * slider){    return lv_bar_get_max_value(slider);
// ***********************************************

static int bind_lv_slider_get_max_value(lua_State *L)
{
  void * lv_bar_get_max_value = lua_touserdata(L,1);

  int16_t ret = lv_slider_get_max_value(lv_bar_get_max_value);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_slider_is_dragged(const lv_obj_t * slider);
// ***********************************************

static int bind_lv_slider_is_dragged(lua_State *L)
{
  void * slider = lua_touserdata(L,1);

  bool ret = lv_slider_is_dragged(slider);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline uint16_t lv_slider_get_anim_time(lv_obj_t * slider){    return lv_bar_get_anim_time(slider);
// ***********************************************

static int bind_lv_slider_get_anim_time(lua_State *L)
{
  void * lv_bar_get_anim_time = lua_touserdata(L,1);

  uint16_t ret = lv_slider_get_anim_time(lv_bar_get_anim_time);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline lv_slider_type_t lv_slider_get_type(lv_obj_t * slider){    lv_bar_type_t type = lv_bar_get_type(slider);
// ***********************************************

static int bind_lv_slider_get_type(lua_State *L)
{
  void * lv_bar_get_type = lua_touserdata(L,1);

  lv_slider_type_t ret = lv_slider_get_type(lv_bar_get_type);

  lua_pushinteger(L, ret);
  return 1;
}

static const luaL_Reg binding_names [] = {
  { "slider_create", bind_lv_slider_create },
  { "slider_set_value", bind_lv_slider_set_value },
  { "slider_set_left_value", bind_lv_slider_set_left_value },
  { "slider_set_range", bind_lv_slider_set_range },
  { "slider_set_anim_time", bind_lv_slider_set_anim_time },
  { "slider_set_type", bind_lv_slider_set_type },
  { "slider_get_value", bind_lv_slider_get_value },
  { "slider_get_left_value", bind_lv_slider_get_left_value },
  { "slider_get_min_value", bind_lv_slider_get_min_value },
  { "slider_get_max_value", bind_lv_slider_get_max_value },
  { "slider_is_dragged", bind_lv_slider_is_dragged },
  { "slider_get_anim_time", bind_lv_slider_get_anim_time },
  { "slider_get_type", bind_lv_slider_get_type },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg * reg);

int bind_lv_slider__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
}


#ifdef __cplusplus
  }
#endif
