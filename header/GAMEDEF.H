//#include <bot.h>
//#//include ".\files\maps.cpp"
#include ".\files\wave.cpp"

enum sfx_play_mode
{
	NORMAL,FULL_PLAY,FORCE_PLAY
};

int audio::ResetDSP(unsigned int Test)
{
  outportb (Test + 0x6, 1);
  delay(10);
  outportb (Test + 0x6, 0);
  delay(10);
  if (((inportb(Test + 0xE) & 0x80) == 0x80) && (inportb (Test + 0xA) == 0xAA)) 
  {
    Base = Test;
    return (1);
  } else
    return (0);
}

void audio::WriteDSP(unsigned char Value)
{
  while ((inportb(Base + 0xC) & 0x80) == 0x80);
  outportb (Base + 0xC, Value);
}

 void music::get_data()
 {
 	if(index>size)
 	reset();
 	XMS_CopyFromXMS(Sample,music_handle,index,M_CHUNK);
 	index+=M_CHUNK;
 }

void music::reset()
{
	index=0;
}

void music::play()
{
  if(counter==0)
  {
  start=clock();
  counter=1;
  get_data();
  LinearAddress = FP_SEG (Sample);
  LinearAddress = (LinearAddress << 4) + FP_OFF (Sample);
  Page = LinearAddress >> 16;
  OffSet = LinearAddress & 0xFFFF;
  outportb (0x0A, 5);
  outportb (0x0C, 0);
  outportb (0x0B, 0x49);
  outportb (0x02, OffSet & 0xFF);
  outportb (0x02, OffSet >> 8);
  outportb (0x03, SoundLength & 0xFF);
  outportb (0x03, SoundLength >> 8);
  outportb (0x83, Page);
  outportb (0x0A, 1);
  WriteDSP (0xD1);
  WriteDSP(0x14);
  WriteDSP(SoundLength & 0xFF);
  WriteDSP(SoundLength >> 8);
  }
  end=clock();
  if (((end-start)/CLK_TCK)>duration)
  {
    start=clock();
    counter=0;
  }
}


void sfx::get_data(int i)
{
	SoundLength=Voice[i].SoundLength;
	if (SoundLength>CHUNK)
	{
		SoundLength=CHUNK;
	}
	if (index==Voice[i].size)
	{
	  		stop=1;
	  		force=0;
  		return;	
	}
  	if ((Voice[i].size-index)<CHUNK)
  	{
  		XMS_CopyFromXMS(Sample,sound_handle,Voice[i].index+index,(Voice[i].size-index)); 		
  		index=Voice[i].size;
  	}
  	else
  	{
  	XMS_CopyFromXMS(Sample,sound_handle,Voice[i].index+index,CHUNK);
  	}
  	if (Voice[i].size<index+CHUNK)
  	{
  		stop=1;
  		force=0;
  	}
  	index+=CHUNK;
}


void sfx::play_it(int i,int mode)
{
	if (mode==-1)
	{
		return;
	}
	if (mode==FULL_PLAY)
	{
		if (cur_i==i && stop==0 || force==1)
		{
			return;
		}
		
	}
	if (mode==NORMAL && force==1 && stop==0)
	{
		return;
	}
	if (mode==FORCE_PLAY)
	{
		force=1;
	}
	is_playing=1;
	stop=0;
	index=0;
	cur_i=i;
}


void sfx::play()
{
	if (stop==1)
	{
		return;
	}
   if(counter==0)
  {
  start=clock();
  counter=1;
  get_data(cur_i);
  LinearAddress = FP_SEG (Sample);
  LinearAddress = (LinearAddress << 4) + FP_OFF (Sample);
  Page = LinearAddress >> 16;
  OffSet = LinearAddress & 0xFFFF;
  outportb (0x0A, 5);
  outportb (0x0C, 0);
  outportb (0x0B, 0x49);
  outportb (0x02, OffSet & 0xFF);
  outportb (0x02, OffSet >> 8);
  outportb (0x03, SoundLength & 0xFF);
  outportb (0x03, SoundLength >> 8);
  outportb (0x83, Page);
  outportb (0x0A, 1);
  WriteDSP (0xD1);
  WriteDSP(0x14);
  WriteDSP(SoundLength & 0xFF);
  WriteDSP(SoundLength >> 8);
  }
  end=clock();
  if (((end-start)/CLK_TCK)>0.16)
  {
    start=clock();
    counter=0;
  }
}

void camera::show_cam()
{
	copy_xms_to_xms(direct_page5,visual_page,1440000L,0,addr);
}

void camera::show_cam(int i)
{
	copy_xms_to_xms(direct_page5,visual_page,1920000L,0,addr);
}

void camera::add_y()
{
	if (i==0)
	{
		y=-OffSet+np->y1+recoil;
		if(recoil!=0)
		recoil-=1;
	}
	else
		y=-OffSet+bots[i-1].y1;

		if (y<0)
		{
			y=0;
		}
		addr=x*y;
}

void camera::add_y(int a)
{
	y=a;
	addr=x*y;
}




void walls::load_walls(char *x)
{
	file_save(log_file,"load_walls is loading walls from ",x);
	fstream myfile;
	myfile.open(x,ios::in|ios::binary);
	myfile.read((char *)this,sizeof(walls));
	myfile.close();
}

int walls::is_inside(float x,float y)
{
	x+=20;
	y+=20;	
	for (int i = 0; i < no_lines; i++)
	{
		if (signum(y - line[i].m * x -line[i].c)!=line[i].sgn)
		{
			return(0);
		}
	}
	return(1);
}

