#ifndef EOS_CONFIG_H
#define EOS_CONFIG_H
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

#ifdef MOS_DESKTOP
  #define START_LUA_EOS_FILENAME "../lua_eos/eos.lua"
  #define EOS_APP_FILENAME "../eos_app/app.lua"
#else
  #define START_LUA_EOS_FILENAME "/spiffs/eos.lua"
  #define EOS_APP_FILENAME "/spiffs/app.lua"
#endif

//#ifdef MOS_DESKTOP
  #define HAS_LVGL // has LVGL
//  #define HAS_LVGL_SPLASH
//#endif

#define EV_QUEUE_LENGTH    32

#ifdef MOS_DESKTOP
  #define LOWEST_PRIORITY 1 // assume low value has low priority
#else
  #define LOWEST_PRIORITY tskIDLE_PRIORITY
#endif

// Stack sizes
#define LUA_EOS_STACK_SIZE (8 * 1024) // 8k
#define LVGL_TASK_STACK_SIZE (8 * 1024) // 8K

// Priorities
#define	LUA_TASK_PRIORITY		( LOWEST_PRIORITY + 1 )
#define	LVGL_TASK_PRIORITY		( LOWEST_PRIORITY + 2 )



//-----------------------------------------------------------------
#endif // EOS_CONFIG_H
