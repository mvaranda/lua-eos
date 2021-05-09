
set(COMPONENT_ADD_INCLUDEDIRS "../../../lua/src"
  "../../../")

#set(COMPONENT_SRCDIRS "../../../lua/src")

set(COMPONENT_SRCS
  "../../../lua/src/lapi.c"
	"../../../lua/src/linit.c"
  "../../../lua/src/lstrlib.c"
  "../../../lua/src/lauxlib.c"
	"../../../lua/src/liolib.c"
  "../../../lua/src/ltable.c"
  "../../../lua/src/lbaselib.c"
	"../../../lua/src/llex.c"
  "../../../lua/src/ltablib.c"
  "../../../lua/src/lcode.c"
	"../../../lua/src/lmathlib.c"
  "../../../lua/src/ltm.c"
  "../../../lua/src/lcorolib.c"
	"../../../lua/src/lmem.c"
  "../../../lua/src/lua.c"
  "../../../lua/src/lctype.c"
	"../../../lua/src/loadlib.c"
  "../../../lua/src/luac.c"
  "../../../lua/src/ldblib.c"
	"../../../lua/src/lobject.c"
  "../../../lua/src/lundump.c"
  "../../../lua/src/ldebug.c"
	"../../../lua/src/lopcodes.c"
  "../../../lua/src/lutf8lib.c"
  "../../../lua/src/ldo.c"
	"../../../lua/src/loslib.c"
  "../../../lua/src/lvm.c"
  "../../../lua/src/ldump.c"
	"../../../lua/src/lparser.c"
  "../../../lua/src/lzio.c"
  "../../../lua/src/lfunc.c"
	"../../../lua/src/lstate.c"
  "../../../lua/src/lgc.c"
	"../../../lua/src/lstring.c"
)


register_component()
add_definitions(-DLUA_EMBEDDED -DUSE_DL_PREFIX -DMSPACES=1 -DUSE_DOUG_LEA_MALLOC -DONLY_MSPACES=0 -DNO_MALLINFO=0 -DHAVE_MMAP=0)
