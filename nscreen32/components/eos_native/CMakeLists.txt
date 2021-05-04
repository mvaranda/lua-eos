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
  "../../../lua_eos/native"
  "../../main"
  "." )
set(COMPONENT_SRCS 
  "../../../lua_eos/native/mos_freertos.c" 
  "../../../lua_eos/native/lua_eos.c"
  "../../../lua_eos/native/mos_test.c"
  "../../../lua_eos/native/bidings.c"
  "../../../lua_eos/native/lvgl_lua.c"
  "../../../lua_eos/native/nat_cmd.c"
  "../../../utils/malloc.c"
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