void walls::collide(float &x,float &y)
{
	if(type==SOLID)
	{
	x+=20;
	y+=20;
	float min=999,dis;
	int k;
	for (int i = 0; i < no_lines; i++)
	{
		dis=distance(x,y,line[i].m,line[i].c);
		if (dis<min)
		{
			min=dis;
			k=i;
		}
	}
	if (line[k].sgn==-1 && line[k].m>0)
	{
		x-=2;
		y+=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==-1 && line[k].m<0)
	{
		x+=2;
		y+=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==1 && line[k].m>0)
	{
		x+=2;
		y-=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==1 && line[k].m<0)
	{
		x-=2;
		y-=2;
	    x-=20;
	    y-=20;
	    return;
	}	
    }

    if (type==GRASS)
    {
    	np->walk=Walk_g;
    }
    if(type==WATER)
    {
    	np->walk=Walk_w;
    }

}



void walls::bot_collide(float &x,float &y)
{
	if(type==SOLID)
	{
	x+=20;
	y+=20;
	float min=999,dis;
	int k;
	for (int i = 0; i < no_lines; i++)
	{
		dis=distance(x,y,line[i].m,line[i].c);
		if (dis<min)
		{
			min=dis;
			k=i;
		}
	}
	if (line[k].sgn==-1 && line[k].m>0)
	{
		x-=2;
		y+=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==-1 && line[k].m<0)
	{
		x+=2;
		y+=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==1 && line[k].m>0)
	{
		x+=2;
		y-=2;
	    x-=20;
	    y-=20;
	    return;
	}
	if (line[k].sgn==1 && line[k].m<0)
	{
		x-=2;
		y-=2;
	    x-=20;
	    y-=20;
	    return;
	}	
    }

}



int Level::load_Level()
{
	
	char addr[50];
	strcpy(addr,".\\levels\\");
	strcat(addr,name);
	strcat(addr,"\\");
	strcat(addr,name);
	strcat(addr,".rob");
	fstream myfile;
	myfile.open(addr,ios::in|ios::binary);
	myfile.read((char *)this,sizeof(Level));
	myfile.close();
	file_save(log_file,"loading map ",name);
	if (iter==KILL_ALL)
	{
		file_save(log_file,"game mod ","KILL_ALL");
	}
	if (iter==HOSTAGE_RESCUE)
	{
		file_save(log_file,"game mod ","HOSTAGE_RESCUE");
	}
	if (iter==ZOMBIE_MOD)
	{
		file_save(log_file,"game mod ","ZOMBIE_MOD");
	}
	if (iter==ZOMBIE_ESCAPE)
	{
		file_save(log_file,"game mod ","ZOMBIE_ESCAPE");
	}
	return(1);
}
Level::Level()
{
	for (int i = 0; i < 16; i++)
	{
	}
}

