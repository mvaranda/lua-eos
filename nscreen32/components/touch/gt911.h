/*
 * GT911 TP driver for arduino/esp8266/esp32
 * auther: original: simon@yeacreate.com
 * I2C TP:
 * SCL:D22[GPIO22]
 * SDA:D21[GPIO21]
 * INT:D5
 * RST:D23
 */
#ifndef GT911_H
#define GT911_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_attr.h"

#define ICACHE_FLASH_ATTR /* */
//#define IRAM_ATTR /**/

#define TP_VERSION "0.0.0.1" //driver version


    
    /* =============================icache functions============================= */
    void ICACHE_FLASH_ATTR readi2c(uint16_t addr, uint8_t *inputbuff, size_t size);
    void ICACHE_FLASH_ATTR read_coordinate();
    void ICACHE_FLASH_ATTR update_config();
#ifdef _TP_DEBUG_
    void ICACHE_FLASH_ATTR read_firmware_info();
#endif
    /* ============================end icache functions========================== */

    /* =============================iram functions=============================== */
    /* ============================end iram functions============================ */

// public:
//     tp_service();
//     ~tp_service();

    /* =============================icache functions============================= */
    void ICACHE_FLASH_ATTR setup();
    bool ICACHE_FLASH_ATTR get_touch(uint16_t pressthou);

    /* ============================end icache functions========================== */

    /* =============================iram functions=============================== */
    /* ============================end iram functions============================ */

/* =============================public icache functions============================= */
/* ============================end public icache functions========================== */

/* =============================public iram functions=============================== */
static bool IRQ = false;
static void IRAM_ATTR irq_handle();
/* ============================end public iram functions============================ */
#endif
