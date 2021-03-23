
set(COMPONENT_ADD_INCLUDEDIRS "src")
set(COMPONENT_SRCDIRS "src")

#set_source_files_properties(../../../lua/src/lua_main.c PROPERTIES COMPILE_FLAGS -Wno-maybe-uninitialized)

register_component()
add_definitions(-DLUA_EMBEDDED)

