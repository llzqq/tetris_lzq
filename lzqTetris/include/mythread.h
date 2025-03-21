#include <pthread.h>
#include <iostream>
#include "table.h"

extern unsigned char flag, buf[2];
extern Table tab; 
extern Block bl;     

class Mythread
{
public:
  void init();
  static void *getkey(void *arg);//线程函数在类里面定义必须定义为static型，以去除类指针。
  static void *paint_loop(void *arg);
}; 