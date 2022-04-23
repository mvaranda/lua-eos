from building import *

cwd  = GetCurrentDir()
CPPPATH = [cwd]

LOCAL_CFLAGS = ''
LOCAL_CFLAGS += ' -DLUA_EMBEDDED'
LOCAL_CFLAGS += ' -Wno-unused-function'

src = Glob("native/*.c") + Glob("native/lua/src/*.c", exclude=['native/lua/src/luac.c'])

group = DefineGroup('lua-eos', src, depend = ['PKG_USING_LUA_EOS'], CPPPATH = CPPPATH, LOCAL_CFLAGS = LOCAL_CFLAGS)

Return('group')
