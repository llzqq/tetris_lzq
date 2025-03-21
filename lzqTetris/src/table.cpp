#include "table.h"
#include <iostream>

using namespace std; 

void Table::init_table() {
  int i=0, j=0; 
  
  for(i; i<width; i++) {
    for(j=0; j<height; j++) {
      table[i][j]=0;
    }
  }
} 
  
Table::Table(int x, int y) {
  height=y; width=x; count=0;
  init_table();
} 
  
int Table::set_block(Block bl) {
  int x, y;
  int i;
  for(i=0; i<=3; i++) {
    x=bl.g[i].x; y=bl.g[i].y;
    if(table[x][y]!=0 || x>=width || x<0 || y>=height || y<0) {
      return 0;
    }
  }
  for(i=0; i<=3; i++) {
    x=bl.g[i].x; y=bl.g[i].y;
    table[x][y]=1;
  }
  return 1;
} 
  
void Table::clr_block(Block bl) {
  int x, y; 
  
  for(int i=0; i<=3; i++) {
    x=bl.g[i].x; y=bl.g[i].y;
    table[x][y]=0;
  }
} 
  
int Table::clr_line(int y) {
  if(y<0 || y>=height) return 0;
  for(int i=0; i<width; i++) {
    table[i][y]=0;
  }
  return 1;
} 
  
int Table::get_h() {
  return height;
} 
  
int Table::get_w() {
  return width;
} 
  
int Table::if_full(int y) {
  int i=0; 
  
  for(i; i<width; i++) {
    if(table[i][y]==0) return 0;
  }
  return 1;
} 
  
int Table::get_table(int x, int y) {
  return table[x][y];
} 
  
void Table::paint() {
  int i, j; 
  
  for(i=0; i<width+2; i++) cout<<"-"<<flush;
  cout<<"\n"<<flush;
  for(i=height-1; i>=0; i--) {
    cout<<"|"<<flush;
    for(j=0; j<width; j++) {
      if(table[j][i]==0) cout<<" "<<flush;
      else cout<<"▣"<<flush;
    }
    if(i==10)
      cout<<"|  得分："<<get_count()<<endl;
    else if(i==7)
      cout<<"|  Press 'q' to quit!"<<endl;
    else
      cout<<"|"<<endl;
  }
  for(i=0; i<width+2; i++) cout<<"-"<<flush;
  cout<<"\n"<<flush;
  //cout<<"得分："<<get_count()<<endl;
} 
  
void Table::move_line(int y) {
  int i, j; 
  
  for(i=y; i<height-1; i++) {
    for(j=0; j<width; j++) {
      table[j][i]=table[j][i+1];
    }
  }
} 
  
void Table::set_count(int c) {
  count+=c;
} 
  
int Table::get_count() {
  return count;
} 
  