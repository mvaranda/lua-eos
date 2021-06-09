
-- ***************************************************************
-- *
-- *                 This code is part of LUA_EOS
-- *
-- * Copyrights 2021 - Varanda Labs Inc.
-- *
-- * License:
-- *   Creative Commons: CC BY-NC-SA 4.0
-- *   Attribution-NonCommercial-ShareAlike 4.0 International
-- *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
-- *
-- *   Note: for purchasing a commertial license contact:
-- *     m@varanda.ca
-- *
-- ***************************************************************

-- Enumerations

-- Load module
  lv.lv_style__init_module()

LV_STYLE_ID_MASK = 0x00FF
LV_STYLE_ATTR_NONE = 0
LV_STYLE_ATTR_INHERIT = (1 << 7)
_LV_STYLE_CLOSING_PROP = 0xFF
LV_STYLE_TRANS_NUM_MAX = 6
LV_STYLE_PROP_ALL = 0xFF


LV_STYLE_ID_MASK = 0x00FF
LV_BORDER_SIDE_NONE     = 0x00
LV_BORDER_SIDE_BOTTOM   = 0x01
LV_BORDER_SIDE_TOP      = 0x02
LV_BORDER_SIDE_LEFT     = 0x04
LV_BORDER_SIDE_RIGHT    = 0x08
LV_BORDER_SIDE_FULL     = 0x0F
LV_BORDER_SIDE_INTERNAL = 0x10

LV_GRAD_DIR_NONE = 0
LV_GRAD_DIR_VER = 1
LV_GRAD_DIR_HOR = 2

LV_TEXT_DECOR_NONE          = 0x00
LV_TEXT_DECOR_UNDERLINE     = 0x01
LV_TEXT_DECOR_STRIKETHROUGH = 0x02

LV_STYLE_ID_VALUE = 0x0
LV_STYLE_ID_COLOR = 0x9
LV_STYLE_ID_OPA   = 0xC
LV_STYLE_ID_PTR   = 0xE

