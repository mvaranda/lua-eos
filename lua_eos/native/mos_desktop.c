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

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);

void * mos_malloc (size_t size) { return malloc(size); }
void * mos_calloc (size_t num, size_t size) {
    void * p = mos_malloc(num * size);
    if (p) memset(p, 0, num * size);
    return p;
}
void mos_free (void * p) { return free(p); }

mos_thread_h_t mos_thread_new( const char *pcName, thread_func_t thread_func, void *pvArg, uint32_t iStackSize, uint32_t iPriority )
{
    pthread_t thread;
    int t = pthread_create(&thread, NULL,
                              (void *(*) (void *)) thread_func, NULL);
    if (t) {
        return NULL;
    }
    return thread;
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

#if 0

#include "mos.h"
//#include "shell_uart.h"
//#include "orbos_shell.h"
//#include "app_cfg.h"
//#include "fsl_src.h"
//#include "board.h"

#ifndef WIN32
//#include "fsl_rtc.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

static mos_mutex_t malloc_mutex;

// FreeRTOS heap
uint8_t ucHeap[configTOTAL_HEAP_SIZE] @ "DTCM_N";

extern int wdog_init(void);

static struct mos_slow_timer_st {
  uint32_t        expiring;     // related to RTC in seconds
  mos_timer_id_t  timer_id;
} slow_timer_pool[SLOW_TIMER_POOL_SIZE];


//--- prototypes ----
static void initRTC(void);
//static uint32_t second_base;
//static uint32_t startup_time; //mos_rtc_time_to_seconds(const mos_rtc_time_t *datetime)
static void init_timers(void);

void mos_loop(void)
{
    vTaskStartScheduler();
    for (;;)
        ;
}

mos_thread_id_t mos_thread_new( const char *pcName, thread_func_t thread_func, void *pvArg, int iStackSize, int iPriority )
{
  TaskHandle_t xCreatedTask;
  portBASE_TYPE xResult;
  mos_thread_id_t xReturn;

  xResult = xTaskCreate( thread_func, pcName, iStackSize, pvArg, iPriority, &xCreatedTask );

  if( xResult == mos_PASS ) {
    xReturn = xCreatedTask;
  }
  else {
    xReturn = NULL;
  }

  return xReturn;
}

void mos_thread_suspend(mos_thread_id_t task)
{
  vTaskSuspend(task);
}

void mos_thread_delete(mos_thread_id_t task)
{
  vTaskDelete( task );
}

mos_thread_id_t mos_thread_get_id (void)
{
  return xTaskGetCurrentTaskHandle( );
}
//----------------- queue -------------------
mos_queue_id_t mos_queue_create ( int len, int item_size)
{
  return xQueueCreate( len, item_size);
}

int mos_queue_put (mos_queue_id_t xQueue, const void * pvItemToQueue)
{
  return xQueueSend(xQueue, pvItemToQueue, 0);
}

int mos_queue_put_from_isr (mos_queue_id_t xQueue, const void * pvItemToQueue)
{
  return xQueueSendToBackFromISR(xQueue, pvItemToQueue, NULL);
}

int mos_queue_waiting (mos_queue_id_t xQueue)
{
  return (int) uxQueueMessagesWaiting( xQueue );
}

int mos_queue_get (mos_queue_id_t xQueue, void *pvBuffer, uint32_t timeout_milliseconds)
{
  TickType_t xTicksToWait;

  if (timeout_milliseconds == 0)
    xTicksToWait = 0;
  else if (timeout_milliseconds == mos_WAIT_FOREVER) {
    xTicksToWait = mos_WAIT_FOREVER;
  }
  else {
    xTicksToWait = pdMS_TO_TICKS(timeout_milliseconds);
  }
  return xQueueReceive( xQueue, pvBuffer, xTicksToWait );
}


void mos_thread_sleep( uint32_t time_milliseconds)
{
  if (time_milliseconds == 0) return;
  vTaskDelay( time_milliseconds / portTICK_PERIOD_MS );
}

void mos_init(void)
{
  malloc_mutex = mos_mutex_create();

  shellUartInit();
  shellInit();
  log_init( (void *) shellGetMainCtx() );


  initRTC();
  init_timers();

  wdog_init();
}

mos_mutex_t mos_mutex_create(void)
{
  return xSemaphoreCreateMutex();
}

void mos_mutex_lock(mos_mutex_t mutex)
{
  xSemaphoreTake(mutex, mos_WAIT_FOREVER);
}

void mos_mutex_unlock(mos_mutex_t mutex)
{
  xSemaphoreGive(mutex);
}

void * mos_malloc (size_t size)
{
  void * ret;
  if (malloc_mutex) mos_mutex_lock(malloc_mutex);
  ret = malloc(size);
  if (malloc_mutex) mos_mutex_unlock(malloc_mutex);
  return ret;
}

void * mos_calloc (size_t num, size_t size)
{
  void * ret;
  if (malloc_mutex) mos_mutex_lock(malloc_mutex);
  ret = malloc(size * num);
  if (ret) {
    memset(ret, 0, size * num);
  }
  if (malloc_mutex) mos_mutex_unlock(malloc_mutex);
  return ret;

}

void mos_free (void * p)
{
  if (p == NULL) return;

  if (malloc_mutex) mos_mutex_lock(malloc_mutex);
  free(p);
  if (malloc_mutex) mos_mutex_unlock(malloc_mutex);
}


void mos_get_rtc_time ( mos_rtc_time_t * time)
{
   //RTC_GetDatetime(RTC, time);
}

uint32_t mos_get_rtc_time_in_seconds(void)
{
//  mos_rtc_time_t datetime;
//  mos_get_rtc_time( &datetime );
//  return mos_rtc_time_to_seconds(&datetime);
  return 0;
}

uint32_t mos_get_uptime_in_secs( void )
{
//  uint32_t now = mos_get_rtc_time_in_seconds();
//  return( now - startup_time);
  return 0;
}


static void initRTC(void)
{
#if 0
//#ifndef WIN32
    //uint32_t sec;
    //uint32_t currSeconds;
    rtc_datetime_t date;
    rtc_config_t rtcConfig;
    /* Init RTC */
    /*
     * rtcConfig.wakeupSelect = false;
     * rtcConfig.updateMode = false;
     * rtcConfig.supervisorAccess = false;
     * rtcConfig.compensationInterval = 0;
     * rtcConfig.compensationTime = 0;
     */
    RTC_GetDefaultConfig(&rtcConfig);
    RTC_Init(RTC, &rtcConfig);
    /* Select RTC clock source */
    RTC->CR |= RTC_CR_OSCE_MASK;    /* Enable the RTC 32KHz oscillator */

    /* Set a start date time and start RT */
    date.year = 2017U;
    date.month = 1U;
    date.day = 1U;
    date.hour = 0U;
    date.minute = 0;
    date.second = 0;

    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
    RTC_StopTimer(RTC);

    /* Set RTC time to default */
    RTC_SetDatetime(RTC, &date);

    /* Enable RTC alarm interrupt */
   // RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);

    /* Enable at the NVIC */
  //  EnableIRQ(RTC_IRQn);

    /* Start the RTC time counter */
    RTC_StartTimer(RTC);
    second_base = RTC->TSR;
    startup_time = mos_rtc_time_to_seconds(&date);
#endif
}

uint64_t mos_get_raw_timestamp(void) // 32768 increments per second
{
  uint64_t ret = 0;
#if 0
//#ifndef WIN32
  uint32_t sec1,sec2,f1,f2;
  do {
    sec1 = RTC->TSR;
    f1 = RTC->TPR;
    sec2 = RTC->TSR;
    f2 = RTC->TPR;
  } while( (f1 != f2) || (sec1 != sec2));
  ret = sec1 - second_base;
  ret *= 32768;
  ret += f1;
#endif
  return ret;
}

uint64_t mos_get_ms_timestamp(void)
{
  TickType_t t = xTaskGetTickCount( );
  uint64_t r = ((uint64_t) t * 1000LL) / (uint64_t) configTICK_RATE_HZ;
  return r;
}

float mos_get_timestamp(void) // second
{
  float ret = mos_get_raw_timestamp();
  ret /= 32768.0;
  return ret;
}

#define SECONDS_IN_A_DAY (86400U)
#define SECONDS_IN_A_HOUR (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR (365U)
#define YEAR_RANGE_START (1970U)
#define YEAR_RANGE_END (2099U)

uint32_t mos_rtc_time_to_seconds(const mos_rtc_time_t *datetime)
{
  return 0;
#if 0
  if ( ! datetime) return -1;

  /* Number of days from begin of the non Leap-year*/
  /* Number of days from begin of the non Leap-year*/
  uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
  uint32_t seconds;

  /* Compute number of days from 1970 till given year*/
  seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
  /* Add leap year days */
  seconds += ((datetime->year / 4) - (1970U / 4));
  /* Add number of days till given month*/
  seconds += monthDays[datetime->month];
  /* Add days in given month. We subtract the current day as it is
  * represented in the hours, minutes and seconds field*/
  seconds += (datetime->day - 1);
  /* For leap year if month less than or equal to Febraury, decrement day counter*/
  if ((!(datetime->year & 3U)) && (datetime->month <= 2U)) {
    seconds--;
  }

  seconds = (seconds * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
    (datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

  return seconds;
#endif
}

void mos_seconds_to_rtc_time(uint32_t seconds, mos_rtc_time_t *datetime)
{
#if 0
  if ( ! datetime) return;

  uint32_t x;
  uint32_t secondsRemaining, days;
  uint16_t daysInYear;
  /* Table of days in a month for a non leap year. First entry in the table is not used,
  * valid months start from 1
  */
  uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

  /* Start with the seconds value that is passed in to be converted to date time format */
  secondsRemaining = seconds;

  /* Calcuate the number of days, we add 1 for the current day which is represented in the
  * hours and seconds field
  */
  days = secondsRemaining / SECONDS_IN_A_DAY + 1;

  /* Update seconds left*/
  secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

  /* Calculate the datetime hour, minute and second fields */
  datetime->hour = secondsRemaining / SECONDS_IN_A_HOUR;
  secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
  datetime->minute = secondsRemaining / 60U;
  datetime->second = secondsRemaining % SECONDS_IN_A_MINUTE;

  /* Calculate year */
  daysInYear = DAYS_IN_A_YEAR;
  datetime->year = YEAR_RANGE_START;
  while (days > daysInYear) {
    /* Decrease day count by a year and increment year by 1 */
    days -= daysInYear;
    datetime->year++;

    /* Adjust the number of days for a leap year */
    if (datetime->year & 3U) {
      daysInYear = DAYS_IN_A_YEAR;
    }
    else {
      daysInYear = DAYS_IN_A_YEAR + 1;
    }
  }

  /* Adjust the days in February for a leap year */
  if (!(datetime->year & 3U)) {
    daysPerMonth[2] = 29U;
  }

  for (x = 1U; x <= 12U; x++) {
    if (days <= daysPerMonth[x]) {
      datetime->month = x;
      break;
    }
    else {
      days -= daysPerMonth[x];
    }
  }

  datetime->day = days;
#endif
}

//-------------- timers ---------------
#define TIMER_MAGIC_WORD 0xb45ae83c

//static mos_mutex_t timer_mutex;
static void internal_slow_timer( mos_timer_id_t timer_id )
{
  int i, now;
  struct mos_slow_timer_st * tm_ptr;

  now = mos_get_rtc_time_in_seconds();

  for (i=0; i<SLOW_TIMER_POOL_SIZE; i++) {
    tm_ptr = &slow_timer_pool[i];
    if (tm_ptr->expiring != -1) {
      if (now >= tm_ptr->expiring) {
        timer_func_t callback;
        callback = (timer_func_t) tm_ptr->timer_id->user_callback;
        if (callback) callback(tm_ptr->timer_id->user_arg);
        tm_ptr->timer_id->magic = 0;
        mos_FREE(tm_ptr->timer_id);
        tm_ptr->expiring = -1; // empty slow timer
      }
    }
  }

  mos_timer_create_single_shot( 60000, internal_slow_timer, NULL );

}

static void init_timers(void)
{
  //timer_mutex  = mos_mutex_create();
  memset(slow_timer_pool, 0xff, sizeof(slow_timer_pool));
  mos_timer_create_single_shot( 60000, internal_slow_timer, NULL );

}

static void internal_timer_callback( TimerHandle_t native_timer_h )
{
  timer_func_t callback;

  //mos_mutex_lock(timer_mutex); Mutex would prevent to have a callback deleting any timer. Lets trust that the pending_destruction can avoid using mutex

  mos_timer_id_t this_timer = (mos_timer_id_t) pvTimerGetTimerID(native_timer_h);
  if (this_timer->magic != TIMER_MAGIC_WORD)
    return;

  if (  (this_timer->type == mos_TIMER_TYPE__SINGLE) ||
        (this_timer->type == mos_TIMER_TYPE__SINGLE_SLOW)) {
    xTimerDelete(this_timer->h, portMAX_DELAY);
    if (this_timer->pending_destruction == false) {
      callback = (timer_func_t) this_timer->user_callback;
      if (callback)
        callback(this_timer->user_arg);
    }
    this_timer->magic = 0; // prevent to have a garbage in the heap that looks like a good timer
    mos_FREE(this_timer);
  }
  else if (this_timer->type == mos_TIMER_TYPE__PERIODIC) {
    if (this_timer->pending_destruction == false) {
      // preserved periodic timer... just call back
      callback = (timer_func_t) this_timer->user_callback;
      if (callback)
        callback(this_timer->user_arg);
    }
    else {
      xTimerDelete(this_timer->h, portMAX_DELAY);
      this_timer->magic = 0; // prevent to have a garbage in the heap that looks like a good timer
      mos_FREE(this_timer);
    }

  }
  else {
    LOG_E("Timer type not yet implemented");
  }
  //mos_mutex_unlock(timer_mutex);
}

static mos_timer_id_t timer_create( int time_milliseconds, timer_func_t callback, void * arg, bool periodic, int tm_type )
{
  mos_timer_id_t this_timer = mos_MALLOC(sizeof(struct mos_timer_id_st));
  if ( ! this_timer ) {
    LOG_E("mos_timer_create_single_shot: no memo");
    return NULL;
  }
  this_timer->h = xTimerCreate( NULL,                                 //const char *pcTimerName,
                                pdMS_TO_TICKS(time_milliseconds),     //const TickType_t xTimerPeriod,
                                periodic,                             //const UBaseType_t uxAutoReload,
                                (void *) this_timer,                  //void * const pvTimerID,
                                internal_timer_callback);             //TimerCallbackFunction_t pxCallbackFunction );
  if ( ! this_timer->h ) {
    mos_FREE(this_timer);
    LOG_W("mos_timer_create_single_shot: fail to create native timer");
    return NULL;
  }
  this_timer->type = tm_type;
  this_timer->user_callback = (void *) callback;
  this_timer->user_arg = arg;
  this_timer->pending_destruction = false;

  if (xTimerStart(this_timer->h, portMAX_DELAY) != pdPASS) {
    xTimerDelete(this_timer->h, portMAX_DELAY);
    mos_FREE(this_timer);
    LOG_W("mos_timer_create_single_shot: fail to start native timer");
    return NULL;
  }
  this_timer->magic = TIMER_MAGIC_WORD;
  return this_timer;
}

mos_timer_id_t mos_timer_create_single_shot( int time_milliseconds, timer_func_t callback, void * arg )
{
  return timer_create( time_milliseconds, callback, arg, false, mos_TIMER_TYPE__SINGLE );
}

mos_timer_id_t mos_timer_create_periodic( int time_milliseconds, timer_func_t callback, void * arg )
{
  return timer_create( time_milliseconds, callback, arg, true, mos_TIMER_TYPE__PERIODIC );
}



void mos_timer_delete ( mos_timer_id_t timer_id )
{
  //mos_mutex_lock(timer_mutex);

  if (timer_id->magic != TIMER_MAGIC_WORD) {
    LOG_W("mos_timer_delete: invalid timer ID");
    return;
  }

  if (timer_id->type == 10) { // it is a slow timer
    slow_timer_pool[timer_id->slow_timer_idx].expiring = -1;     // related to RTC in seconds
    timer_id->magic = 0;
    mos_FREE(timer_id);
    return;
  }

  // if the callback is going to be called soon (within the next 5 seconds) then we just set the timer for destruction
  // and let the internal callback to clean up. User callback will not be called.

  TickType_t xRemainingTime;

  xRemainingTime = xTimerGetExpiryTime( timer_id->h ) - xTaskGetTickCount();
  if ( xRemainingTime < pdMS_TO_TICKS(5000) ) {
    timer_id->pending_destruction = true;
    return;
  }
  xTimerDelete(timer_id->h, portMAX_DELAY);
  timer_id->magic = 0; // prevent to have a garbage in the heap that looks like a good timer
  mos_FREE(timer_id);
  //mos_mutex_unlock(timer_mutex);
}

int mos_timer_get_remaining ( mos_timer_id_t timer_id )
{
  if (timer_id->magic != TIMER_MAGIC_WORD)
    return -1;

  int now = mos_get_rtc_time_in_seconds();

  if (timer_id->type == 10) { // it is a slow timer
    if (slow_timer_pool[timer_id->slow_timer_idx].expiring <= now)
      return 0;
    return (slow_timer_pool[timer_id->slow_timer_idx].expiring - now) / 60;
  }

  TickType_t xRemainingTime;

  xRemainingTime = xTimerGetExpiryTime( timer_id->h ) - xTaskGetTickCount();
  return pdMS_TO_TICKS(xRemainingTime);
}

mos_timer_id_t mos_slow_timer_create_single_shot( int time_minutes, timer_func_t callback, void * arg )
{
  int timer_idx, now;
  struct mos_slow_timer_st * tm_ptr = NULL;

  now = mos_get_rtc_time_in_seconds();

  // find an empty timer
  for (timer_idx=0; timer_idx<SLOW_TIMER_POOL_SIZE; timer_idx++) {
    tm_ptr = &slow_timer_pool[timer_idx];
    if (slow_timer_pool[timer_idx].expiring == -1) {
      tm_ptr = &slow_timer_pool[timer_idx];
      break;
    }
  }

  if (tm_ptr == NULL) {
    LOG_E("No slow timer available. Maybe need to increase SLOW_TIMER_POOL_SIZE or fix leaks");
    return NULL;
  }

  mos_timer_id_t this_timer = mos_MALLOC(sizeof(struct mos_timer_id_st));
  if ( ! this_timer ) {
    LOG_W("mos_timer_create_single_shot: no memo");
    tm_ptr->expiring = -1;
    return NULL;
  }

  this_timer->type = mos_TIMER_TYPE__SINGLE_SLOW; // slow timer
  this_timer->user_callback = (void *) callback;
  this_timer->user_arg = arg;
  this_timer->pending_destruction = false;
  this_timer->slow_timer_idx = timer_idx;

  tm_ptr->timer_id = this_timer;
  tm_ptr->expiring = now + 60 * time_minutes;

  this_timer->magic = TIMER_MAGIC_WORD;
  return this_timer;
}


void mos_reset(void)
{
   SRC_SetGeneralPurposeRegister(SRC, 4, 1);
   NVIC_SystemReset();
}


void mos_shutdown(void)
{
   LOG("=== Shutting down ===");
   mos_thread_sleep(100);
   taskENTER_CRITICAL(); // Disable Int's.
   BOARD_Shutdown();
}

#ifdef __cplusplus
extern "C" {
#endif


#endif
