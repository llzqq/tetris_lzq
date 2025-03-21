#ifndef BLOCK_H
#define BLOCK_H

struct grid{int x; int y;};    //坐标 
#define TABLE_SIZE 20
#define BLOCK_SIZE 4
#define SLEEP_TIME 500 

class Block
{
public:
  enum direct{UP, DOWN, LEFT, RIGHT};         //定义方向
  grid g[BLOCK_SIZE];                 //方块的坐标信息 
  
  void def_block(grid g1, grid g2, grid g3, grid g4); //定义方块
  void rotate();                   //旋转方块
  void move(int dir);                 //移动方块
  void set_cen(grid g);                //设置方块旋转中心
  grid get_cen();                   //获取方块旋转中心
  void set_type(int t);                //设置方块种类
  int get_type();                   //获取方块种类
  void back();                    //旋转还原
  void creat_block(int x, int y);           //随机生成方块 
  
private:
  grid center;                    //方块旋转中心
  int type;                      //方块类型 
  
}; 

#endif