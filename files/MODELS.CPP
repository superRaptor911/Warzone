

void load_models();
void load_loading_screen_assets();
void load_menu_assets();
void load_models_weapons();

void m_us_tr()
{
	showBMP24(200,200,".\\res\\ps\\ustr.bmp");
}

void load_models()//#1
{
direct_load_models(model_handle,0,".\\models\\weapons\\bullets.bmp");
direct_load_models(model_handle,1,".\\res\\mouse\\mouse.bmp");
direct_load_models(model_handle,2,".\\models\\player\\ct\\ct_ak.bmp");
direct_load_models(model_handle,3,".\\models\\player\\ct\\blank.bmp");
direct_load_models(model_handle,4,".\\models\\weapons\\spit.bmp");
direct_load_models(model_handle,5,".\\res\\msg_box.bmp");
}


void load_loading_screen_assets()//#2
{
direct_load_models(model_handle,load_msg1,".\\gui\\load\\1.bmp");
direct_load_models(model_handle,load_msg2,".\\gui\\load\\2.bmp");
direct_load_models(model_handle,load_msg3,".\\gui\\load\\3.bmp");
direct_load_models(model_handle,load_msg4,".\\gui\\load\\4.bmp");
direct_load_models(model_handle,load_msg5,".\\gui\\load\\5.bmp");
}

void load_menu_assets()//#3
{
direct_load_models(model_handle,menu_opt_newgame,".\\gui\\menu\\newgame.bmp");
direct_load_models(model_handle,menu_opt_continue,".\\gui\\menu\\continue.bmp");
direct_load_models(model_handle,menu_opt_options,".\\gui\\menu\\options.bmp");
direct_load_models(model_handle,menu_opt_store,".\\gui\\menu\\store.bmp");
direct_load_models(model_handle,menu_opt_extras,".\\gui\\menu\\extras.bmp");
direct_load_models(model_handle,menu_opt_credits,".\\gui\\menu\\credits.bmp");
direct_load_models(model_handle,menu_opt_exit,".\\gui\\menu\\exit.bmp");
direct_load_models(model_handle,menu_opt_altnewgame,".\\gui\\menu\\1.bmp");
direct_load_models(model_handle,menu_opt_altcontinue,".\\gui\\menu\\2.bmp");
direct_load_models(model_handle,menu_opt_altoptions,".\\gui\\menu\\3.bmp");
direct_load_models(model_handle,menu_opt_altstore,".\\gui\\menu\\4.bmp");
direct_load_models(model_handle,menu_opt_altextras,".\\gui\\menu\\5.bmp");
direct_load_models(model_handle,menu_opt_altcredits,".\\gui\\menu\\6.bmp");
direct_load_models(model_handle,menu_opt_altexit,".\\gui\\menu\\7.bmp");
direct_load_models(model_handle,buy_music,".\\gui\\buy\\1.bmp");
direct_load_models(model_handle,buy_player,".\\gui\\buy\\2.bmp");
direct_load_models(model_handle,buy_gun,".\\gui\\buy\\3.bmp");
direct_load_models(model_handle,buy_spray,".\\gui\\buy\\4.bmp");
direct_load_models(model_handle,gui_glock,".\\gui\\wpn_m\\1.bmp");
direct_load_models(model_handle,gui_usp,".\\gui\\wpn_m\\2.bmp");
direct_load_models(model_handle,gui_deagle,".\\gui\\wpn_m\\3.bmp");
direct_load_models(model_handle,gui_p228,".\\gui\\wpn_m\\4.bmp");
direct_load_models(model_handle,gui_python,".\\gui\\wpn_m\\5.bmp");
direct_load_models(model_handle,gui_elite,".\\gui\\wpn_m\\6.bmp");
direct_load_models(model_handle,gui_colt,".\\gui\\wpn_m\\7.bmp");
direct_load_models(model_handle,gui_nomoney,".\\gui\\buy\\5.bmp");
//--------------------------------------------------------------
direct_load_models(model_handle,gui_iglock,".\\gui\\wpn_i\\1.bmp");
direct_load_models(model_handle,gui_iusp,".\\gui\\wpn_i\\2.bmp");
direct_load_models(model_handle,gui_ideagle,".\\gui\\wpn_i\\3.bmp");
direct_load_models(model_handle,gui_ip228,".\\gui\\wpn_i\\4.bmp");
direct_load_models(model_handle,gui_ipython,".\\gui\\wpn_i\\5.bmp");
direct_load_models(model_handle,gui_ielite,".\\gui\\wpn_i\\6.bmp");
direct_load_models(model_handle,gui_icolt,".\\gui\\wpn_i\\7.bmp");
}
int c=0;

