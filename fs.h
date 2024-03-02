#ifndef FS_H_
#define FS_H_
#ifdef _WIN32
  #include "C:\\zuko\\zapi.h"
  #define EXPORT __declspec(dllexport)
#else
  #include "/opt/zuko/include/zapi.h"
  #define EXPORT
#endif


EXPORT ZObject init();
// Module functionality
EXPORT ZObject LS(ZObject*,int32_t);


#endif