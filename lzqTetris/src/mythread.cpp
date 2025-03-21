#include "mythread.h"

#include <iostream>
#include <cstdlib>
#include <time.h> 
  
#include<termios.h>
#include<fcntl.h> 
#include <unistd.h>

using namespace std;

unsigned char flag=1,buf[2];//全局变量
Table tab(15, 20); //构造一个15,20的棋盘
Block bl;      //构造一个落下方块

void Mythread::init()
{
  pthread_t ntid,ntid2;
  int err,err2;
  err = pthread_create(&ntid,NULL,getkey,NULL);
  err2 = pthread_create(&ntid2,NULL,paint_loop,NULL);
  if(err != 0 || err2 != 0){
    cout<<"can't create thread!"<<endl;
    exit(0);
  }
} 
  

void* Mythread::paint_loop(void *arg)
{
  while(1)
  {
    system("clear");
    tab.paint();
    usleep(50000);    //暂停50 MS
  }
}
void* Mythread::getkey(void *arg)
{
  struct termios saveterm,nt;
  fd_set rfds,rs;
  struct timeval tv;
  int i=0,q,r,fd=0;
  tcgetattr(fd,&saveterm);
  nt=saveterm; 
  
  nt.c_lflag &= ~ECHO;
  nt.c_lflag &= ~ISIG;
  nt.c_lflag &= ~ICANON; 
  
  tcsetattr(fd,TCSANOW,&nt); 
  
  FD_ZERO(&rs);
  FD_SET(fd,&rs);
  tv.tv_sec=0;
  tv.tv_usec=0;
  while(1)
  {
    read(0,buf,1);
    r=select(fd+1,&rfds,NULL,NULL,&tv);
    if(r<0)
    {
      write(1,"select() error.\n",16);
    }
    rfds=rs;
    if(flag==2||buf[0]==113)//游戏结束或者用户按下'q'键，则程序退出
    {
      tcsetattr(0,TCSANOW,&saveterm);
      exit(0);
    }
    if(buf[0]<=68&&buf[0]>=65) flag=0;//如果按的键是方向键，则将标志位置0并执行相应的处理.
    if(flag==0)
    {
      if(buf[0]==65) {
      //if(dir!=0) {
        if(bl.get_type()==5) continue; //如果出现田字形则不作旋转
        tab.clr_block(bl);      //清空方块上一次位置
        bl.rotate();         //开始旋转
        if(!tab.set_block(bl)) {   //将旋转后的方块写在棋盘上
          bl.back();       //如果写失败(例如到边线了，或卡住了)则还原旋转前位置
          continue;
          tab.set_block(bl);
        }
      }
      //下（加速下落）
      //dir=GetAsyncKeyState(VK_DOWN);  //获取向下
      if(buf[0]==66) {
        tab.clr_block(bl);     //清空方块上一次位置
        bl.move(bl.DOWN);      //向下移动一步
        if(!tab.set_block(bl)) {  //将移动后的方块写在棋盘上
          bl.move(bl.UP);     //如果失败，则还原到移动前的位置（即上移一步）
          tab.set_block(bl);
        }
      }
      //左（左移）
      //dir=GetAsyncKeyState(VK_LEFT);
      if(buf[0]==68) {
        tab.clr_block(bl);
        bl.move(bl.LEFT);
        if(!tab.set_block(bl)) {
          bl.move(bl.RIGHT);
          tab.set_block(bl);
        }
      }
      //右（右移）
      //dir=GetAsyncKeyState(VK_RIGHT);
      if(buf[0]==67) {
        tab.clr_block(bl);
        bl.move(bl.RIGHT);
        if(!tab.set_block(bl)) {
          bl.move(bl.LEFT);
          tab.set_block(bl);
        }
      }
      flag=1;
    }
  }
  tcsetattr(0,TCSANOW,&saveterm);
} 