
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
#include "stdlib.h"
#include "lv_btnmatrix.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_btnmatrix_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_btnmatrix_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_btnmatrix_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_btnmatrix_set_map(lv_obj_t * btnm, const char * map[]);
// ***********************************************

static int bind_lv_btnmatrix_set_map(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  lua_len(L, 2);
  lua_Integer mapSize = lua_tointeger(L, -1);
  lua_pop(L, 1);
  const char ** map = (const char **)mos_malloc(mapSize*sizeof(char*));

  for (int i = 0; i < mapSize; i++) {
      const char * str;
      lua_pushinteger(L, i+1);
      lua_gettable(L, 2);
      lua_len(L, -1);
      str = (const char *)malloc(lua_tointeger(L, -1)*sizeof(char));
      strcpy(str, lua_tostring(L, -2));
      map[i] = str;
      lua_pop(L, 2);
  }

  lv_btnmatrix_set_map(btnm, map);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_ctrl_map(lv_obj_t * btnm, const lv_btnmatrix_ctrl_t ctrl_map[]);
// ***********************************************

static int bind_lv_btnmatrix_set_ctrl_map(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  lua_len(L, 2);
  lua_Integer mapSize = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lv_btnmatrix_ctrl_t ctrl_map[mapSize];

  for (int i = 0; i < mapSize; i++) {
      lua_pushinteger(L, i+1);
      lua_gettable(L, 2);
      ctrl_map[i] = lua_tointeger(L, -1);
      lua_pop(L, 1);
  }

  lv_btnmatrix_set_ctrl_map(btnm, ctrl_map);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_focused_btn(lv_obj_t * btnm, uint16_t id);
// ***********************************************

static int bind_lv_btnmatrix_set_focused_btn(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int id = lua_tointeger(L,2);

  lv_btnmatrix_set_focused_btn(btnm, id);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_recolor(const lv_obj_t * btnm, bool en);
// ***********************************************

static int bind_lv_btnmatrix_set_recolor(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int en = lua_toboolean(L,2);

  lv_btnmatrix_set_recolor(btnm, en);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_btn_ctrl(lv_obj_t * btnm, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
// ***********************************************

static int bind_lv_btnmatrix_set_btn_ctrl(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int btn_id = lua_tointeger(L,2);
  int ctrl = lua_tointeger(L,3);

  lv_btnmatrix_set_btn_ctrl(btnm, btn_id, ctrl);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_clear_btn_ctrl(const lv_obj_t * btnm, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
// ***********************************************

static int bind_lv_btnmatrix_clear_btn_ctrl(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int btn_id = lua_tointeger(L,2);
  int ctrl = lua_tointeger(L,3);

  lv_btnmatrix_clear_btn_ctrl(btnm, btn_id, ctrl);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_btn_ctrl_all(lv_obj_t * btnm, lv_btnmatrix_ctrl_t ctrl);
// ***********************************************

static int bind_lv_btnmatrix_set_btn_ctrl_all(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int ctrl = lua_tointeger(L,2);

  lv_btnmatrix_set_btn_ctrl_all(btnm, ctrl);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_clear_btn_ctrl_all(lv_obj_t * btnm, lv_btnmatrix_ctrl_t ctrl);
// ***********************************************

static int bind_lv_btnmatrix_clear_btn_ctrl_all(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int ctrl = lua_tointeger(L,2);

  lv_btnmatrix_clear_btn_ctrl_all(btnm, ctrl);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_btn_width(lv_obj_t * btnm, uint16_t btn_id, uint8_t width);
// ***********************************************

static int bind_lv_btnmatrix_set_btn_width(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int btn_id = lua_tointeger(L,2);
  int width = lua_tointeger(L,3);

  lv_btnmatrix_set_btn_width(btnm, btn_id, width);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_one_check(lv_obj_t * btnm, bool one_chk);
// ***********************************************

static int bind_lv_btnmatrix_set_one_check(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int one_chk = lua_toboolean(L,2);

  lv_btnmatrix_set_one_check(btnm, one_chk);

  return 0;
}


// ***********************************************
// * void lv_btnmatrix_set_align(lv_obj_t * btnm, lv_label_align_t align);
// ***********************************************

static int bind_lv_btnmatrix_set_align(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int align = lua_tointeger(L,2);

  lv_btnmatrix_set_align(btnm, align);

  return 0;
}


// ***********************************************
// * const char ** lv_btnmatrix_get_map_array(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_map_array(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  const char ** ret = lv_btnmatrix_get_map_array(btnm);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_btnmatrix_get_recolor(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_recolor(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  bool ret = lv_btnmatrix_get_recolor(btnm);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_btnmatrix_get_active_btn(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_active_btn(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  uint16_t ret = lv_btnmatrix_get_active_btn(btnm);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * const char * lv_btnmatrix_get_active_btn_text(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_active_btn_text(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  const char * ret = lv_btnmatrix_get_active_btn_text(btnm);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * uint16_t lv_btnmatrix_get_focused_btn(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_focused_btn(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  uint16_t ret = lv_btnmatrix_get_focused_btn(btnm);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * const char * lv_btnmatrix_get_btn_text(const lv_obj_t * btnm, uint16_t btn_id);
// ***********************************************

static int bind_lv_btnmatrix_get_btn_text(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int btn_id = lua_tointeger(L,2);

  const char * ret = lv_btnmatrix_get_btn_text(btnm, btn_id);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_btnmatrix_get_btn_ctrl(lv_obj_t * btnm, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
// ***********************************************

static int bind_lv_btnmatrix_get_btn_ctrl(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);
  int btn_id = lua_tointeger(L,2);
  int ctrl = lua_tointeger(L,3);

  bool ret = lv_btnmatrix_get_btn_ctrl(btnm, btn_id, ctrl);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * bool lv_btnmatrix_get_one_check(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_one_check(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  bool ret = lv_btnmatrix_get_one_check(btnm);

  lua_pushboolean(L, ret);
  return 1;
}


// ***********************************************
// * lv_label_align_t lv_btnmatrix_get_align(const lv_obj_t * btnm);
// ***********************************************

static int bind_lv_btnmatrix_get_align(lua_State *L)
{
  void * btnm = lua_touserdata(L,1);

  lv_label_align_t ret = lv_btnmatrix_get_align(btnm);

  lua_pushinteger(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "btnmatrix_create", bind_lv_btnmatrix_create },
  { "btnmatrix_set_map", bind_lv_btnmatrix_set_map },
  { "btnmatrix_set_ctrl_map", bind_lv_btnmatrix_set_ctrl_map },
  { "btnmatrix_set_focused_btn", bind_lv_btnmatrix_set_focused_btn },
  { "btnmatrix_set_recolor", bind_lv_btnmatrix_set_recolor },
  { "btnmatrix_set_btn_ctrl", bind_lv_btnmatrix_set_btn_ctrl },
  { "btnmatrix_clear_btn_ctrl", bind_lv_btnmatrix_clear_btn_ctrl },
  { "btnmatrix_set_btn_ctrl_all", bind_lv_btnmatrix_set_btn_ctrl_all },
  { "btnmatrix_clear_btn_ctrl_all", bind_lv_btnmatrix_clear_btn_ctrl_all },
  { "btnmatrix_set_btn_width", bind_lv_btnmatrix_set_btn_width },
  { "btnmatrix_set_one_check", bind_lv_btnmatrix_set_one_check },
  { "btnmatrix_set_align", bind_lv_btnmatrix_set_align },
  { "btnmatrix_get_map_array", bind_lv_btnmatrix_get_map_array },
  { "btnmatrix_get_recolor", bind_lv_btnmatrix_get_recolor },
  { "btnmatrix_get_active_btn", bind_lv_btnmatrix_get_active_btn },
  { "btnmatrix_get_active_btn_text", bind_lv_btnmatrix_get_active_btn_text },
  { "btnmatrix_get_focused_btn", bind_lv_btnmatrix_get_focused_btn },
  { "btnmatrix_get_btn_text", bind_lv_btnmatrix_get_btn_text },
  { "btnmatrix_get_btn_ctrl", bind_lv_btnmatrix_get_btn_ctrl },
  { "btnmatrix_get_one_check", bind_lv_btnmatrix_get_one_check },
  { "btnmatrix_get_align", bind_lv_btnmatrix_get_align },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_btnmatrix__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
