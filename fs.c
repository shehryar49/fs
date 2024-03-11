#include "fs.h"
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>

ZObject nil;

ZObject init()
{
    nil.type = Z_NIL;
    Module* fsmod = vm_allocModule();
    fsmod->name = "fs";
    Module_addSigNativeFun(fsmod,"ls",&LS,"s");
    Module_addSigNativeFun(fsmod,"getcwd",&GETCWD,"");
    Module_addSigNativeFun(fsmod, "dirname",&DIRNAME,"s");
    Module_addSigNativeFun(fsmod, "basename",&BASENAME,"s");
    
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
ZObject GETCWD(ZObject* args,int32_t n)
{
  char buffer[1024];
  const char* path = getcwd(buffer, 1024);
  if(!path)
    return Z_Err(Error,strerror(errno));
  return ZObjFromStr(buffer);
}
ZObject DIRNAME(ZObject* args,int32_t n)
{
  ZStr* str = AS_STR(args[0]);
  char* tmp = malloc((str->len+1)*sizeof(char));
  memcpy(tmp,str->val,str->len);
  tmp[str->len] = 0;
  char* name = dirname(tmp);
  return ZObjFromStr(name);
}
ZObject BASENAME(ZObject* args,int32_t n)
{
  ZStr* str = AS_STR(args[0]);
  char* tmp = malloc((str->len+1)*sizeof(char));
  memcpy(tmp,str->val,str->len);
  tmp[str->len] = 0;
  char* name = basename(tmp);
  return ZObjFromStr(name);
}