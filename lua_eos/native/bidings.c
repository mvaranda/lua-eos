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

#include "lua.h"

extern void lvgl_lua_init(lua_State *L); // TODO: use heaer file


#ifdef __cplusplus
extern "C" {
#endif

void lua_bindings_registration(lua_State *L)
{
  lvgl_lua_init(L);
}



#ifdef __cplusplus
  }
#endif


