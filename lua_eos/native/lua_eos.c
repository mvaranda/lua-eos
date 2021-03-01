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
#include "timers.h"
#include "queue.h"
#include "semphr.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "lua_eos.h"

typedef struct ev_queue_item_timer_st {
    int taskID;
    int timerID;
} ev_queue_item_timer_t;

typedef union ev_queue_item_union_st {
    ev_queue_item_timer_t       timer_item;
} ev_queue_item_union_t;

typedef struct ev_queue_item_st {
    ev_queue_item_union_t       item;
} ev_queue_item_t;


#define START_LUA_EOS_FILENAME "../lua_eos/eos.lua"
#define READ_BUF_SIZE 1024



#define EV_QUEUE_LENGTH    16

#define EV_LOCK() xSemaphoreTake(ev_q_mutex, pdMS_TO_TICKS(10000))
#define EV_UNLOCK() xSemaphoreGive(ev_q_mutex)


static SemaphoreHandle_t ev_q_mutex = NULL;
static StaticSemaphore_t ev_q_mutex_buffer;

/* The variable used to hold the event queue's data structure. */
static StaticQueue_t static_event_queue_ctrl;
static QueueHandle_t event_queue;
static uint8_t event_queue_buff[ EV_QUEUE_LENGTH * sizeof( ev_queue_item_t ) ];

static void add_event_to_queue( const void * ev_item)
{
  if ( EV_LOCK() != pdTRUE) {
    LOG_E("timer_callback: EV_LOCK fail");
    return;
  }

  if ( xQueueSend( event_queue, (const void *) ev_item, 0) != pdTRUE) {
    LOG_E("timer_callback: event Q is full");
  }

  if ( EV_UNLOCK() != pdTRUE) {
    LOG_E("timer_callback: EV_UNLOCK fail");
    return;
  }
}

static void timer_callback(TimerHandle_t tm)
{
    uint32_t timer_id = ( uint32_t ) pvTimerGetTimerID( tm );

    ev_queue_item_t ev_u;
    ev_u.item.timer_item.taskID = timer_id >> 16;
    ev_u.item.timer_item.timerID = timer_id & 0xffff;
    LOG("timer_callback: taskID = %d, timerID = %d", ev_u.item.timer_item.taskID, ev_u.item.timer_item.timerID);
    add_event_to_queue(&ev_u);
}

static int luac_eod_read_event_table(lua_State *L)
{
  lua_newtable(L);

  lua_pushstring(L, "aaa_idx");
  lua_pushstring(L, "aaa_value");
  lua_settable(L, -3);

  lua_pushstring(L, "bbb_idx");
  lua_pushinteger(L, 222);
  lua_settable(L, -3);
  return 1;

}

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

    unsigned int _timerID = (taskID << 16) | (timerID & 0xffff);

    TimerHandle_t tm = xTimerCreate
                     ( "lua timer",
                       (const TickType_t)  pdMS_TO_TICKS(time),
                       pdFALSE,
                       (void *) _timerID,
                       timer_callback );

    xTimerStart( tm, -1 );


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

    lua_pushcfunction(L, luac_eod_read_event_table);
    lua_setglobal(L, "eod_read_event_table");

}

void luaTask(void * arg)
{
  LOG("luaInit...");

  if ( ! (event_queue = xQueueCreateStatic( EV_QUEUE_LENGTH,
                                 sizeof( ev_queue_item_t ),
                                 event_queue_buff,
                                 &static_event_queue_ctrl) ) ){
       LOG_E("Could not create event_queue");
       return;
  }

  if ( ! (ev_q_mutex = xSemaphoreCreateMutexStatic( &ev_q_mutex_buffer ) )) {
      LOG_E("Could not create ev_q_mutex");
      return;
  }


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
    LOG_E( "%s", lua_tostring(L, -1));
    lua_pop(L, 1);  /* pop error message from the stack */
  }

  LOG_E("lua thread terminated");
}
