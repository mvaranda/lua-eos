/***************************************************************
 *
 *                 This code is part of LUA_EOS
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */


/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "lua_eos.h"

#define START_LUA_EOS_FILENAME "../lua_eos/eos.lua"
#define READ_BUF_SIZE 1024

// set timer:
// task ID
// if possible: event queue
// timer ID (where 0 is delay)
// expire in milliseconds
static int luac_eos_set_timer(lua_State *L)
{
    int taskID = (int) lua_tointeger(L,1);
    int timerID = (int) lua_tointeger(L,2);
    int time = (int) lua_tointeger(L,3);
    LOG("luac_eos_set_timer: taskID = %d, timerID = %d, time = %d", taskID, timerID, time);
    return 0;
}

static int luac_eos_delay(lua_State *L)
{
    unsigned int d = (unsigned int) luaL_checknumber(L, 1);
    usleep(d * 1000);
    return 0;
}

static void register_luacs(lua_State *L)
{
    lua_pushcfunction(L, luac_eos_delay);
    lua_setglobal(L, "eos_delay");

    lua_pushcfunction(L, luac_eos_set_timer);
    lua_setglobal(L, "eos_set_timer");

}

void luaTask(void * arg)
{
    LOG("luaInit...");

  //int status, result;
  lua_State *L = luaL_newstate();  /* create state */
  if (L == NULL) {
    LOG_E("cannot create state: not enough memory");
    return;
  }

  luaL_openlibs(L);
  register_luacs(L);

  int err;
  if ((err = luaL_loadfile(L, START_LUA_EOS_FILENAME)) != 0) {
      switch(err) {
      case LUA_ERRFILE:
          LOG_E("loadfile: fail to open eos.lua");
          break;
          case LUA_ERRSYNTAX: LOG_E("loadfile: syntax error during pre-compilation");
          break;
        case LUA_ERRMEM:
          LOG_E("loadfile: memory allocation error.");
          break;
      default:
          LOG_E("loadfile: unknown error.");
          break;
      }
      return;
  }
  err = lua_pcall(L, 0, 0, 0);
  if (err) {
    printf( "%s", lua_tostring(L, -1));
    lua_pop(L, 1);  /* pop error message from the stack */
  }

  LOG_E("lua thread terminated");
}
