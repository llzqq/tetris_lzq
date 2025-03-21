#include <iostream>
#include <cstdlib>
#include <time.h> 
  
#include<termios.h>
#include<fcntl.h> 
#include <unistd.h>

#include "table.h"
#include "mythread.h"

using namespace std;


  
////////////主函数部分/////////////////////// 
  
int main()
{
  //Table tab(15, 20); //构造一个15,20的棋盘
  //Block bl;      //构造一个落下方块
  Mythread thread;
  thread.init();
  int dir,i,c;
  while(true) {
    //生成方块
    srand(time(0));
    bl.creat_block(tab.get_w(), tab.get_h());
    //判断游戏是否结束
    if( !tab.set_block(bl) ) {
      system("clear");
      cout<<"GAME OVER!"<<endl;
      flag=2;
      cout<<"PRESS ANY KEY TO CONTINUE!"<<endl;
      while(1);
    }
    ///////////行动按键判定
    while(true){
      usleep(500000);    //暂停500 MS
      /////////////向下移动一格
      tab.clr_block(bl);    //清空上一次方块位置
      bl.move(bl.DOWN);    //向下移动一步
      if(!tab.set_block(bl)) {   //是否触底
        bl.move(bl.UP);    //如果触底，还原触底前位置
        tab.set_block(bl);
        break;
      }
    }
    //如果满行则消行
    for(i=0; i<tab.get_h(); i++) {
      if(tab.if_full(i)) { //是否满行
        tab.clr_line(i); //如果是，消行
        tab.move_line(i); //将所消行的上面的棋盘信息下移
        i--;      //下移后，重新检查这一行是否满（可能出现几行同时消去）
        tab.set_count(100); //记录得分
      }
    } 
  
  }
  return 0;
} 