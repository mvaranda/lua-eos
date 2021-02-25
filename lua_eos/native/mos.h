#ifndef __ORBOS_H__
#define __ORBOS_H__
/****************************************************************************/
//
//  Module:          $URL: $
//  Created By:      Marcelo Varanda
//  Revision:        $Revision: $
//  Last Updated By: $Author: $
//  Last Updated:    $Date:  $
//
//  Description: Part of ORBOS (Cargo Camera Sensor)
//
//  Copyright (c) 2017 ORBCOMM, all rights reserved.
//  This material is Confidential and shall not be disclosed
//  to a third party without the written consent.
//
/****************************************************************************/
#include "orbos_int.h"
#include "filesys.h"
#include "log.h"

void * oos_malloc (size_t size);
void * oos_calloc (size_t num, size_t size);
void oos_free (void * p);

#if 1
  #define OOS_MALLOC(s) oos_malloc (s)
  #define OOS_FREE(p) oos_free(p)
#else
  #define OOS_MALLOC(s) NATIVE_MALLOC(s)
  #define OOS_FREE(p) NATIVE_FREE(p)
#endif

typedef void (*thread_func_t)(void * arg);
typedef void (*timer_func_t)(oos_timer_id_t timer_id);

#define OOS_GET_ELAPSE_TIME(start_time) (oos_get_ms_timestamp() - start_time)


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Inicialize OS
 *
 *
 * @return None
 */
void oos_init(void);

//------------ thread funcs --------------

/**
 * @brief Create a thread
 *
 * Starts a new thread with priority "prio" that will begin its
 * execution in the function "thread_func()". The "arg" argument will be
 * passed as an argument to the thread_func() function. The id of the new
 * thread is returned. Both the id and the priority are system
 * dependent.
 *
 * @param name Name of thread
 * @param thread_func Pointer to function to run.
 * @param arg Argument passed into function
 * @param stacksize Required stack amount in bytes
 * @param prio Thread priority
 *
 * @return upon success returns a valid oos_thread_id_t. NULL if error.
 */
oos_thread_id_t oos_thread_new( const char *name, thread_func_t thread_func, void *arg, int iStackSize, int iPriority );

/**
 * @brief Return the thread ID of the caller thread.
 *
 *
 * @return thread ID.
 */
oos_thread_id_t oos_thread_get_id (void);

/**
 * @brief Delete a thread
 *
 * Starts a new thread with priority "prio" that will begin its
 * execution in the function "thread_func()". The "arg" argument will be
 * passed as an argument to the thread_func() function. The id of the new
 * thread is returned. Both the id and the priority are system
 * dependent.
 *
 * @param thread Thread ID. A NULL can be used for a self-delete operation.
 *
 * @return None.
 */
void oos_thread_delete(oos_thread_id_t thread);

/**
 * @brief Suspend a thread
 *
 * Places a thread into the Suspended state. A thread that is in the Suspended state will never be selected to enter the Running state.
 * The only way of removing a thread from the Suspended state is to make it the subject of a call to oos_thread_resume().
 *
 * @param thread Thread ID. A NULL can be used for a self-delete operation.
 *
 * @return None.
 */
void oos_thread_suspend(oos_thread_id_t thread);

/**
 * @brief Resume a Suspended thread
 *
 *
 * Transition a thread from the Suspended state to the Ready state.
 * The thread must have previously been placed into the Suspended state using a call to oos_thread_suspend
 *
 * @param thread Thread ID.
 *
 * @return None.
 */
void oos_thread_resume(oos_thread_id_t thread);

/**
 * @brief thread sleep (in milliseconds)
 *
 *
 * Places the thread that calls oos_thread_sleep() into the Blocked state for a fixed number of time.
 *
 * @param time_milliseconds Duration that the thread will be blocked (sleeping).
 *
 * @return None.
 */
void oos_thread_sleep( uint32_t time_milliseconds);

//------------- queue ----------------

/**
 * @brief Create a Queue
 *
 *
 * Creates a new queue and returns an id by which the queue can be referenced.
 * Each queue requires RAM that is used to hold the queue state, and to hold the items that are contained
 * in the queue (the queue storage area). the the required RAM
 * is automatically allocated from the orbos heap.
 *
 * @param len The maximum number of items that the queue being created can hold at any one time.
 * @param item_size The size, in bytes, of each data item that can be stored in the queue.
 *
 * @return upon success returns a valid oos_queue_id_t. NULL if error.
 */
oos_queue_id_t oos_queue_create ( int len, int item_size);

/**
 * @brief place an item at the end of a queue
 *
 * @param queue_id The ID of the queue to which the item is being placed (written).
 *        The queue ID will have been returned from the call to oos_queue_create()
 *        or oos_queue_create_static() used to create the queue.
 * @param item_to_queue A pointer to the data to be copied into the queue.
 *        The size of each item the queue can hold is set when the queue is created,
 *        and that many bytes will be copied from pvItemToQueue into the queue storage area.
 *
 * @return OOS_PASS if OK.
 */
int oos_queue_put (oos_queue_id_t queue_id, const void * item_to_queue);

/**
 * @brief place an item at the end of a queue
 *
 * Same than oos_queue_put but oos_queue_put_from_isr can be called inside an ISR.
 *
 * @see oos_queue_put
 */
int oos_queue_put_from_isr (oos_queue_id_t xQueue, const void * pvItemToQueue);

