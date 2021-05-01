/**
 * @file lvgl_helpers.h
 */

#ifndef LVGL_HELPERS_H
#define LVGL_HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "lcd_com.h"
#include "lcd_lib.h"
#include "lvgl.h"



#if CONFIG_INTERFACE_I2S
#define INTERFACE INTERFACE_I2S
#elif CONFIG_INTERFACE_GPIO
#define INTERFACE INTERFACE_GPIO
#elif CONFIG_INTERFACE_REG
#define INTERFACE INTERFACE_REG
#endif

#if CONFIG_ILI9225
#include "ili9225.h"
#define DRIVER "ILI9225"
#define INIT_FUNCTION(a, b, c, d, e) ili9225_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9226
#include "ili9225.h"
#define DRIVER "ILI9226"
#define INIT_FUNCTION(a, b, c, d, e) ili9225_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9325
#include "ili9325.h"
#define DRIVER "ILI9325"
#define INIT_FUNCTION(a, b, c, d, e) ili9325_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9327
#include "ili9327.h"
#define DRIVER "ILI9327"
#define INIT_FUNCTION(a, b, c, d, e) ili9327_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9340
#include "ili9341.h"
#define DRIVER "ILI9340"
#define INIT_FUNCTION(a, b, c, d, e) ili9341_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9341
#include "ili9341.h"
#define DRIVER "ILI9341"
#define INIT_FUNCTION(a, b, c, d, e) ili9341_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9342
#include "ili9342.h"
#define DRIVER "ILI9342"
#define INIT_FUNCTION(a, b, c, d, e) ili9342_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9481
#include "ili9481.h"
#define DRIVER "ILI9481"
#define INIT_FUNCTION(a, b, c, d, e) ili9481_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9486
#include "ili9486.h"
#define DRIVER "ILI9486"
#define INIT_FUNCTION(a, b, c, d, e) ili9486_lcdInit(a, b, c, d, e)

#elif CONFIG_ILI9488
#include "ili9488.h"
#define DRIVER "ILI9488"
#define INIT_FUNCTION(a, b, c, d, e) ili9488_lcdInit(a, b, c, d, e)

#elif CONFIG_SPFD5408
#include "ili9325.h"
#define DRIVER "SPFD5408"
#define INIT_FUNCTION(a, b, c, d, e) ili9325_lcdInit(a, b, c, d, e)

#elif CONFIG_R61505
#include "ili9325.h"
#define DRIVER "R61505"
#define INIT_FUNCTION(a, b, c, d, e) ili9325_lcdInit(a, b, c, d, e)

#elif CONFIG_R61509
#include "r61509.h"
#define DRIVER "R61509"
#define INIT_FUNCTION(a, b, c, d, e) r61509_lcdInit(a, b, c, d, e)

#elif CONFIG_LGDP4532
#include "lgdp4532.h"
#define DRIVER "LGDP4532"
#define INIT_FUNCTION(a, b, c, d, e) lgdp4532_lcdInit(a, b, c, d, e)

#elif CONFIG_ST7775
#include "ili9225.h"
#define DRIVER "ST7775"
#define INIT_FUNCTION(a, b, c, d, e) ili9225_lcdInit(a, b, c, d, e)

#elif CONFIG_ST7781
#include "st7781.h"
#define DRIVER "ST7781"
#define INIT_FUNCTION(a, b, c, d, e) st7781_lcdInit(a, b, c, d, e)

#elif CONFIG_ST7783
#include "st7781.h"
#define DRIVER "ST7783"
#define INIT_FUNCTION(a, b, c, d, e) st7781_lcdInit(a, b, c, d, e)

#elif CONFIG_ST7796
#include "ili9486.h"
#define DRIVER "ST7796"
#define INIT_FUNCTION(a, b, c, d, e) ili9486_lcdInit(a, b, c, d, e)

