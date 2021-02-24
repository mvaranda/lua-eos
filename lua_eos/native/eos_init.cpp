#include <QThread>
#include "eos_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <QDir>


static QThread *thread;

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "log.h"


void luaInit(void);
};

static void luaCppThread(void)
{
    QDir dir; LOG("dir: %s", dir.absolutePath().toStdString().c_str());
  luaInit();

}

void luaCppInit(void)
{
    thread = QThread::create([]{ luaCppThread(); });
    thread->start();
}

extern "C" {

char * argc[] = {
    (char *) "x = 0\n",
    (char *) "print(\"hello Marcelo\")\n",
    (char *) "print(\"LUA is working\")\n",
    (char *) "while(1) do print(x) x=x+1 eos_delay(1000) end\n",

    (char *) NULL
};

static int luac_eos_delay(lua_State *L)
{
    unsigned int d = luaL_checknumber(L, 1);
    usleep(d * 1000);
    return 0;
}

static void register_luacs(lua_State *L)
{
    lua_pushcfunction(L, luac_eos_delay);
    lua_setglobal(L, "eos_delay");
}

#define START_LUA_EOS_FILENAME "../lua_eos/eos.lua"
#define READ_BUF_SIZE 1024

void luaInit(void)
{
    LOG("luaInit...");

    char ** argv = argc;

  char * buf = (char *) calloc(READ_BUF_SIZE,1);

  //int status, result;
  lua_State *L = luaL_newstate();  /* create state */
  if (L == NULL) {
    LOG_E(argv[0], "cannot create state: not enough memory");
    return;
  }

  int error;
  luaL_openlibs(L);
  register_luacs(L);

#if 1
//  FILE * h = fopen(START_LUA_EOS_FILENAME, "r");
//  if ( ! h) {
//      LOG_E("fail to open eos.lua");
//      return;
//  }
  int err;
  if ((err = luaL_loadfile(L, START_LUA_EOS_FILENAME)) != 0) {
      switch(err) {
      case LUA_ERRFILE:
          LOG_E("loadfile: fail to open eos.lua");
          break;
          case LUA_ERRSYNTAX: LOG_E("loadfile: syntax error during pre-compilation");
          break;
        case LUA_ERRMEM:
          LOG_E("loadfile: memory allocation error.");
          break;
      default:
          LOG_E("loadfile: unknown error.");
          break;
      }
      return;
  }
  err = lua_pcall(L, 0, 0, 0);
  if (error) {
    printf( "%s", lua_tostring(L, -1));
    lua_pop(L, 1);  /* pop error message from the stack */
  }

#else
  while (*argv != NULL) {
    error = luaL_loadbuffer(L, *argv, strlen(*argv), "line");
    if ( ! error) error = lua_pcall(L, 0, 0, 0);
    if (error) {
      printf( "%s", lua_tostring(L, -1));
      lua_pop(L, 1);  /* pop error message from the stack */
      break;
    }
    argv++;
  }
#endif
  LOG_E("lua thread terminated");
}


};
