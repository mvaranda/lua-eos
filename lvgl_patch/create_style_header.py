#
#
# recreate prototypes for style get/set
#
# Part of Lua EOS
#
# Copyrights Varanda Labs Inc.
#


"""
#define _OBJ_GET_STYLE(prop_name, func_name, value_type, style_type)                                \
    static inline value_type lv_obj_get_style_##func_name(const lv_obj_t * obj, uint8_t part)       \
    {                                                                                               \
        return (value_type)_lv_obj_get_style##style_type(obj, part, LV_STYLE_##prop_name);          \
    }
#else
#define _OBJ_GET_STYLE(prop_name, func_name, value_type, style_type)                                \
    static inline value_type lv_obj_get_style_##func_name(const lv_obj_t * obj, uint8_t part)       \
    {                                                                                               \
        return _lv_obj_get_style##style_type(obj, part, LV_STYLE_##prop_name);                      \
    }
#endif

#define _OBJ_SET_STYLE_LOCAL(prop_name, func_name, value_type, style_type)                                                      \
    static inline void lv_obj_set_style_local_##func_name(lv_obj_t * obj, uint8_t part, lv_state_t state, value_type value)     \
    {                                                                                                                           \
        _lv_obj_set_style_local##style_type(obj, part, LV_STYLE_##prop_name | (state << LV_STYLE_STATE_POS), value);            \
    }

#define _OBJ_SET_STYLE(prop_name, func_name, value_type, style_type)                                                     \
    static inline void lv_style_set_##func_name(lv_style_t * style, lv_state_t state, value_type value)                  \
    {                                                                                                                    \
        _lv_style_set##style_type(style, LV_STYLE_##prop_name | (state << LV_STYLE_STATE_POS), value);                   \
    }

#define _LV_OBJ_STYLE_SET_GET_DECLARE(prop_name, func_name, value_type, style_type)                                      \
    _OBJ_GET_STYLE(prop_name, func_name, value_type, style_type)                                                         \
    _OBJ_SET_STYLE_LOCAL(prop_name, func_name, value_type, style_type)                                                   \
    _OBJ_SET_STYLE(prop_name, func_name, value_type, style_type)
"""

body = ""

def  _OBJ_GET_STYLE(func_name):
  global body
  # value_type lv_obj_get_style_##func_name(const lv_obj_t * obj, uint8_t part)
  body = body + "value_type lv_obj_get_style_" + func_name + "(const lv_obj_t * obj, uint8_t part);\n"
  
  
def  _OBJ_SET_STYLE(func_name):
  global body
  # void lv_style_set_##func_name(lv_style_t * style, lv_state_t state, value_type value)
  body = body + "void lv_style_set_" + func_name + "(lv_style_t * style, lv_state_t state, value_type value);\n"

def _LV_OBJ_STYLE_SET_GET_DECLARE(func_name):
  _OBJ_GET_STYLE(func_name)
  _OBJ_SET_STYLE(func_name)


def print_prototypes():
  _LV_OBJ_STYLE_SET_GET_DECLARE("radius")
  _LV_OBJ_STYLE_SET_GET_DECLARE("clip_corner")
  _LV_OBJ_STYLE_SET_GET_DECLARE("size")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transform_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transform_height")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transform_angle")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transform_zoom")
  _LV_OBJ_STYLE_SET_GET_DECLARE("opa_scale")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pad_top")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pad_bottom")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pad_left")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pad_right")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pad_inner")
  _LV_OBJ_STYLE_SET_GET_DECLARE("margin_top")
  _LV_OBJ_STYLE_SET_GET_DECLARE("margin_bottom")
  _LV_OBJ_STYLE_SET_GET_DECLARE("margin_left")
  _LV_OBJ_STYLE_SET_GET_DECLARE("margin_right")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_main_stop")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_grad_stop")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_grad_dir")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_grad_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("bg_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_side")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_post")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("border_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("outline_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("outline_pad")
  _LV_OBJ_STYLE_SET_GET_DECLARE("outline_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("outline_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("outline_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_ofs_x")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_ofs_y")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_spread")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("shadow_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_repeat")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_recolor")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_recolor_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("pattern_image")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_letter_space")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_line_space")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_ofs_x")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_ofs_y")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_align")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_font")
  _LV_OBJ_STYLE_SET_GET_DECLARE("value_str")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_letter_space")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_line_space")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_decor")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_sel_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_sel_bg_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("text_font")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_dash_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_dash_gap")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_rounded")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("line_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("image_blend_mode")
  _LV_OBJ_STYLE_SET_GET_DECLARE("image_recolor")
  _LV_OBJ_STYLE_SET_GET_DECLARE("image_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("image_recolor_opa")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_time")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_delay")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_1")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_2")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_3")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_4")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_5")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_prop_6")
  _LV_OBJ_STYLE_SET_GET_DECLARE("transition_path")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_border_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_end_border_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_end_line_width")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_grad_color")
  _LV_OBJ_STYLE_SET_GET_DECLARE("scale_end_color")
  print(body)

if __name__ == "__main__":
  print_prototypes()


