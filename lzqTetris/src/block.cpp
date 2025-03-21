#include "block.h"
#include <cstdlib>

void Block::def_block(grid g1, grid g2, grid g3, grid g4) {
  g[0]=g1; g[1]=g2; g[2]=g3; g[3]=g4;
} 
  
void Block::rotate() {
  int x, y, i=0; 
  
  for(i; i<=3; i++) {
    x=g[i].x-center.x; y=g[i].y-center.y;
    g[i].x=center.x+y; g[i].y=center.y-x;
  }
} 
  
void Block::move(int dir) {
  int d=dir, i=0; 
  
  switch(d) {
  case UP: {
    for(i; i<=3; i++) g[i].y++;
    center.y++; break;
        }
  case DOWN: {
    for(i; i<=3; i++) g[i].y--;
    center.y--; break;
        }
  case LEFT: {
    for(i; i<=3; i++) g[i].x--;
    center.x--; break;
        }
  case RIGHT: {
    for(i; i<=3; i++) g[i].x++;
    center.x++; break;
        }
  }
} 
  
void Block::set_cen(grid g) {
  center=g;
} 
  
grid Block::get_cen() {
  return center;
} 
  
void Block::set_type(int t) {
  type=t;
} 
  
int Block::get_type() {
  return type;
} 
  
void Block::back() {
  int x, y, i=0; 
  
  for(i; i<=3; i++) {
    x=g[i].x-center.x; y=g[i].y-center.y;
    g[i].x=center.x-y; g[i].y=center.y+x;
  }
} 
  
void Block::creat_block(int x, int y) {  //随机创建方块
  int ran;
  grid g[BLOCK_SIZE]; 
  
  ran=1+rand()%7;
  switch(ran) {
  //L
  case 1: {
    g[0].x=x/2; g[0].y=y-3;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x; g[2].y=g[0].y+2;
    g[3].x=g[0].x+1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(1); break;
      }
  //反L
  case 2: {
    g[0].x=x/2; g[0].y=y-3;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x; g[2].y=g[0].y+2;
    g[3].x=g[0].x-1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(2); break;
      }
  //Z
  case 3: {
    g[0].x=x/2; g[0].y=y-2;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x+1; g[2].y=g[0].y+1;
    g[3].x=g[0].x-1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(3); break;
      }
  //反Z
  case 4: {
    g[0].x=x/2; g[0].y=y-2;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x+1; g[2].y=g[0].y+1;
    g[3].x=g[0].x-1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(4); break;
      }
  //田
  case 5: {
    g[0].x=x/2; g[0].y=y-2;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x+1; g[2].y=g[0].y+1;
    g[3].x=g[0].x+1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(5); break;
      }
  //1
  case 6: {
    g[0].x=x/2; g[0].y=y-3;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x; g[2].y=g[0].y+2;
    g[3].x=g[0].x; g[3].y=g[0].y-1;
    set_cen(g[0]); set_type(6); break;
      }
  //山
  case 7: {
    g[0].x=x/2; g[0].y=y-2;
    g[1].x=g[0].x; g[1].y=g[0].y+1;
    g[2].x=g[0].x-1; g[2].y=g[0].y;
    g[3].x=g[0].x+1; g[3].y=g[0].y;
    set_cen(g[0]); set_type(7); break;
      }
  default: ;
  }
  def_block(g[0], g[1], g[2], g[3]);
} 
  