set(COMPONENT_SRCS "main.c"
    "pngle.c"
    "decode_image.c"
    "lvgl_task"
    "lvgl_helpers.c"
    "esp32_cmds.c"
    "xmodem.c"
    "crc16.c"
	)

# # Only ESP32 has enough memory to do jpeg decoding
# if(IDF_TARGET STREQUAL "esp32")
#     list(APPEND srcs "decode_image.c")
# endif()

set(COMPONENT_PRIV_INCLUDEDIRS 
  "../../lua_eos/native"
  "../../lua/src"
  "$ENV{IDF_PATH}/components/freertos/include/freertos"
  "." )

  

#idf_component_register(SRCS ${srcs} INCLUDE_DIRS ".")
register_component()

# Create a SPIFFS image from the contents of the 'font' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash
#spiffs_create_partition_image(storage ../font FLASH_IN_PROJECT)

spiffs_create_partition_image(storage ../../target_files FLASH_IN_PROJECT)


add_definitions(-DBOARD_NSCREEN32)
