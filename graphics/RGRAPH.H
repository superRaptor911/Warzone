struct colour
{
	unsigned char r,g,b;
};
colour red,green,hid;

void init_colours()
{
red.r=237;
red.g=28;
red.b=36;

green.r=34;
green.g=177;
green.b=76;

hid.r=95;
hid.g=94;
hid.b=89;
}

unsigned char far *vb=(char far *)0xA0000000L;
unsigned char far *vb2=(char far *)0xB0000000L;
unsigned char far *vb3=(char far *)0xC0000000L;
unsigned int model_handle,back_img_handle;
unsigned int page_handle,direct_page,direct_page2;
unsigned int direct_page5;
unsigned int map_page,sound_handle,music_handle;
unsigned int visual_page;
void print_int(long int i,int x,int y);
void file_save(char *file,char *msg,char *x,int mode=0);
void file_save(char *file,char *msg,double x,int mode=0);
void direct_pixel_mem(unsigned int &handle,long int x,long int y,long int c);
void display_pixel_mem(long int x,long int y,long int c);


#include ".\graphics\gomphics.h"
#include ".\graphics\rgraph.cpp"
int tfps=0,fps=0;
int cntr=0,cntr2=0;
clock_t st,ed;
clock_t st2,ed2;
char st_fps[10];
float dur=0;
void fps_lock_start(float i=60);
void fps_lock_end();
void chk_fps()
{
	if (cntr==0)
	{
		st=clock();
		cntr=1;
	}
	tfps+=1;
	ed=clock();
	if ((ed-st)/CLK_TCK>1)
	{
		fps=tfps;
		tfps=0;
		cntr=0;
	}
	itoa(fps,st_fps,10);
	strcat(st_fps," fps");
	outtextxy(730,16,st_fps);
}

void fps_lock_start(float i)
{
		dur=1/i;
		
		if (cntr2==0)
		{
			st2=clock();
			cntr2=3;
		}
}

void fps_lock_end()
{
	cntr2-=1;
	if(cntr2==0)
	{
	for(;;)
	{
	ed2=clock();
	if (((ed2-st2))>dur)
	{
		return;
	}
	}
    }
}
	


enum load_modes
{
	CONTINUE,RESET
};
void load_bar(int n,int mode=CONTINUE);
int load_var=0;

void load_bar(int n,int mode)
{
	if (mode=RESET)
	{
		load_var=0;
	}
	for(;load_var<n;load_var++)
	{
      for(int j=0;j<8;j++)
      {
      	putpixel(47+load_var,493+j,0);
      }
    }
}