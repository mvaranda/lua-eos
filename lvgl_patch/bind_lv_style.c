
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
#include "mos.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"


//typedef uint32_t value_type;
//typedef uint32_t vt_color16_t;

#include "lv_style.h"
#include "lv_obj_style_dec.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)

// ***********************************************
// * void lv_style_init(lv_style_t * style);
//// ***********************************************

//static int bind_lv_style_init(lua_State *L)
//{
//  void * style = lua_touserdata(L,1);

//  lv_style_init(style);

//  return 0;
//}


// ***********************************************
// * void lv_style_copy(lv_style_t * style_dest, const lv_style_t * style_src);
// ***********************************************

//static int bind_lv_style_copy(lua_State *L)
//{
//  void * style_dest = lua_touserdata(L,1);
//  void * style_src = lua_touserdata(L,2);

//  lv_style_copy(style_dest, style_src);

//  return 0;
//}


static int bind_lv_style_create(lua_State *L)
{
  void * original = lua_touserdata(L,1);

  lv_style_t * style_obj = (lv_style_t *) mos_calloc(sizeof(lv_style_t), 1);

  if ( ! original) {
        lv_style_init(style_obj);
  }
  else {
      lv_style_list_copy(style_obj, (lv_style_t * ) original);
  }

  if (! style_obj) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, style_obj);
  }
  return 1;
}


// ***********************************************
// * void lv_style_list_init(lv_style_list_t * list);
// ***********************************************

static int bind_lv_style_list_init(lua_State *L)
{
  void * list = lua_touserdata(L,1);

  lv_style_list_init(list);

  return 0;
}


// ***********************************************
// * void lv_style_list_copy(lv_style_list_t * list_dest, const lv_style_list_t * list_src);
// ***********************************************

static int bind_lv_style_list_copy(lua_State *L)
{
  void * list_dest = lua_touserdata(L,1);
  void * list_src = lua_touserdata(L,2);

  lv_style_list_copy(list_dest, list_src);

  return 0;
}


//// ***********************************************
//// * static inline lv_style_t * lv_style_list_get_style(lv_style_list_t * list, uint8_t id){    if(list->has_trans && list->skip_trans) id++;
//// ***********************************************

//static int bind_lv_style_list_get_style(lua_State *L)
//{
//  void * list = lua_touserdata(L,1);
//  int if = lua_tointeger(L,2);

//  lv_style_t * ret = lv_style_list_get_style(list, if);

//  if (! ret) {
//    lua_pushnil(L);
//  }
//  else {
//    lua_pushlightuserdata(L, ret);
//  }
//  return 1;
//}



// ***********************************************
// * void lv_style_reset(lv_style_t * style);
// ***********************************************

static int bind_lv_style_reset(lua_State *L)
{
  void * style = lua_touserdata(L,1);

  lv_style_reset(style);

  return 0;
}


// ***********************************************
// * bool lv_style_remove_prop(lv_style_t * style, lv_style_property_t prop);
// ***********************************************

