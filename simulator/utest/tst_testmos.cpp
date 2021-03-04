#include <QtTest>
#include "mos_desktop_timer.h"

extern "C" {
//-------- mos_desktop_timer variables ------
extern uint64_t tick_counter;
extern list_entry_t list[NUM_MAX_TIMERS];
extern uint32_t list_num_entries;
extern list_entry_t * head;

//-------- mos_desktop_timer variables ------
extern list_entry_t * insert( uint64_t expire, timer_func_t callback, const void * arg);

//------- local test functions -------

static void reset_list(void){
    memset (list, 0, sizeof(list)); //[NUM_MAX_TIMERS];
    list_num_entries = 0;
    head = NULL;
}

static void timer_callback(mos_timer_id_t timer_id) {

}

static bool dumplist(void)  {
    list_entry_t * entry = head;
    uint64_t last_expire = 0;
    while (entry) {
        LOG("entry expire = %d", entry->expire);
        if (entry->expire < last_expire) {
            LOG_E("expire %d is lower than last_expire", entry->expire, last_expire);
            return false;
        }
        last_expire = entry->expire;
        entry++;
    }
    return true;
}

}

// add necessary includes here

class testMos : public QObject
{
    Q_OBJECT

public:
    testMos();
    ~testMos();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testMos::testMos()
{

}

testMos::~testMos()
{

}

void testMos::initTestCase()
{

}

void testMos::cleanupTestCase()
{

}



void testMos::test_case1()
{
  list_entry_t * entry;// = insert( 1000, timer_callback, NULL);
  int i;

#if 0
  //-------- check if list gets full -----
  for (i=0; i< NUM_MAX_TIMERS; i++) {
    entry = insert( 1000 * i, timer_callback, NULL);
    LOG("added entry %d", i+1);
    QVERIFY(entry != NULL);
  }
  entry = insert( 20000, timer_callback, NULL);
  QVERIFY(entry == NULL); // must fail

  reset_list(); // clear list
#endif
  //--------- test add lowest expire -----
  // fill half list
  for (i=0; i< NUM_MAX_TIMERS / 2; i++) {
    entry = insert( 1000 * i, timer_callback, NULL);
    QVERIFY(entry != NULL);
  }
  entry = insert( 500, timer_callback, NULL);
  QVERIFY(dumplist());




}

QTEST_APPLESS_MAIN(testMos)

#include "tst_testmos.moc"
