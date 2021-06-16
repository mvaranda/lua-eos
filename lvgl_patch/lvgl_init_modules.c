
 /*
 ###############################################################
 #
 #                 This code is part of LUA_EOS
 #
 # Copyrights 2021 - Varanda Labs Inc.
 #
 # License:
 #   Creative Commons: CC BY-NC-SA 4.0
 #   Attribution-NonCommercial-ShareAlike 4.0 International
 #   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 #
 #   Note: for purchasing a commertial license contact:
 #     m@varanda.ca
 #
 ###############################################################
*/

#include "log.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"
//#include "lv_font_loader.h"

#ifdef __cplusplus
extern "C" {
#endif

//#include "bind_lv_api_map.h"
//#include "bind_lv_conf_kconfig.h"
//#include "bind_lv_conf_internal.h"
//#include "bind_lv_group.h"
#include "bind_lv_obj.h"
//#include "bind_lv_obj_style_dec.h"
#include "bind_lv_disp.h"
//#include "bind_lv_indev.h"
#include "bind_lv_style.h"
//#include "bind_lv_refr.h"
//#include "bind_lv_printf.h"
//#include "bind_lv_templ.h"
//#include "bind_lv_async.h"
//#include "bind_lv_math.h"
//#include "bind_lv_anim.h"
//#include "bind_lv_bidi.h"
//#include "bind_lv_gc.h"
//#include "bind_lv_debug.h"
//#include "bind_lv_task.h"
//#include "bind_lv_txt.h"
//#include "bind_lv_utils.h"
//#include "bind_lv_types.h"
//#include "bind_lv_mem.h"
//#include "bind_lv_txt_ap.h"
//#include "bind_lv_fs.h"
//#include "bind_lv_area.h"
//#include "bind_lv_log.h"
//#include "bind_lv_ll.h"
//#include "bind_lv_color.h"
#include "bind_lv_linemeter.h"
#include "bind_lv_slider.h"
//#include "bind_lv_img.h"
//#include "bind_lv_imgbtn.h"
//#include "bind_lv_list.h"
//#include "bind_lv_table.h"
#include "bind_lv_arc.h"
#include "bind_lv_bar.h"
//#include "bind_lv_dropdown.h"
//#include "bind_lv_canvas.h"
//#include "bind_lv_objx_templ.h"
//#include "bind_lv_calendar.h"
#include "bind_lv_switch.h"
//#include "bind_lv_tabview.h"
#include "bind_lv_checkbox.h"
//#include "bind_lv_line.h"
//#include "bind_lv_spinner.h"
#include "bind_lv_label.h"
#include "bind_lv_keyboard.h"
//#include "bind_lv_page.h"
//#include "bind_lv_cpicker.h"
//#include "bind_lv_gauge.h"
//#include "bind_lv_win.h"
#include "bind_lv_btn.h"
//#include "bind_lv_roller.h"
//#include "bind_lv_objmask.h"
//#include "bind_lv_chart.h"
#include "bind_lv_textarea.h"
//#include "bind_lv_msgbox.h"
//#include "bind_lv_spinbox.h"
//#include "bind_lv_led.h"
//#include "bind_lv_tileview.h"
//#include "bind_lv_btnmatrix.h"
//#include "bind_lv_cont.h"
//#include "bind_lv_theme_mono.h"
//#include "bind_lv_theme_empty.h"
//#include "bind_lv_theme_template.h"
//#include "bind_lv_theme.h"
//#include "bind_lv_theme_material.h"
//#include "bind_lv_hal_tick.h"
//#include "bind_lv_hal.h"
//#include "bind_lv_hal_indev.h"
//#include "bind_lv_hal_disp.h"
//#include "bind_lv_draw_label.h"
//#include "bind_lv_img_cache.h"
//#include "bind_lv_draw_blend.h"
//#include "bind_lv_draw_mask.h"
//#include "bind_lv_img_buf.h"
//#include "bind_lv_draw.h"
//#include "bind_lv_img_decoder.h"
//#include "bind_lv_draw_triangle.h"
//#include "bind_lv_draw_line.h"
//#include "bind_lv_draw_rect.h"
//#include "bind_lv_draw_arc.h"
//#include "bind_lv_draw_img.h"
//#include "bind_lv_font_fmt_txt.h"
//#include "bind_lv_symbol_def.h"
//#include "bind_lv_font.h"
//#include "bind_lv_font_loader.h"

static const luaL_Reg binding_names [] = {
//  {"lv_api_map__init_module", bind_lv_api_map__init_module},
//  {"lv_conf_kconfig__init_module", bind_lv_conf_kconfig__init_module},
//  {"lv_conf_internal__init_module", bind_lv_conf_internal__init_module},
//  {"lv_group__init_module", bind_lv_group__init_module},
  {"lv_obj__init_module", bind_lv_obj__init_module},
//  {"lv_obj_style_dec__init_module", bind_lv_obj_style_dec__init_module},
  {"lv_disp__init_module", bind_lv_disp__init_module},
//  {"lv_indev__init_module", bind_lv_indev__init_module},
  {"lv_style__init_module", bind_lv_style__init_module},
//  {"lv_refr__init_module", bind_lv_refr__init_module},
//  {"lv_printf__init_module", bind_lv_printf__init_module},
//  {"lv_templ__init_module", bind_lv_templ__init_module},
//  {"lv_async__init_module", bind_lv_async__init_module},
//  {"lv_math__init_module", bind_lv_math__init_module},
//  {"lv_anim__init_module", bind_lv_anim__init_module},
//  {"lv_bidi__init_module", bind_lv_bidi__init_module},
//  {"lv_gc__init_module", bind_lv_gc__init_module},
//  {"lv_debug__init_module", bind_lv_debug__init_module},
//  {"lv_task__init_module", bind_lv_task__init_module},
//  {"lv_txt__init_module", bind_lv_txt__init_module},
//  {"lv_utils__init_module", bind_lv_utils__init_module},
//  {"lv_types__init_module", bind_lv_types__init_module},
//  {"lv_mem__init_module", bind_lv_mem__init_module},
//  {"lv_txt_ap__init_module", bind_lv_txt_ap__init_module},
//  {"lv_fs__init_module", bind_lv_fs__init_module},
//  {"lv_area__init_module", bind_lv_area__init_module},
//  {"lv_log__init_module", bind_lv_log__init_module},
//  {"lv_ll__init_module", bind_lv_ll__init_module},
//  {"lv_color__init_module", bind_lv_color__init_module},
  {"lv_linemeter__init_module", bind_lv_linemeter__init_module},
  {"lv_slider__init_module", bind_lv_slider__init_module},
//  {"lv_img__init_module", bind_lv_img__init_module},
//  {"lv_imgbtn__init_module", bind_lv_imgbtn__init_module},
//  {"lv_list__init_module", bind_lv_list__init_module},
//  {"lv_table__init_module", bind_lv_table__init_module},
  {"lv_arc__init_module", bind_lv_arc__init_module},
  {"lv_bar__init_module", bind_lv_bar__init_module},
//  {"lv_dropdown__init_module", bind_lv_dropdown__init_module},
//  {"lv_canvas__init_module", bind_lv_canvas__init_module},
//  {"lv_objx_templ__init_module", bind_lv_objx_templ__init_module},
//  {"lv_calendar__init_module", bind_lv_calendar__init_module},
  {"lv_switch__init_module", bind_lv_switch__init_module},
//  {"lv_tabview__init_module", bind_lv_tabview__init_module},
  {"lv_checkbox__init_module", bind_lv_checkbox__init_module},
//  {"lv_line__init_module", bind_lv_line__init_module},
//  {"lv_spinner__init_module", bind_lv_spinner__init_module},
  {"lv_label__init_module", bind_lv_label__init_module},
  {"lv_keyboard__init_module", bind_lv_keyboard__init_module},
//  {"lv_page__init_module", bind_lv_page__init_module},
//  {"lv_cpicker__init_module", bind_lv_cpicker__init_module},
//  {"lv_gauge__init_module", bind_lv_gauge__init_module},
//  {"lv_win__init_module", bind_lv_win__init_module},
  {"lv_btn__init_module", bind_lv_btn__init_module},
//  {"lv_roller__init_module", bind_lv_roller__init_module},
//  {"lv_objmask__init_module", bind_lv_objmask__init_module},
//  {"lv_chart__init_module", bind_lv_chart__init_module},
  {"lv_textarea__init_module", bind_lv_textarea__init_module},
//  {"lv_msgbox__init_module", bind_lv_msgbox__init_module},
//  {"lv_spinbox__init_module", bind_lv_spinbox__init_module},
//  {"lv_led__init_module", bind_lv_led__init_module},
//  {"lv_tileview__init_module", bind_lv_tileview__init_module},
//  {"lv_btnmatrix__init_module", bind_lv_btnmatrix__init_module},
//  {"lv_cont__init_module", bind_lv_cont__init_module},
//  {"lv_theme_mono__init_module", bind_lv_theme_mono__init_module},
//  {"lv_theme_empty__init_module", bind_lv_theme_empty__init_module},
//  {"lv_theme_template__init_module", bind_lv_theme_template__init_module},
//  {"lv_theme__init_module", bind_lv_theme__init_module},
//  {"lv_theme_material__init_module", bind_lv_theme_material__init_module},
//  {"lv_hal_tick__init_module", bind_lv_hal_tick__init_module},
//  {"lv_hal__init_module", bind_lv_hal__init_module},
//  {"lv_hal_indev__init_module", bind_lv_hal_indev__init_module},
//  {"lv_hal_disp__init_module", bind_lv_hal_disp__init_module},
//  {"lv_draw_label__init_module", bind_lv_draw_label__init_module},
//  {"lv_img_cache__init_module", bind_lv_img_cache__init_module},
//  {"lv_draw_blend__init_module", bind_lv_draw_blend__init_module},
//  {"lv_draw_mask__init_module", bind_lv_draw_mask__init_module},
//  {"lv_img_buf__init_module", bind_lv_img_buf__init_module},
//  {"lv_draw__init_module", bind_lv_draw__init_module},
//  {"lv_img_decoder__init_module", bind_lv_img_decoder__init_module},
//  {"lv_draw_triangle__init_module", bind_lv_draw_triangle__init_module},
//  {"lv_draw_line__init_module", bind_lv_draw_line__init_module},
//  {"lv_draw_rect__init_module", bind_lv_draw_rect__init_module},
//  {"lv_draw_arc__init_module", bind_lv_draw_arc__init_module},
//  {"lv_draw_img__init_module", bind_lv_draw_img__init_module},
//  {"lv_font_fmt_txt__init_module", bind_lv_font_fmt_txt__init_module},
//  {"lv_symbol_def__init_module", bind_lv_symbol_def__init_module},
//  {"lv_font__init_module", bind_lv_font__init_module},
//  {"lv_font_loader__init_module", bind_lv_font_loader__init_module},

  { NULL, NULL},
};

extern void lv_append_lib_funcs(lua_State *L, luaL_Reg  reg[]);

void bind_init_lvgl_modules(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
}


#ifdef __cplusplus
  }
#endif