void Level::load_walls()
{
	file_save(log_file,"load_walls is loading walls from ",addr_walls);
	fstream myfile;
	myfile.open(addr_walls,ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	long int sz=myfile.tellg();
	no_walls=sz/sizeof(walls);
	myfile.seekg(0,ios::beg);
	for (int i = 0; i < no_walls; i++)
	{
		myfile.read((char*)&wall[i],sizeof(walls));
		if (wall[i].type==SAFE)
		{
			safe=i;
		}
	}
	wals=no_walls;
	file_save(log_file,"found ",wals);
	file_save(log_file," walls"," ",NOSPACE);
	myfile.close();
}





void Level::load_maps()
{
	load_bar(138);
	direct_load_bmp(map_page,addr_map);
	direct_load_bmp(direct_page2,".\\res\\hud.bmp");
    visual_page=map_page;
	load_bar(691);
}

void user_profile::create_profile()
{
	fstream myfile;
	myfile.open(".\\data\\usr.rdb",ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	int no_acc;
	long int sz=myfile.tellg();
	no_acc=sz/sizeof(user_profile);
	myfile.seekg(0,ios::beg);
	user_profile temp;
	file_save(log_file,"username ",usr.account_name);
	for (int i = 0; i < no_acc; i++)
	{
		myfile.read((char *)&temp,sizeof(user_profile));
		if (strcmp(temp.account_name,usr.account_name)==0)
		{
			if (strcmp(temp.account_password,usr.account_password)==0)
			{
				file_save(log_file,"password verification"," success",SPACE);
				usr=temp;
				file_save(log_file,"kills :",usr.kills);
				file_save(log_file,"deaths :",usr.deaths);
				file_save(log_file,"cash :",usr.cash);
				return;
			}
			file_save(log_file,"password verification"," failure",SPACE);
			return;
		}
	}
	file_save(log_file,"\nerror no such account ","create new",SPACE);
	myfile.close();
	myfile.open(".\\data\\usr.rdb",ios::app|ios::binary);
	myfile.write((char *)&usr,sizeof(user_profile));
	myfile.close();
}

void user_profile::save_profile()
{
	char addr[50];
	strcpy(addr,".\\data\\usr.rdb");
	fstream myfile;
	myfile.open(addr,ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	int no_acc;
	long int sz=myfile.tellg();
	no_acc=sz/sizeof(user_profile);
	myfile.seekg(0,ios::beg);
	user_profile temp;
	fstream tamp;
	strcpy(addr,".\\data\\temp");
	tamp.open(addr,ios::app|ios::binary);
	for (int i = 0; i < no_acc; i++)
	{
		myfile.read((char *)&temp,sizeof(user_profile));
		if (strcmp(temp.account_name,usr.account_name)==0)
		{
			if (strcmp(temp.account_password,usr.account_password)==0)
			{
				file_save(log_file,"purchase"," saved");
				tamp.write((char *)&usr,sizeof(usr));
			}
			else
				file_save(log_file,"failure ","unable to save purchase");
		}
		else
		{
			tamp.write((char *)&temp,sizeof(usr));
		}
	}
	tamp.close();
	myfile.close();
	remove(".\\data\\usr.rdb");
	rename(".\\data\\temp",".\\data\\usr.rdb");
}

int user_profile::load_profile()
{
	char addr[50];
	char temp1[30],temp2[30];
	strcpy(temp1,account_name);
	strcpy(temp2,account_password);
	strcat(temp2,"rptr");
	strcpy(addr,".\\data\\");
	strcat(addr,account_name);
	strcat(addr,".rob");
	fstream myfile;
	myfile.open(addr,ios::in|ios::binary);
	myfile.read((char *)&usr,sizeof(usr));
	myfile.close();	
	if(strcmp(account_password,temp2)==0)
		return(1);
	return(0);
}

void menu_item::buy()
{
	if (usr.arsenal[id]==1)
	{
		return;
	}
	if (usr.cash>cost)
	{
		usr.arsenal[id]=1;
		usr.save_profile();
	}
	else
	{
		direct_draw_models(model_handle,gui_nomoney,200,200);
		getch();
	}
}

void menu_item::select_gun()
{
	if (usr.selected_gun[0]==id)
	{
		return;
	}
	usr.selected_gun[0]=id;
}


void hud::set_hud()
{
	if (counter==0)
	{
		st=clock();
		counter=1;
	}
	ed=clock();
	if (((ed-st)/CLK_TCK)>0.5)
	{
		off=np->hp*len/100;
		if (off<0)
		{
			off=0;
		}
		direct_draw_rect(hx,hy,hx+len,hy+wid,hid);
		direct_draw_rect(hx,hy,hx+off,hy+wid,green);
		off=np->ap*len/100;
		if (off<0)
		{
			off=0;
		}
		direct_draw_rect(ax,ay,ax+len+1,ay+wid,hid);
		direct_draw_rect(ax,ay,ax+off,ay+wid,red);
		off=(np->current_weapon->magsize-np->current_weapon->index)*len/np->current_weapon->magsize;
		if (np->current_weapon->mags==0)
		{
			off=0;
		}

		direct_draw_rect(amx,amy,amx+len+1,amy+wid,hid);
		direct_draw_rect(amx,amy,amx+off,amy+wid,red);
		off=(np->current_weapon->mags-1)*len/3;
		if (off<0)
		{
			off=0;
		}
		direct_draw_rect(mx,my,mx+len+1,my+wid,hid);
		direct_draw_rect(mx,my,mx+off,my+wid,red);
		counter=0;
	}
}
void effect::init(int x1,int y1)
{
	no_frames=12;
	doa=0;
	index=ex1;
	dl[0]=5;
	dl[1]=5;
	now=0;
	doa=1;
	x=x1;
	y=y1;
	myaudio->play_it(Explode,FORCE_PLAY);
}

int effect::show()
{
	if (doa==1)
	{
		dl[0]-=1;
		direct_draw_to_page_trans(direct_page5,index+now,x,y-cam.y);
		if (dl[0]<0)
		{
			dl[0]=dl[1];
			now+=1;
		}
		if (now==12)
		{
			doa=0;
			return(1);
		}
	}
	return(0);
}

void game::init()
{
	counter=0;
	for (int i = 0; i < 10; i++)
	{
		events[i][0]=0;
		events[i][1]=60;
	}
	stage_counter=0;
	stage=0;
	bots_alive=10;
	no_bots=10;
	fstream myfile;
	myfile.open("spawn.txt",ios::in);
	char data[5];
	for (i = 0; i < 10; i++)
	{
		myfile>>data;
		spwan_px[i]=atoi(data);
		myfile>>data;
		spwan_py[i]=atoi(data);
	}
	myfile.close();
}
void game::set_msgdata(int i)
{
	if (i==Player_info)
	{
		strcpy(msgdata,"KILLS : ");
		add_to_string(msgdata,np->kills);
		strcat(msgdata,"\nCASH : ");
		add_to_string(msgdata,usr.cash);
		strcat(msgdata,"\nHP : ");
		add_to_string(msgdata,np->hp);
		strcat(msgdata,"\nAP : ");
		add_to_string(msgdata,np->ap);
		strcat(msgdata,"\nROUND TIME : ");
		add_to_string(msgdata,((z2-z1)/CLK_TCK));
	}
	if (i==Player_buy)
	{
		start:
		strcpy(msgdata,"                            BUYMENU");
		strcat(msgdata,"\n1.BUY AMMO   :$80");
		strcat(msgdata,"\n2.BUY MEDKIT :$300");
		strcat(msgdata,"\n3.BUY KEVLAR :$200");
		char ch=show_msgmenu();
		if (ch=='1')
		{
			if (usr.cash>80)
			{
				usr.cash-=80;
				np->current_weapon->mags=4;
				strcpy(msgdata,"                          YOU PURCHASED AMMO");
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
			else
			{
				strcpy(msgdata,"                            SORRY");
				show_msgmenu();	
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
		}
		else if (ch=='2')
		{
			if (usr.cash>300)
			{
				usr.cash-=300;
				np->hp+=50;
				if (np->hp>100)
				{
					np->hp=100;
				}
				strcpy(msgdata,"                          YOU PURCHASED MEDKIT");
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
			else
			{
				strcpy(msgdata,"                            SORRY");
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
		}
		else if (ch=='3')
		{
			if (usr.cash>200)
			{
				usr.cash-=200;
				np->ap+=50;
				if (np->ap>100)
				{
					np->ap=100;
				}
				strcpy(msgdata,"                          YOU PURCHASED KEVLAR");
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
			else
			{
				strcpy(msgdata,"                            SORRY");
				if (show_msgmenu()==char(27))
				{
					return;
				}
				goto start;
			}
		}
	}
}

char game::show_msgmenu()
{
	int len=strlen(msgdata);
	direct_draw_models(model_handle,5,130,218);
	//direct_draw_to_page_transparent(direct_page5,5,130,218);
	int y=272,t=0;
	char data[100];
	for (int i = 0; i < len; i++)
	{
		if (msgdata[i]=='\n')
		{
			memcpy(data,msgdata+t,i-t);
			data[i-t]='\0';
			t=i+1;
			D_outtextxy(154,y,data);
			y+=15;
		}
	}
	memcpy(data,msgdata+t,i-t);
	data[i-t]='\0';
	D_outtextxy(154,y,data);
	D_outtextxy(290,358,"PRESS ESC TO EXIT");
	char c;
    c=getch();
    return(c);
}

void game::show_msg()
{
	int len=strlen(msgdata);
	direct_draw_models(model_handle,5,130,218);
	int y=272,t=0;
	char data[100];
	for (int i = 0; i < len; i++)
	{
		if (msgdata[i]=='\n')
		{
			memcpy(data,msgdata+t,i-t);
			data[i-t]='\0';
			t=i+1;
			D_outtextxy(154,y,data);
			y+=15;
		}
	}
	memcpy(data,msgdata+t,i-t);
	data[i-t]='\0';
	D_outtextxy(154,y,data);
	D_outtextxy(290,358,"PRESS SPACEBAR TO CONTINUE");
char c;    
    s400:
    c=getch();
    if (c!=' ')
    {
    	goto s400;
    }
}

void game::msg_box(char *x,char inp)
{
	int len=strlen(x);
	direct_draw_models(model_handle,5,130,218);
	int y=272,t=0;
	char data[100];
	for (int i = 0; i < len; i++)
	{
		if (x[i]=='\n')
		{
			memcpy(data,x+t,i-t);
			data[i-t]='\0';
			t=i+1;
			D_outtextxy(154,y,data);
			y+=15;
		}
	}
	memcpy(data,x+t,i-t);
	data[i-t]='\0';
	D_outtextxy(154,y,data);
	D_outtextxy(290,358,"PRESS SPACEBAR TO CONTINUE");
char c;    
    s400:
    c=getch();
    if (inp!='.' && c!=inp)
    {
    	goto s400;
    }
}

void game::zme()
{
	if (lvl->iter==ZOMBIE_ESCAPE)
	{
		for (int i = 0; i < lvl->no_bots; i++)
		{
			if (bots[i].doa==0)
			{
				if (bots[i].counter==0)
				{
					bots[i].s1=clock();
					bots[i].counter=1;
					usr.cash+=20;
				}
				bots[i].s2=clock();
				if (((bots[i].s2-bots[i].s1)/CLK_TCK)>5)
				{
					bots[i].update_node();
					bots[i].doa=1;
					bots[i].x1=bots[i].rx[bots[i].cur_node];
					bots[i].y1=bots[i].ry[bots[i].cur_node];
					bots[i].counter=0;
					bots[i].hp=50;
					bots[i].burst_size[0]=30;
	           		bots[i].model_id=zm+rand()%9;
	           		if (bots[i].model_id==zm || bots[i].model_id==zm_hcrab)//hunter
	           		{
	           		 bots[i].v=2;
	           		}
	           		else
	           		{
	           		 bots[i].v=1;
	           		}

	          		 if (bots[i].model_id==zm_boom)
	           		{
	            		bots[i].v=3;
	           		}
	        		if (bots[i].model_id==zm_venom)
	           		{
	            		bots[i].v=3;
	            		bots[i].sdeath=Z_diem;
	            		bots[i].hp=500;
	           		}
	           		if (bots[i].model_id==zm3)
	           		{
	            	  bots[i].sdeath=Z_dief;
	            	  bots[i].img_y=40;
	            	  bots[i].img_x=40;
	           		}
	           		else if(bots[i].model_id==zm_hcrab)
	           		{
	           			bots[i].sdeath=Z_diecrab;
	           			bots[i].img_x=20;
	           			bots[i].img_y=20;
	           		}
	           		else
	           		{
	            		bots[i].sdeath=Z_diem;
	            		bots[i].img_x=40;
	            		bots[i].img_y=40;
	           		}

	           		if (bots[i].model_id==zm_tank)
	           		{
	            	  bots[i].hp=300;
	           		}
				}				
			}
	    }

	}

}

void game::zombies()
{
	if (lvl->iter==ZOMBIE_MOD)
	{
	int xx;
	if (bots_alive==0)
	{
		events[5][1]-=1;
		if (events[5][1]>0)
		{
			return;
		}
		events[5][1]=60;
		stage+=1;
		bots_alive=1;
		strcpy(msgdata,"                        WELL DONE");
		strcat(msgdata,"\nYOU SURVIVED WAVE ");
		add_to_string(msgdata,stage);
		strcat(msgdata,"\nPREPARE FOR NEXT WAVE OF ZOMBIES");
		strcat(msgdata,"\nWARNING ZOMBIES ARE HEADING TOWARDS YOU");
		strcat(msgdata,"\nSURVIVE THIS ROUND ");
		show_msg();
		z1=clock();
		usr.cash+=stage*100;
	}
	else
	{	
		for (int i = 0; i < lvl->no_bots; i++)
		{
			if (bots[i].doa==0)
			{
				if (bots[i].counter==0)
				{
					bots[i].s1=clock();
					bots[i].counter=1;
					usr.cash+=20;
				}
				bots[i].s2=clock();
				if (((bots[i].s2-bots[i].s1)/CLK_TCK)>5)
				{
					xx=rand()%10;
					bots[i].doa=1;
					bots[i].x1=bots[i].rx[0];
					bots[i].y1=bots[i].ry[0];
					bots[i].counter=0;
					bots[i].hp=50;
					bots[i].burst_size[0]=30;
	           		bots[i].model_id=zm+rand()%9;
	           		if (bots[i].model_id==zm || bots[i].model_id==zm_hcrab)//hunter
	           		{
	           		 bots[i].v=2;
	           		}
	           		else
	           		{
	           		 bots[i].v=1;
	           		}

	          		 if (bots[i].model_id==zm_boom)
	           		{
	            		bots[i].v=3;
	           		}
	        		if (bots[i].model_id==zm_venom)
	           		{
	            		bots[i].v=3;
	            		bots[i].sdeath=Z_diem;
	            		bots[i].hp=500;
	           		}
	           		if (bots[i].model_id==zm3)
	           		{
	            	  bots[i].sdeath=Z_dief;
	            	  bots[i].img_y=40;
	            	  bots[i].img_x=40;
	           		}
	           		else if(bots[i].model_id==zm_hcrab)
	           		{
	           			bots[i].sdeath=Z_diecrab;
	           			bots[i].img_x=20;
	           			bots[i].img_y=20;
	           		}
	           		else
	           		{
	            		bots[i].sdeath=Z_diem;
	            		bots[i].img_x=40;
	            		bots[i].img_y=40;
	           		}

	           		if (bots[i].model_id==zm_tank)
	           		{
	            	  bots[i].hp=300;
	           		}
				}				
			}
	    }
	}
		z2=clock();
		if (((z2-z1)/CLK_TCK)>120)
		{
			for (int i = 0; i < lvl->no_bots; i++)
			{
				bots[i].doa=0;
				//bots[i].counter=0;
			}
			bots_alive=0;
		}
    }

}

void game::game_events()
{
	if (events[0][0]==0)//lets go
	{
		events[0][1]-=1;
		if (events[0][1]<0)
		{
			events[0][0]=1;
			myaudio->play_it(Go,NORMAL);
		}
	}
	if (events[1][0]==0)//terrorist win
	{
		if (np->doa==0 && lvl->iter==KILL_ALL)
		{
			events[1][1]-=1;
		}
		if (events[1][1]<0)
		{
			events[1][0]=1;
			myaudio->play_it(Terwin,NORMAL);
		}
	}
	
	if (events[2][0]==1)//hostage interact
	{
		if (events[2][1]==1)
		{
			events[2][1]=0;
			myaudio->play_it(Hostage,NORMAL);
		}
	}
	if (events[3][0]==0)//ct win hostage rescue 0 true
	{
		 if (lvl->iter==HOSTAGE_RESCUE)
        {
    	if (wall[safe].is_inside(bots[host].x1,bots[host].y1)==1)
    	{
			events[3][1]-=1;
    	}
        }
		if (events[3][1]<0)
		{
			events[3][0]=1;
			myaudio->play_it(Ctwin,NORMAL);
		}
	}

	if (events[4][0]==0)//zombie win
	{
		if (np->doa==0 && lvl->iter==ZOMBIE_MOD)
		{
			events[4][1]-=1;
		}
		if (events[4][1]<0)
		{
			if (events[4][1]<-140)
			{
				events[4][0]=1;
			}
			myaudio->play_it(Zwin,FULL_PLAY);
		}
	}
}

void Bots::init_bot(int i)
{
	init_unit();
	doa=0;
	counter=0;
	engage=0;
	cur_node=0;
	side=2;
	exploded=0;
	old_target=0;
	img_x=40;
	img_y=40;
	target=0;
	burst_size[0]=30;
	burst_size[1]=120;
	if (i==EASY)
	{
		at_dl[0]=60;
		at_dl[1]=60;
	       //	burst_size=3;
		acc=0.02;
	}
}
void Bots::update_node()
{
	cur_node+=1;
	if (cur_node==no_waypoints-1)
	{
		cur_node=0;
		return;
	}
	
}

void Bots::load_Bots(char *x)
{
	file_save(log_file,"loading bot from ",x);
	fstream myfile;
	myfile.open(x,ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	long int sz=myfile.tellg();
	no_waypoints=sz/sizeof(Nodes);
	myfile.seekg(0,ios::beg);
	
	file_save(log_file,"loaded ",no_waypoints,SPACE);
	file_save(log_file," waypoints",".",SPACE);
	for (int i = 0; i < no_waypoints; i++)
	{
		myfile.read((char *)&gno,sizeof(Nodes));
		rx[i]=gno.x;
		ry[i]=gno.y;
		file_save(log_file,"x",gno.x,SPACE);
		file_save(log_file,"y",gno.y,SPACE);
	}
	myfile.close();

}

void Bots::bot_path()
{
		x2=rx[cur_node];
		y2=ry[cur_node];
		if (abs(x1-rx[cur_node])<10)
		{
			if (abs(y1-ry[cur_node])<10)
			{
				update_node();
			}
		}
}
void Bots::move()
{
	x1+=v*cos(o);
	y1+=v*sin(o);
}

int Bots::behavior()
{
	if (mode==NONE)
	{
		x2=rx[cur_node];
		y2=ry[cur_node];
		Angle();
		if (abs(x1-rx[cur_node])<10)
		{
			if (abs(y1-ry[cur_node])<10)
			{
				update_node();
			}
		}
		return(0);
	}
	if (mode==ATTACK)
	{
		if (abs(np->y1-y1)<cam.OffSet && hp>20 && np->doa==1)
		{
			y2=np->y1;
			x2=np->x1;
			Angle();
			o+=-acc*(rand()%15);
			acc*=-1;
			if (at_dl[0]>-3)
			{
				at_dl[0]-=1;
			}
			if (at_dl[0]<0)
			{
				fire();
			}
			if (abs(np->y1-y1)<160)
			{
				v=0;
			}
			else
				v=1.5;
			return(1);
		}
		if (hp<20)// || abs(np->y1-y1)>400 || np->doa==0)
		{
			v=1.5;
			y2=-np->y1;
			x2=np->x1;
			Angle();
			return(1);
		}
		if (abs(np->y1-y1)>cam.OffSet)
		{
		Angle();
		at_dl[0]=at_dl[1];
		x2=rx[cur_node];
		y2=ry[cur_node];
		if (abs(x1-rx[cur_node])<30)
		{
			if (abs(y1-ry[cur_node])<30)
			{
				update_node();
			}
		}
		return(1);
		}
	}
	if (mode==ZOMBIE)
	{
			//getch();
			if (model_id==zm_boom)//explosion
			{
				if (exploded==1)
				{
					return(2);
				}
				if (abs(np->y1-y1)<cam.OffSet && np->doa==1)
				{
					y2=np->y1;
					x2=np->x1;
					Angle();
					if (abs(np->y1-y1)<10 && abs(np->x1-x1)<10)
					{
						exp.init(x1,y1);
						if (np->ap>0)
						{
							np->hp-=15;
							np->ap-=45;
							if (np->ap<0)
							{
								np->ap=0;
							}
						}
						else
							np->hp-=60;
						exploded=1;
					}
					return(2);
				}
			}
			else if (model_id==zm_spit)
			{
				if (abs(np->y1-y1)<150 && abs(np->x1-x1)<150 && np->doa==1)
				{
					y2=np->y1+20;
					x2=np->x1+20;
					Angle();
					burst_size[0]-=1;
					if (burst_size[0]<0)
					{
						burst_size[0]=burst_size[1];
						spit.create_Bull(80,x1,y1,o);
						spit.v=6;
						spit.time_to_live=30;
						spit.side=2;
					}
					v=0;
				}
				else
				{
					y2=np->y1;
					x2=np->x1;
					v=1;
					Angle();	
				}
				return(3);
			}
			else if (model_id==zm_hcrab)
			{
				y2=np->y1;
				x2=np->x1;
				Angle();
				if (abs(np->y1-y1)<80 && abs(np->x1-x1)<80)
				{
					v=6;
				}
				else
					v=1;
				if (abs(np->y1-y1)<10 && abs(np->x1-x1)<10)
				{
						if (np->ap>0)
						{
							np->ap-=1;
						}
						else
							np->hp-=1;
				}
				return(0);
			}
			else if (model_id==zm)
			{
				if (abs(np->y1-y1)<cam.OffSet && np->doa==1)
				{
					y2=np->y1;
					x2=np->x1;
					Angle();
					if (abs(np->y1-y1)<10 && abs(np->x1-x1)<10)
					{
						if (np->ap>0)
						{
							np->ap-=1;
						}
						else
							np->hp-=1;
						v=0;
					}
					else
						v=2;
					return(0);
				}
				return(0);
			}
			else if (model_id==zm_venom)
			{
				y2=np->y1;
				x2=np->x1;
				Angle();
				v=0.5;
				if (abs(np->y1-y1)<10 && abs(np->x1-x1)<10)
				{
					if (np->ap>0)
					{
						np->ap-=10;
					}
					else
						np->hp-=5;
				}
				return(0);
			}
			else
			{
				if (abs(np->y1-y1)<cam.OffSet && np->doa==1)
				{
					y2=np->y1;
					x2=np->x1;
					Angle();
					if (abs(np->y1-y1)<10 && abs(np->x1-x1)<10)
					{
						if (np->ap>0)
						{
							np->ap-=1;
						}
						else
							np->hp-=1;
						v=0;
					}
					else
						v=1;
					return(0);
				}
				return(0);
		    }
	}
	if (mode==FFA)
	{
		Angle();
			o+=-acc*(rand()%15);
			acc*=-1;
			if (at_dl[0]>-3)
			{
				at_dl[0]-=1;
			}
			if (target!=old_target)
			{
				at_dl[0]=60;
				old_target=target;
			}
			if (target==69)
			{
				if (abs(np->y1-y1)<cam.OffSet && at_dl[0]<0)
				{
					fire();
				}
			}
			else
			{
			if (abs(y2-y1)<300)
			{
				if (at_dl[0]<0)
				{
				fire();
				}
			}
			}


		if (abs(y2-y1)<160 && abs(x2-x1)<160)
		{
			v=0;
		}
		else
			v=1.5;
		return(1);
	}
	if (mode==HOSTAGE)
	{
		if (mygame->events[2][0]==0)
		{
			model_id=hostage;
			v=0;
		}
		else
		{
			v=1;
			y2=np->y1;
			x2=np->x1;
			Angle();
			if (abs(y1-np->y1)<100 ||abs(y1-np->y1)>300)
			{
				v=0;
			}
			else
				v=1;
			return(0);
		}
	}
}

void Bots::run_bot()
{
	if (doa==1)
	{
		/*if (abs(np->y1-y1)>cam.OffSet+200 && mode!=NONE)
		{
			return;
		}*/
		check_doa();
		behave=behavior();
        if (behave==1)
        {
        	run_Weapons();
        }
        if (behave==2)
        {
        	if (exp.show()==1)
        	{
        		exploded=0;
        	}
        }
        if (behave==3)
        {
        	if (spit.doa==1)
        	{
        		spit.move(4);
        		spit.hit();
        	}
        }
        move();
        impact();
		anim(mode);
	}
}
void Bots::impact()
{
	for(int i=0;i<wals;i++)
	{
		if (wall[i].type==SOLID)
		{
			if(wall[i].is_inside(x1,y1)==1)
			{
				wall[i].bot_collide(x1,y1);
			}
		}

    }
}

void Bots::spawn_bot()
{
	if (doa==0)
	{
		doa=1;
		x1=rx[0];
		y1=ry[0];
	}
}

void Bots::spawn_bot(int x,int y)
{
	if (doa==0)
	{
		doa=1;
		x1=x;
		y1=y;
	}
}

void Player::Player_input()
{
	if (kbhit()!=0)
	{
		kb_input=getch();
	}
}

void Player::move()
{
	if (momentum>0)
	{
	   x1+=vx;
	   y1+=vy;
	}
	momentum-=1;
}

void Player::hud()
{
	char stp[5];
	itoa(hp,stp,10);
	outtextxy(198,493,stp);
	itoa(current_weapon->index,stp,10);
	outtextxy(490,500,stp);
}

void Player::run_Player()
{
	if (doa==1)
	{
		Angle();
		check_doa();
		x2=m[0].x;
		y2=m[0].y+cam.y;
		if (jump_t[0]<20)
		{
			jump_t[0]+=1;
		}
		else
			v=1.5;
		if (jump_t[1]<62)
		{
			jump_t[1]+=1;
		}

		run_Weapons();
		action();
		move();
        Player_input();
		hud();
		impact();
		anim();
	}
}

void Player::impact()
{
	np->walk=Walk;
	for(int i=0;i<wals;i++)
	{
	if(wall[i].is_inside(x1,y1)==1)
	{
		wall[i].collide(x1,y1);
	}
    }
}
int te=0;
void Player::action()
{
	if (kb_input==control.MOVE_UP)
	{
		momentum=30;
		myaudio->play_it(walk,FULL_PLAY);
		vx=0;
	    vy=-2;//kb_input='n';
		//return;
	}
	if (kb_input==control.MOVE_DOWN)
	{
		momentum=30;
		vx=0;myaudio->play_it(walk,FULL_PLAY);
		vy=2;//kb_input='n';
		//return;
	}
	if (kb_input==control.MOVE_RIGHT)
	{
		momentum=30;
		vx=v;myaudio->play_it(walk,FULL_PLAY);
		vy=0;
		//kb_input='n';
		//return;
	}
	if (kb_input==control.MOVE_LEFT)
	{
		momentum=30;
		vx=-v;myaudio->play_it(walk,FULL_PLAY);
		vy=0;//kb_input='n';
		//return;
	}
	if (m[0].cl==1)
	{
		kb_input='n';
		fire(1);
		return;
	}
	if (kb_input==control.RELOAD)
	{
		if (current_weapon->mags>0)
		{
			current_weapon->mags-=1;
			current_weapon->index=0;
			current_weapon->reload_temp=0;
		}
		current_weapon->reload();
		kb_input='n';
		return;
	}
	if (kb_input==control.ITEM_1)
	{
		set_current_weapon(1);
		kb_input='n';
		return;
	}
	if (kb_input==control.ITEM_2)
	{
		set_current_weapon(2);
		kb_input='n';
		return;
	}
	if (kb_input==control.CAM_UP)
	{
		if(cam.OffSet<400)
		cam.OffSet+=2;
	kb_input='n';
		return;
	}
	if (kb_input==control.CAM_DOWN)
	{
		if(cam.OffSet>100)
		cam.OffSet-=2;
	kb_input='n';
		return;
	}
	if (kb_input==control.KILL)
	{
		doa=0;
		myaudio->play_it(Die,NORMAL);
		kb_input='n';
		return;
	}
	if (kb_input==control.SCREENSHOT)
	{
		char addr[50],dat[10];
		strcpy(addr,".\\screensh\\");
		itoa(runs,dat,10);
		strcat(addr,dat);
		itoa(te,dat,10);
		strcat(addr,"_");
		strcat(addr,dat);
		strcat(addr,".bmp");
		te+=1;
		saveBMP24(0,0,800,450,addr);
		kb_input='n';
		return;
	}
	if (kb_input==control.USE)
	{
		if(bots[host].doa==1)
		{
			if (abs(y1-bots[host].y1)<70)
			{
		       mygame->events[2][0]=1;
		       mygame->events[2][1]=1;
			}
		}
		kb_input='n';
		return;
	}
	if (kb_input==control.SCORE)
	{
		mygame->set_msgdata(Player_info);
		clock_t temp,temp2;
		temp=clock();
		mygame->show_msg();
		temp2=clock();
		mygame->z1+=(temp2-temp);
		kb_input='n';
		return;
	}
	if (kb_input==control.BUY)
	{
		clock_t temp,temp2;
		temp=clock();
		mygame->set_msgdata(Player_buy);
		temp2=clock();
		mygame->z1+=(temp2-temp);
		kb_input='n';
		return;
	}
	/*if (kb_input=='g')
	{
		cam.i+=1;
		kb_input='n';
	}
	if (kb_input=='b')
	{
		cam.i-=1;
		kb_input='n';
	}*/
}



void Bull::kill_self()
{
	doa=0;
}

int Bull::hit()
{
	if (side==1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (bots[i].doa==1)
			{
				if (x>bots[i].x1 && x<bots[i].x1+40 && y>bots[i].y1 && y<bots[i].y1+40)
				{
					bots[i].hp-=damage;
					kill_self();
					return(1);
				}
			}
		}
	}
	if (side==2)
	{
			if (np->doa==1)
			{
				if (x>np->x1 && x<np->x1+40 && y>np->y1 && y<np->y1+40)
				{
					if (np->ap>0)
					{
						np->ap-=3*damage/4;
						np->hp-=damage/4;
					}
					else
						np->hp-=damage;
					kill_self();
					return(1);
				}
			}
	}
	if (side==3)
	{
		for (int i = 0; i < 10; i++)
		{
			if (bots[i].doa==1)
			{
				if (x>bots[i].x1 && x<bots[i].x1+40 && y>bots[i].y1 && y<bots[i].y1+40)
				{
					bots[i].hp-=damage;
					kill_self();
					return(1);
				}
			}
		}
		if (np->doa==1)
		{
			if (x>np->x1 && x<np->x1+40 && y>np->y1 && y<np->y1+40)
			{
				if (np->ap>0)
				{
					np->ap-=3*damage/4;
					np->hp-=damage/4;
				}
				else
					np->hp-=damage;
				kill_self();
				return(1);
			}
		}		
	}
	return(0);
}

void Bull::move()
{
	x+=v*cos(o);
	y+=v*sin(o);
	time_to_live-=1;
	hit();
	//direct_draw_to_page(direct_page5,0,x,y-cam.y,o);
	//direct_draw_to_page_trans(direct_page5,0,x,y-cam.y);
	if (time_to_live<0)
	{
		doa=0;
	}
}

void Bull::move(int i)
{
	x+=v*cos(o);
	y+=v*sin(o);
	time_to_live-=1;
	direct_draw_to_page_trans(direct_page5,i,x,y-cam.y);
	if (time_to_live<0)
	{
		doa=0;
	}
}


void Units::check_doa()
{
	if (hp<1)
	{
		doa=0;
	myaudio->play_it(sdeath,FORCE_PLAY);
	np->kills+=1;
	//direct_draw_to_page(visual_page,dead,x1,y1);
	return;
	}
	if (y1<0)
	{
		doa=0;
	}
}
void Units::fire()
{
	current_weapon->side=side;
	current_weapon->fire_weapon();
}
void Units::fire(int i)
{
	current_weapon->side=side;
	current_weapon->fire_weapon(i);
}
void Units::anim()
{
	if (o>0 && o<3.14)
	{
		model_id=current_weapon->id+glock18-1+gun_constant*(side+1);
		direct_draw_to_page_trans(direct_page5,model_id,x1,y1-cam.y,o-1.57);
	}
	else
	{
		model_id=current_weapon->id+glock18-1+gun_constant*(side-1);
		direct_draw_to_page_trans(direct_page5,model_id,x1,y1-cam.y,o+1.57);
	}
}

void Units::anim(int i)
{
	if(i==ATTACK || i==FFA)
	{
	model_id=current_weapon->id+glock18-1+gun_constant*(side-1);
	direct_draw_to_page_trans(direct_page5,model_id,x1,y1-cam.y,o-1.57);
	return;
    }
    if (i==ZOMBIE)
    {
    	direct_draw_to_page_trans(direct_page5,model_id,x1,y1-cam.y,o-1.57);
    }
}
void Units::run_Weapons()
{
	current_weapon->o=o;
	current_weapon->x=x1;
	current_weapon->y=y1;
	current_weapon->run_Bullets();
	if (current_weapon->rate>-1)
	{
		current_weapon->rate-=1;
	}
	if (current_weapon->index>current_weapon->magsize-1)
	{
		current_weapon->reload();
	}
}
void Weapons::run_Bullets()
{
	for (int i = 0; i < magsize;i++)
	{
		if (b[i].doa==1)
		{
			b[i].move();
		}
	}
}

void Weapons::create_Bullet()
{
		float i,j;
		i=5*cos(o)+x+20;
		j=5*sin(o)+y+20;
		b[index].side=side;
		b[index].create_Bull(damage,i,j,o);
}

void Weapons::force_kill_Bull()
{
	for (int i = 0; i < magsize;i++)
	{
		b[i].doa=0;
	}
}
void Weapons::reload()
{
	reload_temp+=1;
	if (reload_temp>reload_dl)
	{
	 index=0;
	 mags-=1;
	 reload_temp=0;
	}
	force_kill_Bull();
}

void Weapons::fire_weapon()
{
	if (id==0)
	{
		return;
	}
	if (rate<0 && (magsize-index)>0 && mags>0)
	{
	   rate=firerate;
	   create_Bullet();
	   myaudio->play_it(id-1,FULL_PLAY);
	   index+=1;
	}

}
void Weapons::fire_weapon(int i)
{
	if (id==0)
	{
		return;
	}
	if (rate<0 && (magsize-index)>0 && mags>0)
	{
	   rate=firerate;
	   create_Bullet();
	   myaudio->play_it(id-1,FORCE_PLAY);
	   cam.recoil+=5;
	   index+=1;
	}

}
void Units::set_current_weapon(int i)
{
    myaudio->play_it(Bolt,FULL_PLAY);
	if(i==1)
	{
		current_weapon=&primary;
	}
	if(i==2)
	{
		current_weapon=&sidearm;
	}
}
float Units::Angle()
{
	float x,dx=x2-x1,dy=y2-y1;
	x=dy/dx;
	o=atan(x);
	if (dx<0 && dy>0)
	{
		o=3.14+o;
	}
	if (dx<0 && dy<0)
	{
		o+=3.14;
	}
	if(dx>0 && dy<0)
	{
		o=6.28+o;
	}
	return(o);
}