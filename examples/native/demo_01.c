
#include <stdio.h>
#include "lv_conf.h"
#include "lvgl.h"
#include "lua.h"
#include "lua_eos.h"

//

static void btn_event_cb(lv_obj_t * btn, lv_event_t event)
{
    printf("btn_event_cb EVENT %d\n", event);
    if(event == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, NULL);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

/**
 * Create a button with a label and react on Click event.
 */

void lv_ex_get_started_2(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
}
#

extern const lv_img_dsc_t logo_0002;
extern const lv_img_dsc_t logo_0006;
extern const lv_img_dsc_t logo_0010;
extern const lv_img_dsc_t logo_0014;
extern const lv_img_dsc_t logo_0018;
extern const lv_img_dsc_t logo_0022;
extern const lv_img_dsc_t logo_0026;
extern const lv_img_dsc_t logo_0030;
extern const lv_img_dsc_t logo_0034;
extern const lv_img_dsc_t logo_0038;
extern const lv_img_dsc_t logo_0042;
extern const lv_img_dsc_t logo_0046;
extern const lv_img_dsc_t logo_0050;
extern const lv_img_dsc_t logo_0054;
extern const lv_img_dsc_t logo_0058;
extern const lv_img_dsc_t logo_0062;
extern const lv_img_dsc_t logo_0066;
extern const lv_img_dsc_t logo_0070;

#define N_FRAMES 18

static const lv_img_dsc_t * frames[N_FRAMES] = {
    &logo_0002,
    &logo_0006,
    &logo_0010,
    &logo_0014,
    &logo_0018,
    &logo_0022,
    &logo_0026,
    &logo_0030,
    &logo_0034,
    &logo_0038,
    &logo_0042,
    &logo_0046,
    &logo_0050,
    &logo_0054,
    &logo_0058,
    &logo_0062,
    &logo_0066,
    &logo_0070,

};

lv_obj_t * logo_obj;

#define LOGO_TIMER 120
#define LOGO_WAIT 15


static void logo_task(void * arg)
{
  static int i = 0;

  if (i < N_FRAMES) {
        lv_img_set_src(logo_obj, frames[i]);
        lv_task_t * task = lv_task_create(logo_task, LOGO_TIMER, LV_TASK_PRIO_MID, logo_obj);
        lv_task_once(task);
        i++;
  }
  else if (i < N_FRAMES + LOGO_WAIT) {
    lv_task_t * task = lv_task_create(logo_task, LOGO_TIMER, LV_TASK_PRIO_MID, logo_obj);
    lv_task_once(task);
    i++;
  }
  else {
      lv_obj_clean(lv_scr_act());
      add_text_event( EV_SYS_SPLASH_DONE, "done");
      //lv_ex_get_started_2();
  }

}

void lv_ex_get_started_1(void)
{
  int i;
  logo_obj = lv_img_create(lv_scr_act(), NULL);

  /*From variable*/
  lv_img_set_src(logo_obj, frames[0]);

  lv_obj_align(logo_obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

  lv_task_t * task = lv_task_create(logo_task, LOGO_TIMER, LV_TASK_PRIO_MID, logo_obj);
  lv_task_once(task);

}

int bind_lv_show_splash(lua_State *L)
{
    lv_ex_get_started_1();
    return 0;
}

void lvgl_splash_init(lua_State *L)
{
    lua_pushcfunction(L, bind_lv_show_splash);
    lua_setglobal(L, "show_splash");
}



