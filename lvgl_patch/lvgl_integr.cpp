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

#include "ui_mainwindow.h"
#include "lvgl.h"
#include "lvgl_integr.h"
#include "log.h"

MainWindow * gMainObj;


static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last);


#ifdef __cplusplus
extern "C" {
#endif

extern void lv_ex_get_started_1(void);

static lv_indev_drv_t indev_drv;
static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];                     /*Declare a buffer for 1/10 screen size*/
static int touchpad_x = 0, touchpad_y = 0;
static int touchpad_state = LV_INDEV_STATE_REL;
static int touchpad_old_state = LV_INDEV_STATE_REL;

//----------- prototypes ----------
static void disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);
static bool lv_integr_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);


void lv_integr_run(void) {
    LOG("runNative from LOG");

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);    /*Initialize the display buffer*/

  lv_init();


  lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
  disp_drv.flush_cb = disp_flush;    /*Set your driver function*/
  disp_drv.buffer = &disp_buf;          /*Assign the buffer to the display*/
  lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

  lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;  /*See below.*/
  indev_drv.read_cb = lv_integr_input_read;              /*See below.*/
  /*Register the driver in LVGL and save the created input device object*/
  lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);

  lv_ex_get_started_1();

}

void lv_integr_update_pointer(int x, int y, int state)
{
    touchpad_x = x;
    touchpad_y = y;
    touchpad_state = state;
}

void lv_integr_timer(void) {
      static int cnt = 0;
      lv_tick_inc(LVGL_TICK_TIME);
      if (cnt++ > 4) {
        cnt = 0;
        lv_task_handler();
      }

}

//-------------- local functions ------------

static void disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
  bool last = lv_disp_flush_is_last( disp);
  updateDisplay(area, color_p, last);
  lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}

static bool lv_integr_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
  Q_UNUSED(drv);
    bool ret = false;
  data->point.x = touchpad_x;
  data->point.y = touchpad_y;
  data->state = touchpad_state; //LV_INDEV_STATE_REL; //LV_INDEV_STATE_PR or LV_INDEV_STATE_REL;
  if ( touchpad_state != touchpad_old_state) {
      touchpad_old_state = touchpad_state;
      LOG("mouse down: x=%d y=%d", touchpad_x, touchpad_y);
  }
  return ret; /*No buffering now so no more data read*/
}




#ifdef __cplusplus
};
#endif

//----------- C++ functions ---------

static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last)
{
    int32_t x, y;
    lv_color_t pixel;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            pixel = *color_p;
            gMainObj->display_image.setPixelColor(x,y, (QRgb) (*color_p).full);
            color_p++;
        }
    }
    if (last) {
        gMainObj->ui->lb_display->setPixmap(QPixmap::fromImage(gMainObj->display_image));
    }



}

