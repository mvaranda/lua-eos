# idf_component_register(SRCS "native/mos_freertos.c"
#                     INCLUDE_DIRS .
#                     REQUIRES console spi_flash)
#   "../../../lua_eos/native/FreeRTOS/FreeRTOS/Source/include/")

set(COMPONENT_ADD_INCLUDEDIRS .)
set(COMPONENT_PRIV_INCLUDEDIRS 
  "$ENV{IDF_PATH}/components/freertos/include/freertos"
  "../../../lua/src"
  "../../../lvgl/src"
  "../../../lua_eos/native"
  "." )
set(COMPONENT_SRCS 
  "../../../lua_eos/native/mos_freertos.c" 
  "../../../lua_eos/native/lua_eos.c"
  "../../../lua_eos/native/mos_test.c"
  "../../../lua_eos/native/bidings.c"
  "../../../lua_eos/native/lvgl_lua.c"
  )
                    
register_component()

