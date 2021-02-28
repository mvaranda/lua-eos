#ifndef __EOS_LUA_H__
#define __EOS_LUA_H__
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

// Stack sizes
#define LUA_EOS_STACK_SIZE (1 * 1024) // 1k

// Priorities
#define	LUA_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )


void luaTask(void * arg);

//---------------------------------------------------------
#endif
