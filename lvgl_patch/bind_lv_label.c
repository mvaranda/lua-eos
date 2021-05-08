
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
#include "lv_label.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_label_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_label_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_label_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_label_set_text(lv_obj_t * label, const char * text);
// ***********************************************

static int bind_lv_label_set_text(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  const char * text = lua_tostring(L,2);

  lv_label_set_text(label, text);

  return 0;
}


// ***********************************************
// * void lv_label_set_text_static(lv_obj_t * label, const char * text);
// ***********************************************

static int bind_lv_label_set_text_static(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  const char * text = lua_tostring(L,2);

  lv_label_set_text_static(label, text);

  return 0;
}


// ***********************************************
// * void lv_label_set_long_mode(lv_obj_t * label, lv_label_long_mode_t long_mode);
// ***********************************************

static int bind_lv_label_set_long_mode(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int long_mode = lua_tointeger(L,2);

  lv_label_set_long_mode(label, long_mode);

  return 0;
}


// ***********************************************
// * void lv_label_set_align(lv_obj_t * label, lv_label_align_t align);
// ***********************************************

static int bind_lv_label_set_align(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int align = lua_tointeger(L,2);

  lv_label_set_align(label, align);

  return 0;
}


// ***********************************************
// * void lv_label_set_recolor(lv_obj_t * label, bool en);
// ***********************************************

static int bind_lv_label_set_recolor(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_label_set_recolor(label, en);

  return 0;
}


// ***********************************************
// * void lv_label_set_anim_speed(lv_obj_t * label, uint16_t anim_speed);
// ***********************************************

static int bind_lv_label_set_anim_speed(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int anim_speed = lua_tointeger(L,2);

  lv_label_set_anim_speed(label, anim_speed);

  return 0;
}


// ***********************************************
// * void lv_label_set_text_sel_start(lv_obj_t * label, uint32_t index);
// ***********************************************

static int bind_lv_label_set_text_sel_start(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int index = lua_tointeger(L,2);

  lv_label_set_text_sel_start(label, index);

  return 0;
}


// ***********************************************
// * void lv_label_set_text_sel_end(lv_obj_t * label, uint32_t index);
// ***********************************************

static int bind_lv_label_set_text_sel_end(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int index = lua_tointeger(L,2);

  lv_label_set_text_sel_end(label, index);

  return 0;
}


// ***********************************************
// * char * lv_label_get_text(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_text(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  char * ret = lv_label_get_text(label);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * lv_label_long_mode_t lv_label_get_long_mode(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_long_mode(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  lv_label_long_mode_t ret = lv_label_get_long_mode(label);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_label_align_t lv_label_get_align(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_align(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  lv_label_align_t ret = lv_label_get_align(label);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_label_get_recolor(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_recolor(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  bool ret = lv_label_get_recolor(label);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_label_get_anim_speed(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_anim_speed(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  uint16_t ret = lv_label_get_anim_speed(label);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_label_get_letter_pos(const lv_obj_t * label, uint32_t index, lv_point_t * pos);
// ***********************************************

static int bind_lv_label_get_letter_pos(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int index = lua_tointeger(L,2);
  void * pos = lua_touserdata(L,3);

  lv_label_get_letter_pos(label, index, pos);

  return 0;
}


// ***********************************************
// * uint32_t lv_label_get_letter_on(const lv_obj_t * label, lv_point_t * pos);
// ***********************************************