static int bind_lv_style_remove_prop(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int prop = lua_tointeger(L,2);

  bool ret = lv_style_remove_prop(style, prop);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_style_t * lv_style_list_get_local_style(lv_style_list_t * list);
// ***********************************************

static int bind_lv_style_list_get_local_style(lua_State *L)
{
  void * list = lua_touserdata(L,1);

  lv_style_t * ret = lv_style_list_get_local_style(list);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * bool lv_debug_check_style(const lv_style_t * style);
// ***********************************************

static int bind_lv_debug_check_style(lua_State *L)
{
  void * style = lua_touserdata(L,1);

  bool ret = lv_debug_check_style(style);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_debug_check_style_list(const lv_style_list_t * list);
// ***********************************************

static int bind_lv_debug_check_style_list(lua_State *L)
{
  void * list = lua_touserdata(L,1);

  bool ret = lv_debug_check_style_list(list);

  lua_pushboolean(L, ret);
  return 1;
}

//---------------------------------- from stype_expanded ---------------------------------
  
// ***********************************************
// * lv_style_int_t lv_obj_get_style_radius(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_radius(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_radius(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_radius(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_radius(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_radius(style, state, value);

  return 0;
}


// ***********************************************
// * bool lv_obj_get_style_clip_corner(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_clip_corner(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  bool ret = lv_obj_get_style_clip_corner(obj, part);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_clip_corner(lv_style_t * style, lv_state_t state, bool value);
// ***********************************************

static int bind_lv_style_set_clip_corner(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_toboolean(L,3);

  lv_style_set_clip_corner(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_size(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_size(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_size(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_size(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_size(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_size(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transform_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transform_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transform_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transform_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transform_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transform_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transform_height(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transform_height(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transform_height(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transform_height(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transform_height(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transform_height(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transform_angle(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transform_angle(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transform_angle(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transform_angle(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transform_angle(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transform_angle(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transform_zoom(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transform_zoom(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transform_zoom(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transform_zoom(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transform_zoom(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transform_zoom(style, state, value);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_opa_scale(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_opa_scale(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_opa_scale(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_opa_scale(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_opa_scale(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_opa_scale(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_pad_top(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pad_top(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_pad_top(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pad_top(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_pad_top(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pad_top(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_pad_bottom(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pad_bottom(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_pad_bottom(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pad_bottom(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_pad_bottom(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pad_bottom(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_pad_left(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pad_left(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_pad_left(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pad_left(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_pad_left(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pad_left(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_pad_right(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pad_right(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_pad_right(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pad_right(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_pad_right(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pad_right(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_pad_inner(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pad_inner(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_pad_inner(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pad_inner(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_pad_inner(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pad_inner(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_margin_top(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_margin_top(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_margin_top(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_margin_top(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_margin_top(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_margin_top(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_margin_bottom(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_margin_bottom(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_margin_bottom(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_margin_bottom(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_margin_bottom(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_margin_bottom(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_margin_left(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_margin_left(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_margin_left(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_margin_left(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_margin_left(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_margin_left(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_margin_right(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_margin_right(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_margin_right(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_margin_right(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_margin_right(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_margin_right(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_bg_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_bg_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_bg_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_bg_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_bg_main_stop(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_main_stop(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_bg_main_stop(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_main_stop(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_bg_main_stop(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_bg_main_stop(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_bg_grad_stop(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_grad_stop(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_bg_grad_stop(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_grad_stop(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_bg_grad_stop(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_bg_grad_stop(style, state, value);

  return 0;
}


// ***********************************************
// * lv_grad_dir_t lv_obj_get_style_bg_grad_dir(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_grad_dir(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_grad_dir_t ret = lv_obj_get_style_bg_grad_dir(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_grad_dir(lv_style_t * style, lv_state_t state, lv_grad_dir_t value);
// ***********************************************

static int bind_lv_style_set_bg_grad_dir(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_bg_grad_dir(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_bg_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_bg_color(obj, part);

  lua_pushinteger(L, (int) ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_bg_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_bg_color(style, state, v); //(lv_color_t) value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_bg_grad_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_grad_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_bg_grad_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_grad_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_bg_grad_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_bg_grad_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_bg_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_bg_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_bg_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_bg_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_bg_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_bg_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_border_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_border_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_border_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_border_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_border_side_t lv_obj_get_style_border_side(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_side(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_border_side_t ret = lv_obj_get_style_border_side(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_side(lv_style_t * style, lv_state_t state, lv_border_side_t value);
// ***********************************************

static int bind_lv_style_set_border_side(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_border_side(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_border_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_border_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_border_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_border_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * bool lv_obj_get_style_border_post(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_post(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  bool ret = lv_obj_get_style_border_post(obj, part);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_post(lv_style_t * style, lv_state_t state, bool value);
// ***********************************************

static int bind_lv_style_set_border_post(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_toboolean(L,3);

  lv_style_set_border_post(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_border_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_border_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_border_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_color_t v;
  v.full = value;
  lv_style_set_border_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_border_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_border_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_border_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_border_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_border_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_border_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_outline_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_outline_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_outline_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_outline_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_outline_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_outline_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_outline_pad(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_outline_pad(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_outline_pad(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_outline_pad(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_outline_pad(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_outline_pad(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_outline_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_outline_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_outline_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_outline_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_outline_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_outline_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_outline_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_outline_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_outline_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_outline_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_outline_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_outline_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_outline_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_outline_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_outline_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_outline_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_outline_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_outline_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_shadow_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_shadow_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_shadow_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_shadow_ofs_x(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_ofs_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_shadow_ofs_x(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_ofs_x(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_shadow_ofs_x(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_ofs_x(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_shadow_ofs_y(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_ofs_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_shadow_ofs_y(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_ofs_y(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_shadow_ofs_y(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_ofs_y(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_shadow_spread(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_spread(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_shadow_spread(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_spread(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_shadow_spread(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_spread(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_shadow_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_shadow_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_shadow_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_shadow_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_shadow_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_shadow_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_shadow_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_shadow_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_shadow_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_shadow_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_shadow_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_shadow_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_shadow_opa(style, state, value);

  return 0;
}


// ***********************************************
// * bool lv_obj_get_style_pattern_repeat(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_repeat(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  bool ret = lv_obj_get_style_pattern_repeat(obj, part);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pattern_repeat(lv_style_t * style, lv_state_t state, bool value);
// ***********************************************

static int bind_lv_style_set_pattern_repeat(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_toboolean(L,3);

  lv_style_set_pattern_repeat(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_pattern_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_pattern_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pattern_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_pattern_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pattern_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_pattern_recolor(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_recolor(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_pattern_recolor(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_pattern_recolor(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_pattern_recolor(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_pattern_recolor(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_pattern_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_pattern_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pattern_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_pattern_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pattern_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_pattern_recolor_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_recolor_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_pattern_recolor_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_pattern_recolor_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_pattern_recolor_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_pattern_recolor_opa(style, state, value);

  return 0;
}


// ***********************************************
// * const void * lv_obj_get_style_pattern_image(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_pattern_image(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_obj_get_style_pattern_image(obj, part);

  return 0;
}


// ***********************************************
// * void lv_style_set_pattern_image(lv_style_t * style, lv_state_t state, const void * value);
// ***********************************************

static int bind_lv_style_set_pattern_image(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  void * value = lua_touserdata(L,3);

  lv_style_set_pattern_image(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_value_letter_space(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_letter_space(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_value_letter_space(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_letter_space(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_value_letter_space(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_letter_space(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_value_line_space(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_line_space(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_value_line_space(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_line_space(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_value_line_space(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_line_space(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_value_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_value_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_value_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_value_ofs_x(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_ofs_x(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_value_ofs_x(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_ofs_x(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_value_ofs_x(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_ofs_x(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_value_ofs_y(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_ofs_y(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_value_ofs_y(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_ofs_y(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_value_ofs_y(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_ofs_y(style, state, value);

  return 0;
}


// ***********************************************
// * lv_align_t lv_obj_get_style_value_align(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_align(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_align_t ret = lv_obj_get_style_value_align(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_align(lv_style_t * style, lv_state_t state, lv_align_t value);
// ***********************************************

static int bind_lv_style_set_value_align(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_align(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_value_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_value_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_value_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_value_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_value_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_value_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_value_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_value_opa(style, state, value);

  return 0;
}


// ***********************************************
// * const lv_font_t * lv_obj_get_style_value_font(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_font(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  const lv_font_t * ret = lv_obj_get_style_value_font(obj, part);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_style_set_value_font(lv_style_t * style, lv_state_t state, const lv_font_t * value);
// ***********************************************

static int bind_lv_style_set_value_font(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  void * value = lua_touserdata(L,3);

  lv_style_set_value_font(style, state, value);

  return 0;
}


// ***********************************************
// * const char * lv_obj_get_style_value_str(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_value_str(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  const char * ret = lv_obj_get_style_value_str(obj, part);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_value_str(lv_style_t * style, lv_state_t state, const char * value);
// ***********************************************

static int bind_lv_style_set_value_str(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  const char * value = lua_tostring(L,3);

  lv_style_set_value_str(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_text_letter_space(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_letter_space(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_text_letter_space(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_letter_space(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_text_letter_space(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_text_letter_space(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_text_line_space(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_line_space(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_text_line_space(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_line_space(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_text_line_space(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_text_line_space(style, state, value);

  return 0;
}


// ***********************************************
// * lv_text_decor_t lv_obj_get_style_text_decor(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_decor(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_text_decor_t ret = lv_obj_get_style_text_decor(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_decor(lv_style_t * style, lv_state_t state, lv_text_decor_t value);
// ***********************************************

static int bind_lv_style_set_text_decor(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_text_decor(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_text_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_text_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_text_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_text_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_text_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_text_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_text_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_text_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_text_sel_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_sel_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_text_sel_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_sel_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_text_sel_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_text_sel_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_text_sel_bg_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_sel_bg_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_text_sel_bg_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_sel_bg_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_text_sel_bg_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_text_sel_bg_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_text_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_text_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_text_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_text_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_text_opa(style, state, value);

  return 0;
}


// ***********************************************
// * const lv_font_t * lv_obj_get_style_text_font(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_text_font(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  const lv_font_t * ret = lv_obj_get_style_text_font(obj, part);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_style_set_text_font(lv_style_t * style, lv_state_t state, const lv_font_t * value);
// ***********************************************

static int bind_lv_style_set_text_font(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  void * value = lua_touserdata(L,3);

  lv_style_set_text_font(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_line_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_line_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_line_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_line_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_line_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_line_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_line_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_line_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_line_dash_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_dash_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_line_dash_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_dash_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_line_dash_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_line_dash_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_line_dash_gap(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_dash_gap(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_line_dash_gap(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_dash_gap(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_line_dash_gap(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_line_dash_gap(style, state, value);

  return 0;
}


// ***********************************************
// * bool lv_obj_get_style_line_rounded(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_rounded(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  bool ret = lv_obj_get_style_line_rounded(obj, part);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_rounded(lv_style_t * style, lv_state_t state, bool value);
// ***********************************************

static int bind_lv_style_set_line_rounded(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_toboolean(L,3);

  lv_style_set_line_rounded(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_line_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_line_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_line_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_line_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_line_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_line_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_line_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_line_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_line_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_line_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_blend_mode_t lv_obj_get_style_image_blend_mode(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_image_blend_mode(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_blend_mode_t ret = lv_obj_get_style_image_blend_mode(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_image_blend_mode(lv_style_t * style, lv_state_t state, lv_blend_mode_t value);
// ***********************************************

static int bind_lv_style_set_image_blend_mode(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_image_blend_mode(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_image_recolor(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_image_recolor(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_image_recolor(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_image_recolor(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_image_recolor(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_image_recolor(style, state, v);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_image_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_image_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_image_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_image_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_image_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_image_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_opa_t lv_obj_get_style_image_recolor_opa(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_image_recolor_opa(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_opa_t ret = lv_obj_get_style_image_recolor_opa(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_image_recolor_opa(lv_style_t * style, lv_state_t state, lv_opa_t value);
// ***********************************************

static int bind_lv_style_set_image_recolor_opa(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_image_recolor_opa(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_time(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_time(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_time(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_time(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_time(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_time(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_delay(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_delay(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_delay(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_delay(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_delay(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_delay(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_1(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_1(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_1(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_1(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_1(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_1(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_2(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_2(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_2(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_2(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_2(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_2(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_3(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_3(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_3(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_3(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_3(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_3(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_4(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_4(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_4(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_4(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_4(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_4(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_5(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_5(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_5(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_5(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_5(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_5(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_transition_prop_6(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_prop_6(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_transition_prop_6(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_prop_6(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_transition_prop_6(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_transition_prop_6(style, state, value);

  return 0;
}


// ***********************************************
// * const lv_anim_path_t * lv_obj_get_style_transition_path(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_transition_path(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  const lv_anim_path_t * ret = lv_obj_get_style_transition_path(obj, part);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_style_set_transition_path(lv_style_t * style, lv_state_t state, const lv_anim_path_t * value);
// ***********************************************

static int bind_lv_style_set_transition_path(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  void * value = lua_touserdata(L,3);

  lv_style_set_transition_path(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_scale_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_scale_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_scale_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_scale_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_scale_border_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_border_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_scale_border_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_border_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_scale_border_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_scale_border_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_scale_end_border_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_end_border_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_scale_end_border_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_end_border_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_scale_end_border_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_scale_end_border_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_style_int_t lv_obj_get_style_scale_end_line_width(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_end_line_width(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_style_int_t ret = lv_obj_get_style_scale_end_line_width(obj, part);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_end_line_width(lv_style_t * style, lv_state_t state, lv_style_int_t value);
// ***********************************************

static int bind_lv_style_set_scale_end_line_width(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);

  lv_style_set_scale_end_line_width(style, state, value);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_scale_grad_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_grad_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_scale_grad_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_grad_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_scale_grad_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_scale_grad_color(style, state, v);

  return 0;
}


// ***********************************************
// * lv_color_t lv_obj_get_style_scale_end_color(const lv_obj_t * obj, uint8_t part);
// ***********************************************

static int bind_lv_obj_get_style_scale_end_color(lua_State *L)
{
  void * obj = lua_touserdata(L,1);
  int part = lua_tointeger(L,2);

  lv_color_t ret = lv_obj_get_style_scale_end_color(obj, part);

  lua_pushinteger(L, ret.full);
  return 1;
}


// ***********************************************
// * void lv_style_set_scale_end_color(lv_style_t * style, lv_state_t state, lv_color_t value);
// ***********************************************

static int bind_lv_style_set_scale_end_color(lua_State *L)
{
  void * style = lua_touserdata(L,1);
  int state = lua_tointeger(L,2);
  int value = lua_tointeger(L,3);
  lv_color_t v;
  v.full = value;
  lv_style_set_scale_end_color(style, state, v);

  return 0;
}




static const luaL_Reg binding_names [] = {
//  { "style_init", bind_lv_style_init },
//  { "style_copy", bind_lv_style_copy },
    { "style_init", bind_lv_style_create },

  { "style_list_init", bind_lv_style_list_init },
  { "style_list_copy", bind_lv_style_list_copy },
//  { "style_list_get_style", bind_lv_style_list_get_style },
  { "style_reset", bind_lv_style_reset },
  { "style_remove_prop", bind_lv_style_remove_prop },
  { "style_list_get_local_style", bind_lv_style_list_get_local_style },
  { "debug_check_style", bind_lv_debug_check_style },
  { "debug_check_style_list", bind_lv_debug_check_style_list },
  
  //----------------- from style expanded --------------------
  { "obj_get_style_radius", bind_lv_obj_get_style_radius },
  { "style_set_radius", bind_lv_style_set_radius },
  { "obj_get_style_clip_corner", bind_lv_obj_get_style_clip_corner },
  { "style_set_clip_corner", bind_lv_style_set_clip_corner },
  { "obj_get_style_size", bind_lv_obj_get_style_size },
  { "style_set_size", bind_lv_style_set_size },
  { "obj_get_style_transform_width", bind_lv_obj_get_style_transform_width },
  { "style_set_transform_width", bind_lv_style_set_transform_width },
  { "obj_get_style_transform_height", bind_lv_obj_get_style_transform_height },
  { "style_set_transform_height", bind_lv_style_set_transform_height },
  { "obj_get_style_transform_angle", bind_lv_obj_get_style_transform_angle },
  { "style_set_transform_angle", bind_lv_style_set_transform_angle },
  { "obj_get_style_transform_zoom", bind_lv_obj_get_style_transform_zoom },
  { "style_set_transform_zoom", bind_lv_style_set_transform_zoom },
  { "obj_get_style_opa_scale", bind_lv_obj_get_style_opa_scale },
  { "style_set_opa_scale", bind_lv_style_set_opa_scale },
  { "obj_get_style_pad_top", bind_lv_obj_get_style_pad_top },
  { "style_set_pad_top", bind_lv_style_set_pad_top },
  { "obj_get_style_pad_bottom", bind_lv_obj_get_style_pad_bottom },
  { "style_set_pad_bottom", bind_lv_style_set_pad_bottom },
  { "obj_get_style_pad_left", bind_lv_obj_get_style_pad_left },
  { "style_set_pad_left", bind_lv_style_set_pad_left },
  { "obj_get_style_pad_right", bind_lv_obj_get_style_pad_right },
  { "style_set_pad_right", bind_lv_style_set_pad_right },
  { "obj_get_style_pad_inner", bind_lv_obj_get_style_pad_inner },
  { "style_set_pad_inner", bind_lv_style_set_pad_inner },
  { "obj_get_style_margin_top", bind_lv_obj_get_style_margin_top },
  { "style_set_margin_top", bind_lv_style_set_margin_top },
  { "obj_get_style_margin_bottom", bind_lv_obj_get_style_margin_bottom },
  { "style_set_margin_bottom", bind_lv_style_set_margin_bottom },
  { "obj_get_style_margin_left", bind_lv_obj_get_style_margin_left },
  { "style_set_margin_left", bind_lv_style_set_margin_left },
  { "obj_get_style_margin_right", bind_lv_obj_get_style_margin_right },
  { "style_set_margin_right", bind_lv_style_set_margin_right },
  { "obj_get_style_bg_blend_mode", bind_lv_obj_get_style_bg_blend_mode },
  { "style_set_bg_blend_mode", bind_lv_style_set_bg_blend_mode },
  { "obj_get_style_bg_main_stop", bind_lv_obj_get_style_bg_main_stop },
  { "style_set_bg_main_stop", bind_lv_style_set_bg_main_stop },
  { "obj_get_style_bg_grad_stop", bind_lv_obj_get_style_bg_grad_stop },
  { "style_set_bg_grad_stop", bind_lv_style_set_bg_grad_stop },
  { "obj_get_style_bg_grad_dir", bind_lv_obj_get_style_bg_grad_dir },
  { "style_set_bg_grad_dir", bind_lv_style_set_bg_grad_dir },
  { "obj_get_style_bg_color", bind_lv_obj_get_style_bg_color },
  { "style_set_bg_color", bind_lv_style_set_bg_color },
  { "obj_get_style_bg_grad_color", bind_lv_obj_get_style_bg_grad_color },
  { "style_set_bg_grad_color", bind_lv_style_set_bg_grad_color },
  { "obj_get_style_bg_opa", bind_lv_obj_get_style_bg_opa },
  { "style_set_bg_opa", bind_lv_style_set_bg_opa },
  { "obj_get_style_border_width", bind_lv_obj_get_style_border_width },
  { "style_set_border_width", bind_lv_style_set_border_width },
  { "obj_get_style_border_side", bind_lv_obj_get_style_border_side },
  { "style_set_border_side", bind_lv_style_set_border_side },
  { "obj_get_style_border_blend_mode", bind_lv_obj_get_style_border_blend_mode },
  { "style_set_border_blend_mode", bind_lv_style_set_border_blend_mode },
  { "obj_get_style_border_post", bind_lv_obj_get_style_border_post },
  { "style_set_border_post", bind_lv_style_set_border_post },
  { "obj_get_style_border_color", bind_lv_obj_get_style_border_color },
  { "style_set_border_color", bind_lv_style_set_border_color },
  { "obj_get_style_border_opa", bind_lv_obj_get_style_border_opa },
  { "style_set_border_opa", bind_lv_style_set_border_opa },
  { "obj_get_style_outline_width", bind_lv_obj_get_style_outline_width },
  { "style_set_outline_width", bind_lv_style_set_outline_width },
  { "obj_get_style_outline_pad", bind_lv_obj_get_style_outline_pad },
  { "style_set_outline_pad", bind_lv_style_set_outline_pad },
  { "obj_get_style_outline_blend_mode", bind_lv_obj_get_style_outline_blend_mode },
  { "style_set_outline_blend_mode", bind_lv_style_set_outline_blend_mode },
  { "obj_get_style_outline_color", bind_lv_obj_get_style_outline_color },
  { "style_set_outline_color", bind_lv_style_set_outline_color },
  { "obj_get_style_outline_opa", bind_lv_obj_get_style_outline_opa },
  { "style_set_outline_opa", bind_lv_style_set_outline_opa },
  { "obj_get_style_shadow_width", bind_lv_obj_get_style_shadow_width },
  { "style_set_shadow_width", bind_lv_style_set_shadow_width },
  { "obj_get_style_shadow_ofs_x", bind_lv_obj_get_style_shadow_ofs_x },
  { "style_set_shadow_ofs_x", bind_lv_style_set_shadow_ofs_x },
  { "obj_get_style_shadow_ofs_y", bind_lv_obj_get_style_shadow_ofs_y },
  { "style_set_shadow_ofs_y", bind_lv_style_set_shadow_ofs_y },
  { "obj_get_style_shadow_spread", bind_lv_obj_get_style_shadow_spread },
  { "style_set_shadow_spread", bind_lv_style_set_shadow_spread },
  { "obj_get_style_shadow_blend_mode", bind_lv_obj_get_style_shadow_blend_mode },
  { "style_set_shadow_blend_mode", bind_lv_style_set_shadow_blend_mode },
  { "obj_get_style_shadow_color", bind_lv_obj_get_style_shadow_color },
  { "style_set_shadow_color", bind_lv_style_set_shadow_color },
  { "obj_get_style_shadow_opa", bind_lv_obj_get_style_shadow_opa },
  { "style_set_shadow_opa", bind_lv_style_set_shadow_opa },
  { "obj_get_style_pattern_repeat", bind_lv_obj_get_style_pattern_repeat },
  { "style_set_pattern_repeat", bind_lv_style_set_pattern_repeat },
  { "obj_get_style_pattern_blend_mode", bind_lv_obj_get_style_pattern_blend_mode },
  { "style_set_pattern_blend_mode", bind_lv_style_set_pattern_blend_mode },
  { "obj_get_style_pattern_recolor", bind_lv_obj_get_style_pattern_recolor },
  { "style_set_pattern_recolor", bind_lv_style_set_pattern_recolor },
  { "obj_get_style_pattern_opa", bind_lv_obj_get_style_pattern_opa },
  { "style_set_pattern_opa", bind_lv_style_set_pattern_opa },
  { "obj_get_style_pattern_recolor_opa", bind_lv_obj_get_style_pattern_recolor_opa },
  { "style_set_pattern_recolor_opa", bind_lv_style_set_pattern_recolor_opa },
  { "obj_get_style_pattern_image", bind_lv_obj_get_style_pattern_image },
  { "style_set_pattern_image", bind_lv_style_set_pattern_image },
  { "obj_get_style_value_letter_space", bind_lv_obj_get_style_value_letter_space },
  { "style_set_value_letter_space", bind_lv_style_set_value_letter_space },
  { "obj_get_style_value_line_space", bind_lv_obj_get_style_value_line_space },
  { "style_set_value_line_space", bind_lv_style_set_value_line_space },
  { "obj_get_style_value_blend_mode", bind_lv_obj_get_style_value_blend_mode },
  { "style_set_value_blend_mode", bind_lv_style_set_value_blend_mode },
  { "obj_get_style_value_ofs_x", bind_lv_obj_get_style_value_ofs_x },
  { "style_set_value_ofs_x", bind_lv_style_set_value_ofs_x },
  { "obj_get_style_value_ofs_y", bind_lv_obj_get_style_value_ofs_y },
  { "style_set_value_ofs_y", bind_lv_style_set_value_ofs_y },
  { "obj_get_style_value_align", bind_lv_obj_get_style_value_align },
  { "style_set_value_align", bind_lv_style_set_value_align },
  { "obj_get_style_value_color", bind_lv_obj_get_style_value_color },
  { "style_set_value_color", bind_lv_style_set_value_color },
  { "obj_get_style_value_opa", bind_lv_obj_get_style_value_opa },
  { "style_set_value_opa", bind_lv_style_set_value_opa },
  { "obj_get_style_value_font", bind_lv_obj_get_style_value_font },
  { "style_set_value_font", bind_lv_style_set_value_font },
  { "obj_get_style_value_str", bind_lv_obj_get_style_value_str },
  { "style_set_value_str", bind_lv_style_set_value_str },
  { "obj_get_style_text_letter_space", bind_lv_obj_get_style_text_letter_space },
  { "style_set_text_letter_space", bind_lv_style_set_text_letter_space },
  { "obj_get_style_text_line_space", bind_lv_obj_get_style_text_line_space },
  { "style_set_text_line_space", bind_lv_style_set_text_line_space },
  { "obj_get_style_text_decor", bind_lv_obj_get_style_text_decor },
  { "style_set_text_decor", bind_lv_style_set_text_decor },
  { "obj_get_style_text_blend_mode", bind_lv_obj_get_style_text_blend_mode },
  { "style_set_text_blend_mode", bind_lv_style_set_text_blend_mode },
  { "obj_get_style_text_color", bind_lv_obj_get_style_text_color },
  { "style_set_text_color", bind_lv_style_set_text_color },
  { "obj_get_style_text_sel_color", bind_lv_obj_get_style_text_sel_color },
  { "style_set_text_sel_color", bind_lv_style_set_text_sel_color },
  { "obj_get_style_text_sel_bg_color", bind_lv_obj_get_style_text_sel_bg_color },
  { "style_set_text_sel_bg_color", bind_lv_style_set_text_sel_bg_color },
  { "obj_get_style_text_opa", bind_lv_obj_get_style_text_opa },
  { "style_set_text_opa", bind_lv_style_set_text_opa },
  { "obj_get_style_text_font", bind_lv_obj_get_style_text_font },
  { "style_set_text_font", bind_lv_style_set_text_font },
  { "obj_get_style_line_width", bind_lv_obj_get_style_line_width },
  { "style_set_line_width", bind_lv_style_set_line_width },
  { "obj_get_style_line_blend_mode", bind_lv_obj_get_style_line_blend_mode },
  { "style_set_line_blend_mode", bind_lv_style_set_line_blend_mode },
  { "obj_get_style_line_dash_width", bind_lv_obj_get_style_line_dash_width },
  { "style_set_line_dash_width", bind_lv_style_set_line_dash_width },
  { "obj_get_style_line_dash_gap", bind_lv_obj_get_style_line_dash_gap },
  { "style_set_line_dash_gap", bind_lv_style_set_line_dash_gap },
  { "obj_get_style_line_rounded", bind_lv_obj_get_style_line_rounded },
  { "style_set_line_rounded", bind_lv_style_set_line_rounded },
  { "obj_get_style_line_color", bind_lv_obj_get_style_line_color },
  { "style_set_line_color", bind_lv_style_set_line_color },
  { "obj_get_style_line_opa", bind_lv_obj_get_style_line_opa },
  { "style_set_line_opa", bind_lv_style_set_line_opa },
  { "obj_get_style_image_blend_mode", bind_lv_obj_get_style_image_blend_mode },
  { "style_set_image_blend_mode", bind_lv_style_set_image_blend_mode },
  { "obj_get_style_image_recolor", bind_lv_obj_get_style_image_recolor },
  { "style_set_image_recolor", bind_lv_style_set_image_recolor },
  { "obj_get_style_image_opa", bind_lv_obj_get_style_image_opa },
  { "style_set_image_opa", bind_lv_style_set_image_opa },
  { "obj_get_style_image_recolor_opa", bind_lv_obj_get_style_image_recolor_opa },
  { "style_set_image_recolor_opa", bind_lv_style_set_image_recolor_opa },
  { "obj_get_style_transition_time", bind_lv_obj_get_style_transition_time },
  { "style_set_transition_time", bind_lv_style_set_transition_time },
  { "obj_get_style_transition_delay", bind_lv_obj_get_style_transition_delay },
  { "style_set_transition_delay", bind_lv_style_set_transition_delay },
  { "obj_get_style_transition_prop_1", bind_lv_obj_get_style_transition_prop_1 },
  { "style_set_transition_prop_1", bind_lv_style_set_transition_prop_1 },
  { "obj_get_style_transition_prop_2", bind_lv_obj_get_style_transition_prop_2 },
  { "style_set_transition_prop_2", bind_lv_style_set_transition_prop_2 },
  { "obj_get_style_transition_prop_3", bind_lv_obj_get_style_transition_prop_3 },
  { "style_set_transition_prop_3", bind_lv_style_set_transition_prop_3 },
  { "obj_get_style_transition_prop_4", bind_lv_obj_get_style_transition_prop_4 },
  { "style_set_transition_prop_4", bind_lv_style_set_transition_prop_4 },
  { "obj_get_style_transition_prop_5", bind_lv_obj_get_style_transition_prop_5 },
  { "style_set_transition_prop_5", bind_lv_style_set_transition_prop_5 },
  { "obj_get_style_transition_prop_6", bind_lv_obj_get_style_transition_prop_6 },
  { "style_set_transition_prop_6", bind_lv_style_set_transition_prop_6 },
  { "obj_get_style_transition_path", bind_lv_obj_get_style_transition_path },
  { "style_set_transition_path", bind_lv_style_set_transition_path },
  { "obj_get_style_scale_width", bind_lv_obj_get_style_scale_width },
  { "style_set_scale_width", bind_lv_style_set_scale_width },
  { "obj_get_style_scale_border_width", bind_lv_obj_get_style_scale_border_width },
  { "style_set_scale_border_width", bind_lv_style_set_scale_border_width },
  { "obj_get_style_scale_end_border_width", bind_lv_obj_get_style_scale_end_border_width },
  { "style_set_scale_end_border_width", bind_lv_style_set_scale_end_border_width },
  { "obj_get_style_scale_end_line_width", bind_lv_obj_get_style_scale_end_line_width },
  { "style_set_scale_end_line_width", bind_lv_style_set_scale_end_line_width },
  { "obj_get_style_scale_grad_color", bind_lv_obj_get_style_scale_grad_color },
  { "style_set_scale_grad_color", bind_lv_style_set_scale_grad_color },
  { "obj_get_style_scale_end_color", bind_lv_obj_get_style_scale_end_color },
  { "style_set_scale_end_color", bind_lv_style_set_scale_end_color },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_style__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
