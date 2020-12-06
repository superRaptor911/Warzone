void load_again();
void menu();
void login();
void buy_menu();
int map_menus() ;
void inventory();
void region_maker();
void bot_maker();
void extras();
void menu()
{
	direct_draw_nbmp(map_page,8);
    visual_page=map_page;
	int last_opt=-1,new_opt=-1;
	for(;;)
	{
	render_N(8);
	getmouse(m[0].x,m[0].y,m[0].cl);
		chk_fps();
		mymusic->play();
	if((m[0].x+10>50)&&(m[0].x+10<103)&&(m[0].y+10>400)&&(m[0].y+10<437))
		{
		   if(m[0].cl==1)
			exit(0);
		}
	if((m[0].x+10>48)&&(m[0].x+10<170)&&(m[0].y+10>194)&&(m[0].y+10<228))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altnewgame,49,195);
		   if(m[0].cl==1)
		   {
			map_menus();
			direct_draw_bmp(direct_page);
			return;
		   }
		}
	if((m[0].x+10>50)&&(m[0].x+10<175)&&(m[0].y+10>231)&&(m[0].y+10<265))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altcontinue,51,232);
		   new_opt=menu_opt_continue;
		   if (m[0].cl==1)
		   {
		   	inventory();
		   }
		}
	if((m[0].x+10>51)&&(m[0].x+10<156)&&(m[0].y+10>266)&&(m[0].y+10<300))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altoptions,52,266);
		   new_opt=menu_opt_options;
		}
	if((m[0].x+10>50)&&(m[0].x+10<132)&&(m[0].y+10>301)&&(m[0].y+10<330))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altstore,51,300);
		   new_opt=menu_opt_store;
		   if (m[0].cl==1)
		   {
		   	buy_menu();
		   }
		}
	if((m[0].x+10>49)&&(m[0].x+10<138)&&(m[0].y+10>337)&&(m[0].y+10<366))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altextras,50,331);
		   new_opt=menu_opt_extras;
		   if (m[0].cl==1)
		   {
		   	extras();
		   }
		}
	if((m[0].x+10>49)&&(m[0].x+10<150)&&(m[0].y+10>367)&&(m[0].y+10<399))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altcredits,51,368);
		   new_opt=menu_opt_credits;
		}
	if((m[0].x+10>50)&&(m[0].x+10<103)&&(m[0].y+10>400)&&(m[0].y+10<437))
		{
		   direct_draw_to_page(direct_page5,menu_opt_altexit,51,401);
		   new_opt=menu_opt_exit;
		   if(m[0].cl==1)
		   	abort();
		}
		show_m_mouse(m[0]);
		render_E();
    }
}