static int bind_lv_label_get_letter_on(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  void * pos = lua_touserdata(L,2);

  uint32_t ret = lv_label_get_letter_on(label, pos);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_label_is_char_under_pos(const lv_obj_t * label, lv_point_t * pos);
// ***********************************************

static int bind_lv_label_is_char_under_pos(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  void * pos = lua_touserdata(L,2);

  bool ret = lv_label_is_char_under_pos(label, pos);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * uint32_t lv_label_get_text_sel_start(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_text_sel_start(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  uint32_t ret = lv_label_get_text_sel_start(label);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint32_t lv_label_get_text_sel_end(const lv_obj_t * label);
// ***********************************************

static int bind_lv_label_get_text_sel_end(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  uint32_t ret = lv_label_get_text_sel_end(label);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * lv_style_list_t * lv_label_get_style(lv_obj_t * label, uint8_t type);
// ***********************************************

static int bind_lv_label_get_style(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int type = lua_tointeger(L,2);

  lv_style_list_t * ret = lv_label_get_style(label, type);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_label_ins_text(lv_obj_t * label, uint32_t pos, const char * txt);
// ***********************************************

static int bind_lv_label_ins_text(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int pos = lua_tointeger(L,2);
  const char * txt = lua_tostring(L,3);

  lv_label_ins_text(label, pos, txt);

  return 0;
}


// ***********************************************
// * void lv_label_cut_text(lv_obj_t * label, uint32_t pos, uint32_t cnt);
// ***********************************************

static int bind_lv_label_cut_text(lua_State *L)
{
  void * label = lua_touserdata(L,1);
  int pos = lua_tointeger(L,2);
  int cnt = lua_tointeger(L,3);

  lv_label_cut_text(label, pos, cnt);

  return 0;
}


// ***********************************************
// * void lv_label_refr_text(lv_obj_t * label);
// ***********************************************

static int bind_lv_label_refr_text(lua_State *L)
{
  void * label = lua_touserdata(L,1);

  lv_label_refr_text(label);

  return 0;
}



int bind_lv_label__init_module(lua_State *L)
{

    lua_pushcfunction(L, bind_lv_label_create);
    lua_setglobal(L, "lv_label_create");

    lua_pushcfunction(L, bind_lv_label_set_text);
    lua_setglobal(L, "lv_label_set_text");

    lua_pushcfunction(L, bind_lv_label_set_text_static);
    lua_setglobal(L, "lv_label_set_text_static");

    lua_pushcfunction(L, bind_lv_label_set_long_mode);
    lua_setglobal(L, "lv_label_set_long_mode");

    lua_pushcfunction(L, bind_lv_label_set_align);
    lua_setglobal(L, "lv_label_set_align");

    lua_pushcfunction(L, bind_lv_label_set_recolor);
    lua_setglobal(L, "lv_label_set_recolor");

    lua_pushcfunction(L, bind_lv_label_set_anim_speed);
    lua_setglobal(L, "lv_label_set_anim_speed");

    lua_pushcfunction(L, bind_lv_label_set_text_sel_start);
    lua_setglobal(L, "lv_label_set_text_sel_start");

    lua_pushcfunction(L, bind_lv_label_set_text_sel_end);
    lua_setglobal(L, "lv_label_set_text_sel_end");

    lua_pushcfunction(L, bind_lv_label_get_text);
    lua_setglobal(L, "lv_label_get_text");

    lua_pushcfunction(L, bind_lv_label_get_long_mode);
    lua_setglobal(L, "lv_label_get_long_mode");

    lua_pushcfunction(L, bind_lv_label_get_align);
    lua_setglobal(L, "lv_label_get_align");

    lua_pushcfunction(L, bind_lv_label_get_recolor);
    lua_setglobal(L, "lv_label_get_recolor");

    lua_pushcfunction(L, bind_lv_label_get_anim_speed);
    lua_setglobal(L, "lv_label_get_anim_speed");

    lua_pushcfunction(L, bind_lv_label_get_letter_pos);
    lua_setglobal(L, "lv_label_get_letter_pos");

    lua_pushcfunction(L, bind_lv_label_get_letter_on);
    lua_setglobal(L, "lv_label_get_letter_on");

    lua_pushcfunction(L, bind_lv_label_is_char_under_pos);
    lua_setglobal(L, "lv_label_is_char_under_pos");

    lua_pushcfunction(L, bind_lv_label_get_text_sel_start);
    lua_setglobal(L, "lv_label_get_text_sel_start");

    lua_pushcfunction(L, bind_lv_label_get_text_sel_end);
    lua_setglobal(L, "lv_label_get_text_sel_end");

    lua_pushcfunction(L, bind_lv_label_get_style);
    lua_setglobal(L, "lv_label_get_style");

    lua_pushcfunction(L, bind_lv_label_ins_text);
    lua_setglobal(L, "lv_label_ins_text");

    lua_pushcfunction(L, bind_lv_label_cut_text);
    lua_setglobal(L, "lv_label_cut_text");

    lua_pushcfunction(L, bind_lv_label_refr_text);
    lua_setglobal(L, "lv_label_refr_text");
};


#ifdef __cplusplus
  }
#endif
