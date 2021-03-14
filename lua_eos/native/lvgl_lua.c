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

#include "lvgl.h"


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
//typedef void (*create_func_prototype_t)(void *obj, lv_event_t event);
typedef lv_obj_t * (*create_func_prototype_t) (lv_obj_t *parent, const lv_obj_t *copy);

typedef struct create_func_st {
    uint32_t                    id;
    create_func_prototype_t     func;
} create_func_t;

static const create_func_t create_func_info[] = {
  { 0, lv_obj_create },             // { name = "lv_obj_create",           func_id = 0 },
  { 1, lv_label_create },           // { name = "lv_lable_create",         func_id = 1 },
  { 2, lv_btn_create },             // { name = "lv_btn_create",           func_id = 2 },
  { 3, NULL}
};

#define CREATE_FUNC_INFO_LEN ((sizeof(create_func_info) / sizeof(create_func_t)) - 1)

static int bind_lv_create(lua_State *L)
{
    long long func_id = lua_tointeger(L,1);
    void * par = lua_touserdata(L,2);
    void * copy = lua_touserdata(L,3);

    if (func_id >= CREATE_FUNC_INFO_LEN || func_id < 0) {
        LOG_E("bind_lv_create: invalid func_id %d", func_id);
        lua_pushnil(L);
        return 1;
    }

    create_func_prototype_t f = create_func_info[func_id].func;

    lv_obj_t * obj = f(par, (const lv_obj_t *) copy);
    LOG("bind_lv_create creted: 0x%x", obj);
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

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

static int bind_lv_btn_create(lua_State *L)
{
    // lv_obj_t *lv_img_create(lv_obj_t *par, const lv_obj_t *copy)
    void * par = lua_touserdata(L,1);
    void * copy = lua_touserdata(L,2);

    lv_obj_t * obj = lv_btn_create(par, (const lv_obj_t *) copy);
    LOG("lv_btn_create creted: 0x%x", obj);
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

static int bind_lv_scr_act(lua_State *L)
{
    void * obj = lv_scr_act();
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

static int bind_lv_obj_set_pos(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    long long x = lua_tointeger(L,2);
    long long y = lua_tointeger(L,3);
    lv_obj_set_pos(obj, x, y);
    return 0;
}

static int bind_lv_obj_set_size(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    long long x = lua_tointeger(L,2);
    long long y = lua_tointeger(L,3);
    lv_obj_set_size(obj, x, y);
    return 0;
}


static int bind_lv_label_create(lua_State *L)
{
    // lv_obj_t *lv_img_create(lv_obj_t *par, const lv_obj_t *copy)
    void * par = lua_touserdata(L,1);
    void * copy = lua_touserdata(L,2);

    lv_obj_t * obj = lv_label_create(par, (const lv_obj_t *) copy);
    LOG("lv_lable_create creted: 0x%x", obj);
    if (! obj) {
        lua_pushnil(L);
    }
    else {
        lua_pushlightuserdata(L, obj);
    }
    return 1;
}

static int bind_lv_label_set_text(lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    const char * txt = lua_tostring(L,2);
    lv_label_set_text(obj, txt);
    return 0;
}


void lvgl_lua_init(lua_State *L)
{
    lua_pushcfunction(L, bind_lv_create);
    lua_setglobal(L, "bind_lv_create");

//    lua_pushcfunction(L, bind_lv_img_create);
//    lua_setglobal(L, "lv_img_create");

    lua_pushcfunction(L, bind_lv_scr_act);
    lua_setglobal(L, "lv_scr_act");

//    lua_pushcfunction(L, bind_lv_btn_create);
//    lua_setglobal(L, "lv_btn_create");

    lua_pushcfunction(L, bind_lv_obj_set_pos);
    lua_setglobal(L, "lv_obj_set_pos");

    lua_pushcfunction(L, bind_lv_obj_set_size);
    lua_setglobal(L, "lv_obj_set_size");

//    lua_pushcfunction(L, bind_lv_label_create);
//    lua_setglobal(L, "lv_label_create");

    lua_pushcfunction(L, bind_lv_label_set_text);
    lua_setglobal(L, "lv_label_set_text");



}


#ifdef __cplusplus
extern }
#endif



