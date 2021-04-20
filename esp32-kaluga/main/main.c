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
#include "mos_test.h"

// #define SHOW_ANIMATED_SPLASH

#include "board.h"

#include "lua_eos.h"
#include "esp32_cmds.h"
#include "main_defs.h"

//#define MOS_TEST
#define USE_UART_FOR_CONSOLE

#ifdef HAS_LVGL
  #include "lvgl_lua.h"
  extern void lvgl_task_init();
#endif


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
        .partition_label = USER_PARTITION_LABLE,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    /*!< Use settings defined above to initialize and mount SPIFFS filesystem. */
    /*!< Note: esp_vfs_spiffs_register is an all-in-one convenience function. */
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));
    size_t total = 0, used = 0;
    ESP_ERROR_CHECK(esp_spiffs_info(USER_PARTITION_LABLE, &total, &used));

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
      fd = fopen(name, "r");
      
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
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
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

#ifndef USE_UART_FOR_CONSOLE
    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);
#endif

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Set command history size */
    linenoiseHistorySetMaxLen(10);

    /* Don't return empty lines */
    linenoiseAllowEmpty(false);

#if 0 //CONFIG_STORE_HISTORY
    /* Load command history from filesystem */
    linenoiseHistoryLoad(HISTORY_PATH);
#endif
}

static void lua_task_wrapper(void * args)
{
    luaTask(args);
    mos_thread_delete(0);
}

static void dump(char * s)
{
  printf("\r\n\r\nDump: \"%s\"\r\n", s);
  while(*s) {
    printf("%02X - ", *s++);
  }
  printf("\r\n\r\n");
}

#ifdef MACOS
  #define BACKSPACE_CHAR 0x7f
#else
  #define BACKSPACE_CHAR 0x08
#endif
//static char line_buf[SHELL_MAX_LINE_SIZE];
static int in_fd = -1;
static mos_queue_h_t console_input_q;

static void console_input_task(void * args)
{
  char c, dummy;
  int nread = 0;

#ifndef USE_UART_FOR_CONSOLE
  freopen(NULL, "rb", stdin);
#endif

  while(1) {
#ifdef USE_UART_FOR_CONSOLE
    nread = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, (void*) &c, 1, MOS_WAIT_FOREVER);
#else
    nread = read(in_fd, &c, 1);
#endif
    if (nread <= 0) {
      LOG_E("stdin read error");
      continue;
    }
    mos_queue_put (console_input_q, (const void *) &c);
  }
}

int get_console_byte(uint32_t timeout)
{
  char c;
  int r = mos_queue_get (console_input_q, &c, timeout);
  if (r == MOS_TRUE) {
    return c;
  }
  return -1;
}

void toConsoleByte(char byte)
{
  toConsoleBin(&byte, 1);
}

char * get_line(bool echo)
{
    // LOG("writeDataFromTerm: '%s', len=%u", data.toStdString().c_str(), data.length());
    static char msg[SHELL_MAX_LINE_SIZE] = {0};
    int msg_len;
    int c_int;
    char c;

    msg_len = 0;
    fflush(stdout);

    while(1) {
#if 1
    c_int = get_console_byte(MOS_WAIT_FOREVER);
    if (c_int < 0) {
        LOG_E("unexpected console input timeout");
        continue;
    }
    c = c_int & 0x000000ff;
    
#else
        int nread = read(in_fd, &c, 1);
        //LOG("char = %c\r\n", c);
        if (nread <= 0) {
            LOG_E("stdin read error");
            return NULL;
        }
#endif
        if (echo) {
          putchar(c);
          fflush(stdout);
        }

        // scan for native console switch pattern (3 scape characters):
        int esc_n = 0;
        char * ptr = msg;
        while(*ptr) {
            if (*ptr == SWITCH_SHELL_MODE_CHAR) {
                esc_n++;
                if (esc_n >= SWITCH_SHELL_MODE_COUNT) {
                    msg_len = 0;
                    memset(msg, 0, sizeof(msg));
                    switchNativeShellMode();
                }
            }
            else {
                esc_n = 0;
            }
            ptr++;
        }

       if (c == BACKSPACE_CHAR) { // note: 0x7f is for Mac
          msg[msg_len] = 0;
          if (msg_len > 1) {
              msg_len--;
          }
          continue;
       }

        //if (c == '\r') continue; // ignore CR
        msg[msg_len++] = c;
        if (c == '\n' || c == '\r') {
            msg[msg_len] = 0;
            return msg;
        }
        if (msg_len > (sizeof(msg) - 1) ) {
            LOG_W("line buffer overflow... ignoring line.");
            msg_len = 0;
        }
    }

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
    mos_thread_sleep(1000);

////// test ///////
    mosTest();
///////////////////

    eos_init();
    esp32_cmds_init();
    initialize_console();
    in_fd = fileno(stdin);
    if (in_fd < 0) {
        LOG_E("stdin not open");
        return NULL;
    }
    console_input_q = mos_queue_create ( SHELL_MAX_LINE_SIZE, 1);
    mos_thread_new( "console_input", console_input_task, 0, CONSOLE_INPUT_STACK_SIZE, CONSOLE_INPUT_TASK_PRIORITY);

#ifdef HAS_LVGL
    lvgl_task_init();
    //lvgl_lua_init();
    mos_thread_sleep(250); // let lvgl task start
#endif

    lua_task = mos_thread_new( "lua_task", lua_task_wrapper, 0, LUA_EOS_STACK_SIZE, LUA_TASK_PRIORITY);

        /* Main loop */
    printf("\r\nStarting Lua Shell\r\n\r\n");
    mos_thread_sleep(50); // let the lua print its prompt
    while(true) {
        char* line = get_line(true);
        if (line == NULL) { /* Break on EOF or error */
            printf("\r\n");
            continue;
        }

        printf("\r\n");
        sendTextToConsoleController(line); // line_buf);
    }

}

void toConsoleBin(char * msg, int len)
{
    /*uart_tx_chars*/ uart_write_bytes (CONFIG_ESP_CONSOLE_UART_NUM, (const char*) msg, len);
}
void toConsole(char * msg)
{
#ifdef USE_UART_FOR_CONSOLE
    /*uart_tx_chars*/ uart_write_bytes (CONFIG_ESP_CONSOLE_UART_NUM, (const char*) msg, strlen(msg));
#else
    printf(msg);
    fflush(stdout);
#endif
}

// fake POSIX's long sysconf(_SC_PAGESIZE) called by Doug Lea malloc.
long sysconf(int v)
{
    return 128;
}