void buy_menu()
{
	char ch;
	direct_draw_nbmp(map_page,2);
	visual_page=map_page;
	int c=2;
	char st[5];
	for(;;)
	{
	render_N(c);
	getmouse(m[0].x,m[0].y,m[0].cl);
	chk_fps();
	if (kbhit()!=0)
	{
		ch=getch();
	}
	if (ch==char(27))
	{
		ch='n';
		return;
	}
	mymusic->play();
		if(c==2)
		{
		if(m[0].x+10>72 && m[0].x+10<212 && m[0].y+10>224 && m[0].y+10<396)
		{
			direct_draw_to_page(direct_page5,buy_music,72,224);
		}
		if(m[0].x+10>258 && m[0].x+10<(258+128) && m[0].y+10>237 && m[0].y+10<(237+168))
		{
			direct_draw_to_page(direct_page5,buy_player,258,237);
		}
		if(m[0].x+10>411 && m[0].x+10<(411+136) && m[0].y+10>269 && m[0].y+10<(269+112))
		{
			direct_draw_to_page(direct_page5,buy_gun,411,269);
			if(m[0].cl==1)
			{
				c+=1;
			}
		}
		if(m[0].x+10>585 && m[0].x+10<(585+132) && m[0].y+10>225 && m[0].y+10<(225+192))
		{
			direct_draw_to_page(direct_page5,buy_spray,585,225);
		}
	    }
	    
	    if(c==3)//main gun menu
	    {
	    if(m[0].x+10>233 && m[0].x+10<520 && m[0].y+10>170 && m[0].y+10<200)//pistols
		{
			if(m[0].cl==1)
			{
				c=4;
				CHARSIZE=4;
			}
		}
		if(m[0].x+10>233 && m[0].x+10<520 && m[0].y+10>250 && m[0].y+10<280)
		{
			if(m[0].cl==1)
			{
				c=5;
			}
		}
		if(m[0].x+10>233 && m[0].x+10<520 && m[0].y+10>337 && m[0].y+10<366)
		{
			if(m[0].cl==1)
			{
				c=6;
			}
		}
		if(m[0].x+10>233 && m[0].x+10<520 && m[0].y+10>422 && m[0].y+10<454)
		{
			if(m[0].cl==1)
			{
				c=7;
			}
		}
			if(m[0].x+10>692 && m[0].x+10<706 && m[0].y+10>54 && m[0].y+10<73)
		    {
			if(m[0].cl==1)
			{
				c=2;
			}
		    }
		}
		
		
		if(c==4)//pistol
		{
			itoa(usr.cash,st,10);
			strcat(st,"$");
			outtextxy(580,70,st);
			if(m[0].x+10>705 && m[0].x+10<719 && m[0].y+10>63 && m[0].y+10<83)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>79 && m[0].x+10<300 && m[0].y+10>476 && m[0].y+10<506)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>79 && m[0].x+10<300 && m[0].y+10>507 && m[0].y+10<537)
		    {
			if(m[0].cl==1)
			{
				c=2;
			}
		    }
		    //gunclicks
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>121 && m[0].y+10<150)
		    {
		    	direct_draw_to_page(direct_page5,gui_glock,447,142);
		    	if (m[0].cl==1)
		    	{
		    		menu_items[0].buy();
		    	}
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>151 && m[0].y+10<179)
		    {
	            direct_draw_to_page(direct_page5,gui_usp,447,142);
	            if (m[0].cl==1)
		    	{
		    		menu_items[1].buy();
		    	}
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>180 && m[0].y+10<209)
		    {
	            direct_draw_to_page(direct_page5,gui_deagle,447,142);
	            if (m[0].cl==1)
		    	{
		    		menu_items[2].buy();
		    	}
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>236 && m[0].y+10<263)
		    {
	            direct_draw_to_page(direct_page5,gui_p228,447,142);
	            if (m[0].cl==1)
		    	{
		    		menu_items[3].buy();
		    	}
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>268 && m[0].y+10<293)
		    {
	            direct_draw_to_page(direct_page5,gui_python,447,142);
	            if (m[0].cl==1)
		    	{
		    		menu_items[4].buy();
		    	}
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>298 && m[0].y+10<324)
		    {
	            direct_draw_to_page(direct_page5,gui_elite,447,142);
		    }
		    if(m[0].x+10>81 && m[0].x+10<301 && m[0].y+10>328 && m[0].y+10<354)
		    {
	            direct_draw_to_page(direct_page5,gui_colt,447,142);	
		    }
		}
		if(c==5)//smg
		{
			if(m[0].x+10>692 && m[0].x+10<706 && m[0].y+10>54 && m[0].y+10<73)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>81 && m[0].x+10<318 && m[0].y+10>441 && m[0].y+10<472)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>81 && m[0].x+10<318 && m[0].y+10>470 && m[0].y+10<506)
		    {
			if(m[0].cl==1)
			{
				c=2;
			}
		    }
		}
		if(c==6)
		{
			if(m[0].x+10>692 && m[0].x+10<706 && m[0].y+10>54 && m[0].y+10<73)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>81 && m[0].x+10<298 && m[0].y+10>469 && m[0].y+10<492)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>81 && m[0].x+10<298 && m[0].y+10>499 && m[0].y+10<522)
		    {
			if(m[0].cl==1)
			{
				c=2;
			}
		    }
		}
		if(c==7)
		{
			if(m[0].x+10>692 && m[0].x+10<706 && m[0].y+10>54 && m[0].y+10<73)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>80 && m[0].x+10<298 && m[0].y+10>467 && m[0].y+10<490)
		    {
			if(m[0].cl==1)
			{
				c=3;
			}
		    }
		    if(m[0].x+10>80 && m[0].x+10<298 && m[0].y+10>498 && m[0].y+10<520)
		    {
			if(m[0].cl==1)
			{
				c=2;
			}
		    }
		}
		
		show_m_mouse(m[0]);
		render_E();
	}

getch();
}