-- following commented lines is to generate the property name.
-- #define LV_STYLE_PROP_INIT(name, group, id, attr)  name = (((group << 4) + id) | ((attr) << 8))
--function init_prop_name(name, group, id, attr)
--  v = (((group << 4) + id) | ((attr) << 8))
--  print(name .. " = " .. string.format("0x%x",v))
--end
--
--function print_defs()
--  LV_STYLE_RADIUS = init_prop_name (             "LV_STYLE_RADIUS", 0x0, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_CLIP_CORNER = init_prop_name (        "LV_STYLE_CLIP_CORNER", 0x0, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SIZE = init_prop_name (               "LV_STYLE_SIZE", 0x0, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSFORM_WIDTH = init_prop_name (    "LV_STYLE_TRANSFORM_WIDTH", 0x0, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSFORM_HEIGHT = init_prop_name (   "LV_STYLE_TRANSFORM_HEIGHT", 0x0, LV_STYLE_ID_VALUE + 5, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSFORM_ANGLE = init_prop_name (    "LV_STYLE_TRANSFORM_ANGLE", 0x0, LV_STYLE_ID_VALUE + 6, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSFORM_ZOOM = init_prop_name (     "LV_STYLE_TRANSFORM_ZOOM", 0x0, LV_STYLE_ID_VALUE + 7, LV_STYLE_ATTR_NONE)
--  LV_STYLE_OPA_SCALE = init_prop_name (          "LV_STYLE_OPA_SCALE", 0x0, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_INHERIT)
--
--  LV_STYLE_PAD_TOP = init_prop_name (            "LV_STYLE_PAD_TOP", 0x1, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PAD_BOTTOM = init_prop_name (         "LV_STYLE_PAD_BOTTOM", 0x1, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PAD_LEFT = init_prop_name (           "LV_STYLE_PAD_LEFT", 0x1, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PAD_RIGHT = init_prop_name (          "LV_STYLE_PAD_RIGHT", 0x1, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PAD_INNER = init_prop_name (          "LV_STYLE_PAD_INNER", 0x1, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_MARGIN_TOP = init_prop_name (         "LV_STYLE_MARGIN_TOP", 0x1, LV_STYLE_ID_VALUE + 5, LV_STYLE_ATTR_NONE)
--  LV_STYLE_MARGIN_BOTTOM = init_prop_name (      "LV_STYLE_MARGIN_BOTTOM", 0x1, LV_STYLE_ID_VALUE + 6, LV_STYLE_ATTR_NONE)
--  LV_STYLE_MARGIN_LEFT = init_prop_name (        "LV_STYLE_MARGIN_LEFT", 0x1, LV_STYLE_ID_VALUE + 7, LV_STYLE_ATTR_NONE)
--  LV_STYLE_MARGIN_RIGHT = init_prop_name (       "LV_STYLE_MARGIN_RIGHT", 0x1, LV_STYLE_ID_VALUE + 8, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_BG_BLEND_MODE = init_prop_name (      "LV_STYLE_BG_BLEND_MODE", 0x2, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_MAIN_STOP = init_prop_name (       "LV_STYLE_BG_MAIN_STOP", 0x2, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_GRAD_STOP = init_prop_name (       "LV_STYLE_BG_GRAD_STOP", 0x2, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_GRAD_DIR = init_prop_name (        "LV_STYLE_BG_GRAD_DIR", 0x2, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_COLOR = init_prop_name (           "LV_STYLE_BG_COLOR", 0x2, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_GRAD_COLOR = init_prop_name (      "LV_STYLE_BG_GRAD_COLOR", 0x2, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BG_OPA = init_prop_name (             "LV_STYLE_BG_OPA", 0x2, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_BORDER_WIDTH = init_prop_name (       "LV_STYLE_BORDER_WIDTH", 0x3, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BORDER_SIDE = init_prop_name (        "LV_STYLE_BORDER_SIDE", 0x3, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BORDER_BLEND_MODE = init_prop_name (  "LV_STYLE_BORDER_BLEND_MODE", 0x3, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BORDER_POST = init_prop_name (        "LV_STYLE_BORDER_POST", 0x3, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BORDER_COLOR = init_prop_name (       "LV_STYLE_BORDER_COLOR", 0x3, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_BORDER_OPA = init_prop_name (         "LV_STYLE_BORDER_OPA", 0x3, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_OUTLINE_WIDTH = init_prop_name (      "LV_STYLE_OUTLINE_WIDTH", 0x4, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_OUTLINE_PAD = init_prop_name (        "LV_STYLE_OUTLINE_PAD", 0x4, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_OUTLINE_BLEND_MODE = init_prop_name ( "LV_STYLE_OUTLINE_BLEND_MODE", 0x4, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_OUTLINE_COLOR = init_prop_name (      "LV_STYLE_OUTLINE_COLOR", 0x4, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_OUTLINE_OPA = init_prop_name (        "LV_STYLE_OUTLINE_OPA", 0x4, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_SHADOW_WIDTH = init_prop_name (       "LV_STYLE_SHADOW_WIDTH", 0x5, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_OFS_X = init_prop_name (       "LV_STYLE_SHADOW_OFS_X", 0x5, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_OFS_Y = init_prop_name (       "LV_STYLE_SHADOW_OFS_Y", 0x5, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_SPREAD = init_prop_name (      "LV_STYLE_SHADOW_SPREAD", 0x5, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_BLEND_MODE = init_prop_name (  "LV_STYLE_SHADOW_BLEND_MODE", 0x5, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_COLOR = init_prop_name (       "LV_STYLE_SHADOW_COLOR", 0x5, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SHADOW_OPA = init_prop_name (         "LV_STYLE_SHADOW_OPA", 0x5, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_PATTERN_BLEND_MODE = init_prop_name ( "LV_STYLE_PATTERN_BLEND_MODE", 0x6, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PATTERN_REPEAT = init_prop_name (     "LV_STYLE_PATTERN_REPEAT", 0x6, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PATTERN_RECOLOR = init_prop_name (    "LV_STYLE_PATTERN_RECOLOR", 0x6, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PATTERN_OPA = init_prop_name (        "LV_STYLE_PATTERN_OPA", 0x6, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PATTERN_RECOLOR_OPA = init_prop_name ( "LV_STYLE_PATTERN_RECOLOR_OPA", 0x6, LV_STYLE_ID_OPA   + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_PATTERN_IMAGE = init_prop_name (      "LV_STYLE_PATTERN_IMAGE", 0x6, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_VALUE_LETTER_SPACE = init_prop_name ( "LV_STYLE_VALUE_LETTER_SPACE", 0x7, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_LINE_SPACE = init_prop_name (   "LV_STYLE_VALUE_LINE_SPACE", 0x7, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_BLEND_MODE = init_prop_name (   "LV_STYLE_VALUE_BLEND_MODE", 0x7, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_OFS_X = init_prop_name (        "LV_STYLE_VALUE_OFS_X", 0x7, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_OFS_Y = init_prop_name (        "LV_STYLE_VALUE_OFS_Y", 0x7, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_ALIGN = init_prop_name (        "LV_STYLE_VALUE_ALIGN", 0x7, LV_STYLE_ID_VALUE + 5, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_COLOR = init_prop_name (        "LV_STYLE_VALUE_COLOR", 0x7, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_OPA = init_prop_name (          "LV_STYLE_VALUE_OPA", 0x7, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_FONT = init_prop_name (         "LV_STYLE_VALUE_FONT", 0x7, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_VALUE_STR = init_prop_name (          "LV_STYLE_VALUE_STR", 0x7, LV_STYLE_ID_PTR   + 1, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_TEXT_LETTER_SPACE = init_prop_name (  "LV_STYLE_TEXT_LETTER_SPACE", 0x8, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_LINE_SPACE = init_prop_name (    "LV_STYLE_TEXT_LINE_SPACE", 0x8, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_DECOR = init_prop_name (         "LV_STYLE_TEXT_DECOR", 0x8, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_BLEND_MODE = init_prop_name (    "LV_STYLE_TEXT_BLEND_MODE", 0x8, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_COLOR = init_prop_name (         "LV_STYLE_TEXT_COLOR", 0x8, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_SEL_COLOR = init_prop_name (     "LV_STYLE_TEXT_SEL_COLOR", 0x8, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_SEL_BG_COLOR = init_prop_name (  "LV_STYLE_TEXT_SEL_BG_COLOR", 0x8, LV_STYLE_ID_COLOR + 2, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_OPA = init_prop_name (           "LV_STYLE_TEXT_OPA", 0x8, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_TEXT_FONT = init_prop_name (          "LV_STYLE_TEXT_FONT", 0x8, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_INHERIT)
--
--  LV_STYLE_LINE_WIDTH = init_prop_name (         "LV_STYLE_LINE_WIDTH", 0x9, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_BLEND_MODE = init_prop_name (    "LV_STYLE_LINE_BLEND_MODE", 0x9, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_DASH_WIDTH = init_prop_name (    "LV_STYLE_LINE_DASH_WIDTH", 0x9, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_DASH_GAP = init_prop_name (      "LV_STYLE_LINE_DASH_GAP", 0x9, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_ROUNDED = init_prop_name (       "LV_STYLE_LINE_ROUNDED", 0x9, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_COLOR = init_prop_name (         "LV_STYLE_LINE_COLOR", 0x9, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_LINE_OPA = init_prop_name (           "LV_STYLE_LINE_OPA", 0x9, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_IMAGE_BLEND_MODE = init_prop_name (   "LV_STYLE_IMAGE_BLEND_MODE", 0xA, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_IMAGE_RECOLOR = init_prop_name (      "LV_STYLE_IMAGE_RECOLOR", 0xA, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_IMAGE_OPA = init_prop_name (          "LV_STYLE_IMAGE_OPA", 0xA, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_INHERIT)
--  LV_STYLE_IMAGE_RECOLOR_OPA = init_prop_name (  "LV_STYLE_IMAGE_RECOLOR_OPA", 0xA, LV_STYLE_ID_OPA   + 1, LV_STYLE_ATTR_INHERIT)
--
--  LV_STYLE_TRANSITION_TIME = init_prop_name (    "LV_STYLE_TRANSITION_TIME", 0xB, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_DELAY = init_prop_name (   "LV_STYLE_TRANSITION_DELAY", 0xB, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_1 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_1", 0xB, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_2 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_2", 0xB, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_3 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_3", 0xB, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_4 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_4", 0xB, LV_STYLE_ID_VALUE + 5, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_5 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_5", 0xB, LV_STYLE_ID_VALUE + 6, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PROP_6 = init_prop_name (  "LV_STYLE_TRANSITION_PROP_6", 0xB, LV_STYLE_ID_VALUE + 7, LV_STYLE_ATTR_NONE)
--  LV_STYLE_TRANSITION_PATH = init_prop_name (    "LV_STYLE_TRANSITION_PATH", 0xB, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_NONE)
--
--  LV_STYLE_SCALE_WIDTH = init_prop_name (            "LV_STYLE_SCALE_WIDTH", 0xC, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SCALE_BORDER_WIDTH = init_prop_name (     "LV_STYLE_SCALE_BORDER_WIDTH", 0xC, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SCALE_END_BORDER_WIDTH = init_prop_name ( "LV_STYLE_SCALE_END_BORDER_WIDTH", 0xC, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SCALE_END_LINE_WIDTH = init_prop_name (   "LV_STYLE_SCALE_END_LINE_WIDTH", 0xC, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SCALE_GRAD_COLOR = init_prop_name (       "LV_STYLE_SCALE_GRAD_COLOR", 0xC, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE)
--  LV_STYLE_SCALE_END_COLOR = init_prop_name (        "LV_STYLE_SCALE_END_COLOR", 0xC, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_NONE)
--end -- print_defs()

-- generated by processing print_defs() in a desktop lua
LV_STYLE_RADIUS = 0x1
LV_STYLE_CLIP_CORNER = 0x2
LV_STYLE_SIZE = 0x3
LV_STYLE_TRANSFORM_WIDTH = 0x4
LV_STYLE_TRANSFORM_HEIGHT = 0x5
LV_STYLE_TRANSFORM_ANGLE = 0x6
LV_STYLE_TRANSFORM_ZOOM = 0x7
LV_STYLE_OPA_SCALE = 0x800c
LV_STYLE_PAD_TOP = 0x10
LV_STYLE_PAD_BOTTOM = 0x11
LV_STYLE_PAD_LEFT = 0x12
LV_STYLE_PAD_RIGHT = 0x13
LV_STYLE_PAD_INNER = 0x14
LV_STYLE_MARGIN_TOP = 0x15
LV_STYLE_MARGIN_BOTTOM = 0x16
LV_STYLE_MARGIN_LEFT = 0x17
LV_STYLE_MARGIN_RIGHT = 0x18
LV_STYLE_BG_BLEND_MODE = 0x20
LV_STYLE_BG_MAIN_STOP = 0x21
LV_STYLE_BG_GRAD_STOP = 0x22
LV_STYLE_BG_GRAD_DIR = 0x23
LV_STYLE_BG_COLOR = 0x29
LV_STYLE_BG_GRAD_COLOR = 0x2a
LV_STYLE_BG_OPA = 0x2c
LV_STYLE_BORDER_WIDTH = 0x30
LV_STYLE_BORDER_SIDE = 0x31
LV_STYLE_BORDER_BLEND_MODE = 0x32
LV_STYLE_BORDER_POST = 0x33
LV_STYLE_BORDER_COLOR = 0x39
LV_STYLE_BORDER_OPA = 0x3c
LV_STYLE_OUTLINE_WIDTH = 0x40
LV_STYLE_OUTLINE_PAD = 0x41
LV_STYLE_OUTLINE_BLEND_MODE = 0x42
LV_STYLE_OUTLINE_COLOR = 0x49
LV_STYLE_OUTLINE_OPA = 0x4c
LV_STYLE_SHADOW_WIDTH = 0x50
LV_STYLE_SHADOW_OFS_X = 0x51
LV_STYLE_SHADOW_OFS_Y = 0x52
LV_STYLE_SHADOW_SPREAD = 0x53
LV_STYLE_SHADOW_BLEND_MODE = 0x54
LV_STYLE_SHADOW_COLOR = 0x59
LV_STYLE_SHADOW_OPA = 0x5c
LV_STYLE_PATTERN_BLEND_MODE = 0x60
LV_STYLE_PATTERN_REPEAT = 0x61
LV_STYLE_PATTERN_RECOLOR = 0x69
LV_STYLE_PATTERN_OPA = 0x6c
LV_STYLE_PATTERN_RECOLOR_OPA = 0x6d
LV_STYLE_PATTERN_IMAGE = 0x6e
LV_STYLE_VALUE_LETTER_SPACE = 0x70
LV_STYLE_VALUE_LINE_SPACE = 0x71
LV_STYLE_VALUE_BLEND_MODE = 0x72
LV_STYLE_VALUE_OFS_X = 0x73
LV_STYLE_VALUE_OFS_Y = 0x74
LV_STYLE_VALUE_ALIGN = 0x75
LV_STYLE_VALUE_COLOR = 0x79
LV_STYLE_VALUE_OPA = 0x7c
LV_STYLE_VALUE_FONT = 0x7e
LV_STYLE_VALUE_STR = 0x7f
LV_STYLE_TEXT_LETTER_SPACE = 0x8080
LV_STYLE_TEXT_LINE_SPACE = 0x8081
LV_STYLE_TEXT_DECOR = 0x8082
LV_STYLE_TEXT_BLEND_MODE = 0x8083
LV_STYLE_TEXT_COLOR = 0x8089
LV_STYLE_TEXT_SEL_COLOR = 0x808a
LV_STYLE_TEXT_SEL_BG_COLOR = 0x808b
LV_STYLE_TEXT_OPA = 0x808c
LV_STYLE_TEXT_FONT = 0x808e
LV_STYLE_LINE_WIDTH = 0x90
LV_STYLE_LINE_BLEND_MODE = 0x91
LV_STYLE_LINE_DASH_WIDTH = 0x92
LV_STYLE_LINE_DASH_GAP = 0x93
LV_STYLE_LINE_ROUNDED = 0x94
LV_STYLE_LINE_COLOR = 0x99
LV_STYLE_LINE_OPA = 0x9c
LV_STYLE_IMAGE_BLEND_MODE = 0x80a0
LV_STYLE_IMAGE_RECOLOR = 0x80a9
LV_STYLE_IMAGE_OPA = 0x80ac
LV_STYLE_IMAGE_RECOLOR_OPA = 0x80ad
LV_STYLE_TRANSITION_TIME = 0xb0
LV_STYLE_TRANSITION_DELAY = 0xb1
LV_STYLE_TRANSITION_PROP_1 = 0xb2
LV_STYLE_TRANSITION_PROP_2 = 0xb3
LV_STYLE_TRANSITION_PROP_3 = 0xb4
LV_STYLE_TRANSITION_PROP_4 = 0xb5
LV_STYLE_TRANSITION_PROP_5 = 0xb6
LV_STYLE_TRANSITION_PROP_6 = 0xb7
LV_STYLE_TRANSITION_PATH = 0xbe
LV_STYLE_SCALE_WIDTH = 0xc0
LV_STYLE_SCALE_BORDER_WIDTH = 0xc1
LV_STYLE_SCALE_END_BORDER_WIDTH = 0xc2
LV_STYLE_SCALE_END_LINE_WIDTH = 0xc3
LV_STYLE_SCALE_GRAD_COLOR = 0xc9
LV_STYLE_SCALE_END_COLOR = 0xca


LV_STYLE_STATE_POS =      8
LV_STYLE_STATE_MASK  =    0x7F00
LV_STYLE_INHERIT_MASK =   0x8000

