/* Camera Example

    This example code is in the Public Domain (or CC0 licensed, at your option.)
    Unless required by applicable law or agreed to in writing, this
    software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "lcd.h"
#include "jpeg.h"

#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"

#include "mos.h"

// #define SHOW_ANIMATED_SPLASH

#include "board.h"

#include "lua_eos.h"

#define MOS_TEST

static const char *TAG = "main";

#define IMAGE_MAX_SIZE (100 * 1024)/**< The maximum size of a single picture in the boot animation */
#define IMAGE_WIDTH    320 /*!< width of jpeg file */
#define IMAGE_HIGHT    240 /*!< height of jpeg file */

static     char name[64];

static mos_thread_h_t lua_task;

static void render_splash_animation(bool animation)
{
    ESP_LOGI(TAG, "LCD photo test....");
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    /*!< Use settings defined above to initialize and mount SPIFFS filesystem. */
    /*!< Note: esp_vfs_spiffs_register is an all-in-one convenience function. */
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));
    size_t total = 0, used = 0;
    ESP_ERROR_CHECK(esp_spiffs_info(NULL, &total, &used));

    uint8_t *img = NULL;
    uint8_t *buf = malloc(IMAGE_MAX_SIZE);
    int width = 0, height = 0;

    FILE *fd;
    int i = 2, read_bytes;

    if (animation == false) i = 70; // last frame
  
    while (i<73) {
      read_bytes = 0;
      width = 0;
      height = 0;
  
      sprintf(name,"/spiffs/logo_%04d.jpg", i);
      // ESP_LOGI(TAG, "open file: \"%s\"", name);
      fd = fopen(name, "r");
      //fd = fopen("/spiffs/image.jpg", "r");
      
      if (! fd) {
        ESP_LOGI(TAG, "Fail to open file \"%s\"", name);
        free(buf);
        return;
      }

      read_bytes = fread(buf, 1, IMAGE_MAX_SIZE, fd);
      // ESP_LOGI(TAG, "spiffs:read_bytes:%d  fd: %p", read_bytes, fd);
      fclose(fd);

      img = jpeg_decode(buf, &width, &height);
      lcd_set_index(0, 0, IMAGE_WIDTH - 1, IMAGE_HIGHT - 1);
      lcd_write_data(img, IMAGE_WIDTH * IMAGE_HIGHT * sizeof(uint16_t));
      free(img);
      //vTaskDelay(5 / portTICK_RATE_MS); // no delay as the processor is lower than the frame-rate.
      i = i + 4;
    }
    free(buf);
}

static void initialize_console(void)
{
    /* Drain stdout before reconfiguring it */
    fflush(stdout);
    fsync(fileno(stdout));

    /* Disable buffering on stdin */
    setvbuf(stdin, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CRLF);

    /* Configure UART. Note that REF_TICK is used so that the baud rate remains
     * correct while APB frequency is changing in light sleep mode.
     */
    const uart_config_t uart_config = {
            .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
        .source_clk = UART_SCLK_REF_TICK,
#else
        .source_clk = UART_SCLK_XTAL,
#endif
    };
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
            256, 0, 0, NULL, 0) );
    ESP_ERROR_CHECK( uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uart_config) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Initialize the console */
//     esp_console_config_t console_config = {
//             .max_cmdline_args = 8,
//             .max_cmdline_length = 256,
// #if CONFIG_LOG_COLORS
//             .hint_color = atoi(LOG_COLOR_CYAN)
// #endif
//     };
//     ESP_ERROR_CHECK( esp_console_init(&console_config) );

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Tell linenoise where to get command completions and hints */
 //   linenoiseSetCompletionCallback(&esp_console_get_completion);
 //   linenoiseSetHintsCallback((linenoiseHintsCallback*) &esp_console_get_hint);

    /* Set command history size */
    linenoiseHistorySetMaxLen(100);

    /* Don't return empty lines */
    linenoiseAllowEmpty(false);

#if 0 //CONFIG_STORE_HISTORY
    /* Load command history from filesystem */
    linenoiseHistoryLoad(HISTORY_PATH);
#endif
}

//////////////////////////// MOS Test ///////////////////////
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
static void mosTest()
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

}

#else
static void mosTest(){} // do nothing
#endif
/////////////////////////// END of MOS Test /////////////////////

static void lua_task_wrapper(void * args)
{
    luaTask(args);
    mos_thread_delete(0);
}

void app_main()
{
    lcd_config_t lcd_config = {
#ifdef CONFIG_LCD_ST7789
        .clk_fre         = 80 * 1000 * 1000, /*!< ILI9341 Stable frequency configuration */
#endif
#ifdef CONFIG_LCD_ILI9341
        .clk_fre         = 40 * 1000 * 1000, /*!< ILI9341 Stable frequency configuration */
#endif
        .pin_clk         = LCD_CLK,
        .pin_mosi        = LCD_MOSI,
        .pin_dc          = LCD_DC,
        .pin_cs          = LCD_CS,
        .pin_rst         = LCD_RST,
        .pin_bk          = LCD_BK,
        .max_buffer_size = 2 * 1024,
        .horizontal      = 2 /*!< 2: UP, 3: DOWN */
    };

    lcd_init(&lcd_config);

    /*< Show splash animation */
#ifdef SHOW_ANIMATED_SPLASH
    render_splash_animation(true);
#else
    render_splash_animation(false);
#endif

////// test ///////
    mosTest();
///////////////////


    initialize_console();

    lua_task = mos_thread_new( "lua_task", lua_task_wrapper, 0, 6000, 6 );

        /* Main loop */
    printf("Starting Lua Shell\r\n");
    while(true) {
        /* Get a line using linenoise.
         * The line is returned when ENTER is pressed.
         */
        char* line = linenoise("lua> ");
        if (line == NULL) { /* Break on EOF or error */
            printf("\r\n");
            continue;
        }
        printf("line: %s\r\n", line);
        linenoiseFree(line);
    }

}

void toConsole(char * msg)
{
    printf(msg);
}

