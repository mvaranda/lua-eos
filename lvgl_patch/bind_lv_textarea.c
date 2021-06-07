
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
#include "lv_textarea.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_textarea_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_textarea_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_textarea_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_textarea_add_char(lv_obj_t * ta, uint32_t c);
// ***********************************************

static int bind_lv_textarea_add_char(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int c = lua_tointeger(L,2);

  lv_textarea_add_char(ta, c);

  return 0;
}


// ***********************************************
// * void lv_textarea_add_text(lv_obj_t * ta, const char * txt);
// ***********************************************

static int bind_lv_textarea_add_text(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_textarea_add_text(ta, txt);

  return 0;
}


// ***********************************************
// * void lv_textarea_del_char(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_del_char(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_del_char(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_del_char_forward(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_del_char_forward(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_del_char_forward(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_text(lv_obj_t * ta, const char * txt);
// ***********************************************

static int bind_lv_textarea_set_text(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_textarea_set_text(ta, txt);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_placeholder_text(lv_obj_t * ta, const char * txt);
// ***********************************************

static int bind_lv_textarea_set_placeholder_text(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_textarea_set_placeholder_text(ta, txt);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_cursor_pos(lv_obj_t * ta, int32_t pos);
// ***********************************************

static int bind_lv_textarea_set_cursor_pos(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int pos = lua_tointeger(L,2);

  lv_textarea_set_cursor_pos(ta, pos);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_cursor_hidden(lv_obj_t * ta, bool hide);
// ***********************************************

static int bind_lv_textarea_set_cursor_hidden(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int hide = lua_toboolean(L,2);

  lv_textarea_set_cursor_hidden(ta, hide);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_cursor_click_pos(lv_obj_t * ta, bool en);
// ***********************************************

static int bind_lv_textarea_set_cursor_click_pos(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_textarea_set_cursor_click_pos(ta, en);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_pwd_mode(lv_obj_t * ta, bool en);
// ***********************************************

static int bind_lv_textarea_set_pwd_mode(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_textarea_set_pwd_mode(ta, en);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_one_line(lv_obj_t * ta, bool en);
// ***********************************************

static int bind_lv_textarea_set_one_line(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_textarea_set_one_line(ta, en);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_text_align(lv_obj_t * ta, lv_label_align_t align);
// ***********************************************

static int bind_lv_textarea_set_text_align(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int align = lua_tointeger(L,2);

  lv_textarea_set_text_align(ta, align);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_accepted_chars(lv_obj_t * ta, const char * list);
// ***********************************************

static int bind_lv_textarea_set_accepted_chars(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  const char * list = lua_tostring(L,2);

  lv_textarea_set_accepted_chars(ta, list);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_max_length(lv_obj_t * ta, uint32_t num);
// ***********************************************

static int bind_lv_textarea_set_max_length(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int num = lua_tointeger(L,2);

  lv_textarea_set_max_length(ta, num);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_insert_replace(lv_obj_t * ta, const char * txt);
// ***********************************************

static int bind_lv_textarea_set_insert_replace(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  const char * txt = lua_tostring(L,2);

  lv_textarea_set_insert_replace(ta, txt);

  return 0;
}


// ***********************************************
// * static inline void lv_textarea_set_scrollbar_mode(lv_obj_t * ta, lv_scrollbar_mode_t mode){    lv_page_set_scrollbar_mode(ta, mode);
// ***********************************************

static int bind_lv_textarea_set_scrollbar_mode(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int lv_page_set_scrollbar_mode = lua_tointeger(L,2);

  lv_textarea_set_scrollbar_mode(ta, lv_page_set_scrollbar_mode);

  return 0;
}


// ***********************************************
// * static inline void lv_textarea_set_scroll_propagation(lv_obj_t * ta, bool en){    lv_page_set_scroll_propagation(ta, en);
// ***********************************************

static int bind_lv_textarea_set_scroll_propagation(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int lv_page_set_scroll_propagation = lua_tointeger(L,2);

  lv_textarea_set_scroll_propagation(ta, lv_page_set_scroll_propagation);

  return 0;
}


// ***********************************************
// * static inline void lv_textarea_set_edge_flash(lv_obj_t * ta, bool en){    lv_page_set_edge_flash(ta, en);
// ***********************************************

static int bind_lv_textarea_set_edge_flash(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int lv_page_set_edge_flash = lua_tointeger(L,2);

  lv_textarea_set_edge_flash(ta, lv_page_set_edge_flash);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_text_sel(lv_obj_t * ta, bool en);
// ***********************************************

static int bind_lv_textarea_set_text_sel(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_textarea_set_text_sel(ta, en);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_pwd_show_time(lv_obj_t * ta, uint16_t time);
// ***********************************************

static int bind_lv_textarea_set_pwd_show_time(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int time = lua_tointeger(L,2);

  lv_textarea_set_pwd_show_time(ta, time);

  return 0;
}


// ***********************************************
// * void lv_textarea_set_cursor_blink_time(lv_obj_t * ta, uint16_t time);
// ***********************************************

static int bind_lv_textarea_set_cursor_blink_time(lua_State *L)
{
  void * ta = lua_touserdata(L,1);
  int time = lua_tointeger(L,2);

  lv_textarea_set_cursor_blink_time(ta, time);

  return 0;
}


// ***********************************************
// * const char * lv_textarea_get_text(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_text(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  const char * ret = lv_textarea_get_text(ta);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * const char * lv_textarea_get_placeholder_text(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_placeholder_text(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  const char * ret = lv_textarea_get_placeholder_text(ta);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * lv_obj_t * lv_textarea_get_label(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_label(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_obj_t * ret = lv_textarea_get_label(ta);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * uint32_t lv_textarea_get_cursor_pos(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_cursor_pos(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  uint32_t ret = lv_textarea_get_cursor_pos(ta);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_get_cursor_hidden(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_cursor_hidden(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_get_cursor_hidden(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_get_cursor_click_pos(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_cursor_click_pos(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_get_cursor_click_pos(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_get_pwd_mode(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_pwd_mode(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_get_pwd_mode(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_get_one_line(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_one_line(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_get_one_line(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * const char * lv_textarea_get_accepted_chars(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_accepted_chars(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  const char * ret = lv_textarea_get_accepted_chars(ta);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * uint32_t lv_textarea_get_max_length(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_max_length(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  uint32_t ret = lv_textarea_get_max_length(ta);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline lv_scrollbar_mode_t lv_textarea_get_scrollbar_mode(const lv_obj_t * ta){    return lv_page_get_scrollbar_mode(ta);
// ***********************************************

static int bind_lv_textarea_get_scrollbar_mode(lua_State *L)
{
  void * lv_page_get_scrollbar_mode = lua_touserdata(L,1);

  lv_scrollbar_mode_t ret = lv_textarea_get_scrollbar_mode(lv_page_get_scrollbar_mode);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * static inline bool lv_textarea_get_scroll_propagation(lv_obj_t * ta){    return lv_page_get_scroll_propagation(ta);
// ***********************************************

static int bind_lv_textarea_get_scroll_propagation(lua_State *L)
{
  void * lv_page_get_scroll_propagation = lua_touserdata(L,1);

  bool ret = lv_textarea_get_scroll_propagation(lv_page_get_scroll_propagation);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * static inline bool lv_textarea_get_edge_flash(lv_obj_t * ta){    return lv_page_get_edge_flash(ta);
// ***********************************************

static int bind_lv_textarea_get_edge_flash(lua_State *L)
{
  void * lv_page_get_edge_flash = lua_touserdata(L,1);

  bool ret = lv_textarea_get_edge_flash(lv_page_get_edge_flash);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_text_is_selected(const lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_text_is_selected(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_text_is_selected(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_textarea_get_text_sel_en(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_text_sel_en(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  bool ret = lv_textarea_get_text_sel_en(ta);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_textarea_get_pwd_show_time(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_pwd_show_time(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  uint16_t ret = lv_textarea_get_pwd_show_time(ta);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_textarea_get_cursor_blink_time(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_get_cursor_blink_time(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  uint16_t ret = lv_textarea_get_cursor_blink_time(ta);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * void lv_textarea_clear_selection(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_clear_selection(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_clear_selection(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_cursor_right(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_cursor_right(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_cursor_right(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_cursor_left(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_cursor_left(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_cursor_left(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_cursor_down(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_cursor_down(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_cursor_down(ta);

  return 0;
}


// ***********************************************
// * void lv_textarea_cursor_up(lv_obj_t * ta);
// ***********************************************

static int bind_lv_textarea_cursor_up(lua_State *L)
{
  void * ta = lua_touserdata(L,1);

  lv_textarea_cursor_up(ta);

  return 0;
}



static const luaL_Reg binding_names [] = {
  { "textarea_create", bind_lv_textarea_create },
  { "textarea_add_char", bind_lv_textarea_add_char },
  { "textarea_add_text", bind_lv_textarea_add_text },
  { "textarea_del_char", bind_lv_textarea_del_char },
  { "textarea_del_char_forward", bind_lv_textarea_del_char_forward },
  { "textarea_set_text", bind_lv_textarea_set_text },
  { "textarea_set_placeholder_text", bind_lv_textarea_set_placeholder_text },
  { "textarea_set_cursor_pos", bind_lv_textarea_set_cursor_pos },
  { "textarea_set_cursor_hidden", bind_lv_textarea_set_cursor_hidden },
  { "textarea_set_cursor_click_pos", bind_lv_textarea_set_cursor_click_pos },
  { "textarea_set_pwd_mode", bind_lv_textarea_set_pwd_mode },
  { "textarea_set_one_line", bind_lv_textarea_set_one_line },
  { "textarea_set_text_align", bind_lv_textarea_set_text_align },
  { "textarea_set_accepted_chars", bind_lv_textarea_set_accepted_chars },
  { "textarea_set_max_length", bind_lv_textarea_set_max_length },
  { "textarea_set_insert_replace", bind_lv_textarea_set_insert_replace },
  { "textarea_set_scrollbar_mode", bind_lv_textarea_set_scrollbar_mode },
  { "textarea_set_scroll_propagation", bind_lv_textarea_set_scroll_propagation },
  { "textarea_set_edge_flash", bind_lv_textarea_set_edge_flash },
  { "textarea_set_text_sel", bind_lv_textarea_set_text_sel },
  { "textarea_set_pwd_show_time", bind_lv_textarea_set_pwd_show_time },
  { "textarea_set_cursor_blink_time", bind_lv_textarea_set_cursor_blink_time },
  { "textarea_get_text", bind_lv_textarea_get_text },
  { "textarea_get_placeholder_text", bind_lv_textarea_get_placeholder_text },
  { "textarea_get_label", bind_lv_textarea_get_label },
  { "textarea_get_cursor_pos", bind_lv_textarea_get_cursor_pos },
  { "textarea_get_cursor_hidden", bind_lv_textarea_get_cursor_hidden },
  { "textarea_get_cursor_click_pos", bind_lv_textarea_get_cursor_click_pos },
  { "textarea_get_pwd_mode", bind_lv_textarea_get_pwd_mode },
  { "textarea_get_one_line", bind_lv_textarea_get_one_line },
  { "textarea_get_accepted_chars", bind_lv_textarea_get_accepted_chars },
  { "textarea_get_max_length", bind_lv_textarea_get_max_length },
  { "textarea_get_scrollbar_mode", bind_lv_textarea_get_scrollbar_mode },
  { "textarea_get_scroll_propagation", bind_lv_textarea_get_scroll_propagation },
  { "textarea_get_edge_flash", bind_lv_textarea_get_edge_flash },
  { "textarea_text_is_selected", bind_lv_textarea_text_is_selected },
  { "textarea_get_text_sel_en", bind_lv_textarea_get_text_sel_en },
  { "textarea_get_pwd_show_time", bind_lv_textarea_get_pwd_show_time },
  { "textarea_get_cursor_blink_time", bind_lv_textarea_get_cursor_blink_time },
  { "textarea_clear_selection", bind_lv_textarea_clear_selection },
  { "textarea_cursor_right", bind_lv_textarea_cursor_right },
  { "textarea_cursor_left", bind_lv_textarea_cursor_left },
  { "textarea_cursor_down", bind_lv_textarea_cursor_down },
  { "textarea_cursor_up", bind_lv_textarea_cursor_up },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_textarea__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
