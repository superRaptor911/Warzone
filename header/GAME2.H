//#include "Bots.h"
  int skip=0,host=0;
  int gun_constant=0;
#define CHUNK 4096
#define M_CHUNK 4096
struct mouse
{
  int x,y,cl,once,x1,y1,r,size;
  	int img_x,img_y;
  char mem[400];
};

struct model
{
	long int index;
	long int size;
	long int width,height;
};



mouse *m;
model *models;


#include ".\graphics\rgraph.h"

class audio
{
public:
  long          LinearAddress;
  unsigned int  Page, OffSet;
  unsigned char TimeConstant;
  unsigned int SoundLength;
  char Sample[M_CHUNK+2];
  audio()
  {
	ResetDSP (0x220);
    TimeConstant = (65536 - (256000000 / 22050)) >> 8;
    WriteDSP(0x40);                  //DSP-command 40h - Set sample frequency
    WriteDSP(TimeConstant);          //Write time constant
    remove("war.obj");
  }
	void endit()
	{
	     //	delete[] Sample;
	}
  int ResetDSP(unsigned int Test);
  void WriteDSP(unsigned char Value);
};

class music:public audio
{
public:
	
	long int index,size;
	int counter;
	float duration,bps;
	clock_t start,end;
  music()
  {
  	SoundLength=M_CHUNK;
  	index=0;
  	size=0;
  	counter=0;
  	bps=22.0;
  	duration=0.16;
  }
  void reset();
  void get_data();
  void play();
  void play_it()
  {
    for(;;)
    {
       play();
       if(kbhit()!=0)
       {
	      break;
       }
    }
  }
};

class sfx:public audio
{
public:
 // char Sample[CHUNK+2];
	int counter;
	long int index;
	int cur_i,stop;
	int is_playing;
	int force;
	clock_t start,end;
	sfx()
	{
		cur_i=index=counter=is_playing=0;
		stop=1;
		force=0;
	}
  void get_data(int i);
  void play_it(int i,int mode=0);
  void play();
};



class WaveData 
{
public:
  long int SoundLength, Frequency;
  long int index;
  long int size;
};
WaveData Voice[50];
class Nodes
{
public:
	int x,y;
}gno;

class lines
{
public:
	float m,c;
	int sgn;
};
class walls
{
public:
	int no_lines;
	lines line[10];
	int type;
	void load_walls(char *x);
	int is_inside(float x,float y);
	void collide(float &x,float &y);
	void bot_collide(float &x,float &y);
};


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
	void move(int i);
	void kill_self();
	int hit();
};

int wals=0,safe=0;
class game
{
public:
	int events[10][2];
	int no_maps;
	int counter;
	clock_t z1,z2;
	char msgdata[200];
	int spwan_px[10];
	int spwan_py[10];
	int bots_alive;
	int stage_counter;
	int stage;
	int no_bots;
	void init();
	void game_events();
	void zombies();
	void zme();
	void msg_box(char *x,char inp='.');
	void show_msg();
	void set_msgdata(int i);
	char show_msgmenu();
};


class Controls
{
public:
	char MOVE_UP;
	char MOVE_DOWN;
	char MOVE_LEFT;
	char MOVE_RIGHT;
	int ATTACK_1;
	int ATTACK_2;
	char SPRAY;
	char KILL;
	char CAM_UP;
	char CAM_DOWN;
	char USE;
	char BUY;
	char RELOAD;
	char JUMP;
	char SCORE;
	char SCREENSHOT;
	char ALT_ATTACK_1;
	char ALT_ATTACK_2;
	char NEXT_WEAPON;
	char ITEM_1;
	char ITEM_2;
	char SAY;
	Controls()
	{
    MOVE_UP='w';
    MOVE_DOWN='s';
    MOVE_LEFT='a';
    MOVE_RIGHT='d';
    USE='e';
    CAM_UP='H';
    SCREENSHOT='?';
    KILL='k';
    CAM_DOWN='P';
    RELOAD='r';
    SCORE=char(9);
    ITEM_1='1';
    JUMP=' ';
    ITEM_2='2';
    NEXT_WEAPON='q';
    BUY='b';
	}
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
	int reload_temp;
	Bull b[40];
	void init()
	{
		index=0;
		rate=0;
		mags=4;
		reload_temp=0;	
	}
	void force_kill_Bull();
	void create_Bullet();
	void run_Bullets();
	void fire_weapon();
	void fire_weapon(int i);
	void reload();
};


