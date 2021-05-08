
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
#include "lv_disp.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_disp_get_scr_act(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_get_scr_act(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_obj_t * ret = lv_disp_get_scr_act(disp);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_disp_get_scr_prev(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_get_scr_prev(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_obj_t * ret = lv_disp_get_scr_prev(disp);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_disp_load_scr(lv_obj_t * scr);
// ***********************************************

static int bind_lv_disp_load_scr(lua_State *L)
{
  void * scr = lua_touserdata(L,1);

  lv_disp_load_scr(scr);

  return 0;
}


// ***********************************************
// * lv_obj_t * lv_disp_get_layer_top(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_get_layer_top(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_obj_t * ret = lv_disp_get_layer_top(disp);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_disp_get_layer_sys(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_get_layer_sys(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_obj_t * ret = lv_disp_get_layer_sys(disp);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_disp_assign_screen(lv_disp_t * disp, lv_obj_t * scr);
// ***********************************************

static int bind_lv_disp_assign_screen(lua_State *L)
{
  void * disp = lua_touserdata(L,1);
  void * scr = lua_touserdata(L,2);

  lv_disp_assign_screen(disp, scr);

  return 0;
}


// ***********************************************
// * void lv_disp_set_bg_color(lv_disp_t * disp, lv_color_t color);
// ***********************************************

static int bind_lv_disp_set_bg_color(lua_State *L)
{
  void * disp = lua_touserdata(L,1);
  int color = lua_tointeger(L,2);
  lv_color16_t c;
  c.full = color;

  lv_disp_set_bg_color(disp, c);

  return 0;
}


// ***********************************************
// * void lv_disp_set_bg_image(lv_disp_t * disp, const void  * img_src);
// ***********************************************

static int bind_lv_disp_set_bg_image(lua_State *L)
{
  void * disp = lua_touserdata(L,1);
  void * img_src = lua_touserdata(L,2);

  lv_disp_set_bg_image(disp, img_src);

  return 0;
}


// ***********************************************
// * void lv_disp_set_bg_opa(lv_disp_t * disp, lv_opa_t opa);
// ***********************************************

static int bind_lv_disp_set_bg_opa(lua_State *L)
{
  void * disp = lua_touserdata(L,1);
  int opa = lua_tointeger(L,2);

  lv_disp_set_bg_opa(disp, opa);

  return 0;
}


// ***********************************************
// * void lv_scr_load_anim(lv_obj_t * scr, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del);
// ***********************************************

static int bind_lv_scr_load_anim(lua_State *L)
{
  void * scr = lua_touserdata(L,1);
  int anim_type = lua_tointeger(L,2);
  int time = lua_tointeger(L,3);
  int delay = lua_tointeger(L,4);
  int auto_del = lua_toboolean(L,5);

  lv_scr_load_anim(scr, anim_type, time, delay, auto_del);

  return 0;
}


// ***********************************************
// * uint32_t lv_disp_get_inactive_time(const lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_get_inactive_time(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  uint32_t ret = lv_disp_get_inactive_time(disp);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_disp_trig_activity(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_trig_activity(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_disp_trig_activity(disp);

  return 0;
}


// ***********************************************
// * void lv_disp_clean_dcache(lv_disp_t * disp);
// ***********************************************

static int bind_lv_disp_clean_dcache(lua_State *L)
{
  void * disp = lua_touserdata(L,1);

  lv_disp_clean_dcache(disp);

  return 0;
}


// ***********************************************
// * static inline lv_obj_t * lv_scr_act(void){    return lv_disp_get_scr_act(lv_disp_get_default());
// ***********************************************

static int bind_lv_scr_act(lua_State *L)
{

  lv_obj_t * ret = lv_scr_act();

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * static inline lv_obj_t * lv_layer_top(void){    return lv_disp_get_layer_top(lv_disp_get_default());
// ***********************************************

static int bind_lv_layer_top(lua_State *L)
{
  lv_obj_t * ret = lv_layer_top();

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * static inline lv_obj_t * lv_layer_sys(void){    return lv_disp_get_layer_sys(lv_disp_get_default());
// ***********************************************

static int bind_lv_layer_sys(lua_State *L)
{
  lv_obj_t * ret = lv_layer_sys();

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * static inline void lv_scr_load(lv_obj_t * scr){    lv_disp_load_scr(scr);
// ***********************************************

static int bind_lv_scr_load(lua_State *L)
{
  void * lv_disp_load_scr = lua_touserdata(L,1);

  lv_scr_load(lv_disp_load_scr);

  return 0;
}



int bind_lv_disp__init_module(lua_State *L)
{

    lua_pushcfunction(L, bind_lv_disp_get_scr_act);
    lua_setglobal(L, "lv_disp_get_scr_act");

    lua_pushcfunction(L, bind_lv_disp_get_scr_prev);
    lua_setglobal(L, "lv_disp_get_scr_prev");

    lua_pushcfunction(L, bind_lv_disp_load_scr);
    lua_setglobal(L, "lv_disp_load_scr");

    lua_pushcfunction(L, bind_lv_disp_get_layer_top);
    lua_setglobal(L, "lv_disp_get_layer_top");

    lua_pushcfunction(L, bind_lv_disp_get_layer_sys);
    lua_setglobal(L, "lv_disp_get_layer_sys");

    lua_pushcfunction(L, bind_lv_disp_assign_screen);
    lua_setglobal(L, "lv_disp_assign_screen");

    lua_pushcfunction(L, bind_lv_disp_set_bg_color);
    lua_setglobal(L, "lv_disp_set_bg_color");

    lua_pushcfunction(L, bind_lv_disp_set_bg_image);
    lua_setglobal(L, "lv_disp_set_bg_image");

    lua_pushcfunction(L, bind_lv_disp_set_bg_opa);
    lua_setglobal(L, "lv_disp_set_bg_opa");

    lua_pushcfunction(L, bind_lv_scr_load_anim);
    lua_setglobal(L, "lv_scr_load_anim");

    lua_pushcfunction(L, bind_lv_disp_get_inactive_time);
    lua_setglobal(L, "lv_disp_get_inactive_time");

    lua_pushcfunction(L, bind_lv_disp_trig_activity);
    lua_setglobal(L, "lv_disp_trig_activity");

    lua_pushcfunction(L, bind_lv_disp_clean_dcache);
    lua_setglobal(L, "lv_disp_clean_dcache");

    lua_pushcfunction(L, bind_lv_scr_act);
    lua_setglobal(L, "lv_scr_act");

    lua_pushcfunction(L, bind_lv_layer_top);
    lua_setglobal(L, "lv_layer_top");

    lua_pushcfunction(L, bind_lv_layer_sys);
    lua_setglobal(L, "lv_layer_sys");

    lua_pushcfunction(L, bind_lv_scr_load);
    lua_setglobal(L, "lv_scr_load");
};


#ifdef __cplusplus
  }
#endif
