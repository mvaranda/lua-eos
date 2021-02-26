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

extern void rtos_entry(void);

};

static void luaCppThread(void)
{
    QDir dir; LOG("dir: %s", dir.absolutePath().toStdString().c_str());
    rtos_entry();
}

void luaCppInit(void)
{
    thread = QThread::create([]{ luaCppThread(); });
    thread->start();
}