class user_profile
{
public:
	int kills,deaths;
	float eff;
	char account_name[30];
	char account_password[28];
	long int cash;
	int runs;
	int arsenal[20];
	int selected_gun[2];
	user_profile()
	{
		runs=0;
		cash=500;
		kills=deaths=0;
		eff=0;
		arsenal[0]=1;
		arsenal[2]=1;
		selected_gun[0]=14;
		selected_gun[1]=15;
	}
	int is_new()
	{
		if (runs==0)
		{
			return(1);
		}
		else
			return(0);
	}
	void create_profile();
	int load_profile();
	void save_profile();
}usr;

class menu_item
{
public:
	int id;
	int cost;
	void buy();	
	void select_gun();
};

class effect
{
public:
	int x,y;
	int no_frames;
	int dl[2];
	int frps;
	int doa;
	int now;
	int index;
	void init(int x1,int y1);
	int show();
};

class Units
{
public:
	char name[15];
	int img_y,img_x;
    float o;
	int kills,deaths;
	float v;
	int side;
	int doa;
	int hp;
	int ap;
	float x1,y1;
	float x2,y2;
	float x3,y3;
	int model_id;
	int sdeath;
	clock_t s1,s2;
	int counter;
	Weapons primary,sidearm,*current_weapon;
	Units()
	{
	 kills=0,deaths=0;
	 v=1.5;
	 model_id=2;
	 doa=0;
	 hp=100;
	 counter=0;
	 ap=100;
	 x1=0,y1=0;
	 x2=0,y2=0;
	 x3=0,y3=0;
	 o=0;
	 img_x=40;
	 img_y=40;
	}
	void init_unit()
	{
	 kills=0,deaths=0;
	 v=1.5;
	 model_id=2;
	 doa=0;
	 hp=100;
	 ap=100;
	 x1=0,y1=0;
	 x2=0,y2=0;
	 x3=0,y3=0;
	 o=0;
	 img_x=40;
	 img_y=40;
	}
	void check_doa();
	float Angle();
	void set_weapon(Weapons &w,Weapons &w2)
	{
		primary=w;
		sidearm=w2;
	}
	void set_weapon_primary(Weapons w)
	{
		primary=w;
	}
	void set_weapon_sidearm(Weapons w)
	{
		sidearm=w;
	}
	void set_current_weapon(int i);
	void anim();
	void anim(int i);
	void fire();
	void fire(int i);
	void run_Weapons();
};



class Player : public Units
{
public:
	int momentum;
	int vx,vy;
	int zone;
	char kb_input;
	int walk;
	int jump_t[2];
	Controls control;
	Player()
	{
		side=1;
		momentum=60;
		vx=vy=0;
		model_id=2;
		zone=-1;
	}
	void Player_input();
	void action();
	void move();
	void impact();
	void hud();
	void run_Player();
};

class Bots : public Units
{
public:
	int cur_node;
	int w_id,w_id2;
	int no_waypoints;
	int engage;
	int id;
	int at_dl[2];
	int old_target;
	int target;
	int burst_size[2];
	float acc;
	int mode;
	int mob[2];
	int rx[20],ry[20];
	int behave;
	effect exp;
	int exploded;
	Bull spit;
	Bots()
	{
		cur_node=0;
		side=2;
	}
	void init_bot(int i=0);
	void update_node();
	void bot_path();
	void spawn_bot();
	void spawn_bot(int x,int y);
	void move();
	void run_bot();
	void load_Bots(char *x);
	void impact();
	int behavior();
};

class hud
{
	public:
	int hx,hy;
	int ax,ay;
	int amx,amy;
	int mx,my;
	clock_t st,ed;
	int counter;
	int len,wid;
	float off;
	hud()
	{
		counter=0;
		hx=76;
		hy=555;
		ax=77;
		ay=575;
		len=150;
		wid=5;
		amx=382;
		amy=552;
		mx=383;
		my=571;
	}
	void set_hud();
};

