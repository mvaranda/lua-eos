
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
#include "lv_calendar.h"

#ifdef __cplusplus
extern "C" {
#endif


#define UNUSED(x) (void)(x)
// ***********************************************
// * lv_obj_t * lv_calendar_create(lv_obj_t * par, const lv_obj_t * copy);
// ***********************************************

static int bind_lv_calendar_create(lua_State *L)
{
  void * par = lua_touserdata(L,1);
  void * copy = lua_touserdata(L,2);

  lv_obj_t * ret = lv_calendar_create(par, copy);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * void lv_calendar_set_today_date(lv_obj_t * calendar, lv_calendar_date_t * today);
// ***********************************************

static int bind_lv_calendar_set_today_date(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);
  void * today = lua_touserdata(L,2);

  lv_calendar_set_today_date(calendar, today);

  return 0;
}


// ***********************************************
// * void lv_calendar_set_showed_date(lv_obj_t * calendar, lv_calendar_date_t * showed);
// ***********************************************

static int bind_lv_calendar_set_showed_date(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);
  void * showed = lua_touserdata(L,2);

  lv_calendar_set_showed_date(calendar, showed);

  return 0;
}


// ***********************************************
// * void lv_calendar_set_highlighted_dates(lv_obj_t * calendar, lv_calendar_date_t highlighted[], uint16_t date_num);
// ***********************************************

static int bind_lv_calendar_set_highlighted_dates(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);
  int highlighted[] = lua_tointeger(L,2);
  int date_num = lua_tointeger(L,3);

  lv_calendar_set_highlighted_dates(calendar, highlighted[], date_num);

  return 0;
}


// ***********************************************
// * void lv_calendar_set_day_names(lv_obj_t * calendar, const char ** day_names);
// ***********************************************

static int bind_lv_calendar_set_day_names(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);
  const char * day_names = lua_tostring(L,2);

  lv_calendar_set_day_names(calendar, day_names);

  return 0;
}


// ***********************************************
// * void lv_calendar_set_month_names(lv_obj_t * calendar, const char ** month_names);
// ***********************************************

static int bind_lv_calendar_set_month_names(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);
  const char * month_names = lua_tostring(L,2);

  lv_calendar_set_month_names(calendar, month_names);

  return 0;
}


// ***********************************************
// * lv_calendar_date_t * lv_calendar_get_today_date(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_today_date(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  lv_calendar_date_t * ret = lv_calendar_get_today_date(calendar);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_calendar_date_t * lv_calendar_get_showed_date(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_showed_date(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  lv_calendar_date_t * ret = lv_calendar_get_showed_date(calendar);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_calendar_date_t * lv_calendar_get_pressed_date(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_pressed_date(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  lv_calendar_date_t * ret = lv_calendar_get_pressed_date(calendar);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * lv_calendar_date_t * lv_calendar_get_highlighted_dates(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_highlighted_dates(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  lv_calendar_date_t * ret = lv_calendar_get_highlighted_dates(calendar);

  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}


// ***********************************************
// * uint16_t lv_calendar_get_highlighted_dates_num(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_highlighted_dates_num(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  uint16_t ret = lv_calendar_get_highlighted_dates_num(calendar);

  lua_pushinteger(L, ret);
  return 1;
}


// ***********************************************
// * const char ** lv_calendar_get_day_names(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_day_names(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  const char ** ret = lv_calendar_get_day_names(calendar);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * const char ** lv_calendar_get_month_names(const lv_obj_t * calendar);
// ***********************************************

static int bind_lv_calendar_get_month_names(lua_State *L)
{
  void * calendar = lua_touserdata(L,1);

  const char ** ret = lv_calendar_get_month_names(calendar);

  lua_pushstring(L, ret);
  return 1;
}


// ***********************************************
// * uint8_t lv_calendar_get_day_of_week(uint32_t year, uint32_t month, uint32_t day);
// ***********************************************

static int bind_lv_calendar_get_day_of_week(lua_State *L)
{
  int year = lua_tointeger(L,1);
  int month = lua_tointeger(L,2);
  int day = lua_tointeger(L,3);

  uint8_t ret = lv_calendar_get_day_of_week(year, month, day);

  lua_pushinteger(L, ret);
  return 1;
}



static const luaL_Reg binding_names [] = {
  { "calendar_create", bind_lv_calendar_create },
  { "calendar_set_today_date", bind_lv_calendar_set_today_date },
  { "calendar_set_showed_date", bind_lv_calendar_set_showed_date },
  { "calendar_set_highlighted_dates", bind_lv_calendar_set_highlighted_dates },
  { "calendar_set_day_names", bind_lv_calendar_set_day_names },
  { "calendar_set_month_names", bind_lv_calendar_set_month_names },
  { "calendar_get_today_date", bind_lv_calendar_get_today_date },
  { "calendar_get_showed_date", bind_lv_calendar_get_showed_date },
  { "calendar_get_pressed_date", bind_lv_calendar_get_pressed_date },
  { "calendar_get_highlighted_dates", bind_lv_calendar_get_highlighted_dates },
  { "calendar_get_highlighted_dates_num", bind_lv_calendar_get_highlighted_dates_num },
  { "calendar_get_day_names", bind_lv_calendar_get_day_names },
  { "calendar_get_month_names", bind_lv_calendar_get_month_names },
  { "calendar_get_day_of_week", bind_lv_calendar_get_day_of_week },

  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_lv_calendar__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}


#ifdef __cplusplus
  }
#endif
