#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "xcollisiondetection.h"
#include "gfx/tiles_gfx.h"
#include "gfx/dungeon.h"
//#include "gfx/dungeon2.h"
#include "structs.h"
#include "minimap.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <setjmp.h>
#include <fileioc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>

int i;
int goleft;
int goright;
int goup;
int godown;
int spritexoffset = 160;
int spriteyoffset = 128;
int tileoffsetx;
int tileoffsety;
int player;

//1=left,2=up,3=right,4=down
int playerface;
int player_screenpxlx;
int player_screenpxly;
int player_mappxlx;
int player_mappxly;
int hpbar_length;
int hpbar_color;
int greencolor = 0x25;
int yellowcolor = 0xE7;
extern int redcolor;
gfx_sprite_t *weapon;
gfx_sprite_t *weaponrotated;
gfx_sprite_t *flippedequip;
gfx_sprite_t *playerwalk;
gfx_sprite_t *bootanimation;
gfx_sprite_t *animation;
gfx_sprite_t *player_health;
gfx_sprite_t *helmet;
gfx_sprite_t *chestplate;
gfx_sprite_t *boots;   
	
extern int menuyes;
extern int textcolor;
extern uint8_t tilemap_map[];
extern unsigned int tmap_pxl_x_offset;
extern unsigned int tmap_pxl_y_offset;
extern int mapstartx;
extern int mapstarty;
extern int mapshift;
int player_maptilex;
int player_maptiley;
int *inputx;
int *inputy;
extern uint24_t player_setup[];
int dmgmultiplier = 1;
int damagenumbers = 0;
int blockchance;
int walkwait = 1500;
int w;
int walkspeed = 100;
int minimapposition = 1;
extern int menuoption;

extern gfx_tilemap_t tilemap;

extern uint16_t default_potylist[];
extern uint16_t default_potxlist[];

extern int mmhotkey;
extern int purchased[];
extern int equipped[];

int showminimap = 1;

int walkanimation = 1;
int animationcount_min = 1;
int animationcount_mid = 3;
int animationcount_max = 6;
int p_hit;
int num_p = 0;
int max_p = 100;

