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
#include "stdbool.h"

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
  EV_SYS_TEXT_FROM_CONSOLE = 4,
  EV_SYS_SPLASH_DONE = 5,

} sys_events_t;

typedef struct ev_queue_item_timer_st {
    int           taskID;
    int           timerID;
} ev_queue_item_timer_t;

typedef struct ev_queue_item_text_st {
    char *           text;
} ev_queue_item_text_t;

typedef union ev_queue_item_union_st {
    ev_queue_item_timer_t       timer_item;
    ev_queue_item_text_t        generic_text;
} ev_queue_item_union_t;

//typedef union ev_item_st {
//    sys_events_t                event_id;
//    ev_queue_item_union_t       item_union;
//} ev_item_t;




typedef struct ev_queue_item_st {
    sys_events_t                event_id;
    void *                      cb_event_push;
    ev_queue_item_union_t       item;
} ev_queue_item_t;

typedef void (*cb_event_push_t)(lua_State *L, ev_queue_item_t * queue_item_ptr);


bool add_text_event(sys_events_t id, char * txt);

void luaTask(void * arg);

#ifdef __cplusplus
extern "C" {
#endif

void sendTextToConsoleController(char * msg);

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------
#endif
