#pragma  once
#include<stdio.h>
#include<fcntl.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>
struct termios save; //保存原始的终端输入状态
void recover_keyboard();
int init_keyboard()
{
  struct termios tmp;
  int ret=tcgetattr(0,&save);//获取读缓冲区的termios属性
  if(ret<0)
    return -1;
  tmp=save; 
  tmp.c_lflag&=~(ECHO|ICANON); //关闭屏幕回显和规范输入模式
  ret=tcsetattr(0,TCSANOW,&tmp);//设置输入模式为不等数据传送完成,直接改变状态
  if(ret<0)
    return -1;
  return 0;
}
int get_key()
{
  int key;
  read(0,&key,1);
  return key;
}
int getch()
{
  init_keyboard();
  int key=get_key();
  recover_keyboard();
  return key;
}
void recover_keyboard()
{
  tcsetattr(0,TCSAFLUSH,&save);
}
