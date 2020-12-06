#include <raptor.h>
#include "xms.h"
char log_file[50];
int runs;
#include <game2.h>
#include ".\graphics\Mouse.h"
#include ".\files\models.cpp"
#include ".\header\RPhysyx.cpp"
#include ".\files\menu.cpp"



void load_objects();

void load_objects()
{
m=new mouse;
models=new model[140];
myhud=new hud;
}

void checks(int i)
{
  file_save("testing.txt","ID ",guns[i].id);
	file_save("testing.txt","name ",guns[i].name);
	file_save("testing.txt","firerate ",guns[i].firerate);
	file_save("testing.txt","damage ",guns[i].damage);
	file_save("testing.txt","magsize ",guns[i].magsize);
       //	file_save("testing.txt","accuracy ",guns[i].accuracy);
	file_save("testing.txt","accuracy ","-----------------------------");
}



// bot1 is default hostage
void run_bot()
{
  for (int i = 0; i < 10; i++)
  {
    if (bots[i].doa==1)
    {
      bots[i].run_bot();
    }
  }
}

void load_data()
{
  init_xms_handles();
  init_log();
  logs(THETIME);
  logs(INITIAL_MEM);
  direct_load_bmp(direct_page,".\\res\\load\\back2.bmp");
  initmouse();
  restrictmouse(0,0,800,600);
  positionmouuse(100,200);
  load_objects();
  loadx();
  load();



}



void reload_bots()
{

  logs(FINAL_MEM);
}
void reload_player()
{
  delete np;
  np=new Player;
  np->x1=300;
  np->y1=1800;
  np->doa=1;
  np->walk=Walk;
}

void reload_game()
{
  delete mygame;
  mygame=new game;
  
}

void reload_map_data()
{
  delete lvl;
  lvl=new Level;
  lvl->load_Level();
  lvl->load_walls();
}

void ready_bots()
{
  for (int i = 0; i < lvl->no_bots; i++)
  {
    
    bots[i].mode=lvl->bot_mob[i][0];
    bots[i].sdeath=Die;
    if (bots[i].mode==HOSTAGE)
    {
      host=i;
    }
    bots[i].init_bot();
      bots[i].load_Bots(lvl->addr_bot_profile[i]);
      if (bots[i].mode==HOSTAGE)
      {
        bots[i].spawn_bot(400,400);
      }
      else
      {
        bots[i].spawn_bot();
      }
       bots[i].set_weapon(guns[lvl->bot_mob[i][2]-1],guns[4]);
       bots[i].set_current_weapon(1);
      if (bots[i].mode==HOSTAGE)
      {
        bots[i].current_weapon->id=36;
        bots[i].side=1;
      }
      if (bots[i].mode==ZOMBIE)
      {
           bots[i].hp=50;
           bots[i].model_id=zm+rand()%6;
           if (bots[i].model_id==zm)//hunter
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

           if (bots[i].model_id==zm3)
           {
              bots[i].sdeath=Z_dief;
           }
           else
           {
            bots[i].sdeath=Z_diem;
           }

           if (bots[i].model_id==zm_tank)
           {
              bots[i].hp=300;
           }
      }
      if (bots[i].mode==FFA)
      {
         //bots[i].side=2;
      }
  }
}

void main()
{
  initgraph(_800x600x32);
load_data();


  lvl->load_Level();
  lvl->load_maps();
  lvl->load_walls();
  logs(FINAL_MEM);
  star:
  file_save(log_file,"------------------","----------------");
   lvl->load_Level();
  lvl->load_walls();
  logs(FINAL_MEM);
ready_bots();
reload_player();
reload_game();
  mygame->bots_alive=0;
 np->set_weapon(guns[usr.selected_gun[0]],guns[usr.selected_gun[1]]);
 np->set_current_weapon(1);

  copy_xms_to_xms(direct_page5,direct_page2);
  restrictmouse(0,0,800,430);


char str[24];
direct_draw_bmp(direct_page2);
mygame->init();
mygame->msg_box("1.KILL ZOMBIES\n2.DONT GET KILLED\n3.RAPTOR ROCKS");

mygame->z1=clock();
for (int i = 0; i < lvl->no_bots; i++)
{
      bots[i].doa=0;
     //bots[i].counter=0;
}
for (;;)
{/*
for (int i = 0; i < 4;i++)
{
  file_save("ll.txt","\n\nx ",bots[i].x1);
  file_save("ll.txt","y ",bots[i].y1);
    file_save("ll.txt","rx ",bots[i].rx[0]);
    file_save("ll.txt","ry ",bots[i].ry[0]);
}*/

fps_lock_start();
  render_G();
  cam.add_y();
	chk_fps();
	getmouse(m[0].x,m[0].y,m[0].cl);
	show_m_mouse(m[0]);

	np->run_Player();
run_bot();
mygame->zombies();
//mygame->zme();
mygame->game_events();
myhud->set_hud();
	myaudio->play();
render_E(22);
if(lvl->iter==KILL_ALL)
{
if (mygame->events[1][0]==1 && m[0].cl==2)
{
   usr.kills+=np->kills-1;
   usr.deaths+=1;
   file_save(log_file,"kills :",np->kills-1);
   np->kills=0;
   usr.save_profile();
  goto star;
}
}
else
{
if (mygame->events[4][0]==1)
{
   char str[50];
   strcpy(str,"YOU KILLED ");
   add_to_string(str,np->kills-1);
   strcat(str," ZOMBIES");
   mygame->msg_box(str,' ');
   usr.kills+=np->kills-1;
   usr.deaths+=1;
   file_save(log_file,"kills :",np->kills-1);
   np->kills=0;
   usr.save_profile();
  goto star;
}
}

fps_lock_end();
    }
    getch();
}