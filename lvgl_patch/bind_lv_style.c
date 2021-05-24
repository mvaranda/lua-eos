
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
#include "lv_style.h"

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
