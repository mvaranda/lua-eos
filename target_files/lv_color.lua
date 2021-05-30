
local function LV_COLOR_MAKE(r,g,b)
  -- 16 # define LV_COLOR_MAKE16(r8, g8, b8) (_LV_COLOR_MAKE_TYPE_HELPER{{(uint8_t)((g8 >> 5) & 0x7U), (uint8_t)((r8 >> 3) & 0x1FU), (uint8_t)((b8 >> 3) & 0x1FU), (uint8_t)((g8 >> 2) & 0x7U)}})
  -- Assume RGB 565:
  -- |b7|b6|b5|b4|b3|g7|g6|g5|g4|g3|g2|r7|r6|r5|r4|r3|
  --                         |
  
  local c = (r << 8) & 0xf800
  c = c | ((g << 3) & 0xffe0)
  c = c | (b >> 3)
  
  -- if swap
--  local s = (c << 8) & 0xff00
--  s = s | (c >> 8)
--  return s

  return c


end


LV_COLOR_WHITE   = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)
LV_COLOR_SILVER  = LV_COLOR_MAKE(0xC0, 0xC0, 0xC0)
LV_COLOR_GRAY    = LV_COLOR_MAKE(0x80, 0x80, 0x80)
LV_COLOR_BLACK   = LV_COLOR_MAKE(0x00, 0x00, 0x00)
LV_COLOR_RED     = LV_COLOR_MAKE(0xFF, 0x00, 0x00)
LV_COLOR_MAROON  = LV_COLOR_MAKE(0x80, 0x00, 0x00)
LV_COLOR_YELLOW  = LV_COLOR_MAKE(0xFF, 0xFF, 0x00)
LV_COLOR_OLIVE   = LV_COLOR_MAKE(0x80, 0x80, 0x00)
LV_COLOR_LIME    = LV_COLOR_MAKE(0x00, 0xFF, 0x00)
LV_COLOR_GREEN   = LV_COLOR_MAKE(0x00, 0x80, 0x00)
LV_COLOR_CYAN    = LV_COLOR_MAKE(0x00, 0xFF, 0xFF)
LV_COLOR_AQUA    = LV_COLOR_CYAN
LV_COLOR_TEAL    = LV_COLOR_MAKE(0x00, 0x80, 0x80)
LV_COLOR_BLUE    = LV_COLOR_MAKE(0x00, 0x00, 0xFF)
LV_COLOR_NAVY    = LV_COLOR_MAKE(0x00, 0x00, 0x80)
LV_COLOR_MAGENTA = LV_COLOR_MAKE(0xFF, 0x00, 0xFF)
LV_COLOR_PURPLE  = LV_COLOR_MAKE(0x80, 0x00, 0x80)
LV_COLOR_ORANGE  = LV_COLOR_MAKE(0xFF, 0xA5, 0x00)


LV_OPA_TRANSP = 0
LV_OPA_0      = 0
LV_OPA_10     = 25
LV_OPA_20     = 51
LV_OPA_30     = 76
LV_OPA_40     = 102
LV_OPA_50     = 127
LV_OPA_60     = 153
LV_OPA_70     = 178
LV_OPA_80     = 204
LV_OPA_90     = 229
LV_OPA_100    = 255
LV_OPA_COVER  = 255


