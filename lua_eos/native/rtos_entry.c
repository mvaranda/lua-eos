/*
 * FreeRTOS V202012.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * a more comprehensive test and demo application.
 * The mainSELECTED_APPLICATION setting is used to select between
 * the three
 *
 * If mainSELECTED_APPLICATION = BLINKY_DEMO the simple blinky demo will be built.
 * The simply blinky demo is implemented and described in main_blinky.c.
 *
 * If mainSELECTED_APPLICATION = FULL_DEMO the more comprehensive test and demo
 * application built. This is implemented and described in main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 *
 *******************************************************************************
 * NOTE: Linux will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Linux port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Linux
 * port for further information:
 * https://freertos.org/FreeRTOS-simulator-for-Linux.html
 *
 *******************************************************************************
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Local includes. */
// #include "console.h"

#define    BLINKY_DEMO       0
#define    FULL_DEMO         1

#define mainSELECTED_APPLICATION BLINKY_DEMO

/* This demo uses heap_3.c (the libc provided malloc() and free()). */

/*-----------------------------------------------------------*/
extern void main_blinky( void );
extern void main_full( void );
static void traceOnEnter( void );
/*
 * Only the comprehensive demo uses application hook (callback) functions.  See
 * http://www.freertos.org/a00016.html for more information.
 */
void vFullDemoTickHookFunction( void );
void vFullDemoIdleFunction( void );

/*
 * Prototypes for the standard FreeRTOS application hook (callback) functions
 * implemented within this file.  See http://www.freertos.org/a00016.html .
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char *pcTaskName );
void vApplicationTickHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize );

/*
 * Writes trace data to a disk file when the trace recording is stopped.
 * This function will simply overwrite any trace files that already exist.
 */
static void prvSaveTraceFile( void );

/*-----------------------------------------------------------*/

/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
use a callback function to optionally provide the memory required by the idle
and timer tasks.  This is the stack that will be used by the timer task.  It is
declared here, as a global, so it can be checked by a test that is implemented
in a different file. */
StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/* Notes if the trace is running or not. */
static BaseType_t xTraceRunning = pdTRUE;

/*-----------------------------------------------------------*/

int original_main( void )
{
    /* Do not include trace code when performing a code coverage analysis. */
    #if ( projCOVERAGE_TEST != 1 )
    {
        /* Initialise the trace recorder.  Use of the trace recorder is optional.
        See http://www.FreeRTOS.org/trace for more information. */
        vTraceEnable( TRC_START );

        /* Start the trace recording - the recording is written to a file if
        configASSERT() is called. */
        printf( "\r\nTrace started.\r\nThe trace will be dumped to disk if a call to configASSERT() fails.\r\n" );
        printf( "\r\nThe trace will be dumped to disk if Enter is hit.\r\n" );
        uiTraceStart();
    }
    #endif

//    console_init();
    #if ( mainSELECTED_APPLICATION == BLINKY_DEMO )
    {
//        console_print("Starting echo blinky demo\n");
        //main_blinky();
    }
    #elif ( mainSELECTED_APPLICATION == FULL_DEMO)
    {
//        console_print("Starting full demo\n");
        main_full();
    }
    #else
    {
        #error "The selected demo is not valid"
    }
    #endif /* if ( mainSELECTED_APPLICATION ) */

    return 0;
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
    size of the    heap available to pvPortMalloc() is defined by
    configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
    API function can be used to query the size of free heap space that remains
    (although it does not provide information on how the remaining heap might be
    fragmented).  See http://www.freertos.org/a00111.html for more
    information. */
    vAssertCalled( __FILE__, __LINE__ );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If application tasks make use of the
    vTaskDelete() API function to delete themselves then it is also important
    that vApplicationIdleHook() is permitted to return to its calling function,
    because it is the responsibility of the idle task to clean up memory
    allocated by the kernel to any task that has since deleted itself. */


    usleep(15000);
    traceOnEnter();

    #if ( mainSELECTED_APPLICATION == FULL_DEMO )
    {
        /* Call the idle task processing used by the full demo.  The simple
        blinky demo does not use the idle task hook. */
        vFullDemoIdleFunction();
    }
    #endif
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  This function is
    provided as an example only as stack overflow checking does not function
    when running the FreeRTOS POSIX port. */
    vAssertCalled( __FILE__, __LINE__ );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */

    #if (mainSELECTED_APPLICATION == FULL_DEMO )
    {
        vFullDemoTickHookFunction();
    }
    #endif /* mainSELECTED_APPLICATION */
}

