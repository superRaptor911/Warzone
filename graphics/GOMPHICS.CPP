#include	<stdlib.h>
#include	<math.h>
#include	<dos.h>
#include ".\graphics\gomphics.h"

#define DIRECT_BANKING

extern char BPP;
extern long COLOR;
extern int  _X;
extern int  _Y;

int			bytesperline;
unsigned	bankShift;
int			oldMode;
void		(*bankSwitch) (void);

typedef enum
{
	memPL	=3,
	memPK	=4,
	memRBG	=6,
	memYUV	=7
} memModels;

const unsigned short MODES[]={0x118,0x117,0x116,0x105,0x104,		//1024x768
								0x115,0x114,0x113,0x103,0x102,		//800x600
								0x112,0x111,0x110,0x101,0x012,		//640x480
								0xFFFF};

const unsigned short MODES_COL[]={0x118,0x115,0x112,				//32,24 bit
								0x117,0x114,0x111,					//16 bit
								0x116,0x113,0x110,					//15 bit
								0x105,0x103,0x101,					//8 bit
								0x104,0x102,0x012,					//4 bit
								0xFFFF};
/*-----------------------------------------------------------------------*/



struct
{
	char 	VESASignature[4];
	short 	VESAVersion;
	char 	*OEMStringPtr;
	long 	Capabilities;
	unsigned*VideoModePtr;
	short   TotalMemory;
	short 	OemSoftwareRev;
	char 	*OemVendorNamePtr;
	char 	*OemProductNamePtr;
	char 	*OemProductRevPtr;
	char 	reserved[222];
	char 	OemData[256];
}VbeInfoBlock;

struct
{
	unsigned short	ModeAttributes;
	unsigned char	WinAAttributes;
	unsigned char	WinBAttributes;
	unsigned short	WinGranularity;
	unsigned short	WinSize;
	unsigned short	WinASegment;
	unsigned short	WinBSegment;
	void (*WinFuncPtr) (void);
	unsigned short	BytesPerScanLine;
	unsigned short	XResolution;
	unsigned short	YResolution;
	unsigned char	XCharSize;
	unsigned char	YCharSize;
	unsigned char	NumberOfPlanes;
	unsigned char	BitsPerPixel;
	unsigned char	NumberOfBanks;
	unsigned char	MemoryModel;
	unsigned char	BankSize;
	unsigned char	NumberOfImagePages;
	unsigned char	res1;
	unsigned char	RedMaskSize;
	unsigned char	RedFieldPosition;
	unsigned char	GreenMaskSize;
	unsigned char	GreenFieldPosition;
	unsigned char	BlueMaskSize;
	unsigned char	BlueFieldPosition;
	unsigned char	RvsdMaskSize;
	unsigned char	RsvdFieldPosition;
	unsigned char	DirectColorModeInfo;
	unsigned char	res2[216];
} ModeInfoBlock;



int getVbeInfo(void)
{
	union  REGS in,out;
	struct SREGS segs;
	char   *VbeInfo=(char*) &VbeInfoBlock;
	unsigned retrn;
	in.x.ax = 0x4F00;
	in.x.di = FP_OFF(VbeInfo);
	segs.es = FP_SEG(VbeInfo);
	int86x(0x10, &in,&out,&segs);
	return (out.x.ax == 0x004F);
}

int getModeInfo(int mode)
{
	union  REGS in,out;
	struct SREGS segs;
	char	*modeInfo = (char*) &ModeInfoBlock;
	if (mode<0x0100)
	{
		return 0;
	}
	in.x.ax = 0x4F01;
	in.x.cx = mode;
	in.x.di = FP_OFF(modeInfo);
	segs.es = FP_SEG(modeInfo);
	int86x(0x0010,&in,&out,&segs);
   //	mx=ModeInfoBlock.WinASegment;
	if (out.x.ax != 0x004F)
	{
		return 0;
	}
	if (ModeInfoBlock.ModeAttributes & 0x0001)
	{
		return 1;
	}
	return 0;
}
void getAllModes(void)
{
	for(int mode=0x100;mode<0x200;mode++)
	{
		if(getModeInfo(mode))
		{
			cout<<hex<<mode<<"h\t";
		}
	}
	cout<<endl;
}

int getVBEMode(void)		//get present VBE mode
{
	int mode;
	_asm{
		mov ax, 0x4F03;
		int 0x0010;
		mov [mode], bx;
	}
	return mode;
}


