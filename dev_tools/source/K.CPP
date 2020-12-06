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

class zones
{
public:
	int x1,y1,x2,y2;
	int mode;
	int sound_id;
   //	zones();
};

class map_addr
{
public:
char addr[70];
}map;
class Level
{
public:
	char name[20];
	char addr_map[70];
	char addr_walls[70];
    char addr_ambience[10][70];
    zones zone[10];
	int no_bots;
	int no_walls;
	int no_zones;
	int iter;
	int bot_mob[16][3];//index mode mob gun
	char addr_bot_profile[16][70];
	Level();
	void init(char *x)
	{
		strcpy(name,x);
	}
	int load_Level();
	void load_maps();
	void load_walls(int i);
	void run_map();
	void show();
};

Level::Level()
{
	iter=0;
	for (int i = 0; i < 16; i++)
	{
		bot_mob[i][0]=0;//index mode mob on/off (mode=0)
		bot_mob[i][1]=0;//(mob=0)
	}
}
void Level::show()
{
	clrscr();
	cout<<"map name "<<name;
	cout<<"\nsize of rob "<<sizeof(Level)<<"\n";
	cout<<"\naddr of map "<<addr_map<<"\n";
	cout<<"\naddr of wall "<<addr_walls<<"\n";
	cout<<"\nnumber of bots "<<no_bots<<"\n";
	cout<<"\nnumber of walls "<<no_walls<<"\n";
cout<<"\nnumber of zones "<<no_zones<<"\n";

for (int i = 0; i < no_bots; i++)
{
	cout<<"\nmode of bot"<<i<<" is "<<bot_mob[i][0];
	cout<<"\ngun of bot"<<i<<" is "<<bot_mob[i][2];
}

for (i = 0; i < no_bots; i++)
{
	if (bot_mob[i][0]!=3)
	{
		cout<<"\naddr of bot"<<i<<" is "<<addr_bot_profile[i];
	}
}
	getch();
}

enum zone_modes
{
	KILL_ZONE,AMBIENCE,TOXIC,EVENT
};
enum bot_behavior
{
	NONE,ATTACK,DEFENCE,HOSTAGE,TRUCK
};
Level lvl;
void load_data()
{
		char dat[70],addr[70];
		strcpy(addr,".\\");
	cout<<"enter map name :";
	cin>>dat;
	strcat(addr,dat);
	strcat(addr,"\\");
	strcat(addr,dat);
	strcat(addr,".rob");
	fstream myfile;
	myfile.open(addr,ios::in|ios::binary);
	myfile.read((char*)&lvl,sizeof(Level));
	lvl.show();
	exit(0);
}

void main()
{
	clrscr();

int ch2;
cout<<"1.read map data 2.create map data  :";
cin>>ch2;
if (ch2==1)
{
	load_data();
}
	char dat[70],addr[70];
	strcpy(addr,".\\");
	cout<<"enter map name :";
	cin>>dat;
	mkdir(dat);
	strcpy(lvl.name,dat);
	strcat(addr,dat);
	strcat(addr,"\\");
	strcat(addr,dat);
	strcat(addr,".rob");
	fstream myfile;
	myfile.open(addr,ios::app|ios::binary);
	cout<<"saving to "<<addr;
	cout<<"\nenter name of map file(eg. map.bmp) :";
	cin>>dat;
	strcpy(addr,".\\levels\\");
	strcat(addr,lvl.name);
	strcat(addr,"\\");
	strcat(addr,dat);
	strcpy(lvl.addr_map,addr);
	cout<<"\nenter name of wall file(eg. walls.rob) :";
	cin>>dat;
	strcpy(addr,".\\levels\\");
	strcat(addr,lvl.name);
	strcat(addr,"\\");
	strcat(addr,dat);
	strcpy(lvl.addr_walls,addr);

	cout<<"\nenter no. bots (min 0) :";
	cin>>lvl.no_bots;
	for (int i = 0; i < lvl.no_bots; i++)
	{

		cout<<"\nbot type (0.NONE 1.ATTACK 2.DEFENCE 3.HOSTAGE 4.VEHICLE) :" ;
		cin>>lvl.bot_mob[i][0];
		if (lvl.bot_mob[i][0]!=3)
		{
		cout<<"\nenter name of bot file for bot"<<i<<" (eg. bot.rob) :";
			cin>>dat;
	        strcpy(addr,".\\levels\\");
	        strcat(addr,lvl.name);
	        strcat(addr,"\\");
	        strcat(addr,dat);
	        strcpy(lvl.addr_bot_profile[i],addr);
		}
		cout<<"\nbot primary weapon (1.glock18 2.usp 3.deagle 4.p228 5.tmp) :" ;
		cin>>lvl.bot_mob[i][2];
	}

	cout<<"\nenter no. zones (min 0) :";
	cin>>lvl.no_zones;
	int count=0;
	for (i = 0; i < lvl.no_zones; i++)
	{
		cout<<"\nenter zone type for zone "<<i<<"\n (0.kill zone 1.AMBIENCE 2.TOXIC 3.toggle bot)";
		cin>>lvl.zone[i].mode;
		cout<<"x1 ";
		cin>>lvl.zone[i].x1;
		cout<<"y1 ";
		cin>>lvl.zone[i].y1;
		cout<<"x2 ";
		cin>>lvl.zone[i].x2;
		cout<<"y2 ";
		cin>>lvl.zone[i].y2;
		if (lvl.zone[i].mode==AMBIENCE)
		{
			lvl.zone[i].sound_id=count;
			cout<<"\nenter name of sound file for zone"<<i<<" (eg. t.wav)";
			cin>>dat;
	        strcpy(addr,".\\levels\\");
	        strcat(addr,lvl.name);
	        strcat(addr,"\\");
	        strcat(addr,dat);
	        strcpy(lvl.addr_ambience[count],addr);
	        count+=1;
		}

	}
	clrscr();
	cout<<"\nzones awailable to toggle bots are ";
	for (i = 0; i < lvl.no_zones; i++)
	{
		if (lvl.zone[i].mode==EVENT)
		{
			cout<<"zone"<<i<<" ";
		}
	}
	cout<<"\npress 1 for yes 0 for no\n";
	int ch;
	for (i = 0; i < lvl.no_zones; i++)
	{
		if (lvl.zone[i].mode==EVENT)
		{
			for (int j = 0; j < lvl.no_bots; j++)
			{
				if (lvl.bot_mob[j][1]==0)
				{
					cout<<"\ndo you want bot"<<j<<" to be toggled at zone"<<i;
					cin>>ch;
					if (ch==1)
					{
						lvl.bot_mob[j][1]=1;
					}
				}
			}
		}
	}
	myfile.write((char*)&lvl,sizeof(Level));
	myfile.close();
	myfile.open("mapmap.cfg",ios::app|ios::binary);
	strcpy(map.addr,lvl.name);
	myfile.write((char*)&map,sizeof(map_addr));
	myfile.close();
lvl.show();
exit(0);
}