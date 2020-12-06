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

class Nodes
{
public:
	int x,y;
	void get_data()
	{
		cout<<"\nx ";
		cin>>x;
		cout<<"\ny ";
		cin>>y;
	}
};
Nodes n[20];

void save_data()
{
	cout<<"enter name of the file ";
	char fl[30];
	cin>>fl;
	strcat(fl,".rob");
	fstream my;
	my.open(fl,ios::app|ios::binary);
	for (int i = 0; i < 20; i++)
	{
		cout<<"x ";
		cin>>n[i].x;
		cout<<"y ";
		cin>>n[i].y;
		if(n[i].x==-47 && n[i].y==-47)
			break;
		my.write((char*)&n[i],sizeof(n[i]));
	}
	my.close();
}

void main()
{
	clrscr();
	save_data();
	cout<<"done";
	getch();
}
