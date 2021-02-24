#ifndef LOG_H
#define LOG_H


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
