/****************************************************************************/
//
//  Module:          $URL: $
//  Created By:      Marcelo Varanda
//  Revision:        $Revision: $
//  Last Updated By: $Author: $
//  Last Updated:    $Date:  $
//
//  Description: Part of M-OS 
//
//  Copyright (c) 2021 Marcelo Varanda, all rights reserved.
//
//
/****************************************************************************/

#include "eos_config.h"
#include "lua.h"
#include "splash.h"
#include "lvgl_lua.h"
#include "log.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void bind_init_lvgl_modules(lua_State *L);

void lua_bindings_registration(lua_State *L)
{
#ifdef HAS_LVGL
  bind_init_lvgl_modules(L);
  lvgl_lua_init(L);
  #ifdef  MOS_DESKTOP_SPLASH
    lvgl_splash_init(L);
  #endif
#endif // HAS_LVGL
}



#ifdef __cplusplus
  }
#endif


