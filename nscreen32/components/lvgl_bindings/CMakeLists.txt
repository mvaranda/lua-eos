# idf_component_register(SRCS "native/mos_freertos.c"
#                     INCLUDE_DIRS .
#                     REQUIRES console spi_flash)
#   "../../../lua_eos/native/FreeRTOS/FreeRTOS/Source/include/")

set(COMPONENT_ADD_INCLUDEDIRS .)
set(COMPONENT_PRIV_INCLUDEDIRS 
  "$ENV{IDF_PATH}/components/freertos/include/freertos"
  "../../../"
  "../../../lua/src"
  "../../../lvgl/src"
  "../../../lvgl/src/lv_core"
  "../../../lvgl/src/lv_widgets"
  "../../../lvgl_patch"
  "../../../lua_eos/native"
  "../../main"
  "." )

#lvgl_integr.cpp

set(COMPONENT_SRCS
  "../../../lvgl_patch/bind_lv_btn.c"	
  "../../../lvgl_patch/bind_lv_obj.c"	
  "../../../lvgl_patch/bind_lv_disp.c"
  "../../../lvgl_patch/lvgl_init_modules.c"
  "../../../lvgl_patch/bind_lv_slider.c"
  "../../../lvgl_patch/bind_lv_label.c"
  "../../../lvgl_patch/bind_lv_linemeter.c"
  "../../../lvgl_patch/bind_lv_switch.c"
  "../../../lvgl_patch/bind_lv_keyboard.c"
  "../../../lvgl_patch/bind_lv_textarea.c"
  "../../../lvgl_patch/bind_lv_checkbox.c"
  "../../../lvgl_patch/bind_lv_style.c"
  )
                    
register_component()

add_definitions(
  -DBOARD_DEF="NSCREEN32"
  -DUSE_DL_PREFIX 
  -DMSPACES=1 
  -DUSE_DOUG_LEA_MALLOC 
  -DONLY_MSPACES=0 
  -DNO_MALLINFO=0 
  -DHAVE_MMAP=0 
  -DHAVE_MORECORE=0)

