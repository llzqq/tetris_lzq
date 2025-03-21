#ifndef TABLE_H
#define TABLE_H
#include "block.h"


class Table
{
public: 
  
  Table() {             //构造棋盘
    height=20; width=10; count=0;
    init_table();
  }
  Table(int x, int y);
  int set_block(Block bl);     //安设方块
  void clr_block(Block bl);     //清除方块
  int clr_line(int y);       //消行
  int get_h();           //获取棋盘高度
  int get_w();           //获取棋盘宽度
  int if_full(int y);        //判定是否满行
  int get_table(int x, int y);   //获取棋盘上点信息
  void paint();           //绘制棋盘
  void move_line(int y);      //整行下移
  void set_count(int c);      //记录得分
  int get_count();         //获取得分 
  
private:
  int table[TABLE_SIZE][TABLE_SIZE];//棋盘
  int height, width;        //棋盘的高和宽
  int count;            //得分 
  
  void init_table();        //棋盘初始化 
  
}; 

#endif