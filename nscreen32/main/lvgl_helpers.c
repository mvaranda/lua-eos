/**
 * @file lvgl_helpers.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
//#include <stdio.h>
#include "lvgl_helpers.h"
#include "esp_log.h"
#include "log.h"

#include "ili9486.h"

/*********************
 *      DEFINES
 *********************/

 #define TAG "lvgl_helpers"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if CONFIG_INTERFACE_I2S
#define INTERFACE INTERFACE_I2S
#elif CONFIG_INTERFACE_GPIO
#define INTERFACE INTERFACE_GPIO
#elif CONFIG_INTERFACE_REG
#define INTERFACE INTERFACE_REG
#endif

static TFT_t dev;

/* Interface and driver initialization */
void lvgl_driver_init(void)
{
	//TFT_t dev;
	lcd_interface_cfg(&dev, INTERFACE);
	//lcd_interface_cfg(&dev, INTERFACE_GPIO);

    INIT_FUNCTION(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
 
    //ili9486_lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

}

TFT_t * lvgl_driver_get_dev(void)
{
    return &dev;
}
extern void ili9486_lcdDrawMultiPixels(TFT_t * dev, uint16_t x, uint16_t y, uint16_t size, uint16_t * colors);


static void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;
    lv_color_t color;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            //set_pixel(x, y, *color_p);  /* Put a pixel to the display.*/
            color = *color_p;

            lcdDrawPixel(&dev, x, y, color.full);
            color_p++;
        }
    }
}

void lvgl_driver_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map)
{

    LOG("lvgl_driver_flush\r\n");

    uint16_t x = area->x1;
    uint16_t y = area->y1;
    uint16_t size = (area->x2 - area->x1) * (area->y2 - area->y1);
    uint16_t * colors = (uint16_t *) color_map;

    LOG("\r\n"
        "  x1 = %d\r\n"
        "  x2 = %d\r\n"
        "  y1 = %d\r\n"
        "  y2 = %d\r\n"
        "  size = %d\r\n",
        area->x1, area->x2, area->y1, area->y2, size        );
#if 1
    my_disp_flush(drv, area, color_map);
#else
    //ili9486_lcdDrawMultiPixels(&dev, x, y, size,  colors);
    lcdDrawMultiPixels(&dev, x, y, size,  colors);
#endif

    lv_disp_flush_ready(drv);
}