int initgraph(int mode)
{
	/*if(mode == oldMode)
	{
		return 0;
	}*/
	if(mode == _DETECT_COLOR)
	{
		for(int mno=0; MODES[mno] != 0xFFFF; mno++)
		{
			if(getModeInfo(MODES[mno]) != 0)
			{
				mode = MODES_COL[mno];
				break;
			}
		}
	}
	if(mode == _DETECT_RESOLUTION)
	{
		for(int mno=0; MODES[mno] != 0xFFFF; mno++)
		{
			if(getModeInfo(MODES[mno]) != 0)
			{
				mode = MODES[mno];
				break;
			}
		}
	}
	oldMode = getVBEMode();
	int retn;
	_asm{
		mov ax, 0x4F02;
		mov bx, [mode];
		int 0x0010;
		mov [retn], ax;
	}
	if (retn != 0x004F)
	{
		return 0;
	}
	getModeInfo(mode);
	MAXX = ModeInfoBlock.XResolution-1;
	MAXY = ModeInfoBlock.YResolution-1;
	BPP  = ModeInfoBlock.BitsPerPixel/8;
	bankSwitch = ModeInfoBlock.WinFuncPtr;
	loadfont();
	return 1;
}



void int10ax0501(struct REGPACK *regs)
{
	_asm{
		mov bx,0x0000;
		mov ax,0xB000;		
	    }
}

void setBank(int bank)
{
	union REGS in,out;
	if (bank == curBank)
	{
		return;
	}
	curBank = bank;
	bank  <<= bankShift;
	_asm{
		mov bx,0x0000;
		mov dx,[bank];
	}
	bankSwitch();
}

void putpixel(long x,long y,long color)
{
	if(color<0)
	{
		color = -color;
	}
	if (x>799 || y>599 || x<0 || y<0)
	{
		return;
	}

	unsigned rw    = color >> 16;
	unsigned bw    = color &  0x0000FFFF;

	long addr = (y*(MAXX+1)+x)*BPP;
	unsigned offset_b = addr & 0xFFFF;

	setBank((int)(addr >> 16));

	_asm {
		push 	ds;
		push	es;
		mov 	ax, 0xA000;
		mov		es, ax;

		mov 	bx, [offset_b];
		mov		di, bx;

		mov 	ax, [bw];
		mov		es: [di],   ax;

		mov 	ax, [rw];
		mov		es: [di+2], ax;

		pop		es;
		pop		ds;
	}
}

void xputpixel(long x,long y,unsigned char r,unsigned char g,unsigned char b)
{

	if (x>799 || y>599 || x<0 || y<0)
	{
		return;
	}
	long addr = (y*(800)+x)*4;
	unsigned offset_b = addr & 0xFFFF;

	setBank((int)(addr >> 16));

	vb[offset_b]=r;
	vb[offset_b+1]=g;
	vb[offset_b+2]=b;

}



void setcolor(long color)
{
	COLOR = color;
}

long getcolor(void)
{
	return COLOR;
}

void setbkcolor(long color)
{
	BGCOLOR = color;
}

long getbkcolor(void)
{
	return BGCOLOR;
}

int  getmaxmode(void)
{
	int i = 0;
	int mode;
	while(MODES[i]!= 0xFFFF)
	{
		if(ModeInfoBlock.ModeAttributes)
		{
			mode = MODES[i];
		}
		i++;
	}
	return mode;
}



long getpixel(long x,long y)
{

	if(x<0)
	{
		x=0;
	}
	if(y<0)
	{
		y=0;
	}
	if(x>MAXX)
	{
		x=MAXX;
	}
	if(y>MAXY)
	{
		y=MAXY;
	}
	
	long addr = (y*(MAXX+1)+x)*BPP;
	unsigned offset_b = addr & 0xFFFF;

	setBank((int)(addr >> 16));
	
	long color;
	unsigned colorh;
	unsigned colorl;

	_asm {
		push 	ds;
		push	es;
		mov 	ax, 0xA000;
		mov		es, ax;

		mov 	bx, [offset_b];
		mov		si, bx;

		mov		ax, es: [si];
		mov		[colorl],ax;

		mov		ax, es: [si+2];
		mov		[colorh],ax;

		pop		es;
		pop		ds;
	}
	color = (((long)colorh) << 16) + colorl;
	return color;
}

int getx(void)
{
	return _X;
}

int gety(void)
{
	return _Y;
}

long imagesize(int x1, int y1, int x2, int y2)
{
	long x = abs(x2-x1);
	long y = abs(y2-y1);
	char bytes = BPP;
	if(bytes == 4)
	{
		bytes = 3;
	}
	return (x*y*bytes+5); //	5 to store dx, dy, bytes in 1st 2 'int' & 'char' locations .	
}

void bar(int x1,int y1,int x2,int y2)
{
	for(int y=y1;y<=y2;y++)
	{
		for(int x=x1;x<=x2;x++)
		{
			putpixel(x,y,COLOR);
		}
	}
	_X = x2;
	_Y = y2;
}

int getmaxx(void)
{
	return MAXX;
}

int getmaxy(void)
{
	return MAXY;
}