class camera
{
public:
	long int x,y;
	long int addr,OffSet;
	int ymin,ymax;
	int i;
	int recoil;
	camera()
	{
		i=0;
		x=3200;
		addr=0;//1024000;//10240000L;
		OffSet=200;
		y=0;
		ymin=0;
		recoil=0;
		ymax=1800;
	}
	void show_cam();
	void show_cam(int i);
	void add_y();
	void add_y(int a);
}cam;




class zones
{
public:
	int x1,y1,x2,y2;
	int mode;
	int sound_id;
	int run_zone();
};

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
	char addr_img[70];
	Level();
	void init(char *x)
	{
		strcpy(name,x);
	}
	int load_Level();
	void load_maps();
	void load_walls();
	void run_map();
};
class map_addr
{
public:
char addr[70];
char addr_img[70];
}map;
class map_menu
{
public:
int x1,y1,x2,y2;
int model_id;
char name[70];	
};

enum msg_mode
{
	Player_info,Player_buy
};

enum bot_difficulty
{
	EASY,MEDIUM,HARD,EXPERT,BOSS
};

enum game_modes
{
	KILL_ALL,HOSTAGE_RESCUE,ZOMBIE_MOD,ZOMBIE_ESCAPE
};

enum wall_modes
{
	SOLID,GRASS,WATER,TOXIC,SAFE
};
enum bot_behavior
{
	NONE,ATTACK,DEFENCE,HOSTAGE,TRUCK,ZOMBIE,FFA
};

enum sound_effects
{
	Usp=1,Deagle,P22,Python,Elite,Colt,Tmp,Mp5,Ump45,P90,
	Mp7,Galil,Famas,Ak47,M4a1,Scout,Walk,Walk_w,Walk_g,Wall,Die,Go,
	Terwin,Hostage,Bolt,Ctwin,Z_dief,Z_diem,Zwin,Hwin,Explode,Z_diecrab,
	eo_sound
};

enum assets_index
{
	load_msg1=6,load_msg2,load_msg3,load_msg4,load_msg5,
	menu_opt_newgame,menu_opt_continue,menu_opt_options,
	menu_opt_store,menu_opt_extras,menu_opt_credits,
	menu_opt_exit,menu_opt_altnewgame,menu_opt_altcontinue,
	menu_opt_altoptions,menu_opt_altstore,menu_opt_altextras,
	menu_opt_altcredits,menu_opt_altexit,buy_music,buy_player,buy_gun,buy_spray,gui_glock,
	gui_usp,gui_deagle,gui_p228,gui_python,gui_elite,gui_colt,
	gui_nomoney,gui_iglock,gui_iusp,gui_ideagle,gui_ip228,gui_ipython,
	gui_ielite,gui_icolt,eo_assets_index
};
enum weapon_model_index
{
	glock18=eo_assets_index,dead=glock18+51,
	hostage,eo_weapon
};

enum zombie_index
{
	zm=eo_weapon,zm2,zm3,zm_boom,zm_spit,zm_tank,zm_hcrab,zm_venom,
	zm_spike,zm_bug,eo_obj
};

enum effects_index
{
	ex1=eo_obj,eo_eff=ex1+12
};


Player *np;
sfx *myaudio;
music *mymusic;
Weapons far *guns;
Level *lvl;
Bots far *null_bots;
Bots far *bots;
walls *wall;
hud *myhud;
map_menu far *maps;
menu_item far *menu_items;
game far *mygame;
void loadx()
{
	np=new Player;
	lvl=new Level;
	wall=new walls[40];
	myaudio=new sfx;
	mymusic=new music;
	
	np->x1=300;
	np->y1=1800;
	np->doa=1;
	np->sdeath=Die;
	long int sz=sizeof(Bots);
sz=sz*18;
 null_bots=(Bots *)farmalloc(sz);
  bots=(Bots *)farmalloc(sz);
  sz=sizeof(map_menu);sz=sz*10;
  maps=(map_menu *)farmalloc(sz);
  sz=sizeof(menu_item);sz=sz*20;
  menu_items=(menu_item *)farmalloc(sz);
  sz=sizeof(Weapons);sz=sz*20;
  guns=(Weapons *)farmalloc(sz);
  mygame=(game *)farmalloc(sizeof(game));

}

#include <gamedef.h>
