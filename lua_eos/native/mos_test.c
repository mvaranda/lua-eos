
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
#include "mos_test.h"


#ifdef MOS_TEST

#define UNITY_TEST_ASSERT(c,l,m) do { \
  if (c) break; \
  printf("Fail line %d: %s\r\n", l, m); \
} while(0)

#define UNITY_TEST_ASSERT_RET(c,l,m) do { \
  if (c) break; \
  printf("Fail line %d: %s\r\n", l, m); \
  return; \
} while(0)

#define TEST_ASSERT(condition,m)          UNITY_TEST_ASSERT(    (condition), __LINE__, m)
#define TEST_ASSERT_FALSE(condition,m)    UNITY_TEST_ASSERT(   !(condition), __LINE__, m)
#define TEST_ASSERT_NULL(pointer,m)       UNITY_TEST_ASSERT(    (pointer == NULL), __LINE__, m)
#define TEST_ASSERT_RET(condition,m)      UNITY_TEST_ASSERT_RET((condition), __LINE__, m)

static mos_queue_h_t myQ;
static mos_mutex_h_t mutex;
static uint32_t cnt1 = 0;
static uint32_t cnt2 = 0;
static bool mos_test_end = false;
//mos_queue_create ( uint32_t len, uint32_t item_size);

static void myQueuReader(void * params)
{
    uint32_t entry;
    int ret;
    uint32_t stop_val = 0xffffffff;
    while(1) {
        ret = mos_queue_get(myQ, &entry, MOS_WAIT_FOREVER);
        if (ret == MOS_TRUE) {
            if (entry == stop_val) {
                printf("myQueuReader: got stop val\r\n");
                mos_thread_delete(0);
                return;
            }
            printf("myQueuReader: got value %d\r\n", entry);
        }
        else {
            LOG_E("myQueuReader: error\r\n");
        }
    }

}

static void myTimerCallback( mos_timer_id_t id) {
  if (mos_test_end) {
      printf("myTimerCallback: timer id %d, but test MOS is ending\r\n", id);
      uint32_t stop_val = 0xffffffff;
      mos_queue_put (myQ, &stop_val);
      return;
  }

  if (id == 1) {
    mos_queue_put (myQ, &cnt1);
    cnt1++;

    if (! mos_timer_create_single_shot( 1000, myTimerCallback, 1 )) {
        LOG_E("fail to to create timer 1");
    }

  }
  else if (id == 2) {
    mos_queue_put (myQ, &cnt2);
    cnt2++;
    if (! mos_timer_create_single_shot( 2000, myTimerCallback, 2 )) {
        LOG_E("fail to to create timer 2");
    }
  }
  else {
      printf("bad timer ID");
  }
}
#define RET_IF_NULL(ptr) do { if (ptr == NULL) { LOG_E("%s: NULL pointer at %d\r\n", __func__, __LINE__); return;} } while(0)

static void myTestTask(void * params)
{
    int c = 0;
    printf("Starting myTestTask...\r\n");

    mos_mutex_lock(mutex);
    cnt1 = 1;
    cnt2 = 1001;
    mos_mutex_unlock(mutex);

    if (! mos_timer_create_single_shot( 1000, myTimerCallback, 1 )) {
        LOG_E("fail to to create timer 1");
    }
    if (! mos_timer_create_single_shot( 2000, myTimerCallback, 2 )) {
        LOG_E("fail to to create timer 2");
    }

    while ( ! mos_test_end) {
        printf("myTestTask: c = %d\r\n", c++);
        mos_thread_sleep(10000);
    }
    mos_thread_delete(0);
}

void mosTest(void)
{
    //TEST_ASSERT((1 != 1),"");
    myQ = mos_queue_create ( 5, sizeof(uint32_t));
    TEST_ASSERT_RET(myQ, "Fail to create queue");
    mutex = mos_mutex_create();
    TEST_ASSERT_RET(mutex, "Fail to create mutex");

    // get max memo allocation
    int m = 0;
    int s = 1024;
    void * ptr;
    while ( (ptr = MOS_MALLOC(s)) != NULL) {
        m = s;
        s *= 2;
        MOS_FREE(ptr);
    }
    printf("Max heap allocation = %d\r\n", m); // 1048576 about 1~2 mega.
    TEST_ASSERT_RET(m >= 1048576, "Heap size lower than expected");


    // take mutex
    mos_mutex_lock(mutex);

    mos_thread_h_t task1 = mos_thread_new( "myTestTask", myTestTask, 0, 3000, 6 );
    TEST_ASSERT_RET(task1, "Fail to create task1");
    mos_thread_h_t task2 = mos_thread_new( "myQueuReader", myQueuReader, 0, 3000, 6 );
    TEST_ASSERT_RET(task2, "Fail to create task2");

    // sleep to check that myTestTask is locked
    mos_thread_sleep(10);
    TEST_ASSERT_RET(cnt1 == 0, "mutex fail to block myTestTask");
    mos_mutex_unlock(mutex);
    mos_thread_sleep(10);
    TEST_ASSERT_RET(cnt1 > 0, "mutex fail to unblock myTestTask");

    mos_thread_sleep(7000);

    printf("cnt1 = %d, cnt2 = %d\r\n", cnt1, cnt2);
    // cnt1 = 8, cnt2 = 1004
    TEST_ASSERT_RET(cnt1 == 8, "undexpected cnt1 value, it should be 8");
    TEST_ASSERT_RET(cnt2 == 1004, "undexpected cnt2 value, it should be 1004");
    mos_test_end = true; // end test
}

#else
void mosTest(void){} // do nothing
#endif
