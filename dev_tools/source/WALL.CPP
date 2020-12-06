#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#include <process.h>
#include <dos.h>
#include <alloc.h>
#include <math.h>
#include <time.h>
//#include <graphics.h>
#include <string.h>
#include <io.h>
class lines
{
public:
	float m,c;
	int sgn;
};
int signum(float x)
{
	if (x>0)
	{
		return(1);
	}
	if (x==0)
	{
		return(0);
	}
	return(-1);
}
class walls
{
public:
	int no_lines;
	lines line[10];
	int type;
	void load_walls(char *x);
	int is_inside(float x,float y);
	void collide(float &x,float &y);
	void show_data();
};
walls w[30];

enum wall_modes
{
	SOLID,GRASS,WATER,TOXIC,SAFE
};

void walls::show_data()
{
	for (int i = 0; i < no_lines; i++)
	{
		cout<<"m="<<line[i].m<<"\nc="<<line[i].c<<"\nsgn="<<line[i].sgn;
	   getch();
	   cout<<endl;
	}
}
void get_data()
{
	fstream myfile;
	myfile.open("walls1.rob",ios::app|ios::binary);
	int no;
	cout<<"enter no walls TO BE ADDED ";
	cin>>no;
	float x1,x2,y1,y2;
	float t_x,t_y;
	for (int i = 0; i < no; i++)
	{
	cout<<"enter no lines ";
	cin>>w[i].no_lines;
	cout<<"enter type (0.solid 1.grass 2.water 3.toxic 4.safe) ";
	cin>>w[i].type;
	cout<<"tru x ";
	cin>>t_x;
	cout<<"tru y ";
	cin>>t_y;
	for (int j = 0; j < w[i].no_lines; j++)
	{
		if (j==0)
		{
			cout<<"x1 ";
			cin>>x1;
			cout<<"y1 ";
			cin>>y1;
			cout<<"x2 ";
			cin>>x2;
			cout<<"y2 ";
			cin>>y2;
			w[i].line[0].m=(y2-y1)/(x2-x1);
			w[i].line[0].c=y1-w[i].line[0].m*x1;
			w[i].line[0].sgn=signum(t_y-w[i].line[0].m*t_x-w[i].line[0].c);
		}
		else
		{
			if (j==w[i].no_lines-1)
			{
				cout<<"final ";
			}
			cout<<"x ";
			cin>>x1;
			cout<<"y ";
			cin>>y1;
			w[i].line[j].m=(y2-y1)/(x2-x1);
			w[i].line[j].c=y1-w[i].line[j].m*x1;
			w[i].line[j].sgn=signum(t_y-w[i].line[j].m*t_x-w[i].line[j].c);
			x2=x1;
			y2=y1;
		}
	}
	myfile.write((char*)&w[i],sizeof(w[i]));
	}
	myfile.close();
	cout<<"done";

}

void main()
{
	clrscr();
	get_data();
	clrscr();
	fstream m;
	m.open("walls1.rob",ios::in|ios::binary);
	for (int i = 0; i < 3; i++)
	{
		m.read((char*)&w[i],sizeof(w[i]));
		w[i].show_data();
		cout<<endl;
	}
	getch();
}
