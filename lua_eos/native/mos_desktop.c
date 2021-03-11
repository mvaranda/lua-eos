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

/* mos_thread_new

  mos_queue_create
  mos_queue_get
  mos_queue_put
  mos_queue_waiting
  mos_timer_create_single_shot */

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "mos.h"


#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

void * mos_malloc (size_t size) { return malloc(size); }
void * mos_calloc (size_t num, size_t size) {
    void * p = mos_malloc(num * size);
    if (p) memset(p, 0, num * size);
    return p;
}
void mos_free (void * p) { return free(p); }

mos_thread_h_t mos_thread_new( const char *pcName, thread_func_t thread_func, void *pvArg, uint32_t iStackSize, uint32_t iPriority )
{
#ifdef WIN32
  pthread_t * thread = (pthread_t *) MOS_MALLOC(sizeof(pthread_t));
  int t = pthread_create(thread, NULL,
                            (void *(*) (void *)) thread_func, NULL);
#else
    pthread_t thread;
    int t = pthread_create(&thread, NULL,
                              (void *(*) (void *)) thread_func, NULL);
#endif
    if (t) {
        return NULL;
    }
    return (mos_thread_h_t) thread;
}

typedef struct queue_st {
    uint8_t *       buffer;
    mos_mutex_h_t   mutex;
    uint32_t        item_size;
    uint32_t        max_num_items;
    uint32_t        num_items;
    uint32_t        head_idx;
    uint32_t        tail_idx;
} queue_t;

mos_queue_h_t mos_queue_create ( uint32_t len, uint32_t item_size)
{
  // return xQueueCreate( len, item_size);
  queue_t * h = (queue_t *) MOS_MALLOC(sizeof(queue_t));
  if ( ! h) {
      LOG_E("mos_queue_create: no memo for handle");
      return NULL;
  }
  h->buffer = MOS_CALLOC(len, item_size);
  if ( ! h->buffer) {
      LOG_E("mos_queue_create: no memo for buffer");
      MOS_FREE(h);
      return NULL;
  }

  h->mutex = mos_mutex_create();
  h->item_size = item_size;
  h->max_num_items = len;
  h->num_items = 0;
  h->head_idx = 0;
  h->tail_idx = 0;

  return h;
}

int mos_queue_put (mos_queue_h_t queue_id, const void * item_to_queue)
{
  queue_t * q = (queue_t *) queue_id;
  mos_mutex_lock(q->mutex);
  if (q->num_items >= q->max_num_items) {
    LOG_W("mos_queue_put: queue full");
    mos_mutex_unlock(q->mutex);
    return MOS_ERROR;
  }

  uint8_t * byte_ptr = q->buffer + (q->item_size * q->head_idx);
  memcpy(byte_ptr, item_to_queue, q->item_size);
  q->num_items++;
  q->head_idx++;
  if (q->head_idx >= q->max_num_items) {
      q->head_idx = 0;
  }

  mos_mutex_unlock(q->mutex);
  return MOS_PASS;
}

int mos_queue_get (mos_queue_h_t queue_id, void *item_buf, uint32_t timeout_milliseconds)
{
    queue_t * q = (queue_t *) queue_id;
    mos_mutex_lock(q->mutex);
    if (q->num_items == 0) {
      // TODO: add timeout_milliseconds wait
      mos_mutex_unlock(q->mutex);
      return MOS_ERROR;
    }

    uint8_t * byte_ptr = q->buffer + (q->item_size * q->tail_idx);
    memcpy(item_buf, byte_ptr, q->item_size);
    q->num_items--;
    q->tail_idx++;
    if (q->tail_idx >= q->max_num_items) {
        q->tail_idx = 0;
    }

    mos_mutex_unlock(q->mutex);
    return MOS_PASS;
}

int mos_queue_waiting (mos_queue_h_t queue_id)
{
  queue_t * q = (queue_t *) queue_id;
  return q->num_items; // note: assuming 32 bits CPU (atomic read)
}

//----------------- Mutex ------------------
mos_mutex_h_t mos_mutex_create(void)
{
    pthread_mutex_t * mutex_ptr = (pthread_mutex_t *) MOS_MALLOC(sizeof(pthread_mutex_t));
    if ( ! mutex_ptr) {
        LOG_E("mos_mutex_create: no memo for mutex");
        return NULL;
    }
    pthread_mutex_init(mutex_ptr, NULL);
    return mutex_ptr;
}

void mos_mutex_lock(mos_mutex_h_t mutex)
{
    if (pthread_mutex_lock(mutex)) {
        LOG_E("mos_mutex_lock: fail");
    }
}

void mos_mutex_unlock(mos_mutex_h_t mutex)
{
    if (pthread_mutex_unlock(mutex)) {
        LOG_E("mos_mutex_unlock: fail");
    }
}

void mos_mutex_destroy(mos_mutex_h_t mutex)
{
    pthread_mutex_destroy(mutex);
    MOS_FREE(mutex);
}



#ifdef __cplusplus
  }
#endif


