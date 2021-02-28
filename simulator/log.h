#ifndef LOG_H
#define LOG_H
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


#include <stdio.h>
#if 1
#define LOG         qDebugC
#define LOG_E       qDebugC
#define LOG_I       qDebugC
#define LOG_W       qDebugC
#else
#define LOG         printf
#define LOG_E       printf
#define LOG_I       printf
#define LOG_W       printf
#endif


#ifdef __cplusplus
  extern "C" {
#endif


  void qDebugC(const char * format,...);


#ifdef __cplusplus
}
#endif




#endif // LOG_H
