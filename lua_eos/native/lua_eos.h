#ifndef __EOS_LUA_H__
#define __EOS_LUA_H__
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

#include "lua.h"

#ifdef MOS_DESKTOP
  #define LOWEST_PRIORITY 1 // assume low value has low priority
#else
  #define LOWEST_PRIORITY tskIDLE_PRIORITY
#endif

// Stack sizes
#define LUA_EOS_STACK_SIZE (4 * 1024) // 4k

// Priorities
#define	LUA_TASK_PRIORITY		( LOWEST_PRIORITY + 1 )

typedef enum {
  EV_SYS_START_UP = 1,
  EV_SYS_SHUT_DOWN = 2,

  EV_SYS_TIMER = 3,

} sys_events_t;

typedef struct ev_queue_item_timer_st {
    int           taskID;
    int           timerID;
} ev_queue_item_timer_t;

typedef union ev_queue_item_union_st {
    ev_queue_item_timer_t       timer_item;
} ev_queue_item_union_t;

typedef void (*cb_event_push_t)(lua_State *L, ev_queue_item_union_t * item_ptr);


typedef struct ev_queue_item_st {
    cb_event_push_t            cb_event_push;
    ev_queue_item_union_t       item;
} ev_queue_item_t;



void luaTask(void * arg);

//---------------------------------------------------------
#endif