void inventory()
{
	int x,y;
	char ch;
	x=21;y=51;
	int d=54;//48x48
	int no[10],count=0;
	direct_draw_nbmp(map_page,9);
	visual_page=map_page;
	y+=5400;
	int block;
	for (int i = 0; i < 20; i++)
	{
		if (usr.arsenal[i]==1)
		{
			direct_draw_to_page(visual_page,gui_iglock+i,x,y);
			no[count]=i;
			count+=1;
			x+=54;
			if (x>600)
			{
				x=100;
				y+=256;
			}
		}
	}
	ch='n';
	for(;;)
	{	
		render_N(9);
		getmouse(m[0].x,m[0].y,m[0].cl);
		chk_fps();
		if (kbhit()!=0)
		{
			ch=getch();
		}
		if (ch==char(27))
		{
			ch='n';
			return;
		}
		if (ch=='k')
		{
			direct_draw_to_page_transparent(direct_page5,menu_opt_newgame,130,218,char(130));
		}
		mymusic->play();
		if(m[0].cl==1)
		{
			block=m[0].x-11;
			block=block/48;
			if (block<count+1)
			{
				menu_items[no[block]].select_gun();
				direct_draw_to_page(visual_page,gui_iglock+no[block],21,5936);
			}
		}
		show_m_mouse(m[0]);
		render_E();
   }
}

void login()
{
	direct_draw_nbmp(map_page,0);
	visual_page=map_page;
    char piw[20],piw1[5],username[28],pass[28],psss[28];
    int c=0,j=0,i=0;
    username[0]='\0';
    pass[0]='\0';
    psss[0]='\0';
    piw[0]='\0';
	for(;;)
	{
	render_N(0);
	getmouse(m[0].x,m[0].y,m[0].cl);
	chk_fps();
	mymusic->play();
	outtextxy(66,267,username);
	if((m[0].x+10>66)&&(m[0].x+10<312)&&(m[0].y+10>256)&&(m[0].y+10<283)&&(m[0].cl==1))
	{
		setcolor(0);
        c=1;
	}
	if(c==1)
	{
		if (kbhit()!=0 && j<29)
		{
		piw[0]=getch();
		if(int(piw[0])==13)
		{
			c=2;
		}
		if (int(piw[0])==8)
		{
			username[j-1]='\0';
			j-=1;
		}
		if (c==1 && int(piw[0])!=8 && int(piw[0])!=13)
		{
		username[j]=piw[0];
		username[j+1]='\0';
		piw[1]='\0';
		j+=1;
		}
	    }
	}
	if((m[0].x+10>65)&&(m[0].x+10<311)&&(m[0].y+10>324)&&(m[0].y+10<350)&&(m[0].cl==1))
	{
        c=2;
	}
	if(c==2)
	{
		outtextxy(66,335,psss);
		if(kbhit()!=0 && i<29)
		{

		piw[0]=getch();
		if(int(piw[0])==13)
		{
			
		}
		if (int(piw[0])==8)
		{
			pass[i-1]='\0';
			psss[i-1]='\0';
			i-=1;
		}
		if (c==2 && int(piw[0])!=8 && int(piw[0])!=13)
		{
			pass[i]=piw[0];
			pass[i+1]='\0';
			piw[1]='\0';
			psss[i]='*';
			psss[i+1]='\0';
			i+=1;
		}
	    }
	if((m[0].x+10>264)&&(m[0].x+10<310)&&(m[0].y+10>372)&&(m[0].y+10<391)&&(m[0].cl==1))
	{
		strcpy(usr.account_name,username);
		strcpy(usr.account_password,pass);
		setcolor(34324L);
		usr.create_profile();
		return;
	}
	}
		show_m_mouse(m[0]);
		render_E();
    }
}


void load_level(char *lvl_name)
{
  lvl->init(lvl_name);
}

