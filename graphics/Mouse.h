#ifndef __MOUSEH__
#define __MOUSEH__

int  initmouse(void);
void showmouse(void);
void hidemouse(void);
int  mouseMoved(void);
void getmouse(int &x,int &y,int &sstatus);

#include ".\graphics\mouse.cpp"

#endif
