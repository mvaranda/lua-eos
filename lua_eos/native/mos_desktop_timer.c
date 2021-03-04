/****************************************************************************/
//
//  Module:          $URL: $
//  Created By:      Marcelo Varanda
//  Revision:        $Revision: $
//  Last Updated By: $Author: $
//  Last Updated:    $Date:  $
//
//  Description: Part of M-OS 
//
//  Copyright (c) 2021 Marcelo Varanda, all rights reserved.
//
//
/****************************************************************************/

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "mos.h"


#include <pthread.h>

#define NUM_MAX_TIMERS 10

typedef enum {
    ST_EMPTY = 0,
    ST_COUNTING,
    ST_EXPIRED,
    ST_IDLE,
} state_t;

typedef struct list_entry_st {
    struct list_entry_st *   next;
    state_t             state;

    uint64_t            expire;
    timer_func_t        callback;
    const void *        arg;

} list_entry_t;

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);

#ifdef __cplusplus
extern "C" {
#endif

static list_entry_t list[NUM_MAX_TIMERS];
static list_num_entries = 0;
static list_entry_t * head = NULL;

static list_entry_t * insert( uint64_t expire, timer_func_t callback, const void * arg) {
    int i;

    list_entry_t * entry = NULL;

    if (list_num_entries >= NUM_MAX_TIMERS) {
        LOG_E("timer list full");
        return NULL;
    }
    for (i = 0; i < NUM_MAX_TIMERS; i++) {
        if (list[i].state == ST_EMPTY) {
            entry = &list[i];
            break;
        }
    }
    if ( ! entry) {
        LOG_E("unexpected: timer not full but no empty record");
        return NULL;
    }
    entry->state = ST_COUNTING;
    entry->expire = expire;
    entry->callback = callback;
    entry->arg = arg;
    entry->next = NULL;

    list_num_entries++;

    list_entry_t * ptr = head;
    if ( ! ptr) {
        head = entry;
        return entry;
    }

    if (entry->expire < ptr->expire) {
        entry->next = ptr;
        head = entry;
        return entry;
    }

    while(ptr) {
        if (ptr->next == NULL) {
            ptr->next = entry;
            break;
        }

        if (entry->expire < ptr->next->expire) {
            entry->next = ptr->next;
            ptr->next = entry;
            break;
        }
        ptr = ptr->next;
    }

    return entry;
}

mos_timer_h_t mos_timer_create_single_shot( uint32_t time_milliseconds, timer_func_t callback, const void * arg )
{

}

static void timer_thread(void *arg)
{
    LOG("Timer therad started");
}

void mos_timer_init(void)
{
    memset (list, 0, sizeof(list));
    mos_thread_h_t task = mos_thread_new( "luaTask", timer_thread, NULL, 1024 * 1024, 10 );

}

#ifdef __cplusplus
}
#endif



