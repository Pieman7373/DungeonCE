#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "collisiondetection.h"
#include "gfx/dungeon_gfx.h"
#include "gfx/tiles_gfx.h"
#include "gfx/dungeon.h"

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

int goleft;
int goright;
int goup;
int godown;
int spritexoffset = 160;
int spriteyoffset = 128;
//1=left,2=up,3=right,4=down
int playerface = 2;
int playerx;
int playery;
int playertilex;
int playertiley;
gfx_sprite_t *weapon;
gfx_sprite_t *weaponrotated;
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
extern uint8_t player_setup [];

extern gfx_tilemap_t tilemap;
extern gfx_tilemap_t enemytilemap;

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
		drawplayerattack();
		mapshifter();
	if (kb_Data[1] & kb_Yequ) {
		drawsavemenu();
		}
	
	} while (!((kb_Data[6] & kb_Clear)||(kb_Data[1] & kb_Window)));
}


void setmapshift(void) {
	if (player_setup[2] == 0) {(mapshift = 1);}
	if (player_setup[2] == 1) {(mapshift = 8);}
	if (player_setup[2] == 2) {(mapshift = 16);}
	if (player_setup[2] == 3) {(mapshift = 24);}
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
	gfx_TransparentTilemap(&enemytilemap, x_offset, y_offset);
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetTextFGColor(textcolor);
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
	gfx_PrintStringXY("SAVE",8,226);
}
void mapshifter(void) {
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
	if (player_setup[0] == 1){
	if (playerface == 1) {helmet = leather_helmet_left;}
	else if (playerface == 2) {helmet = leather_chestplate_up;}
	else if (playerface == 3) {helmet = leather_helmet_right;}
	else if (playerface == 4) {helmet = leather_helmet_down;}
	}
	else if (player_setup[0] == 2){
		if (playerface == 1) {helmet = chain_helmet_left;}
	else if (playerface == 2) {helmet = chain_helmet_up;}
	else if (playerface == 3) {helmet = chain_helmet_right;}
	else if (playerface == 4) {helmet = chain_helmet_down;}
	}
	else if (player_setup[0] == 3){
		if (playerface == 1) {helmet = steel_helmet_left;}
	else if (playerface == 2) {helmet = steel_helmet_up;}
	else if (playerface == 3) {helmet = steel_helmet_right;}
	else if (playerface == 4) {helmet = steel_helmet_down;}
	}
	else if (player_setup[0] == 4){
		if (playerface == 1) {helmet = dragon_helmet_left;}
	else if (playerface == 2) {helmet = dragon_helmet_up;}
	else if (playerface == 3) {helmet = dragon_helmet_right;}
	else if (playerface == 4) {helmet = dragon_helmet_down;}
	}
	gfx_TransparentSprite(helmet,playerx,playery);
}
void drawchestplate(void) {
	if (player_setup[1] == 1){
	if (playerface == 1) {chestplate = leather_chestplate_left;}
	else if (playerface == 2) {chestplate = leather_chestplate_up;}
	else if (playerface == 3) {chestplate = leather_chestplate_right;}
	else if (playerface == 4) {chestplate = leather_chestplate_down;}
	}
	else if (player_setup[1] == 2){
	if (playerface == 1) {chestplate = chain_chestplate_left;}
	else if (playerface == 2) {chestplate = chain_chestplate_up;}
	else if (playerface == 3) {chestplate = chain_chestplate_right;}
	else if (playerface == 4) {chestplate = chain_chestplate_down;}
	}
	else if (player_setup[1] == 3){
	if (playerface == 1) {chestplate = steel_chestplate_left;}
	else if (playerface == 2) {chestplate = steel_chestplate_up;}
	else if (playerface == 3) {chestplate = steel_chestplate_right;}
	else if (playerface == 4) {chestplate = steel_chestplate_down;}
	}
	else if (player_setup[1] == 4){
	if (playerface == 1) {chestplate = dragon_chestplate_left;}
	else if (playerface == 2) {chestplate = dragon_chestplate_up;}
	else if (playerface == 3) {chestplate = dragon_chestplate_right;}
	else if (playerface == 4) {chestplate = dragon_chestplate_down;}
	}
	gfx_TransparentSprite(chestplate,playerx,playery);
}
void drawboot(void) {
	if (player_setup[2] == 1){
	if (playerface == 1) {boots = leather_boots_left;}
	else if (playerface == 2) {boots = leather_boots_up;}
	else if (playerface == 3) {boots = leather_boots_right;}
	else if (playerface == 4) {boots = leather_boots_down;}
	}
	else if (player_setup[2] == 2){
		if (playerface == 1) {boots = chain_boots_left;}
	else if (playerface == 2) {boots = chain_boots_up;}
	else if (playerface == 3) {boots = chain_boots_right;}
	else if (playerface == 4) {boots = chain_boots_down;}
	}
	else if (player_setup[2] == 3){
		if (playerface == 1) {boots = steel_boots_left;}
	else if (playerface == 2) {boots = steel_boots_up;}
	else if (playerface == 3) {boots = steel_boots_right;}
	else if (playerface == 4) {boots = steel_boots_down;}
	}
	else if (player_setup[2] == 4){
	if (playerface == 1) {boots = dragon_boots_left;}
	else if (playerface == 2) {boots = dragon_boots_up;}
	else if (playerface == 3) {boots = dragon_boots_right;}
	else if (playerface == 4) {boots = dragon_boots_down;}
	}
	gfx_TransparentSprite(boots,playerx,playery);
}

void drawplayerattack(void){
	gfx_UninitedSprite(weaponrotated, 32, 32);
	if (kb_Data[1] & kb_2nd){
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

void updateenemies(void){}