void traceOnEnter()
{
    int ret;
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    ret = select(1, &fds, NULL, NULL, &tv);
    if ( ret > 0 )
    {
    if( xTraceRunning == pdTRUE )
    {
        prvSaveTraceFile();
    }
    /* clear the buffer */
    char buffer[200];
    read(1, &buffer, 200);
    }
}

void vLoggingPrintf( const char *pcFormat,
                     ... )
{
va_list arg;

    va_start( arg, pcFormat );
    vprintf( pcFormat, arg );
    va_end( arg );
}
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{
    /* This function will be called once only, when the daemon task starts to
    execute    (sometimes called the timer task).  This is useful if the
    application includes initialisation code that would benefit from executing
    after the scheduler has been started. */
}
/*-----------------------------------------------------------*/

void vAssertCalled( const char * const pcFileName,
                    unsigned long ulLine )
{
static BaseType_t xPrinted = pdFALSE;
volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Called if an assertion passed to configASSERT() fails.  See
    http://www.freertos.org/a00110.html#configASSERT for more information. */

    /* Parameters are not used. */
    ( void ) ulLine;
    ( void ) pcFileName;


    taskENTER_CRITICAL();
    {
        /* Stop the trace recording. */
        if( xPrinted == pdFALSE )
        {
            xPrinted = pdTRUE;

            if( xTraceRunning == pdTRUE )
            {
                prvSaveTraceFile();
            }
        }

        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while( ulSetToNonZeroInDebuggerToContinue == 0 )
        {
            __asm volatile ( "NOP" );
            __asm volatile ( "NOP" );
        }
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvSaveTraceFile( void )
{
    /* Tracing is not used when code coverage analysis is being performed. */
    #if ( projCOVERAGE_TEST != 1 )
    {
    FILE * pxOutputFile;

        vTraceStop();

        pxOutputFile = fopen( "Trace.dump", "wb" );

        if( pxOutputFile != NULL )
        {
            fwrite( RecorderDataPtr, sizeof( RecorderDataType ), 1, pxOutputFile );
            fclose( pxOutputFile );
            printf( "\r\nTrace output saved to Trace.dump\r\n" );
        }
        else
        {
            printf( "\r\nFailed to create trace dump file\r\n" );
        }
    }
    #endif /* if ( projCOVERAGE_TEST != 1 ) */
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "log.h"

#define START_LUA_EOS_FILENAME "../lua_eos/eos.lua"
#define READ_BUF_SIZE 1024
static int luac_eos_delay(lua_State *L)
{
    unsigned int d = (unsigned int) luaL_checknumber(L, 1);
    usleep(d * 1000);
    return 0;
}

static void register_luacs(lua_State *L)
{
    lua_pushcfunction(L, luac_eos_delay);
    lua_setglobal(L, "eos_delay");
}

static void luaTask(void * arg)
{
    LOG("luaInit...");

//    char ** argv = argc;

//  char * buf = (char *) calloc(READ_BUF_SIZE,1);

  //int status, result;
  lua_State *L = luaL_newstate();  /* create state */
  if (L == NULL) {
    LOG_E("cannot create state: not enough memory");
    return;
  }

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
  if (err) {
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


#define	LUA_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

void rtos_entry(void)
{

    /* Start the two tasks as described in the comments at the top of this
        file. */
    xTaskCreate( luaTask,			/* The function that implements the task. */
                 "luaTask", 		/* The text name assigned to the task - for debug only as it is not used by the kernel. */
                 configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
                 NULL, 							/* The parameter passed to the task - not used in this simple case. */
                 LUA_TASK_PRIORITY, /* The priority assigned to the task. */
                 NULL );							/* The task handle is not required, so NULL is passed. */

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

}