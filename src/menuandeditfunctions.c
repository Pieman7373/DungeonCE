#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "enemymovement.h"
#include "gfx/dungeon.h"
#include "gfx/dungeon2.h"
#include "gfx/dungeon_gfx.h"
#include "structs.h"

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
	 

extern int i;
extern int menuoption;
extern int menuyes;
extern int textcolor;
extern int menucolor;
extern int submenucolor;
extern int accentcolor;
extern int transcolor;
extern int editscale;
extern int editscalep;
extern int editweaponx;
extern int editweapony;
extern int editweaponsmallx;
extern int editweaponsmally;
extern int editpx;
extern int editpy;
extern unsigned int x_offset;
extern unsigned int y_offset;

uint8_t enemytype;
int deadset;
uint24_t enemyx;
uint24_t enemyy;
int enemyhealth;

int drawhealth = 1;
extern signed int setnumber;
extern uint8_t player_setup[];

uint16_t defaultenemy_movelist[NUM_ENEMIES] = {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint16_t defaultenemy_typelist[NUM_ENEMIES] = {0,1,2,3,4,5,6,2,2,2,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6};
uint16_t defaultenemy_xlist[NUM_ENEMIES] = {76,76,76,77,77,78,78,106,107,107,106,15,52,53,54,55,56,57,58,52,53,54,55,56,57,58,25,26,27,28,29,30,31};
uint16_t defaultenemy_ylist[NUM_ENEMIES] = {90,91,92,90,91,90,91,74,75,74,75,93,80,80,80,80,80,80,80,81,81,81,81,81,81,81,65,65,65,65,65,65,65};


extern int mapstartx;
extern int mapstarty;
extern int tileoffsetx;
extern int tileoffsety;
extern kb_key_t key;


gfx_sprite_t *enemySprite;
enemy_t  enemy[NUM_ENEMIES];
int ii;

void keywait(void) {os_GetCSC();}

void mainmenu(void) {
	//type, dead, enemyx,enemyy,health
	
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
    gfx_ScaledTransparentSprite_NoClip(mainmenulogo,33,20,2,2);
    gfx_TransparentSprite(menuwords,100,130);
	gfx_SwapDraw();
	
    do {
       menuyes = 0;
        if (kb_Data[3] & kb_1) {
            menuyes = 1;
            menuoption = 1;
        }
        if (kb_Data[4] & kb_2) {
            menuyes = 1;
            menuoption = 2;
        }
        if (kb_Data[5] & kb_3) {
            menuyes = 1;
            menuoption = 3;
        }
} while (!((menuoption) || (kb_Data[6] & kb_Clear)));
 
}
void options(void) {
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(40,60,215,100);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(40,60,215,100);
	gfx_Rectangle(42,62,211,96);
	gfx_TransparentSprite(optionsmenu,45,65);
	gfx_SwapDraw();
		do {
			if (kb_Data[3] & kb_1) {
				playercreate();
			}
			if (kb_Data[4] & kb_2){
				menuyes = 3;
			}
		} while (menuyes != 3);
}
void drawsavemenu(void){
	
	gfx_SetDrawBuffer();
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(0,154,108,66);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,154,108,66);
	gfx_Rectangle(2,156,104,62);
	submenubottombar();
	gfx_PrintStringXY("1. Save",5,160);
	gfx_SwapDraw();
	do {
		if (kb_Data[3] & kb_1) {savegame();}
	} while (!(kb_Data[1] & kb_Window));
}
void submenubottombar(void){
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("[Close]",80,228);
}
void savegame(void) {
	//save player_setup to Appvar
}
void loadsave(void) {
	//load player_setup from Appvar
	mapstartx = player_setup[4];
	mapstarty = player_setup[5];
}
void newgame(void) {
	player_setup[6] = 100;
	resetenemies();
	resetpots();
}
void playercreate(void) {
	int keypress;
	do{
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_HorizLine(0,223,320);
	gfx_HorizLine(0,221,320);
	gfx_SetTextTransparentColor(transcolor);
	gfx_SetTextFGColor(textcolor);
    gfx_SetTextBGColor(transcolor);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("f(1-5) = change set, # = select item, del = back",8,227);
	gfx_TransparentSprite(editmenunumbers,40,20);
	drawequipment();
	draweditedplayer();
	gfx_SwapDraw();
		
		do {
			keypress = 0;
				if (kb_Data[1] & kb_Yequ) {
					(setnumber = 0);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Window) {
					(setnumber = 1);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Zoom) {
					(setnumber = 2);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Trace) {
					(setnumber = 3);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Graph) {
					(setnumber = 4);
					keypress = 1;
					}
			
				if (kb_Data[3] & kb_1){
					(player_setup[0] = setnumber);
					keypress = 1;
				}
				if (kb_Data[4] & kb_2) {
					(player_setup[1] = setnumber);
					keypress = 1;
				}
				if (kb_Data[5] & kb_3) {
					(player_setup[2] = setnumber);
					keypress = 1;
				}
				if (kb_Data[3] & kb_4) {
					(player_setup[3] = setnumber);
					keypress = 1;
				}
				if (kb_Data[1] & kb_Del) {keypress = 1;}
		}	while (keypress == 0);
		
	}	while (!(kb_Data[1] & kb_Del));
	
	(menuyes = 3);
}
void draweditedplayer(void) {
	gfx_SetColor(0x00);
	gfx_FillRectangle(editpx,editpy,((editscale * 32)-15),(editscale * 32));
	gfx_ScaledTransparentSprite_NoClip(player_naked_down,editpx,editpy,editscale,editscale);
	if (player_setup [0] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_boots_down,editpx,editpy,editscale,editscale);}
	if (player_setup [3] == 1) {gfx_ScaledTransparentSprite_NoClip(club,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_boots_down,editpx,editpy,editscale,editscale);}
	if (player_setup [3] == 2) {gfx_ScaledTransparentSprite_NoClip(iron_sword,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_boots_down,editpx,editpy,editscale,editscale);}
	if (player_setup [3] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_sword,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_boots_down,editpx,editpy,editscale,editscale);}
	if (player_setup [3] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_sword,editweaponx,editweapony,editscale-1,editscale-1);}
}
void drawequipment(void) {
	gfx_SetColor(0x00);
	gfx_FillRectangle(65,12,96,208);
	if (setnumber == 1) {
		gfx_ScaledTransparentSprite_NoClip(leather_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(leather_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(leather_boots_down,50,55,3,3);
		gfx_ScaledTransparentSprite_NoClip(club,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 2) {
		gfx_ScaledTransparentSprite_NoClip(chain_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(chain_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(chain_boots_down,50,55,3,3);
		gfx_ScaledTransparentSprite_NoClip(iron_sword,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 3) {
		gfx_ScaledTransparentSprite_NoClip(steel_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_boots_down,50,55,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_sword,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 4) {
		gfx_ScaledTransparentSprite_NoClip(dragon_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_boots_down,50,55,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_sword,editweaponsmallx,editweaponsmally,2,2);
	}
}
void menubkgnd(void) {
	/*
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_SwapDraw();
	*/
}
void resetenemies(void) {
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy[i].type = defaultenemy_typelist[i];
		enemy[i].dead = 0;
		enemy[i].x = defaultenemy_xlist[i]*32;
		enemy[i].y = defaultenemy_ylist[i]*32;
		enemy[i].move = defaultenemy_movelist[i];
		enemy[i].health = ((enemy[i].type + 1) * 10);
	}
}
void updateenemies(void) {
	int randcheck = 20;
	for (ii = 0; ii < NUM_ENEMIES; ii++) {
		if ((enemy[ii].type) == 0) {enemySprite = slime_blue;}
		if ((enemy[ii].type) == 1) {enemySprite = slime_green;}
		if ((enemy[ii].type) == 2) {enemySprite = slime_red;}
		if ((enemy[ii].type) == 3) {enemySprite = bokoblin_light;}
		if ((enemy[ii].type) == 4) {enemySprite = bokoblin_dark;}
		if ((enemy[ii].type) == 5) {enemySprite = knight_green;}
		if ((enemy[ii].type) == 6) {enemySprite = knight_red;}
		
		//if within current screen view
		if (enemy[ii].health <= 0) {enemy[ii].dead = 1;}
		if ((enemy[ii].dead) == 0) {
			if (x_offset <= (enemy[ii].x)){
				if ((enemy[ii].x) <= (x_offset + 288)){
					if (y_offset <= (enemy[ii].y)) {
						if  ((enemy[ii].y) <= (y_offset + 192)) {
							if (enemy[ii].move == 1) {
								if (randcheck >= randInt(0,100)) {
									enemymove();
								}
							}
							renderenemy(&enemy[ii]);
						}
					}
				}
			}		
		}
	}
}
void renderenemy(enemy_t *enemy) {
		gfx_TransparentSprite(enemySprite, enemy->x - x_offset, enemy->y - y_offset); 
		gfx_SetTextFGColor(0xA8);
		if (drawhealth == 1) {
		gfx_SetTextXY(enemy->x - x_offset,enemy->y - y_offset);
		gfx_PrintUInt(enemy->health,2);
		}
		/*only for debug
		gfx_PrintString("---");
		gfx_PrintUInt((enemy->x)/32,3);
		gfx_PrintString("-");
		gfx_PrintUInt((enemy->y)/32,3);
		*/
		enemyattack();
	}
void drawstatsmenu(void) {
extern int dmgmultiplier;
extern int blockchance;
extern int playerdamage;
extern int walkspeed;

	gfx_SetDrawBuffer();
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(140,140,150,80);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(140,140,150,80);
	gfx_Rectangle(142,142,146,76);
	submenubottombar();
	gfx_PrintStringXY("Player Damage:  ",150,145);
	gfx_PrintInt(playerdamage,2);
	gfx_PrintStringXY("Damage Mult. :  ",150,160);
	gfx_PrintInt(dmgmultiplier,2);
	gfx_PrintStringXY("Block % Chance:  ",150,175);
	gfx_PrintInt(blockchance,2);
	gfx_PrintString("%");
	gfx_PrintStringXY("Walk Speed:  ",150,190);
	gfx_PrintInt(walkspeed,2);
	gfx_PrintStringXY("Health:  ",150,205);
	gfx_PrintInt(player_setup[6],sizeof(player_setup[6]));
	gfx_SwapDraw();
	do {
	} while (!(kb_Data[1] & kb_Window));
}