/**
 * @brief get an item from a queue
 *
 * @param queue_id The ID of the queue from which the data is being received (read).
 *        The queue ID will have been returned from the call to oos_queue_create()
 *        or oos_queue_create_static() used to create the queue.
 * @param item_buf A pointer to the memory into which the received data will be copied to.
 *        The length of the buffer must be at least equal to the queue item size.
 *        The item size will have been set by the item_size parameter of the call to oos_queue_create()
 *        or oos_queue_create_static() used to create the queue.
 * @param timeout_milliseconds The maximum amount of time the thread should remain in the Blocked state
 *        to wait for data to become available on the queue, should the queue already be empty.
 *        If timeout_milliseconds is zero, then oos_queue_get() will return immediately if the queue is already empty.
 *        timeout_milliseconds = OOS_WAIT_FOREVER will cause the thread to wait indefinitely (without timing out).
 *
 * @return OOS_PASS if an item was. Otherwise, either timeout or error.
 * @note called must be sure that it is providing a valid queue ID as there is no distinction between timeout and error.
 */
int oos_queue_get (oos_queue_id_t queue_id, void *item_buf, uint32_t timeout_milliseconds);

/**
 * @brief return num entries queued
 *
 * @return num entries queued.
 *
 */
int oos_queue_waiting (oos_queue_id_t xQueue);

//--------------- RTC -------------------

/**
 * @brief get a time-of-the-day structure
 *
 * @param rtc_time structure for time-of-the-day.
 *
 * @return None.
 */
void oos_get_rtc_time ( oos_rtc_time_t * rtc_time);

/**
 * @brief get a time-of-the-day in seconds
 *
 * @return RTC time-of-the-day in seconds.
 */
uint32_t oos_get_rtc_time_in_seconds(void);

/**
 * @brief convert a time in a time-of-the-day structure to seconds
 *
 * @return RTC time-of-the-day in seconds.
 */
uint32_t oos_rtc_time_to_seconds(const oos_rtc_time_t *datetime);

/**
 * @brief convert a time in seconds to a time-of-the-day structure
 *
 * @return None
 */
void oos_seconds_to_rtc_time(uint32_t seconds, oos_rtc_time_t *datetime);

/**
 * @brief get a time in seconds since the system was initialized.
 *
 * @return time in seconds since power up.
 */
uint32_t oos_get_uptime_in_secs( void );

/**
 * @brief get a time in milliseconds since the system was initialized.
 *
 * @return time in seconds since power up.
 */
uint64_t oos_get_ms_timestamp(void);


//---------- timers ----------

/**
 * @brief Create and start a single shot timer
 *
 * After the time expires the callback function is called. The timer self destroys once it expires.
 * A call for oos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_milliseconds Expiring time (max 2,900,000 milliseconds)
 * @param callback Function called upon time expiring
 * @param arg Generic user defined argument passed to the callback.
 *
 * @return timer ID or NULL if error.
 *
 * @note For values > 2,900,000 milliseconds (~48 minutes) the oos_slow_timer_create should be used.
 */
oos_timer_id_t oos_timer_create_single_shot( int time_milliseconds, timer_func_t callback, void * arg );

/**
 * @brief Create and start a single shot timer
 *
 * After the time expires the callback function is called. Timer restarts
 * A call for oos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_milliseconds periodic Expiring time (max 2,900,000 milliseconds)
 * @param callback Function called upon time expiring
 * @param arg Generic user defined argument passed to the callback.
 *
 * @return timer ID or NULL if error.
 *
 */
oos_timer_id_t oos_timer_create_periodic( int time_milliseconds, timer_func_t callback, void * arg );


/**
 * @brief Create and start a single shot SLOW timer
 *
 * After the time expires the callback function is called. The timer self destroys once it expires.
 * A call for oos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_minutes Expiring time in minutes
 * @param callback Function called upon time expiring
 * @param arg Generic user defined argument passed to the callback.
 *
 * @return timer ID or NULL if error.
 * @note this timer has a (low) precision of +/- 1 minute.
 *
 */
oos_timer_id_t oos_slow_timer_create_single_shot( int time_minutes, timer_func_t callback, void * arg );

/**
 * @brief Delete a timer
 *
 *
 * @param timer_id Timer ID
 *
 * @return None
 */
void oos_timer_delete ( oos_timer_id_t timer_id );

/**
 * @brief Delete a timer
 *
 *
 * @param timer_id Timer ID
 *
 * @return Remaining time to expire: in milliseconds for regular timer or in minutes for slow timers. -1 if given an invalid timer ID.
 */
int oos_timer_get_remaining ( oos_timer_id_t timer_id );

//--------- counters -------
/**
 * @brief Get a timestamp from a freerunner counter.
 *
 * @return timestamp incremented 32768 per second.
 */
uint64_t oos_get_raw_timestamp(void);

/**
 * @brief Get a float timestamp.
 *
 * @return float timestamp wher its granularity is based on oos_get_raw_timestamp.
 */
float oos_get_timestamp(void); // second

//----------- Mutex -----------
/**
 * @brief Create a mutex object.
 *
 * @return mutex ID.
 */
oos_mutex_t oos_mutex_create(void);

/**
 * @brief Lock a mutex.
 *
 * *param mutex Mutex ID to be locked
 *
 * @return mutex None.
 */
void oos_mutex_lock(oos_mutex_t mutex);

/**
 * @brief Unlock a mutex.
 *
 * *param mutex Mutex ID to be unlocked
 *
 * @return mutex None.
 */
void oos_mutex_unlock(oos_mutex_t mutex);

//------------------------------------------
void oos_loop(void);

__noreturn void oos_reset(void);

void oos_shutdown(void);


#ifdef __cplusplus
}
#endif


//----------------------------
#endif