#elif CONFIG_S6D1121
#include "s6d1121.h"
#define DRIVER "S6D1121"
#define INIT_FUNCTION(a, b, c, d, e) s6d1121_lcdInit(a, b, c, d, e)

#elif CONFIG_HX8347A
#include "hx8347.h"
#define DRIVER "HX8347A"
#define INIT_FUNCTION(a, b, c, d, e) hx8347_lcdInit(a, b, c, d, e)

#elif CONFIG_HX8347D
#include "hx8347.h"
#define DRIVER "HX8347D"
#define INIT_FUNCTION(a, b, c, d, e) hx8347_lcdInit(a, b, c, d, e)

#elif CONFIG_HX8347G
#include "hx8347.h"
#define DRIVER "HX8347G"
#define INIT_FUNCTION(a, b, c, d, e) hx8347_lcdInit(a, b, c, d, e)

#elif CONFIG_HX8347I
#include "hx8347.h"
#define DRIVER "HX8347I"
#define INIT_FUNCTION(a, b, c, d, e) hx8347_lcdInit(a, b, c, d, e)

#elif
  #error "No LCD driver defined"

#endif


#ifdef BOARD_NSCREEN32
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
void lvgl_driver_init(void);
TFT_t * lvgl_driver_get_dev(void);
void lvgl_driver_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map);


#else

#include "lvgl_spi_conf.h"
#include "lvgl_tft/disp_driver.h"
#include "lvgl_touch/touch_driver.h"

/*********************
 *      DEFINES
 *********************/

/* DISP_BUF_SIZE value doesn't have an special meaning, but it's the size
 * of the buffer(s) passed to LVGL as display buffers. The default values used
 * were the values working for the contributor of the display controller.
 *
 * As LVGL supports partial display updates the DISP_BUF_SIZE doesn't
 * necessarily need to be equal to the display size.
 *
 * When using RGB displays the display buffer size will also depends on the
 * color format being used, for RGB565 each pixel needs 2 bytes.
 * When using the mono theme, the display pixels can be represented in one bit,
 * so the buffer size can be divided by 8, e.g. see SSD1306 display size. */
#if defined (CONFIG_CUSTOM_DISPLAY_BUFFER_SIZE)
#define DISP_BUF_SIZE   CONFIG_CUSTOM_DISPLAY_BUFFER_BYTES
#else
#if defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7735S
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7796S
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_HX8357
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SH1107
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * LV_VER_RES_MAX)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9481
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9486
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9488
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9341
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306
#if defined (CONFIG_LV_THEME_MONO)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * (LV_VER_RES_MAX / 8))
#else
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * LV_VER_RES_MAX)
#endif
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_FT81X)
#define DISP_BUF_LINES  40
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * DISP_BUF_LINES)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820)
#define DISP_BUF_SIZE (LV_VER_RES_MAX * IL3820_COLUMNS)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_RA8875
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_GC9A01)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A)
#define DISP_BUF_SIZE ((LV_VER_RES_MAX * LV_VER_RES_MAX) / 8) // 5KB
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D)
#define DISP_BUF_SIZE ((LV_VER_RES_MAX * LV_VER_RES_MAX) / 8) // 2888 bytes
#else
#error "No display controller selected"
#endif
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* Initialize detected SPI and I2C bus and devices */
void lvgl_driver_init(void);


/* Initialize SPI master  */
bool lvgl_spi_driver_init(int host, int miso_pin, int mosi_pin, int sclk_pin,
    int max_transfer_sz, int dma_channel, int quadwp_pin, int quadhd_pin);
/* Initialize I2C master  */
bool lvgl_i2c_driver_init(int port, int sda_pin, int scl_pin, int speed);

/**********************
 *      MACROS
 **********************/

#endif /* #ifdef BOARD_NSCREEN32 */


#ifdef __cplusplus
} /* extern "C" */
#endif



#endif /* LVGL_HELPERS_H */
