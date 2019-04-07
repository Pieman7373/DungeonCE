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


extern int menuyes;
extern int textcolor;
extern uint8_t tilemap_map[];
extern unsigned int x_offset;
extern unsigned int y_offset;
extern int mapstartx;
extern int mapstarty;
extern int mapshift;
extern uint8_t player_setup [];

extern gfx_tilemap_t tilemap;

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
	
	} while (!((kb_Data[6] & kb_Clear)||(kb_Data[1] & kb_Yequ)));
	menuyes = 3;
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
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetTextFGColor(textcolor);
	//gfx_PrintStringXY("x", 8, 224);
	//gfx_PrintUInt(x_offset, 4);
	//gfx_PrintString("  y");
	//gfx_PrintUInt(y_offset, 4);
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
	keywait();
	keywait();
	keywait();
	keywait();
	keywait();
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
gfx_SwapDraw();
}
void drawhelmet(void) {
	if (player_setup[0] == 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_helmet_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_helmet_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_helmet_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_helmet_down,playerx,playery);
	}
	}
	else if (player_setup[0] == 2){
		if (playerface == 1) {
		gfx_TransparentSprite(chain_helmet_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_helmet_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_helmet_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_helmet_down,playerx,playery);
	}
	}
	else if (player_setup[0] == 3){
		if (playerface == 1) {
		gfx_TransparentSprite(steel_helmet_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_helmet_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_helmet_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_helmet_down,playerx,playery);
	}
	}
	else if (player_setup[0] == 4){
		if (playerface == 1) {
		gfx_TransparentSprite(dragon_helmet_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_helmet_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_helmet_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_helmet_down,playerx,playery);
	}
	}
}
void drawchestplate(void) {
	if (player_setup[1] == 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_chestplate_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_chestplate_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_chestplate_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_chestplate_down,playerx,playery);
	}
	}
	else if (player_setup[1] == 2){
	if (playerface == 1) {
		gfx_TransparentSprite(chain_chestplate_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_chestplate_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_chestplate_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_chestplate_down,playerx,playery);
	}
	}
	else if (player_setup[1] == 3){
	if (playerface == 1) {
		gfx_TransparentSprite(steel_chestplate_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_chestplate_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_chestplate_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_chestplate_down,playerx,playery);
	}
	}
	else if (player_setup[1] == 4){
	if (playerface == 1) {
		gfx_TransparentSprite(dragon_chestplate_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_chestplate_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_chestplate_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_chestplate_down,playerx,playery);
	}
	}
}
void drawboot(void) {
	if (player_setup[2] == 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_boots_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_boots_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_boots_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_boots_down,playerx,playery);
	}
	}
	else if (player_setup[2] == 2){
		if (playerface == 1) {
		gfx_TransparentSprite(chain_boots_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_boots_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_boots_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_boots_down,playerx,playery);
	}
	}
	else if (player_setup[2] == 3){
		if (playerface == 1) {
		gfx_TransparentSprite(steel_boots_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_boots_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_boots_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_boots_down,playerx,playery);
	}
	}
	else if (player_setup[2] == 4){
	if (playerface == 1) {
		gfx_TransparentSprite(dragon_boots_left,playerx,playery);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_boots_up,playerx,playery);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_boots_right,playerx,playery);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_boots_down,playerx,playery);
	}
	}
}

void drawplayerattack(void){}
void drawenemies(void){}
