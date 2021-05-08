
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
#include "lv_obj.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * void lv_init(void);
// ***********************************************

static int bind_lv_init(lua_State *L)
{

  UNUSED(L);

  lv_init();

  return 0;
}


// ***********************************************
// * void lv_deinit(void);
// ***********************************************

static int bind_lv_deinit(lua_State *L)
{

  UNUSED(L);

  lv_deinit();

  return 0;
}


// ***********************************************
// * lv_obj_t * lv_obj_create(lv_obj_t * parent, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_obj_create(lua_State *L)
{
  void * parent = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_obj_create(parent, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_res_t lv_obj_del(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_del(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_res_t ret = lv_obj_del(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_del_anim_ready_cb(lv_anim_t * a);
// ***********************************************

static int bind_lv_obj_del_anim_ready_cb(lua_State *L)
{
  void * a = lua_touserdata(L,1);

  lv_obj_del_anim_ready_cb(a);

  return 0;
}


// ***********************************************
// * void lv_obj_del_async(struct _lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_del_async(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_del_async(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_clean(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_clean(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_clean(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_invalidate_area(const lv_obj_t * obj, const lv_area_t * area);
// ***********************************************

static int bind_lv_obj_invalidate_area(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * area = lua_touserdata(L,2);

  lv_obj_invalidate_area(obj, area);

  return 0;
}


// ***********************************************
// * void lv_obj_invalidate(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_invalidate(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_invalidate(obj);

  return 0;
}


// ***********************************************
// * bool lv_obj_area_is_visible(const lv_obj_t * obj, lv_area_t * area);
// ***********************************************

static int bind_lv_obj_area_is_visible(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * area = lua_touserdata(L,2);

  bool ret = lv_obj_area_is_visible(obj, area);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_is_visible(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_is_visible(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_is_visible(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_set_parent(lv_obj_t * obj, lv_obj_t * parent);
// ***********************************************

static int bind_lv_obj_set_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * parent = lua_touserdata(L,2);

  lv_obj_set_parent(obj, parent);

  return 0;
}


// ***********************************************
// * void lv_obj_move_foreground(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_move_foreground(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_move_foreground(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_move_background(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_move_background(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_move_background(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_set_pos(lv_obj_t * obj, lv_coord_t x, lv_coord_t y);
// ***********************************************

static int bind_lv_obj_set_pos(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int x = lua_tointeger(L,2);
  int y = lua_tointeger(L,3);

  lv_obj_set_pos(obj, x, y);

  return 0;
}


// ***********************************************
// * void lv_obj_set_x(lv_obj_t * obj, lv_coord_t x);
// ***********************************************

static int bind_lv_obj_set_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int x = lua_tointeger(L,2);

  lv_obj_set_x(obj, x);

  return 0;
}


// ***********************************************
// * void lv_obj_set_y(lv_obj_t * obj, lv_coord_t y);
// ***********************************************

static int bind_lv_obj_set_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int y = lua_tointeger(L,2);

  lv_obj_set_y(obj, y);

  return 0;
}


// ***********************************************
// * void lv_obj_set_size(lv_obj_t * obj, lv_coord_t w, lv_coord_t h);
// ***********************************************

static int bind_lv_obj_set_size(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int w = lua_tointeger(L,2);
  int h = lua_tointeger(L,3);

  lv_obj_set_size(obj, w, h);

  return 0;
}


// ***********************************************
// * void lv_obj_set_width(lv_obj_t * obj, lv_coord_t w);
// ***********************************************

static int bind_lv_obj_set_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int w = lua_tointeger(L,2);

  lv_obj_set_width(obj, w);

  return 0;
}


// ***********************************************
// * void lv_obj_set_height(lv_obj_t * obj, lv_coord_t h);
// ***********************************************

static int bind_lv_obj_set_height(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int h = lua_tointeger(L,2);

  lv_obj_set_height(obj, h);

  return 0;
}


// ***********************************************
// * void lv_obj_set_width_fit(lv_obj_t * obj, lv_coord_t w);
// ***********************************************

static int bind_lv_obj_set_width_fit(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int w = lua_tointeger(L,2);

  lv_obj_set_width_fit(obj, w);

  return 0;
}


// ***********************************************
// * void lv_obj_set_height_fit(lv_obj_t * obj, lv_coord_t h);
// ***********************************************

static int bind_lv_obj_set_height_fit(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int h = lua_tointeger(L,2);

  lv_obj_set_height_fit(obj, h);

  return 0;
}


// ***********************************************
// * void lv_obj_set_width_margin(lv_obj_t * obj, lv_coord_t w);
// ***********************************************

static int bind_lv_obj_set_width_margin(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int w = lua_tointeger(L,2);

  lv_obj_set_width_margin(obj, w);

  return 0;
}


// ***********************************************
// * void lv_obj_set_height_margin(lv_obj_t * obj, lv_coord_t h);
// ***********************************************

static int bind_lv_obj_set_height_margin(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int h = lua_tointeger(L,2);

  lv_obj_set_height_margin(obj, h);

  return 0;
}


// ***********************************************
// * void lv_obj_align(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
// ***********************************************

static int bind_lv_obj_align(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int x_ofs = lua_tointeger(L,4);
  int y_ofs = lua_tointeger(L,5);

  lv_obj_align(obj, base, align, x_ofs, y_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_align_x(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs);
// ***********************************************

static int bind_lv_obj_align_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int x_ofs = lua_tointeger(L,4);

  lv_obj_align_x(obj, base, align, x_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_align_y(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t y_ofs);
// ***********************************************

static int bind_lv_obj_align_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int y_ofs = lua_tointeger(L,4);

  lv_obj_align_y(obj, base, align, y_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_align_mid(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
// ***********************************************

static int bind_lv_obj_align_mid(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int x_ofs = lua_tointeger(L,4);
  int y_ofs = lua_tointeger(L,5);

  lv_obj_align_mid(obj, base, align, x_ofs, y_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_align_mid_x(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs);
// ***********************************************

static int bind_lv_obj_align_mid_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int x_ofs = lua_tointeger(L,4);

  lv_obj_align_mid_x(obj, base, align, x_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_align_mid_y(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t y_ofs);
// ***********************************************

static int bind_lv_obj_align_mid_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * base = lua_touserdata(L,2);
  int align = lua_tointeger(L,3);
  int y_ofs = lua_tointeger(L,4);

  lv_obj_align_mid_y(obj, base, align, y_ofs);

  return 0;
}


// ***********************************************
// * void lv_obj_realign(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_realign(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_realign(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_set_auto_realign(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_auto_realign(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_auto_realign(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_ext_click_area(lv_obj_t * obj, lv_coord_t left, lv_coord_t right, lv_coord_t top, lv_coord_t bottom);
// ***********************************************

static int bind_lv_obj_set_ext_click_area(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int left = lua_tointeger(L,2);
  int right = lua_tointeger(L,3);
  int top = lua_tointeger(L,4);
  int bottom = lua_tointeger(L,5);

  lv_obj_set_ext_click_area(obj, left, right, top, bottom);

  return 0;
}


// ***********************************************
// * void lv_obj_add_style(lv_obj_t * obj, uint8_t part, lv_style_t * style);
// ***********************************************

static int bind_lv_obj_add_style(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  void * style = lua_touserdata(L,3);

  lv_obj_add_style(obj, part, style);

  return 0;
}


// ***********************************************
// * void lv_obj_remove_style(lv_obj_t * obj, uint8_t part, lv_style_t * style);
// ***********************************************

static int bind_lv_obj_remove_style(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  void * style = lua_touserdata(L,3);

  lv_obj_remove_style(obj, part, style);

  return 0;
}


// ***********************************************
// * void lv_obj_clean_style_list(lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_clean_style_list(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_obj_clean_style_list(obj, part);

  return 0;
}


// ***********************************************
// * void lv_obj_reset_style_list(lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_reset_style_list(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_obj_reset_style_list(obj, part);

  return 0;
}


// ***********************************************
// * void lv_obj_refresh_style(lv_obj_t * obj, uint8_t part, lv_style_property_t prop);
// ***********************************************

static int bind_lv_obj_refresh_style(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  int prop = lua_tointeger(L,3);

  lv_obj_refresh_style(obj, part, prop);

  return 0;
}


// ***********************************************
// * void lv_obj_report_style_mod(lv_style_t * style);
// ***********************************************

static int bind_lv_obj_report_style_mod(lua_State *L)
{
  void * style = lua_touserdata(L,1);

  lv_obj_report_style_mod(style);

  return 0;
}


// ***********************************************
// * bool lv_obj_remove_style_local_prop(lv_obj_t * obj, uint8_t part, lv_style_property_t prop);
// ***********************************************

static int bind_lv_obj_remove_style_local_prop(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  int prop = lua_tointeger(L,3);

  bool ret = lv_obj_remove_style_local_prop(obj, part, prop);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_set_hidden(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_hidden(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_hidden(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_adv_hittest(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_adv_hittest(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_adv_hittest(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_click(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_click(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_click(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_top(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_top(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_top(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_drag(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_drag(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_drag(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_drag_dir(lv_obj_t * obj, lv_drag_dir_t drag_dir);
// ***********************************************

static int bind_lv_obj_set_drag_dir(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int drag_dir = lua_tointeger(L,2);

  lv_obj_set_drag_dir(obj, drag_dir);

  return 0;
}


// ***********************************************
// * void lv_obj_set_drag_throw(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_drag_throw(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_drag_throw(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_drag_parent(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_drag_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_drag_parent(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_focus_parent(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_focus_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_focus_parent(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_gesture_parent(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_gesture_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_gesture_parent(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_parent_event(lv_obj_t * obj, bool en);
// ***********************************************

static int bind_lv_obj_set_parent_event(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_obj_set_parent_event(obj, en);

  return 0;
}


// ***********************************************
// * void lv_obj_set_base_dir(lv_obj_t * obj, lv_bidi_dir_t dir);
// ***********************************************

static int bind_lv_obj_set_base_dir(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int dir = lua_tointeger(L,2);

  lv_obj_set_base_dir(obj, dir);

  return 0;
}


// ***********************************************
// * void lv_obj_add_protect(lv_obj_t * obj, uint8_t prot);
// ***********************************************

static int bind_lv_obj_add_protect(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int prot = lua_tointeger(L,2);

  lv_obj_add_protect(obj, prot);

  return 0;
}


// ***********************************************
// * void lv_obj_clear_protect(lv_obj_t * obj, uint8_t prot);
// ***********************************************

static int bind_lv_obj_clear_protect(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int prot = lua_tointeger(L,2);

  lv_obj_clear_protect(obj, prot);

  return 0;
}


// ***********************************************
// * void lv_obj_set_state(lv_obj_t * obj, lv_state_t state);
// ***********************************************

static int bind_lv_obj_set_state(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);

  lv_obj_set_state(obj, state);

  return 0;
}


// ***********************************************
// * void lv_obj_add_state(lv_obj_t * obj, lv_state_t state);
// ***********************************************

static int bind_lv_obj_add_state(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);

  lv_obj_add_state(obj, state);

  return 0;
}


// ***********************************************
// * void lv_obj_clear_state(lv_obj_t * obj, lv_state_t state);
// ***********************************************

static int bind_lv_obj_clear_state(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);

  lv_obj_clear_state(obj, state);

  return 0;
}


// ***********************************************
// * void lv_obj_finish_transitions(lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_finish_transitions(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_obj_finish_transitions(obj, part);

  return 0;
}


// ***********************************************
// * void lv_obj_set_event_cb(lv_obj_t * obj, lv_event_cb_t event_cb);
// ***********************************************

static int bind_lv_obj_set_event_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int event_cb = lua_tointeger(L,2);

  lv_obj_set_event_cb(obj, event_cb);

  return 0;
}


// ***********************************************
// * lv_res_t lv_event_send(lv_obj_t * obj, lv_event_t event, const void * data);
// ***********************************************

static int bind_lv_event_send(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int event = lua_tointeger(L,2);
  void * data = lua_touserdata(L,3);

  lv_res_t ret = lv_event_send(obj, event, data);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_res_t lv_event_send_refresh(lv_obj_t * obj);
// ***********************************************

static int bind_lv_event_send_refresh(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_res_t ret = lv_event_send_refresh(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_event_send_refresh_recursive(lv_obj_t * obj);
// ***********************************************

static int bind_lv_event_send_refresh_recursive(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_event_send_refresh_recursive(obj);

  return 0;
}


// ***********************************************
// * lv_res_t lv_event_send_func(lv_event_cb_t event_xcb, lv_obj_t * obj, lv_event_t event, const void * data);
// ***********************************************

static int bind_lv_event_send_func(lua_State *L)
{
  int event_xcb = lua_tointeger(L,1);
  void * obj = lua_touserdata(L,2);
  int event = lua_tointeger(L,3);
  void * data = lua_touserdata(L,4);

  lv_res_t ret = lv_event_send_func(event_xcb, obj, event, data);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * const void * lv_event_get_data(void);
// ***********************************************

static int bind_lv_event_get_data(lua_State *L)
{

  UNUSED(L);

  lv_event_get_data();

  return 0;
}


// ***********************************************
// * void lv_obj_set_signal_cb(lv_obj_t * obj, lv_signal_cb_t signal_cb);
// ***********************************************

static int bind_lv_obj_set_signal_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int signal_cb = lua_tointeger(L,2);

  lv_obj_set_signal_cb(obj, signal_cb);

  return 0;
}


// ***********************************************
// * lv_res_t lv_signal_send(lv_obj_t * obj, lv_signal_t signal, void * param);
// ***********************************************

static int bind_lv_signal_send(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int signal = lua_tointeger(L,2);
  void * param = lua_touserdata(L,3);

  lv_res_t ret = lv_signal_send(obj, signal, param);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_set_design_cb(lv_obj_t * obj, lv_design_cb_t design_cb);
// ***********************************************

static int bind_lv_obj_set_design_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int design_cb = lua_tointeger(L,2);

  lv_obj_set_design_cb(obj, design_cb);

  return 0;
}


// ***********************************************
// * void * lv_obj_allocate_ext_attr(lv_obj_t * obj, uint16_t ext_size);
// ***********************************************

static int bind_lv_obj_allocate_ext_attr(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int ext_size = lua_tointeger(L,2);

  lv_obj_allocate_ext_attr(obj, ext_size);

  return 0;
}


// ***********************************************
// * void lv_obj_refresh_ext_draw_pad(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_refresh_ext_draw_pad(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_refresh_ext_draw_pad(obj);

  return 0;
}


// ***********************************************
// * lv_obj_t * lv_obj_get_screen(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_screen(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_t * ret = lv_obj_get_screen(obj);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_disp_t * lv_obj_get_disp(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_disp(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_disp_t * ret = lv_obj_get_disp(obj);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_obj_get_parent(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_t * ret = lv_obj_get_parent(obj);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_obj_get_child(const lv_obj_t * obj, const lv_obj_t * child);
// ***********************************************

static int bind_lv_obj_get_child(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * child = lua_touserdata(L,2);

  lv_obj_t * ret = lv_obj_get_child(obj, child);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_obj_get_child_back(const lv_obj_t * obj, const lv_obj_t * child);
// ***********************************************

static int bind_lv_obj_get_child_back(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * child = lua_touserdata(L,2);

  lv_obj_t * ret = lv_obj_get_child_back(obj, child);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * uint16_t lv_obj_count_children(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_count_children(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  uint16_t ret = lv_obj_count_children(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_obj_count_children_recursive(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_count_children_recursive(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  uint16_t ret = lv_obj_count_children_recursive(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_get_coords(const lv_obj_t * obj, lv_area_t * cords_p);
// ***********************************************

static int bind_lv_obj_get_coords(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * cords_p = lua_touserdata(L,2);

  lv_obj_get_coords(obj, cords_p);

  return 0;
}


// ***********************************************
// * void lv_obj_get_inner_coords(const lv_obj_t * obj, lv_area_t * coords_p);
// ***********************************************

static int bind_lv_obj_get_inner_coords(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * coords_p = lua_touserdata(L,2);

  lv_obj_get_inner_coords(obj, coords_p);

  return 0;
}


// ***********************************************
// * lv_coord_t lv_obj_get_x(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_x(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_y(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_y(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_width(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_width(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_height(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_height(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_height(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_width_fit(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_width_fit(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_width_fit(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_height_fit(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_height_fit(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_height_fit(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_height_margin(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_height_margin(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_height_margin(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_width_margin(lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_width_margin(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_width_margin(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_width_grid(lv_obj_t * obj, uint8_t div, uint8_t span);
// ***********************************************

static int bind_lv_obj_get_width_grid(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int div = lua_tointeger(L,2);
  int span = lua_tointeger(L,3);

  lv_coord_t ret = lv_obj_get_width_grid(obj, div, span);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_height_grid(lv_obj_t * obj, uint8_t div, uint8_t span);
// ***********************************************

static int bind_lv_obj_get_height_grid(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int div = lua_tointeger(L,2);
  int span = lua_tointeger(L,3);

  lv_coord_t ret = lv_obj_get_height_grid(obj, div, span);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_auto_realign(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_auto_realign(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_auto_realign(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_ext_click_pad_left(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_click_pad_left(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_ext_click_pad_left(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_ext_click_pad_right(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_click_pad_right(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_ext_click_pad_right(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_ext_click_pad_top(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_click_pad_top(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_ext_click_pad_top(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_ext_click_pad_bottom(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_click_pad_bottom(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_ext_click_pad_bottom(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_coord_t lv_obj_get_ext_draw_pad(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_draw_pad(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_coord_t ret = lv_obj_get_ext_draw_pad(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_style_list_t * lv_obj_get_style_list(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_list(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_list_t * ret = lv_obj_get_style_list(obj, part);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_style_t * lv_obj_get_local_style(lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_local_style(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_t * ret = lv_obj_get_local_style(obj, part);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * bool lv_obj_get_hidden(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_hidden(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_hidden(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_adv_hittest(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_adv_hittest(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_adv_hittest(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_click(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_click(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_click(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_top(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_top(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_top(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_drag(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_drag(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_drag(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_drag_dir_t lv_obj_get_drag_dir(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_drag_dir(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_drag_dir_t ret = lv_obj_get_drag_dir(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_drag_throw(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_drag_throw(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_drag_throw(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_drag_parent(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_drag_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_drag_parent(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_focus_parent(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_focus_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_focus_parent(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_parent_event(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_parent_event(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_parent_event(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_get_gesture_parent(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_gesture_parent(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_get_gesture_parent(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_bidi_dir_t lv_obj_get_base_dir(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_base_dir(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_bidi_dir_t ret = lv_obj_get_base_dir(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint8_t lv_obj_get_protect(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_protect(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  uint8_t ret = lv_obj_get_protect(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_is_protected(const lv_obj_t * obj, uint8_t prot);
// ***********************************************

static int bind_lv_obj_is_protected(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int prot = lua_tointeger(L,2);

  bool ret = lv_obj_is_protected(obj, prot);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_state_t lv_obj_get_state(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_state(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_state_t ret = lv_obj_get_state(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_signal_cb_t lv_obj_get_signal_cb(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_signal_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_signal_cb_t ret = lv_obj_get_signal_cb(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_design_cb_t lv_obj_get_design_cb(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_design_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_design_cb_t ret = lv_obj_get_design_cb(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_event_cb_t lv_obj_get_event_cb(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_event_cb(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_event_cb_t ret = lv_obj_get_event_cb(obj);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_is_point_on_coords(lv_obj_t * obj, const lv_point_t * point);
// ***********************************************

static int bind_lv_obj_is_point_on_coords(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * point = lua_touserdata(L,2);

  bool ret = lv_obj_is_point_on_coords(obj, point);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_obj_hittest(lv_obj_t * obj, lv_point_t * point);
// ***********************************************

static int bind_lv_obj_hittest(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * point = lua_touserdata(L,2);

  bool ret = lv_obj_hittest(obj, point);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void * lv_obj_get_ext_attr(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_ext_attr(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_get_ext_attr(obj);

  return 0;
}


// ***********************************************
// * void lv_obj_get_type(const lv_obj_t * obj, lv_obj_type_t * buf);
// ***********************************************

static int bind_lv_obj_get_type(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  void * buf = lua_touserdata(L,2);

  lv_obj_get_type(obj, buf);

  return 0;
}


//// ***********************************************
//// * lv_obj_user_data_t lv_obj_get_user_data(const lv_obj_t * obj);
//// ***********************************************

//static int bind_lv_obj_get_user_data(lua_State *L)
//{
//  void * obj = lua_touserdata(L,1);

//  void * ret = lv_obj_get_user_data(obj);

//  lua_pushinteger(L, ret);
//  return 1;
//}


//// ***********************************************
//// * lv_obj_user_data_t * lv_obj_get_user_data_ptr(const lv_obj_t * obj);
//// ***********************************************

//static int bind_lv_obj_get_user_data_ptr(lua_State *L)
//{
//  void * obj = lua_touserdata(L,1);

//  void * ret = lv_obj_get_user_data_ptr(obj);

//  if (! ret) {
//    lua_pushnil(L);
//  }
//  else {
//    lua_pushlightuserdata(L, ret);
//  }
//  return 1;
//}


//// ***********************************************
//// * void lv_obj_set_user_data(lv_obj_t * obj, lv_obj_user_data_t data);
//// ***********************************************

//static int bind_lv_obj_set_user_data(lua_State *L)
//{
//  void * obj = lua_touserdata(L,1);
//  int data = lua_tointeger(L,2);

//  lv_obj_set_user_data(obj, data);

//  return 0;
//}


// ***********************************************
// * void * lv_obj_get_group(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_group(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_get_group(obj);

  return 0;
}


// ***********************************************
// * bool lv_obj_is_focused(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_is_focused(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_obj_is_focused(obj);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_obj_get_focused_obj(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_obj_get_focused_obj(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  lv_obj_t * ret = lv_obj_get_focused_obj(obj);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_res_t lv_obj_handle_get_type_signal(lv_obj_type_t * buf, const char * name);
// ***********************************************

static int bind_lv_obj_handle_get_type_signal(lua_State *L)
{
  void * buf = lua_touserdata(L,1);
  const char * name = lua_tostring(L,2);

  lv_res_t ret = lv_obj_handle_get_type_signal(buf, name);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_init_draw_rect_dsc(lv_obj_t * obj, uint8_t type, lv_draw_rect_dsc_t * draw_dsc);
// ***********************************************

static int bind_lv_obj_init_draw_rect_dsc(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);
  void * draw_dsc = lua_touserdata(L,3);

  lv_obj_init_draw_rect_dsc(obj, type, draw_dsc);

  return 0;
}


// ***********************************************
// * void lv_obj_init_draw_label_dsc(lv_obj_t * obj, uint8_t type, lv_draw_label_dsc_t * draw_dsc);
// ***********************************************

static int bind_lv_obj_init_draw_label_dsc(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);
  void * draw_dsc = lua_touserdata(L,3);

  lv_obj_init_draw_label_dsc(obj, type, draw_dsc);

  return 0;
}


// ***********************************************
// * void lv_obj_init_draw_img_dsc(lv_obj_t * obj, uint8_t part, lv_draw_img_dsc_t * draw_dsc);
// ***********************************************

static int bind_lv_obj_init_draw_img_dsc(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  void * draw_dsc = lua_touserdata(L,3);

  lv_obj_init_draw_img_dsc(obj, part, draw_dsc);

  return 0;
}


// ***********************************************
// * void lv_obj_init_draw_line_dsc(lv_obj_t * obj, uint8_t part, lv_draw_line_dsc_t * draw_dsc);
// ***********************************************

static int bind_lv_obj_init_draw_line_dsc(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);
  void * draw_dsc = lua_touserdata(L,3);

  lv_obj_init_draw_line_dsc(obj, part, draw_dsc);

  return 0;
}


// ***********************************************
// * lv_coord_t lv_obj_get_draw_rect_ext_pad_size(lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_draw_rect_ext_pad_size(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_coord_t ret = lv_obj_get_draw_rect_ext_pad_size(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_obj_fade_in(lv_obj_t * obj, uint32_t time, uint32_t delay);
// ***********************************************

static int bind_lv_obj_fade_in(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int time = lua_tointeger(L,2);
  int delay = lua_tointeger(L,3);

  lv_obj_fade_in(obj, time, delay);

  return 0;
}


// ***********************************************
// * void lv_obj_fade_out(lv_obj_t * obj, uint32_t time, uint32_t delay);
// ***********************************************

static int bind_lv_obj_fade_out(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int time = lua_tointeger(L,2);
  int delay = lua_tointeger(L,3);

  lv_obj_fade_out(obj, time, delay);

  return 0;
}


// ***********************************************
// * bool lv_debug_check_obj_type(const lv_obj_t * obj, const char * obj_type);
// ***********************************************

static int bind_lv_debug_check_obj_type(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  const char * obj_type = lua_tostring(L,2);

  bool ret = lv_debug_check_obj_type(obj, obj_type);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_debug_check_obj_valid(const lv_obj_t * obj);
// ***********************************************

static int bind_lv_debug_check_obj_valid(lua_State *L)
{
  void * obj = lua_touserdata(L,1);

  bool ret = lv_debug_check_obj_valid(obj);

  lua_pushboolean(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "init", bind_lv_init },
  { "deinit", bind_lv_deinit },
  { "obj_create", bind_lv_obj_create },
  { "obj_del", bind_lv_obj_del },
  { "obj_del_anim_ready_cb", bind_lv_obj_del_anim_ready_cb },
  { "obj_del_async", bind_lv_obj_del_async },
  { "obj_clean", bind_lv_obj_clean },
  { "obj_invalidate_area", bind_lv_obj_invalidate_area },
  { "obj_invalidate", bind_lv_obj_invalidate },
  { "obj_area_is_visible", bind_lv_obj_area_is_visible },
  { "obj_is_visible", bind_lv_obj_is_visible },
  { "obj_set_parent", bind_lv_obj_set_parent },
  { "obj_move_foreground", bind_lv_obj_move_foreground },
  { "obj_move_background", bind_lv_obj_move_background },
  { "obj_set_pos", bind_lv_obj_set_pos },
  { "obj_set_x", bind_lv_obj_set_x },
  { "obj_set_y", bind_lv_obj_set_y },
  { "obj_set_size", bind_lv_obj_set_size },
  { "obj_set_width", bind_lv_obj_set_width },
  { "obj_set_height", bind_lv_obj_set_height },
  { "obj_set_width_fit", bind_lv_obj_set_width_fit },
  { "obj_set_height_fit", bind_lv_obj_set_height_fit },
  { "obj_set_width_margin", bind_lv_obj_set_width_margin },
  { "obj_set_height_margin", bind_lv_obj_set_height_margin },
  { "obj_align", bind_lv_obj_align },
  { "obj_align_x", bind_lv_obj_align_x },
  { "obj_align_y", bind_lv_obj_align_y },
  { "obj_align_mid", bind_lv_obj_align_mid },
  { "obj_align_mid_x", bind_lv_obj_align_mid_x },
  { "obj_align_mid_y", bind_lv_obj_align_mid_y },
  { "obj_realign", bind_lv_obj_realign },
  { "obj_set_auto_realign", bind_lv_obj_set_auto_realign },
  { "obj_set_ext_click_area", bind_lv_obj_set_ext_click_area },
  { "obj_add_style", bind_lv_obj_add_style },
  { "obj_remove_style", bind_lv_obj_remove_style },
  { "obj_clean_style_list", bind_lv_obj_clean_style_list },
  { "obj_reset_style_list", bind_lv_obj_reset_style_list },
  { "obj_refresh_style", bind_lv_obj_refresh_style },
  { "obj_report_style_mod", bind_lv_obj_report_style_mod },
  { "obj_remove_style_local_prop", bind_lv_obj_remove_style_local_prop },
  { "obj_set_hidden", bind_lv_obj_set_hidden },
  { "obj_set_adv_hittest", bind_lv_obj_set_adv_hittest },
  { "obj_set_click", bind_lv_obj_set_click },
  { "obj_set_top", bind_lv_obj_set_top },
  { "obj_set_drag", bind_lv_obj_set_drag },
  { "obj_set_drag_dir", bind_lv_obj_set_drag_dir },
  { "obj_set_drag_throw", bind_lv_obj_set_drag_throw },
  { "obj_set_drag_parent", bind_lv_obj_set_drag_parent },
  { "obj_set_focus_parent", bind_lv_obj_set_focus_parent },
  { "obj_set_gesture_parent", bind_lv_obj_set_gesture_parent },
  { "obj_set_parent_event", bind_lv_obj_set_parent_event },
  { "obj_set_base_dir", bind_lv_obj_set_base_dir },
  { "obj_add_protect", bind_lv_obj_add_protect },
  { "obj_clear_protect", bind_lv_obj_clear_protect },
  { "obj_set_state", bind_lv_obj_set_state },
  { "obj_add_state", bind_lv_obj_add_state },
  { "obj_clear_state", bind_lv_obj_clear_state },
  { "obj_finish_transitions", bind_lv_obj_finish_transitions },
  { "obj_set_event_cb", bind_lv_obj_set_event_cb },
  { "event_send", bind_lv_event_send },
  { "event_send_refresh", bind_lv_event_send_refresh },
  { "event_send_refresh_recursive", bind_lv_event_send_refresh_recursive },
  { "event_send_func", bind_lv_event_send_func },
  { "event_get_data", bind_lv_event_get_data },
  { "obj_set_signal_cb", bind_lv_obj_set_signal_cb },
  { "signal_send", bind_lv_signal_send },
  { "obj_set_design_cb", bind_lv_obj_set_design_cb },
  { "obj_allocate_ext_attr", bind_lv_obj_allocate_ext_attr },
  { "obj_refresh_ext_draw_pad", bind_lv_obj_refresh_ext_draw_pad },
  { "obj_get_screen", bind_lv_obj_get_screen },
  { "obj_get_disp", bind_lv_obj_get_disp },
  { "obj_get_parent", bind_lv_obj_get_parent },
  { "obj_get_child", bind_lv_obj_get_child },
  { "obj_get_child_back", bind_lv_obj_get_child_back },
  { "obj_count_children", bind_lv_obj_count_children },
  { "obj_count_children_recursive", bind_lv_obj_count_children_recursive },
  { "obj_get_coords", bind_lv_obj_get_coords },
  { "obj_get_inner_coords", bind_lv_obj_get_inner_coords },
  { "obj_get_x", bind_lv_obj_get_x },
  { "obj_get_y", bind_lv_obj_get_y },
  { "obj_get_width", bind_lv_obj_get_width },
  { "obj_get_height", bind_lv_obj_get_height },
  { "obj_get_width_fit", bind_lv_obj_get_width_fit },
  { "obj_get_height_fit", bind_lv_obj_get_height_fit },
  { "obj_get_height_margin", bind_lv_obj_get_height_margin },
  { "obj_get_width_margin", bind_lv_obj_get_width_margin },
  { "obj_get_width_grid", bind_lv_obj_get_width_grid },
  { "obj_get_height_grid", bind_lv_obj_get_height_grid },
  { "obj_get_auto_realign", bind_lv_obj_get_auto_realign },
  { "obj_get_ext_click_pad_left", bind_lv_obj_get_ext_click_pad_left },
  { "obj_get_ext_click_pad_right", bind_lv_obj_get_ext_click_pad_right },
  { "obj_get_ext_click_pad_top", bind_lv_obj_get_ext_click_pad_top },
  { "obj_get_ext_click_pad_bottom", bind_lv_obj_get_ext_click_pad_bottom },
  { "obj_get_ext_draw_pad", bind_lv_obj_get_ext_draw_pad },
  { "obj_get_style_list", bind_lv_obj_get_style_list },
  { "obj_get_local_style", bind_lv_obj_get_local_style },
  { "obj_get_hidden", bind_lv_obj_get_hidden },
  { "obj_get_adv_hittest", bind_lv_obj_get_adv_hittest },
  { "obj_get_click", bind_lv_obj_get_click },
  { "obj_get_top", bind_lv_obj_get_top },
  { "obj_get_drag", bind_lv_obj_get_drag },
  { "obj_get_drag_dir", bind_lv_obj_get_drag_dir },
  { "obj_get_drag_throw", bind_lv_obj_get_drag_throw },
  { "obj_get_drag_parent", bind_lv_obj_get_drag_parent },
  { "obj_get_focus_parent", bind_lv_obj_get_focus_parent },
  { "obj_get_parent_event", bind_lv_obj_get_parent_event },
  { "obj_get_gesture_parent", bind_lv_obj_get_gesture_parent },
  { "obj_get_base_dir", bind_lv_obj_get_base_dir },
  { "obj_get_protect", bind_lv_obj_get_protect },
  { "obj_is_protected", bind_lv_obj_is_protected },
  { "obj_get_state", bind_lv_obj_get_state },
  { "obj_get_signal_cb", bind_lv_obj_get_signal_cb },
  { "obj_get_design_cb", bind_lv_obj_get_design_cb },
  { "obj_get_event_cb", bind_lv_obj_get_event_cb },
  { "obj_is_point_on_coords", bind_lv_obj_is_point_on_coords },
  { "obj_hittest", bind_lv_obj_hittest },
  { "obj_get_ext_attr", bind_lv_obj_get_ext_attr },
  { "obj_get_type", bind_lv_obj_get_type },
//  { "obj_get_user_data", bind_lv_obj_get_user_data },
//  { "obj_get_user_data_ptr", bind_lv_obj_get_user_data_ptr },
//  { "obj_set_user_data", bind_lv_obj_set_user_data },
  { "obj_get_group", bind_lv_obj_get_group },
  { "obj_is_focused", bind_lv_obj_is_focused },
  { "obj_get_focused_obj", bind_lv_obj_get_focused_obj },
  { "obj_handle_get_type_signal", bind_lv_obj_handle_get_type_signal },
  { "obj_init_draw_rect_dsc", bind_lv_obj_init_draw_rect_dsc },
  { "obj_init_draw_label_dsc", bind_lv_obj_init_draw_label_dsc },
  { "obj_init_draw_img_dsc", bind_lv_obj_init_draw_img_dsc },
  { "obj_init_draw_line_dsc", bind_lv_obj_init_draw_line_dsc },
  { "obj_get_draw_rect_ext_pad_size", bind_lv_obj_get_draw_rect_ext_pad_size },
  { "obj_fade_in", bind_lv_obj_fade_in },
  { "obj_fade_out", bind_lv_obj_fade_out },
  { "debug_check_obj_type", bind_lv_debug_check_obj_type },
  { "debug_check_obj_valid", bind_lv_debug_check_obj_valid },
  { "debug_check_obj_valid", bind_lv_debug_check_obj_valid },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg * reg);

int bind_lv_obj__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
}


#ifdef __cplusplus
  }
#endif