int map_menus()
{
	char ch;
	direct_draw_nbmp(map_page,1);
	visual_page=map_page;
	fstream myfile;
	myfile.open("list.cfg",ios::in|ios::binary);
	myfile.seekg(0,ios::end);
	long int sz=myfile.tellg();
	mygame->no_maps=sz/sizeof(map_addr);
	myfile.seekg(0,ios::beg);
	file_save(log_file,"loading map data from ","list.cfg");
	file_save(log_file,"found ",mygame->no_maps);
	file_save(log_file,"maps",".",SPACE);
	for (int i = 0; i < mygame->no_maps; i++)
	{
		myfile.read((char *)&map,sizeof(map_addr));
		strcpy(maps[i].name,map.addr);
		load_map_image(map.addr_img,i);
		file_save(log_file,"map ",maps[i].name);
		file_save(log_file,"thumbnail ",map.addr_img);
	}
	myfile.close();
	int x_side=100;
	int y_side=100;
	for (i = 0; i <mygame->no_maps ;i++)
	{
		maps[i].x1=x_side;
		maps[i].y1=y_side;
		maps[i].x2=x_side+128;
		maps[i].y2=y_side+128;
		direct_draw_to_page(visual_page,eo_eff+i,x_side,y_side+600);
		x_side+=200;
		if (x_side>600)
		{
			x_side=100;
			y_side+=200;
		}
	}
	for(;;)
	{
	render_N(1);
	getmouse(m[0].x,m[0].y,m[0].cl);
		chk_fps();
		if (kbhit()!=0)
		{
			ch=getch();
		}
		if (ch==char(27))
		{
			ch='n';
			return(1);
		}
		mymusic->play();
		for ( i = 0; i < mygame->no_maps; i++)
		{
			if (m[0].x+10>maps[i].x1 && m[0].x+10<maps[i].x2 && m[0].y+10>maps[i].y1 && m[0].y+10<maps[i].y2 && m[0].cl==1)
			{
				load_level(maps[i].name);
				return(0);
			}
		}
		show_m_mouse(m[0]);
		render_E();
	}
}


void load_w()
{
  fstream myfile;
  myfile.open(".\\data\\weapons.rob",ios::in|ios::binary);
  myfile.seekp(0,ios::end);
  int no_weapons;
  long int sz=myfile.tellp();
  no_weapons=sz/sizeof(Weapons);
  myfile.seekg(0,ios::beg);
  gun_constant=no_weapons;
  for (int i = 0; i < no_weapons; i++)
  {
  	guns[i].init();
    myfile.read((char *)&guns[i],sizeof(Weapons));
    file_save(log_file,"reading weapon data of weapon ",guns[i].name);
  }
  myfile.close();
}

void load_menu_items()
{
	fstream myfile;
	myfile.open("items.cfg",ios::in|ios::binary);
  myfile.seekg(0,ios::end);
  int no_weapons;
  long int sz=myfile.tellg();
  no_weapons=sz/sizeof(menu_item);
  myfile.seekg(0,ios::beg);
  for (int i = 0; i < no_weapons; i++)
  {
  	myfile.read((char *)&menu_items[i],sizeof(menu_item));
  }
  myfile.close();
}

void extras()
{
	char ch;
	for(;;)
	{
		render_N(10);
		getmouse(m[0].x,m[0].y,m[0].cl);
		show_m_mouse(m[0]);
		chk_fps();
		if (kbhit()!=0)
		{
			ch=getch();
		}
		if (ch==char(27))
		{
			ch='n';
			return;
		}
		mymusic->play();
		if (m[0].x+10>280 && m[0].x+10<483 && m[0].y+10>172 && m[0].y+10<206 && m[0].cl==1)
		{
			bot_maker();
		}
		if (m[0].x+10>264 && m[0].x+10<504 && m[0].y+10>275 && m[0].y+10<308 && m[0].cl==1)
		{
			region_maker();
		}
		render_E();
	}
}

