set(component_srcs
	"gt911.c"
	)

	set(COMPONENT_PRIV_INCLUDEDIRS 
	"$ENV{IDF_PATH}/components/freertos/include/freertos"
	"../../../lua_eos/native"
	"../eos_native"
	"." )

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS ${COMPONENT_PRIV_INCLUDEDIRS})

#add_definitions(-DLOG_LOCAL_LEVEL=ESP_LOG_DEBUG)
