#include ".\graphics\gomphics.h"
#include <string.h>

unsigned font[256][64];
	

void loadfont(void)
{
	FILE *f;
	f=fopen("Font8x8.bmp","r");
	fseek(f,1078,SEEK_SET);

	char bits,bit0,bit1,bit2,bit3,bit4,bit5,bit6,bit7;
	int ascii;
	for(bits=0;bits<64;bits+=8)
	{
		for(ascii=0;ascii<256;ascii++)
		{
			font[ascii][bits+7] = fgetc(f) ? 1:0;
			font[ascii][bits+6] = fgetc(f) ? 1:0;
			font[ascii][bits+5] = fgetc(f) ? 1:0;
			font[ascii][bits+4] = fgetc(f) ? 1:0;
			font[ascii][bits+3] = fgetc(f) ? 1:0;
			font[ascii][bits+2] = fgetc(f) ? 1:0;
			font[ascii][bits+1] = fgetc(f) ? 1:0;
			font[ascii][bits+0] = fgetc(f) ? 1:0;
		}
	}
	fclose(f);
}

void outtextxy(int x1,int y1,const char *str)
{
	char ch;
	int tx = x1,ty = y1;
	int i=0;

	while(str[i]!='\0')
	{
		putchr(tx,ty,str[i++],COLOR);
		tx += 9;
	}
	_X = tx;
	_Y = ty;
}

void D_putchr(int x1,int y1,unsigned char char_no,long color)
{
	

	int x=x1;
	int y=y1;

	for(int i=63;i>=0;i--)
	{
		if(CHARSIZE)
		{
			if((font[char_no][i]))
			{
				display_pixel_mem(x,y,color);
				y++;
				display_pixel_mem(x++,y--,color);
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=2;
				x=x1;
			}
		}
		else
		{
			if((font[char_no][i]))
			{
				display_pixel_mem(x,y,color);
				x++;
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=1;
				x=x1;
			}
		}
	}
	
}

void D_outtextxy(int x1,int y1,const char *str)
{
	char ch;
	int tx = x1,ty = y1;
	int i=0;

	while(str[i]!='\0')
	{
		D_putchr(tx,ty,str[i++],COLOR);
		tx += 9;
	}
	_X = tx;
	_Y = ty;
}

void P_putchr(int x1,int y1,unsigned char char_no,long color)
{
	

	int x=x1;
	int y=y1;

	for(int i=63;i>=0;i--)
	{
		if(CHARSIZE)
		{
			if((font[char_no][i]))
			{
				direct_pixel_mem(visual_page,x,y,color);
				y++;
				direct_pixel_mem(visual_page,x++,y--,color);
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=2;
				x=x1;
			}
		}
		else
		{
			if((font[char_no][i]))
			{
				direct_pixel_mem(visual_page,x,y,color);
				x++;
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=1;
				x=x1;
			}
		}
	}
	
}

void P_outtextxy(int x1,int y1,const char *str)
{
	char ch;
	int tx = x1,ty = y1;
	int i=0;

	while(str[i]!='\0')
	{
		P_putchr(tx,ty,str[i++],COLOR);
		tx += 9;
	}
	_X = tx;
	_Y = ty;
}

void outtext(const char *str)
{
	char ch;
	int tx = _X,ty = _Y;
	int i=0;

	while(str[i]!='\0')
	{
		putchr(tx,ty,str[i++],COLOR);
		tx += 9;
	}
	_X = tx;
	_Y = ty;
}




void putchr(int x1,int y1,unsigned char char_no,long color)
{
	

	int x=x1;
	int y=y1;

	for(int i=63;i>=0;i--)
	{
		if(CHARSIZE)
		{
			if((font[char_no][i]))
			{
				direct_pixel_mem(direct_page5,x,y,color);
				y++;
				direct_pixel_mem(direct_page5,x++,y--,color);
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=2;
				x=x1;
			}
		}
		else
		{
			if((font[char_no][i]))
			{
				direct_pixel_mem(direct_page5,x,y,color);
				x++;
			}
			else
			{
				x++;
			}
			if( i%8 == 0)
			{
				y+=1;
				x=x1;
			}
		}
	}
	
}

void settextstyle(int font, int direction, int charsize)
{
	int font_dummy = font;
	int dir_dummy  =direction;
	dir_dummy = 1;
	font_dummy = 0;
	if(charsize>1)
	{
		CHARSIZE = dir_dummy;
	}
	else
	{
		CHARSIZE = font_dummy;
	}
}
