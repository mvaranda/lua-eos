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
#define EOS_VERSION "0.02"

#ifdef MOS_DESKTOP
  #define START_LUA_EOS_FILENAME "../target_files/eos.lua"
  #define EOS_APP_FILENAME "../target_files/app.lua"
  #define EOS_PLATFORM "SIMULATOR"

#else // for now assume ESP32
  #define START_LUA_EOS_FILENAME "/spiffs/eos.lua"
  #define EOS_APP_FILENAME "/spiffs/app.lua"
  #define EOS_PLATFORM "ESP32"
#endif


#define HAS_LVGL // has LVGL

#ifdef HAS_LVGL
  #define SHOW_ANIMATED_SPLASH
  #ifdef MOS_DESKTOP
    #define MOS_DESKTOP_SPLASH
  #endif
#endif

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