void bot_maker()
{
	if (map_menus()==1)
	{
		return;
	}
	direct_draw_bmp(direct_page);
  lvl->load_Level();
  lvl->load_maps();	
  char ch;
  long int i=0;  
	int x[20],y[20];
    int new_bot=0;
    int bot_count=0;
    int count=0;
    file_save(log_file,"RAPTOR INC BOT EDITOR","------(-__-)-------");
	for (;;)
	{
		cam.add_y(i);
	    render_F();
		chk_fps();
		getmouse(m[0].x,m[0].y,m[0].cl);
		show_m_mouse(m[0]);	
		if (kbhit()!=0)
		{
			ch=getch();
		}
		if (ch==char(27))
		{
			load_again();
			return;
		}
		if (ch=='H')
		{
			i-=10;
			if (i<0)
			{
				i=1;
			}
			ch='n';
		}
		if (ch=='b' && count>0 && new_bot==1)
		{
			char addr[70];
			strcpy(addr,".\\levels\\");
			strcat(addr,lvl->name);
			strcat(addr,"\\bot");
			add_to_string(addr,bot_count);
			strcat(addr,".rob");
			fstream myfile;
			myfile.open(addr,ios::app|ios::trunc|ios::binary);
			file_save(log_file,"---------------->BOT ",bot_count);
			for (int j = 0; j < count; j++)
			{
				gno.x=x[j];
				gno.y=y[j];		
				file_save(log_file,"\nNODES (x,y) :",x[j],NOSPACE);
				file_save(log_file,",",y[j],NOSPACE);
				myfile.write((char*)&gno,sizeof(Nodes));
				if (j==count-1)
				{
					for (int k = 0; k < count; k++)
					{
						gno.x=x[j-k];
						gno.y=y[j-k];
						file_save(log_file,"\nNODES (x,y) :",gno.x,NOSPACE);
						file_save(log_file,",",gno.y,NOSPACE);
						myfile.write((char*)&gno,sizeof(Nodes));
					}
				}
			}
			myfile.close();
			count=0;
			new_bot=0;
			ch='n';
		}
		if (ch=='P')
		{
			i+=10;
			ch='n';
		}
		if (m[0].cl==1 && new_bot==0)
		{
			new_bot=1;
			bot_count+=1;
			direct_draw_to_page_trans(visual_page,2,m[0].x-10,m[0].y-10+i);
			myaudio->play_it(Bolt,FULL_PLAY);
			x[0]=m[0].x+10;
			y[0]=m[0].y+10+i;
			count+=1;
		}
		if (m[0].cl==1 && new_bot==1)
		{
			if (abs(x[count-1] - m[0].x)>20 || abs(y[count-1] - m[0].y-i)>20)
			{
				x[count]=m[0].x+10;
				y[count]=m[0].y+10+i;
				count+=1;
				direct_draw_to_page_trans(visual_page,4,m[0].x+2,m[0].y+2+i);
				myaudio->play_it(Bolt,FULL_PLAY);
			}
		}
		myaudio->play();
		render_E();
	}
}

