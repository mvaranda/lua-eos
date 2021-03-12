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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <memory.h>

//#include "mos.h"

#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "lua_eos.h"
//#include "ui_mainwindow.h"
#include "lvgl.h"
//#include "lvgl_integr.h"
//#include "log.h"

#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "lua_eos.h"



//static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last);


#ifdef __cplusplus
extern "C" {
#endif

//----------- prototypes ----------


// bindings
/*
int lv_img_create(lv_scr_act(), NULL);

lv_img_set_src(logo_obj, frames[0]);

lv_obj_align(logo_obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

lv_task_t * task = lv_task_create(logo_task, LOGO_TIMER, LV_TASK_PRIO_MID, logo_obj);
lv_task_once(task);




    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     //Add a button the current screen
    lv_obj_set_pos(btn, 10, 10);                            // Set its position
    lv_obj_set_size(btn, 120, 50);                          // Set its size
    lv_obj_set_event_cb(btn, btn_event_cb);                 // Assign a callback to the button

    lv_obj_t * label = lv_label_create(btn, NULL);          // Add a label to the button
    lv_label_set_text(label, "Button");                     //Set the labels text
*/

static int bind_lv_img_create(lua_State *L)
{
    // lv_obj_t *lv_img_create(lv_obj_t *par, const lv_obj_t *copy)
    void * par = lua_touserdata(L,1);
    void * copy = lua_touserdata(L,2);

    lv_obj_t * obj = lv_img_create(par, (const lv_obj_t *) copy);
    LOG("lv_img_create creted: 0x%x", obj);
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

void lvgl_lua_init(lua_State *L)
{
    lua_pushcfunction(L, bind_lv_img_create);
    lua_setglobal(L, "lv_img_create");

}


#ifdef __cplusplus
extern }
#endif



