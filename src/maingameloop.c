#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "xcollisiondetection.h"
#include "gfx/tiles_gfx.h"
#include "gfx/dungeon.h"
#include "gfx/dungeon2.h"
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
int playerface = 2;
int playerx;
int playery;
int playertilex;
int playertiley;
gfx_sprite_t *weapon;
gfx_sprite_t *weaponrotated;
gfx_sprite_t *flippedequip;
gfx_sprite_t *player_health;
gfx_sprite_t *helmet;
gfx_sprite_t *chestplate;
gfx_sprite_t *boots;   
	
extern int menuyes;
extern int textcolor;
extern uint8_t tilemap_map[];
extern uint8_t tilemap_enemies[];
extern unsigned int x_offset;
extern unsigned int y_offset;
extern int mapstartx;
extern int mapstarty;
extern int mapshift;
int playertilemapx;
int playertilemapy;
int *inputx;
int *inputy;
extern uint24_t player_setup[];
int dmgmultiplier = 1;
int blockchance;
int walkwait = 1500;
int w;
int walkspeed = 100;
extern int menuoption;

extern gfx_tilemap_t tilemap;
pots_t pots[NUM_POTS];
money_t money[NUM_POTS];

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
				maingameloop();
			}
		}
		if (menuyes == 1) {
			if (menuoption == 3) {
				options();
			}
		}
		//menuyes chunk end
	} while (!(kb_Data[6] & kb_Clear));
	gfx_End();
	exit(0);
	
}	
void maingameloop(void){
	
x_offset = mapstartx * 32;
y_offset = mapstarty * 32;
	do{
			
		(goleft = 0);
		(goright = 0);
		(goup = 0);
		(godown = 0);
		
		setmapshift();
	
		drawmap();
		drawcharacter();
		updateenemies();
		updatepots();
		updatemoney();
		checkplayerstatus();
		drawbottombar();
		drawplayerattack();
		mapshifter();
	if (kb_Data[1] & kb_Yequ) {
		drawsavemenu();
	}
	if (kb_Data[1] & kb_Zoom) {
		drawstatsmenu();
	}
	
	} while (!((kb_Data[1] & kb_Graph)||(kb_Data[6] & kb_Clear)));
	menuloop();
}
void setmapshift(void) {
	if (player_setup[2] == 0) {(mapshift = 32);}
	if (player_setup[2] == 1) {(mapshift = 32);}
	if (player_setup[2] == 2) {(mapshift = 32);}
	if (player_setup[2] == 3) {(mapshift = 32);}
	if (player_setup[2] == 4) {(mapshift = 32);}
}	
void drawmap(void) {
	playerx = ((x_offset/x_offset)+spritexoffset);
	playery = ((y_offset/y_offset)+spriteyoffset);
	playertilex = (x_offset + (32*5));
	playertiley = (y_offset + (32*4));
	gfx_SetDrawBuffer();
	gfx_SetPalette(tiles_gfx_pal, sizeof_tiles_gfx_pal, 0);
	gfx_Tilemap(&tilemap, x_offset, y_offset);
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	
	
	//gfx_SetTextXY(48,226);
	//gfx_PrintUInt(x_offset,4);
	//gfx_PrintString("----");
	//gfx_PrintUInt(y_offset,4);
/*print debug numbers for collision and stuff
	gfx_PrintStringXY("tile", 8, 224);
	gfx_PrintUInt((gfx_GetTile(&tilemap,playertilex,playertiley)),2);
	gfx_PrintString("  tile L");
	gfx_PrintUInt((gfx_GetTile(&tilemap,playertilex-32,playertiley)),2);
	gfx_PrintString("  tile U");
	gfx_PrintUInt((gfx_GetTile(&tilemap,playertilex,playertiley-32)),2);
	gfx_PrintString("  tile R");
	gfx_PrintUInt((gfx_GetTile(&tilemap,playertilex+32,playertiley)),2);
	gfx_PrintString("  tile D");
	gfx_PrintUInt((gfx_GetTile(&tilemap,playertilex,playertiley+32)),2);
*/
}
void mapshifter(void) {
	playertilemapx = (playertilex/32);
	playertilemapy = (playertiley/32);
	inputx = &playertilemapx;
	inputy = &playertilemapy;
	player = 1;
	
	for(w=0; w < (walkwait - (walkspeed*10)); w++) {}
	
	if (kb_Data[7] & kb_Left) {
		(playerface = 1);
		collisionleft();
		if (goleft == 1) {
			(x_offset = (x_offset - mapshift));
		}
	}
	if (kb_Data[7] & kb_Right) {
		(playerface = 3);
		collisionright();
		if (goright == 1){
			(x_offset = (x_offset + mapshift));
		}
	}
	if (kb_Data[7] & kb_Up) {
		(playerface = 2);
			collisionup();
			if (goup == 1){
			(y_offset = (y_offset - mapshift));
		}
	}
	if (kb_Data[7] & kb_Down) {
			(playerface = 4);
			collisiondown();
			if (godown == 1){
			(y_offset = (y_offset + mapshift));
		}
	}
}
void drawcharacter(void) {
	if (playerface == 1) {
		gfx_TransparentSprite(player_naked_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(player_naked_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(player_naked_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(player_naked_down,playerx,playery);
	}
drawhelmet();
drawchestplate();
drawboot();
}
void drawhelmet(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	if (player_setup[0] == 0){
	if (playerface == 1) {helmet = player_naked_left;}
	else if (playerface == 2) {helmet = player_naked_up;}
	else if (playerface == 3) {helmet = player_naked_right;}
	else if (playerface == 4) {helmet = player_naked_down;}
	}
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
	gfx_TransparentSprite(helmet,playerx,playery);
}
void drawchestplate(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	if (player_setup[1] == 0){
	if (playerface == 1) {chestplate = player_naked_left;}
	else if (playerface == 2) {chestplate = player_naked_up;}
	else if (playerface == 3) {chestplate = player_naked_right;}
	else if (playerface == 4) {chestplate = player_naked_down;}
	}
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
	gfx_TransparentSprite(chestplate,playerx,playery);
}
void drawboot(void) {
	gfx_UninitedSprite(flippedequip, 32,32);
	if (player_setup[2] == 0){
	if (playerface == 1) {boots = player_naked_left;}
	else if (playerface == 2) {boots = player_naked_up;}
	else if (playerface == 3) {boots = player_naked_right;}
	else if (playerface == 4) {boots = player_naked_down;}
	}
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
	gfx_TransparentSprite(boots,playerx,playery);
}
void drawplayerattack(void){
	
	gfx_UninitedSprite(weaponrotated, 32, 32);
	if (kb_Data[1] & kb_2nd){
		if (player_setup[3] == 0) {weapon = fist;}
		if (player_setup[3] == 1) {weapon = club;}
		if (player_setup[3] == 2) {weapon = iron_sword;}
		if (player_setup[3] == 3) {weapon = steel_sword;}
		if (player_setup[3] == 4) {weapon = dragon_sword;}
		
		if (playerface == 1) {
			gfx_TransparentSprite(gfx_RotateSpriteCC(weapon,weaponrotated),playerx-32,playery);
		}
		if (playerface == 2) {
			gfx_TransparentSprite(weapon,playerx,playery-32);
		}
		if (playerface == 3) {
			gfx_TransparentSprite(gfx_RotateSpriteC(weapon,weaponrotated),playerx+32,playery);
		}
		if (playerface == 4) {
			gfx_TransparentSprite(gfx_RotateSpriteHalf(weapon,weaponrotated),playerx,playery+32);
		}
		playerattackhitcheck();
	}
	gfx_SwapDraw();
}
void checkplayerstatus(void){
	extern int playerdamage;
	//checks if you are standing on a spike
	if ((gfx_GetTile(&tilemap,playertilex,playertiley)) == 9){
		(player_setup[6] = player_setup[6] - 5);
		gfx_FillScreen(0xE0);
	}
	if (player_setup[6] > 100) {player_setup[6] = 100;}
	
	if ((100 >= player_setup[6]) & (player_setup[6] > 90)){player_health = health100;}
	else if ((90 >= player_setup[6]) & (player_setup[6] > 80)){player_health = health90;}
	else if ((80 >= player_setup[6]) & (player_setup[6] > 70)){player_health = health80;}
	else if ((70 >= player_setup[6]) & (player_setup[6] > 60)){player_health = health70;}
	else if ((60 >= player_setup[6]) & (player_setup[6] > 50)){player_health = health60;}
	else if ((50 >= player_setup[6]) & (player_setup[6] > 40)){player_health = health50;}
	else if ((40 >= player_setup[6]) & (player_setup[6] > 30)){player_health = health40;}
	else if ((30 >= player_setup[6]) & (player_setup[6] > 20)){player_health = health30;}
	else if ((20 >= player_setup[6]) & (player_setup[6] > 10)){player_health = health20;}
	else if ((10 >= player_setup[6]) & (player_setup[6] > 0)){player_health = health10;}
	if (player_setup[6] <= 0) {youdied();}
	
	//determined by weapon
	playerdamage = player_setup[3]+1;
	//helmet and chestplate added together
	blockchance = ((player_setup[0] + player_setup[1]) * 10);
	//set by boots
	walkspeed = ((player_setup[2]+1)*20);
}
void drawbottombar(void){
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_TransparentSprite(player_health,80,224);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("[SAVE]   HP:",8,228);
	gfx_SetTextXY(150,228);
	gfx_PrintString("[STATS]");
	gfx_SetTextXY(250,228);
	gfx_PrintInt(player_setup[7],5);
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
	gfx_PrintStringXY("You died!",120,200);
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
gfx_TransparentSprite(pot,(pots->p_x - x_offset), (pots->p_y - y_offset));

/*only for testing
gfx_SetTextFGColor(0xA8);
gfx_SetTextXY(pots->p_x - x_offset,pots->p_y - y_offset);
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
	gfx_TransparentSprite(moneySprite, money->m_x - x_offset, money->m_y - y_offset);
	
	gfx_SetTextFGColor(0xA8);
	gfx_SetTextXY(money->m_x - x_offset,money->m_y - y_offset);
	gfx_PrintUInt(money->moneyvalue,3);
}