void load_models_weapons()//#4
{
char addr[50];
	for(int i=0;i<gun_constant;i++)
	{
	strcpy(addr,".\\models\\player\\ct\\");
	strcat(addr,guns[i].name);
	strcat(addr,".bmp");
 	direct_load_models(model_handle,i+glock18,addr);
    }
	for(i=0;i<gun_constant;i++)
	{
	strcpy(addr,".\\models\\player\\t\\");
	strcat(addr,guns[i].name);
	strcat(addr,".bmp");
 	direct_load_models(model_handle,i+glock18+gun_constant,addr);
    }
	for(i=0;i<gun_constant;i++)
	{
	strcpy(addr,".\\models\\player\\alt_ct\\");
	strcat(addr,guns[i].name);
	strcat(addr,".bmp");
 	direct_load_models(model_handle,i+glock18+2*gun_constant,addr);
    }
    direct_load_models(model_handle,dead,".\\models\\player\\t\\dead.bmp");
    direct_load_models(model_handle,hostage,".\\models\\player\\hostage.bmp");

}

void load_models_object()//#5
{
  direct_load_models(model_handle,zm,".\\models\\player\\z\\hunt.bmp");
  direct_load_models(model_handle,zm2,".\\models\\player\\z\\smok.bmp");
  direct_load_models(model_handle,zm3,".\\models\\player\\z\\witch.bmp");
  direct_load_models(model_handle,zm_boom,".\\models\\player\\z\\boom.bmp");
  direct_load_models(model_handle,zm_spit,".\\models\\player\\z\\spit.bmp");
  direct_load_models(model_handle,zm_tank,".\\models\\player\\z\\tank.bmp");
  direct_load_models(model_handle,zm_hcrab,".\\models\\player\\z\\crab.bmp");
  direct_load_models(model_handle,zm_venom,".\\models\\player\\z\\venom.bmp");
  direct_load_models(model_handle,zm_spike,".\\models\\player\\z\\spike.bmp");
   direct_load_models(model_handle,zm_bug,".\\models\\player\\z\\bug.bmp");  
}

void load_explosion()//#6
{
direct_load_models(model_handle,ex1,".\\models\\static\\e1.bmp");
direct_load_models(model_handle,ex1+1,".\\models\\static\\e2.bmp");
direct_load_models(model_handle,ex1+2,".\\models\\static\\e3.bmp");
direct_load_models(model_handle,ex1+3,".\\models\\static\\e4.bmp");
direct_load_models(model_handle,ex1+4,".\\models\\static\\e5.bmp");
direct_load_models(model_handle,ex1+5,".\\models\\static\\e6.bmp");
direct_load_models(model_handle,ex1+6,".\\models\\static\\e7.bmp");
direct_load_models(model_handle,ex1+7,".\\models\\static\\e8.bmp");
direct_load_models(model_handle,ex1+8,".\\models\\static\\e9.bmp");
direct_load_models(model_handle,ex1+9,".\\models\\static\\e10.bmp");
direct_load_models(model_handle,ex1+10,".\\models\\static\\e11.bmp");
direct_load_models(model_handle,ex1+11,".\\models\\static\\e12.bmp");
}

void load_map_image(char *x,int i)//#7
{
	i+=eo_eff;
	direct_load_models(model_handle,i,x);
}
