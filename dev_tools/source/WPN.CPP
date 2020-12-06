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
#include <dir.h>
#include <string.h>
#include <io.h>

class Bull
{
public:
	int doa;
	int x,y,v,x1,y1;
	float o,damage;
	int side;
	int time_to_live;
	int img_x,img_y;
	Bull()
	{
		doa=0;
		v=20;
		img_y=img_x=12;
		time_to_live=15;
	}
	void create_Bull(float d,int xpos,int ypos,float oo)
	{
		damage=d;
		doa=1;
		x=xpos;
		y=ypos;
		o=oo;
		time_to_live=15;
	}
	void move();
	void kill_self();
	void hit();
};

class Weapons///////////////////do not edit without changing size 1006
{
public:
	int id;
	int side;
	char name[10];
	int damage;
	int rate;
	int firerate;
	int magsize,mags;
	int index;
	float x,y;
	float o;
	int reload_dl;
	Bull b[40];
	Weapons()
	{
		index=0;
		rate=0;
		mags=3;
	}
	void set_name(char *x,int i)
	{
		strcpy(name,x);
		id=i;
	}
	void read_data();
	void force_kill_Bull();
	void create_Bullet();
	void run_Bullets();
	void fire_weapon();
	void reload();
	void show_data();
};
void Weapons::show_data()
{
	cout<<index<<endl;
	cout<<name<<endl;
	cout<<damage<<endl;
	cout<<magsize<<endl;
	cout<<firerate<<endl;
	cout<<reload_dl<<endl;
}
void save_wpn()
{
	clrscr();
	Weapons w;
	fstream myfile;
	myfile.open("weapons.rob",ios::app|ios::binary);
	myfile.seekp(0,ios::end);
	int no_weapons;
	long int sz=myfile.tellp();
	no_weapons=sz/sizeof(Weapons);
	cout<<"enter name of the weapon :";
	cin>>w.name;
	w.index=no_weapons+1;
	cout<<"\nenter damage(max 100):";
	cin>>w.damage;
	cout<<"\nenter magsize(max 40) :";
	cin>>w.magsize;
	cout<<"\nenter rounds per minute(rpm) (ak47=500rpm) :";
	float rpm,fps;
	fps=3540;
	cin>>rpm;
	fps=fps/rpm;
	w.firerate=fps;
	cout<<"\nenter reload time(in sec) :";
	cin>>rpm;
	rpm*=59;
	w.reload_dl=rpm;
	myfile.write((char*)&w,sizeof(Weapons));
	clrscr();
	cout<<"gun "<<w.name<<" saved at index "<<w.index;
	myfile.close();
	getch();
}

void view_weapon()
{
	clrscr();
	Weapons w;
	char name[50];
	fstream myfile;
	myfile.open("weapons.rob",ios::in|ios::binary);
	cout<<"enter name of the weapon :";
	cin>>name;
	myfile.seekg(0,ios::end);
	int no_weapons;
	long int sz=myfile.tellg();
	no_weapons=sz/sizeof(Weapons);
	myfile.seekg(0,ios::beg);
	for (int i = 0; i < no_weapons; i++)
	{
		myfile.read((char*)&w,sizeof(Weapons));
		if (strcmp(w.name,name)==0)
		{
			w.show_data();
			break;
		}
		if (i==no_weapons-1)
		{
			cout<<"no such weapon";
		}
	}
	myfile.close();
	getch();
}

void edit_wpn()
{
	char name[50];
	Weapons w;
	fstream myfile;
	myfile.open("weapons.rob",ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	int no_weapons;
	long int sz=myfile.tellg();
	no_weapons=sz/sizeof(Weapons);
	myfile.seekg(0,ios::beg);
	cout<<"enter name of the weapon :";
	cin>>w.name;
	cout<<"\nenter index of the weapon(-1 for default) :";
	cin>>w.index;

	cout<<"\nenter damage(max 100):";
	cin>>w.damage;
	cout<<"\nenter magsize(max 40) :";
	cin>>w.magsize;
	cout<<"\nenter rounds per minute(rpm) (ak47=500rpm)(set rpm=-1 for pistols) :";
	float rpm,fps;
	fps=3540;
	cin>>rpm;
	fps=fps/rpm;
	w.firerate=fps;
	cout<<"\nenter reload time(in sec) :";
	cin>>rpm;
	rpm*=59;
	w.reload_dl=rpm;
	Weapons temp;
	fstream ts;
	ts.open("temp",ios::app|ios::binary);
	for (int i = 0; i < no_weapons; i++)
	{
		myfile.read((char*)&temp,sizeof(Weapons));
		if (strcmp(temp.name,w.name)==0)
		{
			if (w.index==-1)
			{
				w.index=temp.index;
			}
			ts.write((char*)&w,sizeof(Weapons));
		}
		else
		{
			ts.write((char*)&temp,sizeof(Weapons));
		}
	}
	myfile.close();
	ts.close();
	remove("weapons.rob");
	rename("temp","weapons.rob");
	cout<<"\n done";
	getch();
}

void main()
{
	clrscr();
	cout<<"warzone weapon editor\n";
	cout<<"enter admin password";
	int pass;
	cin>>pass;
	if (pass!=1234)
	{
		exit(0);
	}
	clrscr();
	start:
	int ch1,ch2;
	cout<<"1.save new weapon \t\t2.batch save new weapon\n3.edit weapon \t\t4.batch edit weapon";
	cout<<"\n5.view weapon  \t\t6.exit\n==>";
	cin>>ch1;
	if (ch1==1)
	{
		save_wpn();
	}
	if (ch1==2)
	{
		clrscr();
		cout<<"how many weapons to add ";
		cin>>ch2;
		for (int i = 0; i < ch2; i++)
		{
			save_wpn();
		}
	}
	if (ch1==3)
	{
		edit_wpn();
	}
	if (ch1==4)
	{
		clrscr();
		cout<<"how many weapons to add ";
		cin>>ch2;
		for (int i = 0; i < ch2; i++)
		{
		edit_wpn();
	    }
	}
	if (ch1==5)
	{
		view_weapon();
	}
	if (ch1==6)
	{
		exit(0);
	}
	goto start;
}