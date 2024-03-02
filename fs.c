#include "fs.h"
#include <dirent.h>

ZObject nil;

ZObject init()
{
    nil.type = Z_NIL;
    Module* fsmod = vm_allocModule();
    fsmod->name = "fs";
    Module_addSigNativeFun(fsmod,"ls",&LS,"s");
    return ZObjFromModule(fsmod);
}

ZObject LS(ZObject* args,int32_t n)
{
  const char* path = AS_STR(args[0])->val;
  ZList* list = vm_allocList();
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  if (d) 
  {
    while ((dir = readdir(d)) != NULL) 
      if(strcmp(dir->d_name,".") && strcmp(dir->d_name,".."))
        ZList_push(list,ZObjFromStr(dir->d_name));
    closedir(d);
    return ZObjFromList(list);
  }
  else
    return Z_Err(Error,"Error opening path!");
}