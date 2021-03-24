set(COMPONENT_SRCS "main.c")

register_component()

# Create a SPIFFS image from the contents of the 'spiffs_image' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash'.
#spiffs_create_partition_image(storage ../spiffs_image FLASH_IN_PROJECT)
spiffs_create_partition_image(storage ../../lua_eos/native/splash_logo/spiffs_image FLASH_IN_PROJECT)

add_compile_options("-DCONFIG_LCD_PAD_ESP32_S2_KALUGA_V1_3")