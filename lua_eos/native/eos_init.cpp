/***************************************************************
 *
 *                 This code is part of LUA_EOS
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

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
#include "mos.h"
#include "lua_eos.h"

extern void rtos_entry(void);

};

static void luaCppThread(void)
{
    QDir dir; LOG("dir: %s", dir.absolutePath().toStdString().c_str());


#ifdef MOS_DESKTOP
    mos_thread_h_t task = mos_thread_new( "luaTask", luaTask, NULL, LUA_EOS_STACK_SIZE, LUA_TASK_PRIORITY );

#else
    rtos_entry();
#endif
}

void luaCppInit(void)
{
    thread = QThread::create([]{ luaCppThread(); });
    thread->setStackSize(1024 * 1024);
    LOG("Stack size = %d", thread->stackSize());

    thread->start();
}

