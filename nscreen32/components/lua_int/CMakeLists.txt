
set(COMPONENT_ADD_INCLUDEDIRS "../../../lua/src"
  "../../../")
set(COMPONENT_SRCDIRS "../../../lua/src")

register_component()
add_definitions(-DLUA_EMBEDDED -DUSE_DL_PREFIX -DMSPACES=1 -DUSE_DOUG_LEA_MALLOC -DONLY_MSPACES=0 -DNO_MALLINFO=0 -DHAVE_MMAP=0)