void region_maker()
{
	if (map_menus()==1)
	{
		return;
	}
	direct_draw_bmp(direct_page);
  lvl->load_Level();
  lvl->load_maps();
  char ch;
  long int i=0;
  int no_lines=0;  
	float t_x=0,t_y=0;
	float x[20],y[20];
	float slope,constant;
	float sign;
    walls w;
    int counter=0;
    int tru_val=0;
    file_save(log_file,"RAPTOR INC REGION EDITOR","------(-__-)-------");
	for (;;)
	{
		cam.add_y(i);
	    render_F();
		chk_fps();
		getmouse(m[0].x,m[0].y,m[0].cl);
		show_m_mouse(m[0]);	
		if (kbhit()!=0)
		{
			ch=getch();
		}
		if (ch==char(27))
		{
			load_again();
			return;
		}
		if (ch=='H')
		{
			i-=10;
			if (i<0)
			{
				i=1;
			}
			ch='n';
		}
		if (ch=='P')
		{
			i+=10;
			ch='n';
		}
		if (m[0].cl==1)
		{
			counter=0;
			for (int j = 0; j < no_lines; j++)
			{
				if (abs(x[j]-m[0].x-10)<20 && abs(y[j]-m[0].y-10-i)<20)
				{
					counter=1;
					if (j==0 && no_lines>2)
					{
						counter=2;
					}
					break;
				}
			}
			if (counter==0)
			{
				x[no_lines]=m[0].x+10;
				y[no_lines]=m[0].y+10+i;
				if (no_lines!=0)
				{
					line(x[no_lines-1],y[no_lines-1],x[no_lines],y[no_lines],19600);
				}
				no_lines+=1;
				direct_draw_to_page_trans(visual_page,4,m[0].x+2,m[0].y+2+i);
				myaudio->play_it(Bolt,FULL_PLAY);
			}
			if (no_lines==4)
			{
				x[no_lines]=x[0];
				y[no_lines]=y[0];
				w.no_lines=no_lines;
				t_x=x[0]+x[2];
				t_x=t_x/2;
				t_y=y[0]+y[2];
				t_y=t_y/2;
				for (int p = 0; p < no_lines; p++)
				{
					float x1,y1,x2,y2;
					x1=x[p];
					x2=x[p+1];
					y2=y[p+1];
					y1=y[p];
					if (int(x1)==int(x2))
					{
						x2+=2;
						file_save(log_file,"--------ZERO ERROR FIXED","----------");
					}
					slope=(y2-y1)/(x2-x1);
					constant=(y1 - slope * x1);
					sign=(t_y - slope * t_x - constant);
					w.line[p].m=slope;
					w.line[p].c=constant;
					w.line[p].sgn=signum(sign);
					file_save(log_file,"\nline ",p);
					file_save(log_file," m =",w.line[p].m,NOSPACE);
					file_save(log_file," c =",w.line[p].c,NOSPACE);
					file_save(log_file," sgn =",w.line[p].sgn,NOSPACE);
				}
				strcpy(mygame->msgdata,"enter type(no lines = ");
				add_to_string(mygame->msgdata,w.no_lines);
				strcat(mygame->msgdata,")\n0.solid 1.grass 2.water 3.toxic 4.safe");
				char ch2=mygame->show_msgmenu();
				if (ch2=='0')
				{
					w.type=0;
				}
				else if (ch2=='1')
				{
					w.type=1;
				}
				else if (ch2=='2')
				{
					w.type=2;
				}
				else if (ch2=='3')
				{
					w.type=3;
				}
				else if (ch2=='4')
				{
					w.type=4;
				}
				fstream myfile;
				char addr[70];
				strcpy(addr,".\\levels\\");
				strcat(addr,lvl->name);
				strcat(addr,"\\walls1.rob");
				myfile.open(addr,ios::app|ios::binary);
				myfile.write((char*)&w,sizeof(walls));
				myfile.close();
				myaudio->play_it(Ak47,FULL_PLAY);
				no_lines=0;
			}
		}
		if (ch=='t')
		{
			t_x=m[0].x+10;
			t_y=m[0].y+10+i;
			tru_val=1;
			no_lines=0;
			ch='n';
			direct_draw_to_page_trans(visual_page,4,m[0].x+2,m[0].y+2+i);
			myaudio->play_it(M4a1,FULL_PLAY);
		}

		if (ch==char(9))//info
		{
			strcpy(mygame->msgdata,"tru x : ");
			add_to_string(mygame->msgdata,t_x);
			strcat(mygame->msgdata,"\ntru y : ");
			add_to_string(mygame->msgdata,t_y);
			for (int j = 0; j < no_lines; j++)
			{
				strcat(mygame->msgdata,"\nx,y : ");
				add_to_string(mygame->msgdata,x[j]);
				strcat(mygame->msgdata,",");
				add_to_string(mygame->msgdata,y[j]);
			}
			mygame->show_msgmenu();
			ch='n';
		}
		myaudio->play();
		render_E();
	}
}


