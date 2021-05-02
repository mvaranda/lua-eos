/*
 *  GT911 TP driver for arduino/esp8266/esp32
 * original auther: simon@yeacreate.com
 * port to C and using espressit driver: Marcelo Varanda
 * 
 */
#ifndef GT911_H
#define GT911_H

#include <stdbool.h>
#include <stdint.h>

typedef struct touch_info
{
    uint16_t x;
    uint16_t y;
    bool touch;
} touch_info_t;

void read_coordinate();
void update_config();
void touch_setup();
void get_touch(touch_info_t * info);

//======================================================== */
#endif
