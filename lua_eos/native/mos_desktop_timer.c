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
#include "mos_desktop_timer.h"


#include <pthread.h>

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);

#ifndef UNIT_TEST
  #define STATIC static
#else
  #define STATIC
#endif

#ifdef __cplusplus
extern "C" {
#endif


STATIC uint64_t tick_counter = 0;

STATIC list_entry_t list[NUM_MAX_TIMERS];
STATIC uint32_t list_num_entries = 0;
STATIC list_entry_t * head = NULL;

STATIC list_entry_t * insert( uint64_t expire, timer_func_t callback, const void * arg) {
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
    uint64_t last = 0;
    LOG("Timer therad started");
    while(1) {
        usleep(TICK_PERIOD);

        tick_counter++;
        if (tick_counter - last > MILLISEC_TO_TICK(1000)) {
            last = tick_counter;
            LOG("tick");
        }
    }
}

void mos_timer_init(void)
{
    memset (list, 0, sizeof(list));
    mos_thread_h_t task = mos_thread_new( "luaTask", timer_thread, NULL, 1024 * 1024, 10 );

}

#ifdef __cplusplus
}
#endif