void load()
{
   direct_draw_bmp(direct_page);
	for(int i=0;i<691;i++)
	{ 
      for(int j=0;j<8;j++)
      {
      	putpixel(47+i,493+j,0);
      }
      if (i==50)
      {
      	load_models();
      }
      if (i==150)
      {
      	//load_models_weapons();
      }
      if (i==200)
      {
      	load_loading_screen_assets();
      	//(305,554
      	direct_draw_models(model_handle,load_msg1,305,554);
      }
      if(i==231)
      {
      	load_menu_assets();
	      direct_load_nbmp(map_page,".\\res\\login\\login.bmp",0);
      	direct_load_nbmp(map_page,".\\res\\map_img.bmp",1);
      	direct_load_nbmp(map_page,".\\res\\buymenu.bmp",2);
      	direct_draw_models(model_handle,load_msg2,305,554);
      }
      if(i==346)
      {
      	direct_load_nbmp(map_page,".\\gui\\wpn\\1.bmp",3);
      	direct_load_nbmp(map_page,".\\gui\\wpn\\2.bmp",4);
      	direct_load_nbmp(map_page,".\\gui\\wpn\\3.bmp",5);
      	direct_load_nbmp(map_page,".\\gui\\wpn\\4.bmp",6);
      	direct_load_nbmp(map_page,".\\gui\\wpn\\5.bmp",7);
	direct_load_nbmp(map_page,".\\res\\back.bmp",8);
      }
      if(i==346)
      {
        init_colours();
        direct_set_color(red);
        direct_copy_xms_to_vmem(model_handle,vb2,16000);
        direct_draw_models(model_handle,load_msg5,305,554);
      }
      if(i==412)
      {
            LoadVoice(0,".\\sound\\glock18.wav");
            LoadVoice(Usp,".\\sound\\usp.wav");
            LoadVoice(Deagle,".\\sound\\deagle.wav");
            LoadVoice(P22,".\\sound\\p228.wav");
            LoadVoice(Python,".\\sound\\python.wav");
            LoadVoice(Elite,".\\sound\\elite.wav");
            LoadVoice(Colt,".\\sound\\colt.wav");
            LoadVoice(Tmp,".\\sound\\tmp.wav");
            LoadVoice(Mp5,".\\sound\\mp5.wav");
            LoadVoice(Ump45,".\\sound\\ump45.wav");
            LoadVoice(P90,".\\sound\\p90.wav");
            LoadVoice(Mp7,".\\sound\\mp7.wav");
            LoadVoice(Galil,".\\sound\\galil.wav");
            LoadVoice(Famas,".\\sound\\famas.wav");
            LoadVoice(Ak47,".\\sound\\ak47.wav");
            LoadVoice(M4a1,".\\sound\\m4a1.wav");
            LoadVoice(Scout,".\\sound\\scout.wav");
            LoadVoice(Walk,".\\sound\\effects\\walk.wav");
            LoadVoice(Walk_w,".\\sound\\effects\\water.wav");
            LoadVoice(Walk_g,".\\sound\\effects\\walk_g.wav");
            LoadVoice(Wall,".\\sound\\effects\\wall.wav");
            LoadVoice(Die,".\\sound\\effects\\die.wav");
            LoadVoice(Go,".\\sound\\effects\\go.wav");
            LoadVoice(Terwin,".\\sound\\effects\\terwin.wav");
            LoadVoice(Hostage,".\\sound\\effects\\hostage.wav");
            LoadVoice(Bolt,".\\sound\\bolt.wav");
            LoadVoice(Ctwin,".\\sound\\effects\\ctwin.wav");
            LoadVoice(Z_dief,".\\sound\\zm\\death_f.wav");
            LoadVoice(Z_diem,".\\sound\\zm\\death_m.wav");
            LoadVoice(Zwin,".\\sound\\zm\\zwin.wav");
            LoadVoice(Hwin,".\\sound\\zm\\hwin.wav");
            LoadVoice(Explode,".\\sound\\effects\\explode.wav");
            LoadVoice(Z_diecrab,".\\sound\\zm\\headcrab.wav");
            mymusic->size=Loadmusic(".\\sound\\theme\\hl1.wav");
	  }
	  if(i==500)
	  {
      	direct_load_nbmp(map_page,".\\res\\inv.bmp",9);
      	direct_load_nbmp(map_page,".\\res\\back2.bmp",10);
      }
	}
	load_w();
	load_menu_items();
	load_models_weapons();
load_models_object ();
load_explosion();
login();
	menu();
	  //login();
}

void load_again()
{
	direct_draw_bmp(direct_page);
	load_bar(0);
   direct_load_nbmp(map_page,".\\res\\login\\login.bmp",0);
   load_bar(100);
  	direct_load_nbmp(map_page,".\\res\\map_img.bmp",1);
  	load_bar(140);
  	direct_load_nbmp(map_page,".\\res\\buymenu.bmp",2);
  	load_bar(210);
  	direct_load_nbmp(map_page,".\\gui\\wpn\\1.bmp",3);
  	load_bar(270);
  	direct_load_nbmp(map_page,".\\gui\\wpn\\2.bmp",4);
  	direct_load_nbmp(map_page,".\\gui\\wpn\\3.bmp",5);
  	load_bar(370);
  	direct_load_nbmp(map_page,".\\gui\\wpn\\4.bmp",6);
  	direct_load_nbmp(map_page,".\\gui\\wpn\\5.bmp",7);
  	load_bar(480);
	direct_load_nbmp(map_page,".\\res\\back.bmp",8);
	load_bar(620);
	direct_load_nbmp(map_page,".\\res\\inv.bmp",9);
	direct_load_nbmp(map_page,".\\res\\back2.bmp",10);
	load_bar(691);
}