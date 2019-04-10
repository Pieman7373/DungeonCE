#include "menuandeditfunctions.h"
#include "gfx/dungeon.h"
#include "gfx/dungeon_gfx.h"

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

#define NUM_ENEMIES  2
#define TYPE         
#define DEAD         
#define X			 
#define Y            
#define HEALTH		 

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
uint8_t enemyhealth;

int i;
extern signed int setnumber;
extern uint8_t player_setup[];
uint16_t defaultenemy_typelist[NUM_ENEMIES] = {0,1};
uint16_t defaultenemy_xlist[NUM_ENEMIES] = {192,224};
uint16_t defaultenemy_ylist[NUM_ENEMIES] = {160,192};

extern int mapstartx;
extern int mapstarty;

typedef struct enemy {
	uint8_t type;
	int dead;
	uint24_t x; 
	uint24_t y; 
	uint8_t health;
	} enemy_t;

gfx_sprite_t *enemySprite;

enemy_t  enemy[NUM_ENEMIES];

void keywait(void) { while (os_GetCSC()); }

void mainmenu(void) {
	
		//type, dead, enemyx,enemyy,health
	enemy[NUM_ENEMIES].type   = enemytype;
	enemy[NUM_ENEMIES].dead   = deadset;
	enemy[NUM_ENEMIES].x      = enemyx;
	enemy[NUM_ENEMIES].y      = enemyy;
	enemy[NUM_ENEMIES].health = enemyhealth;
	
	resetenemies();
	
	menubkgnd();
    gfx_ScaledTransparentSprite_NoClip(mainmenulogo,33,20,2,2);
    gfx_TransparentSprite(menuwords,100,130);
   
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
       
    } while (!((kb_Data[3] & kb_1)||(kb_Data[4] & kb_2)||(kb_Data[5] & kb_3)||(kb_Data[6] & kb_Clear)));
    return;
}
void options(void) {
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(40,60,215,100);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(40,60,215,100);
	gfx_Rectangle(42,62,211,96);
	gfx_TransparentSprite(optionsmenu,45,65);
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
	gfx_TransparentSprite(savemenu, 4, 158);
	gfx_SwapDraw();
	do {
		if (kb_Data[3] & kb_1) {savegame();}
	} while (!(kb_Data[4] & kb_2));
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
	mapstartx = 70;
	mapstarty = 96;
	//Initiate Enemies

	resetenemies();
}

void playercreate(void) {
	menubkgnd();
	gfx_HorizLine(0,223,320);
	gfx_HorizLine(0,221,320);
	gfx_SetTextTransparentColor(transcolor);
	gfx_SetTextFGColor(textcolor);
    gfx_SetTextBGColor(transcolor);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("f(1-5) = change set, # = select item, del = back",8,227);
	gfx_TransparentSprite(editmenunumbers,40,20);
	do {
		drawequipment();
		draweditedplayer();
		do {
				if (kb_Data[1] & kb_Yequ) {(setnumber = 0);}
				else if (kb_Data[1] & kb_Window) {(setnumber = 1);}
				else if (kb_Data[1] & kb_Zoom) {(setnumber = 2);}
				else if (kb_Data[1] & kb_Trace) {(setnumber = 3);}
				else if (kb_Data[1] & kb_Graph) {(setnumber = 4);}
			
				if (kb_Data[3] & kb_1){
					(player_setup[0] = setnumber);
				}
				else if (kb_Data[4] & kb_2) {
					(player_setup[1] = setnumber);
				}
				else if (kb_Data[5] & kb_3) {
					(player_setup[2] = setnumber);
				}
				else if (kb_Data[3] & kb_4) {
					(player_setup[3] = setnumber);
				}		
		}	while (!os_GetCSC());
		
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
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
}


void resetenemies(void) {
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy[i].type = defaultenemy_typelist[i];
		enemy[i].x = defaultenemy_xlist[i];
		enemy[i].y = defaultenemy_ylist[i];
		if ((enemy[i].type) == 0) {enemy[i].health = 10;}
		if ((enemy[i].type) == 1) {enemy[i].health = 20;}
	}
}

void updateenemies(void) {
	for (i = 0; i < NUM_ENEMIES; i++) {
		if ((enemy[i].type) == 0) {enemySprite = slime_blue;}
		else if ((enemy[i].type) == 1) {enemySprite = slime_green;}
		
		if ((enemy->dead) == 0) {
		renderenemy(&enemy[i]);
		}
	}
}
void renderenemy(enemy_t *enemy) {
		gfx_TransparentSprite(enemySprite, enemy->x + (x_offset/x_offset), enemy->y + (y_offset/y_offset)); 
		gfx_SetTextFGColor(0xA8);
		gfx_SetTextXY(enemy->x + (x_offset/x_offset),enemy->y + (y_offset/y_offset));
		gfx_PrintUInt(enemy->health,2);
	}

