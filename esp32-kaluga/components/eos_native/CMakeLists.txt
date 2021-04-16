# idf_component_register(SRCS "native/mos_freertos.c"
#                     INCLUDE_DIRS .
#                     REQUIRES console spi_flash)
#   "../../../lua_eos/native/FreeRTOS/FreeRTOS/Source/include/")

set(COMPONENT_ADD_INCLUDEDIRS .)
set(COMPONENT_PRIV_INCLUDEDIRS 
  "$ENV{IDF_PATH}/components/freertos/include/freertos"
  "../../../lua/src"
  "../../../lvgl/src"
  "." )
set(COMPONENT_SRCS 
  "native/mos_freertos.c" 
  "native/lua_eos.c"
  "native/mos_test.c"
  "native/bidings.c"
  "native/lvgl_lua.c"
  )
                    
register_component()

