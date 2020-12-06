#ifndef __GOMPHICSH__
#define __GOMPHICSH__

int			MAXX,MAXY;
char		BPP;
char		CHARSIZE = 0;
long		COLOR = 0x00ffffff;
long		BGCOLOR = 0x0;
int			_X;
int			_Y;

int			curBank;
/*	Global Constants	*/
const double PI = 3.1415927;
const int _DETECT_RESOLUTION	= 0x00FF;
const int _DETECT_COLOR			= 0x000F;
const int _text			= 0x0003;
const int _640x480x4    = 0x0012;
const int _800x600x4    = 0x0102;
const int _1024x768x4   = 0x0104;
const int _640x480x8    = 0x0101;
const int _640x480x16   = 0x0111;
const int _640x480x32   = 0x0112;
const int _800x600x8    = 0x0103;
const int _800x600x16   = 0x0114;
const int _800x600x32   = 0x0115;
const int _1024x768x8   = 0x0105;
const int _1024x768x16  = 0x0117;
const int _1024x768x32	= 0x0118;


#ifdef __cplusplus
extern "C" {
#endif


/*	Driver Functions	*/
void getAllModes(void);
int initgraph(int mode);
void closegraph(void);

/*	 Graphics Functions	*/
void putpixel(long x,long y,long color);


void setcolor(long color);
long getcolor(void);
void setbkcolor(long color);
long getbkcolor(void);
int  getmaxmode(void);
long getmaxcolor(void);
long getpixel(long x,long y);
int  getx(void);
int  gety(void);
int  getmaxx(void);
int  getmaxy(void);

int  saveBMP24(long int x1,long int y1,long int x2,long int y2,char *filename);
int  showBMP24(int x1,int y1,const char *filename);


/*	 Text Handling	*/
void loadfont(void);
void settextstyle(int font, int direction, int charsize);
void putchr(int x1,int y1,unsigned char char_no,long color);
void outtextxy(int x1,int y1,const char *str);
void outtext(const char *str);

#ifdef __cplusplus
};
#endif


#include ".\graphics\gomphics.cpp"
#include ".\graphics\bmp.cpp"
#include ".\graphics\font.cpp"

#endif