//Start of the game
void menuloop(void){
	
	do {
		/*pick whether to continue or not*/
		mainmenu ();

		//menuyes comes from the mainmenu function
		//menuyes chunk begin
		if (menuyes == 1) {
			if (menuoption == 1) {
				//loadsave();
				//maingameloop();
			}
		}
		if (menuyes == 1) {
			if (menuoption == 2) {
				newgame();
					player_setup[0] = 0;
					player_setup[1] = 0;
					player_setup[2] = 0;
					player_setup[3] = 0;
					player_setup[4] = 0;
					player_setup[5] = 0;
					player_setup[6] = 100;
					player_setup[7] = 0;
				maingameloop();
			}
		}
		if (menuyes == 1) {
			if (menuoption == 3) {
				newgame();
					equipped[0] = player_setup[0];
					equipped[1] = player_setup[1];
					equipped[2] = player_setup[2];
					equipped[3] = player_setup[3];
				maingameloop();
			}
		}
		if (menuyes == 1) {
			if (menuoption == 4) {
				//options();
				playercreate();
			}
		}
		//menuyes chunk end
	} while (!(kb_Data[6] & kb_Clear));
	gfx_End();
	exit(0);
	
}	
void maingameloop(void){
	
	do{
		
		(goleft = 0);
		(goright = 0);
		(goup = 0);
		(godown = 0);
		
		setmapshift();
		
		gfx_SetDrawBuffer();
		
		drawmap();
		drawcharacter();
		drawplayerattack();
		updateenemies();
		updatepots();
		updatemoney();
		updateprojectiles();
		minimap();
		checkplayerstatus();
		drawbottombar();
		
		
		//gfx_SetTextBGColor(0x00);
		//gfx_SetTextXY(10,150);
		//gfx_PrintInt(num_p,3);
		
		
		gfx_SwapDraw();
		
		mapshifter();
	if (kb_Data[1] & kb_Yequ) {
		drawpouch();
	}
	if (kb_Data[1] & kb_Zoom) {
		drawstatsmenu();
	}
	if (kb_Data[1] & kb_Trace) {
		drawstore();
	}
	if (kb_Data[1] & kb_Graph) {
		drawoptions();
	}
	if (kb_Data[2] & kb_Alpha) {
		if (mmhotkey == 1) {
			if (showminimap == 1){showminimap = 0;}
			else if (showminimap == 0){showminimap = 1;}
		}
	}
	if (kb_Data[1] & kb_Mode) {
		if (mmhotkey == 2) {
			if (showminimap == 1){showminimap = 0;}
			else if (showminimap == 0){showminimap = 1;}
		}
	}
	if (kb_Data[1] & kb_Del) {
		if (mmhotkey == 3) {
			if (showminimap == 1){showminimap = 0;}
			else if (showminimap == 0){showminimap = 1;}
		}
	}
		
	walkanimation++;
		if (walkanimation > animationcount_max) {
			walkanimation = animationcount_min;
		}
		
	} while (!(kb_Data[6] & kb_Clear));
	//menuloop();
}
void setmapshift(void) {
	mapshift = 32;
	/*
	if (player_setup[2] == 0) {(mapshift = 32);}
	if (player_setup[2] == 1) {(mapshift = 32);}
	if (player_setup[2] == 2) {(mapshift = 32);}
	if (player_setup[2] == 3) {(mapshift = 32);}
	if (player_setup[2] == 4) {(mapshift = 32);}
	*/
}	
void drawmap(void) {
	player_screenpxlx = ((tmap_pxl_x_offset/tmap_pxl_x_offset)+spritexoffset);
	player_screenpxly = ((tmap_pxl_y_offset/tmap_pxl_y_offset)+spriteyoffset);
	player_mappxlx = (tmap_pxl_x_offset + (spritexoffset));
	player_mappxly = (tmap_pxl_y_offset + (spriteyoffset));
	gfx_SetDrawBuffer();
	gfx_Tilemap(&tilemap, tmap_pxl_x_offset, tmap_pxl_y_offset);
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	
//coordinate debug numbers
	/*
	gfx_SetTextBGColor(0x00);
	gfx_SetTextXY(10,10);
	gfx_PrintString("tmap_px_offset---");
	gfx_PrintInt(tmap_pxl_x_offset,4);
	gfx_PrintString(" , ");
	gfx_PrintInt(tmap_pxl_y_offset,4);
	*/
	
/*print debug numbers for collision and stuff
	gfx_PrintStringXY("tile", 8, 224);
	gfx_PrintUInt((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly)),2);
	gfx_PrintString("  tile L");
	gfx_PrintUInt((gfx_GetTile(&tilemap,player_mappxlx-32,player_mappxly)),2);
	gfx_PrintString("  tile U");
	gfx_PrintUInt((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly-32)),2);
	gfx_PrintString("  tile R");
	gfx_PrintUInt((gfx_GetTile(&tilemap,player_mappxlx+32,player_mappxly)),2);
	gfx_PrintString("  tile D");
	gfx_PrintUInt((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly+32)),2);
*/
}
void mapshifter(void) {
	player_maptilex = (player_mappxlx/32);
	player_maptiley = (player_mappxly/32);
	inputx = &player_maptilex;
	inputy = &player_maptiley;
	player = 1;
	
	if (kb_Data[7] & kb_Left) {
		(playerface = 1);
		collisionleft();
		if (goleft == 1) {
			(tmap_pxl_x_offset = (tmap_pxl_x_offset - mapshift));
		}
	}
	if (kb_Data[7] & kb_Right) {
		(playerface = 3);
		collisionright();
		if (goright == 1){
			(tmap_pxl_x_offset = (tmap_pxl_x_offset + mapshift));
		}
	}
	if (kb_Data[7] & kb_Up) {
		(playerface = 2);
			collisionup();
			if (goup == 1){
			(tmap_pxl_y_offset = (tmap_pxl_y_offset - mapshift));
		}
	}
	if (kb_Data[7] & kb_Down) {
			(playerface = 4);
			collisiondown();
			if (godown == 1){
			(tmap_pxl_y_offset = (tmap_pxl_y_offset + mapshift));
		}
	}
}
void drawcharacter(void) {
gfx_UninitedSprite(playerwalk, 32,32);
	if (playerface == 1) {
		animation = player_naked_left;
	}
	if (playerface == 2) {
		if (walkanimation <= animationcount_mid) {
			animation = player_naked_up;
		}
		if (walkanimation > animationcount_mid) {
			gfx_FlipSpriteY(player_naked_up,playerwalk);
			animation = playerwalk;
		}
	}
	if (playerface == 3) {
		animation = player_naked_right;
	}
	if (playerface == 4) {
		if (walkanimation <= animationcount_mid) {
			animation = player_naked_down;
		}
		if (walkanimation > animationcount_mid) {
			gfx_FlipSpriteY(player_naked_down,playerwalk);
			animation = playerwalk;
		}
	}
gfx_TransparentSprite(animation,player_screenpxlx,player_screenpxly);
drawhelmet();
drawchestplate();
drawboot();
	
	/*
	gfx_SetTextXY(10,30);
	gfx_PrintString("player_screenpxl-");
	gfx_PrintInt(player_screenpxlx,4);
	gfx_PrintString(" , ");
	gfx_PrintInt(player_screenpxly,4);
	gfx_SetTextXY(10,50);
	gfx_PrintString("player_mappxl-----");
	gfx_PrintInt(player_mappxlx,4);
	gfx_PrintString(" , ");
	gfx_PrintInt(player_mappxly,4);
	gfx_SetTextXY(10,70);
	gfx_PrintString("player_maptile----");
	gfx_PrintInt(player_maptilex,4);
	gfx_PrintString(" , ");
	gfx_PrintInt(player_maptiley,4);
	*/
	
}
void drawhelmet(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	if (player_setup[0] == 1){
	if (playerface == 1) {helmet = leather_helmet_left;}
	else if (playerface == 2) {helmet = leather_helmet_up;}
	else if (playerface == 3) {helmet = (gfx_FlipSpriteY(leather_helmet_left,flippedequip));}
	else if (playerface == 4) {helmet = leather_helmet_down;}
	}
	else if (player_setup[0] == 2){
		if (playerface == 1) {helmet = chain_helmet_left;}
	else if (playerface == 2) {helmet = chain_helmet_up;}
	else if (playerface == 3) {helmet = (gfx_FlipSpriteY(chain_helmet_left,flippedequip));}
	else if (playerface == 4) {helmet = chain_helmet_down;}
	}
	else if (player_setup[0] == 3){
		if (playerface == 1) {helmet = steel_helmet_left;}
	else if (playerface == 2) {helmet = steel_helmet_up;}
	else if (playerface == 3) {helmet = (gfx_FlipSpriteY(steel_helmet_left,flippedequip));}
	else if (playerface == 4) {helmet = steel_helmet_down;}
	}
	else if (player_setup[0] == 4){
		if (playerface == 1) {helmet = dragon_helmet_left;}
	else if (playerface == 2) {helmet = dragon_helmet_up;}
	else if (playerface == 3) {helmet = (gfx_FlipSpriteY(dragon_helmet_left,flippedequip));}
	else if (playerface == 4) {helmet = dragon_helmet_down;}
	}
	if (player_setup[0] != 0) {
	gfx_TransparentSprite(helmet,player_screenpxlx,player_screenpxly);
	}
}
void drawchestplate(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	if (player_setup[1] == 1){
		if (playerface == 1) {chestplate = leather_chestplate_left;}
		else if (playerface == 2) {chestplate = leather_chestplate_up;}
		else if (playerface == 3) {chestplate = (gfx_FlipSpriteY(leather_chestplate_left,flippedequip));}
		else if (playerface == 4) {chestplate = leather_chestplate_down;}
	}
	else if (player_setup[1] == 2){
		if (playerface == 1) {chestplate = chain_chestplate_left;}
		else if (playerface == 2) {chestplate = chain_chestplate_up;}
		else if (playerface == 3) {chestplate = (gfx_FlipSpriteY(chain_chestplate_left,flippedequip));}
		else if (playerface == 4) {chestplate = chain_chestplate_down;}
	}
	else if (player_setup[1] == 3){
		if (playerface == 1) {chestplate = steel_chestplate_left;}
		else if (playerface == 2) {chestplate = steel_chestplate_up;}
		else if (playerface == 3) {chestplate = (gfx_FlipSpriteY(steel_chestplate_left,flippedequip));}
		else if (playerface == 4) {chestplate = steel_chestplate_down;}
	}
	else if (player_setup[1] == 4){
		if (playerface == 1) {chestplate = dragon_chestplate_left;}
		else if (playerface == 2) {chestplate = dragon_chestplate_up;}
		else if (playerface == 3) {chestplate = (gfx_FlipSpriteY(dragon_chestplate_left,flippedequip));}
		else if (playerface == 4) {chestplate = dragon_chestplate_down;}
	}
	if (player_setup[1] != 0){
		gfx_TransparentSprite(chestplate,player_screenpxlx,player_screenpxly);
	}
}
void drawboot(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	gfx_UninitedSprite(bootanimation, 32, 32);
	//beck: if player_setup[2] is zero, "boots" will never be set
	if (player_setup[2]){
		if (player_setup[2] == 1){
			if (playerface == 1) {boots = leather_boots_left;}
			else if (playerface == 2) {boots = leather_boots_up;}
			else if (playerface == 3) {boots = (gfx_FlipSpriteY(leather_boots_left,flippedequip));}
			else if (playerface == 4) {boots = leather_boots_down;}
		}
		else if (player_setup[2] == 2){
			if (playerface == 1) {boots = chain_boots_left;}
			else if (playerface == 2) {boots = chain_boots_up;}
			else if (playerface == 3) {boots = (gfx_FlipSpriteY(chain_boots_left,flippedequip));}
			else if (playerface == 4) {boots = chain_boots_down;}
		}
		else if (player_setup[2] == 3){
			if (playerface == 1) {boots = steel_boots_left;}
			else if (playerface == 2) {boots = steel_boots_up;}
			else if (playerface == 3) {boots = (gfx_FlipSpriteY(steel_boots_left,flippedequip));}
			else if (playerface == 4) {boots = steel_boots_down;}
		}
		else if (player_setup[2] == 4){
			if (playerface == 1) {boots = dragon_boots_left;}
			else if (playerface == 2) {boots = dragon_boots_up;}
			else if (playerface == 3) {boots = (gfx_FlipSpriteY(dragon_boots_left,flippedequip));}
			else if (playerface == 4) {boots = dragon_boots_down;}
		}

		//Only draw the sprite "boots" if it was set.
		//The only case it gets set is when player_setup[2] is not zero
		if (walkanimation <= animationcount_mid) {
			gfx_TransparentSprite(boots,player_screenpxlx,player_screenpxly + 27);
		}
		else if (walkanimation > animationcount_mid) {
			if ((playerface == 2) || (playerface == 4)) {
				gfx_FlipSpriteY(boots,bootanimation);
			}
			if ((playerface == 1) || (playerface == 3)) {
				bootanimation = boots;
			}
			if (player_setup[2] != 0){
				gfx_TransparentSprite(bootanimation,player_screenpxlx,player_screenpxly + 27);
			}
		}
	}
}
void drawplayerattack(void){
	gfx_UninitedSprite(weaponrotated, 32, 32);
	int pressed;
		//player_setup[3] = 5;
		//permanently enables bow
	
	if (kb_Data[1] & kb_2nd){
		if (player_setup[3] == 0) {weapon = fist;}
		if (player_setup[3] == 1) {weapon = club;}
		if (player_setup[3] == 2) {weapon = iron_sword;}
		if (player_setup[3] == 3) {weapon = steel_sword;}
		if (player_setup[3] == 4) {weapon = dragon_sword;}
		if (player_setup[3] == 5) {weapon = bow_basic;}
		if (player_setup[3] == 6) {weapon =	bow_recurve;}
		if (player_setup[3] == 7) {weapon = bow_compound;}
		if (player_setup[3] == 8) {weapon = bow_dragon;}
		
		
		if (playerface == 1) {
			if (player_setup[3] < 5){
				gfx_TransparentSprite(gfx_RotateSpriteCC(weapon,weaponrotated),player_screenpxlx-32,player_screenpxly);
			}
		}
		if (playerface == 2) {
			if (player_setup[3] < 5){
				gfx_TransparentSprite(weapon,player_screenpxlx,player_screenpxly-32);
			}

		}
		if (playerface == 3) {
			if (player_setup[3] < 5){
				gfx_TransparentSprite(gfx_RotateSpriteC(weapon,weaponrotated),player_screenpxlx+32,player_screenpxly);
			}
				
		}
		if (playerface == 4) {
			if (player_setup[3] < 5){
				gfx_TransparentSprite(gfx_RotateSpriteHalf(weapon,weaponrotated),player_screenpxlx,player_screenpxly+32);
			}
		}
		

			if (player_setup[3] >= 5){
				if (num_p < max_p){
					num_p++;
				}
				if (player_setup[3] <= 8){
					projectile[num_p].p_type = 1;
				}
				projectile[num_p].p_x = player_mappxlx;	
				projectile[num_p].p_y = player_mappxly;
				projectile[num_p].p_alive = 1;
				projectile[num_p].p_direction = playerface;
				projectile[num_p].p_speed = 5;
			
			
				if (projectile[num_p].p_direction == 1) {
					gfx_TransparentSprite(gfx_RotateSpriteCC(weapon,weaponrotated),player_screenpxlx-7,player_screenpxly);
					if (projectile[num_p].p_type == 1){
						projectile[num_p].p_y = (projectile[num_p].p_y + 13);
					}
					projectile[num_p].p_vx = -1;
					projectile[num_p].p_vy = 0;
				}
				if (projectile[num_p].p_direction == 2) {
					gfx_TransparentSprite(weapon,player_screenpxlx,player_screenpxly-7);
					if (projectile[num_p].p_type == 1){
						projectile[num_p].p_x = (projectile[num_p].p_x + 13);
					}
					projectile[num_p].p_vx = 0;
					projectile[num_p].p_vy = -1;
				}
				if (projectile[num_p].p_direction == 3) {
					gfx_TransparentSprite(gfx_RotateSpriteC(weapon,weaponrotated),player_screenpxlx+32,player_screenpxly);
					if (projectile[num_p].p_type == 1){
						projectile[num_p].p_y = (projectile[num_p].p_y + 13);
					}
					projectile[num_p].p_vx = 1;
					projectile[num_p].p_vy = 0;
				}
				if (projectile[num_p].p_direction == 4) {
					gfx_TransparentSprite(gfx_RotateSpriteHalf(weapon,weaponrotated),player_screenpxlx,player_screenpxly+32);
					if (projectile[num_p].p_type == 1){
						projectile[num_p].p_x = (projectile[num_p].p_x + 13);
					}
					projectile[num_p].p_vx = 0;
					projectile[num_p].p_vy = 1;
				}
			
			/*
			gfx_SetTextBGColor(0x00);
			gfx_SetTextXY(10,90);
			gfx_PrintString("arrow coords-----");
			gfx_PrintInt(projectile[num_p].p_x,4);
			gfx_PrintString(" , ");
			gfx_PrintInt(projectile[num_p].p_y,4);
			*/
			
		}
		playerattackhitcheck();
	}
}
void checkplayerstatus(void){
	extern int playerdamage;
	int i;
	//checks if you are standing on a spike
	if ((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly)) == 9){
		(player_setup[6] = player_setup[6] - 5);
		gfx_FillScreen(0xE0);
	}
	
	//checks player health and adjusts healthbar
	if (player_setup[6] > 100) {player_setup[6] = 100;}
	if ((100 >= player_setup[6]) & (player_setup[6] > 90)){
		hpbar_length = 60;
		hpbar_color = greencolor;
	}
	else if ((90 >= player_setup[6]) & (player_setup[6] > 80)){
		hpbar_length = 54;
		hpbar_color = greencolor;
	}
	else if ((80 >= player_setup[6]) & (player_setup[6] > 70)){
		hpbar_length = 48;
		hpbar_color = greencolor;
	}
	else if ((70 >= player_setup[6]) & (player_setup[6] > 60)){
		hpbar_length = 42;
		hpbar_color = greencolor;
	}
	else if ((60 >= player_setup[6]) & (player_setup[6] > 50)){
		hpbar_length = 36;
		hpbar_color = yellowcolor;
	}
	else if ((50 >= player_setup[6]) & (player_setup[6] > 40)){
		hpbar_length = 30;
		hpbar_color = yellowcolor;
	}
	else if ((40 >= player_setup[6]) & (player_setup[6] > 30)){
		hpbar_length = 24;
		hpbar_color = yellowcolor;
	}
	else if ((30 >= player_setup[6]) & (player_setup[6] > 20)){
		hpbar_length = 18;
		hpbar_color = redcolor;
	}
	else if ((20 >= player_setup[6]) & (player_setup[6] > 10)){
		hpbar_length = 12;
		hpbar_color = redcolor;
	}
	if (player_setup[6] <= 0) {youdied();}
	
	//determines player_setup
	player_setup[0] = equipped[0];
	player_setup[1] = equipped[1];				
	player_setup[2] = equipped[2];
	player_setup[3] = equipped[3];
	
	//determined by weapon
	playerdamage = player_setup[3]+1;
	//helmet and chestplate added together
	blockchance = ((player_setup[0] + player_setup[1]) * 10);
	//set by boots
	//walkspeed = ((player_setup[2]+1)*20);
	

	
}
void drawbottombar(void){
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetColor(hpbar_color);
	gfx_FillRectangle(80,227,hpbar_length,10); 
	gfx_TransparentSprite(health_empty,80,224);
	if ((10 >= player_setup[6]) & (player_setup[6] > 0)){gfx_TransparentSprite(health10,80,224);}
	gfx_SetTextScale(1,1);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("[POUCH]  HP:",4,228);
	gfx_PrintStringXY("[STATS]",150,228);
	gfx_PrintStringXY("[STORE]",208,228);
	gfx_PrintStringXY("[OPTNS]",266,228);
}
void youdied(void){
	extern int menucolor;
	extern int accentcolor;
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_ScaledTransparentSprite_NoClip(tombstone,70,30,5,5);
	gfx_SetTextFGColor(0xE8);
	gfx_SetTextScale(2,2);
	gfx_PrintStringXY("You died!",102,192);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("[f1] Main Menu",100,210);
	gfx_PrintStringXY("[f2] Quit",100,218);
	gfx_SwapDraw();
	do {
		if (kb_Data[1] & kb_Yequ) {menuloop();}
	} while (!(kb_Data[1] & kb_Window));
	gfx_End();
	exit(0);
}
void resetpots(void){
int n = 0;
	for (i = 0; i < NUM_POTS; i++) {
		n++;
		if (n>5) {n=0;}
		if (3<= n) {
			pots[i].pottype = 0;
		}
		else {
			pots[i].pottype = 1;
		}
		pots[i].potdead = 0;
		pots[i].p_x = default_potxlist[i]*32;
		pots[i].p_y = default_potylist[i]*32;
	}
}
void updatepots(void){
	for (i = 0; i < NUM_POTS; i++) {	
		if ((pots[i].potdead) == 0) {
		renderpots(&pots[i]);
		}
	}
}
void renderpots(pots_t *pots){
gfx_TransparentSprite(pot,(pots->p_x - tmap_pxl_x_offset), (pots->p_y - tmap_pxl_y_offset));

/*only for testing
gfx_SetTextFGColor(0xA8);
gfx_SetTextXY(pots->p_x - tmap_pxl_x_offset,pots->p_y - tmap_pxl_y_offset);
gfx_PrintUInt(pots->pottype,1);
*/

/*for debug
gfx_PrintString("---");
gfx_PrintUInt((pots->p_x)/32,3);
gfx_PrintString("-");
gfx_PrintUInt((pots->p_y)/32,3);
*/
		
}
void updatemoney(void){
	for (i = 0; i < NUM_POTS; i++) {	
		if ((money[i].moneydead) == 0) {
			rendermoney(&money[i]);
		}
	}
}
void rendermoney(money_t *money){
	gfx_sprite_t *moneySprite;
	
	moneySprite = money1;
	if (money->moneyvalue == 5) {moneySprite = money5;}
	if (money->moneyvalue == 10) {moneySprite = money10;}
	if (money->moneyvalue == 20) {moneySprite = money20;}
	if (money->moneyvalue == 100) {moneySprite = money100;}
	gfx_TransparentSprite(moneySprite, money->m_x - tmap_pxl_x_offset, money->m_y - tmap_pxl_y_offset);
	
}
void updateprojectiles(void){
/*for fixing dumb counting errors
int projectile_test_x = 100;
int projectile_test_y = 100;
int deadcheck = 0;
*/
	
	for(i = 0; i < num_p; i++){
		
		/* for testing dumb counting error fixes
			gfx_SetTextXY(projectile_test_x,projectile_test_y);
			gfx_PrintInt(projectile[i].p_alive,1);
			projectile_test_x = (projectile_test_x + 20);
			if (projectile_test_x >= 190){
				projectile_test_x = 100;
				projectile_test_y = (projectile_test_y + 20);
			}
		*/
	/*	for fixing dumb counting errors
		if (num_p > 1){
			if (projectile[i].p_alive == 0){
				deadcheck++;
				if (deadcheck = num_p){
					num_p--;
				}
			}
		}
	*/	
		if ((projectile[i].p_alive) == 1) {
			projectile[i].p_x = (projectile[i].p_x + (projectile[i].p_vx * projectile[i].p_speed));
			projectile[i].p_y = (projectile[i].p_y + (projectile[i].p_vy * projectile[i].p_speed));
			p_hit = 0;
								 
			projectilemapcollision();
			projectileentitycollision();
								 
			//if it hit a wall
			if (p_hit == 1){
				gfx_TransparentSprite(arrow_hitwall,projectile[i].p_x - tmap_pxl_x_offset,projectile[i].p_y - tmap_pxl_y_offset);
				num_p--;
				projectile[i].p_alive = 0;
			}
			if (p_hit == 0){
				renderprojectiles(&projectile[i]);
			}
		}
	}
}
void renderprojectiles(projectile_t *projectile){
	gfx_UninitedSprite(p_unrotated,32,5);
	gfx_UninitedSprite(p_rotated,32,5);
	
	if (projectile->p_type == 1) {p_unrotated = arrow;}
	
	if (projectile->p_direction == 1){
		gfx_RotateSpriteHalf(p_unrotated,p_rotated);
	}
	if (projectile->p_direction == 2){
		gfx_RotateSpriteCC(p_unrotated,p_rotated);
	}
	if (projectile->p_direction == 3){
		p_rotated = p_unrotated;
	}
	if (projectile->p_direction == 4){
		gfx_RotateSpriteC(p_unrotated,p_rotated);
	}
	gfx_TransparentSprite(p_rotated, projectile->p_x - tmap_pxl_x_offset, projectile->p_y - tmap_pxl_y_offset);
}


