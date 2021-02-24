#ifndef __LVGL_INTEGR_H__
#define __LVGL_INTEGR_H__

#include "mainwindow.h"

#define LVGL_TICK_TIME 10 // 10 milliseconds

extern MainWindow * gMainObj;

#ifdef __cplusplus
extern "C" {
#endif

void lv_integr_run(void);
void lv_integr_timer(void);
void lv_integr_update_pointer(int x, int y, int state);

#ifdef __cplusplus
};
#endif

//--------------------------------------------------------
#endif // __LVGL_INTEGR_H__



