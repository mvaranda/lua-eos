#ifndef _MAIN_DEFS_H_
#define _MAIN_DEFS_H_
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
#include <stdint.h>
#include <stdbool.h>

#define USER_PARTITION_LABLE NULL // from doc: 
                                  // Optional, label of SPIFFS partition to use. If set to NULL, first partition with subtype=spiffs will be used. 

char * get_line(bool echo);
void toConsole(char * msg);
int get_console_byte(uint32_t timeout);
void byteToConsole(int c);
//-----------------------------------------
#endif

