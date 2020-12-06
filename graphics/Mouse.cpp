#include <dos.h>
#include ".\graphics\gomphics.h"


int initmouse(void)
{
	_asm{
		mov		ax, 0x0000;
		int		0x0033;
	}
	return _BX;
}

void showmouse(void)
{
	_asm{
		push	es;
		push	ds;
		mov		ax, 0x0001;
		int		0x0033;
		pop		ds;
		pop		es;
	}
}

void getmouse(int &x,int &y,int &status)
{
	int xx,yy,stats;
	_asm{
		mov		ax, 0x0003;
		int		0x0033;
		mov		[stats], bx;
		mov		[xx], cx;
		mov		[yy], dx;
	}
	status = stats;
	x = xx;
	y = yy;
}

void positionmouuse(int x,int y)
{
	_asm{
		mov		ax, 0x0004;
		mov		cx, [x];
		mov		dx, [y];
		int		0x0033;
	}
}


void restrictmouse(int minx,int miny,int maxx,int maxy)
{
	union REGS regs;

	regs.x.cx=minx;
	regs.x.dx=maxx;
	regs.x.ax=0x7;
	int86(0x33,&regs,&regs);
	regs.x.cx=miny;
	regs.x.dx=maxy;
	regs.x.ax=0x8;
	int86(0x33,&regs,&regs);
}



  