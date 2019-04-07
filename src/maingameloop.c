#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "collisiondetection.h"
#include "gfx/dungeon_gfx.h"
#include "gfx/tiles_gfx.h"

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
int dumb = 0;

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

	gfx_SetDrawBuffer();
	gfx_SetPalette(tiles_gfx_pal, sizeof_tiles_gfx_pal, 0);
	gfx_Tilemap(&tilemap, x_offset, y_offset);
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("x", 8, 224);
	gfx_PrintUInt(x_offset, 4);
	gfx_PrintString("  y");
	gfx_PrintUInt(y_offset, 4);
}

void mapshifter(void) {
	if (kb_Data[7] & kb_Left) {
		collisionleft();
		if (goleft == 1) {
			(playerface = 1);
			if (x_offset  == 0) {
				(x_offset = 0);
			}
			else {
				(x_offset = (x_offset - mapshift));
			}
		}
	}
	if (kb_Data[7] & kb_Right) {
		collisionright();
		if (goright == 1){
			(playerface = 3);
			(x_offset = (x_offset + mapshift));
			if (x_offset > 4480) { 
				(x_offset = (x_offset - mapshift));
			}

		}
	}
	if (kb_Data[7] & kb_Up) {
			collisionup();
			if (goup == 1){
				(playerface = 2);
			(y_offset = (y_offset - mapshift));
			if (y_offset > 3105) {
				(y_offset = 0);
			}
		}
	}
	if (kb_Data[7] & kb_Down) {
			collisiondown();
			if (godown == 1){
				(playerface = 4);
			(y_offset = (y_offset + mapshift));
			if (y_offset > 3104) {
				(y_offset =(y_offset - mapshift));
			}
		}
	}
}

void drawcharacter(void) {
	if (playerface == 1) {
		gfx_TransparentSprite(player_naked_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(player_naked_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(player_naked_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(player_naked_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}

drawhelmet();
drawchestplate();
drawboot();
gfx_SwapDraw();
}



void drawhelmet(void) {
	if (player_setup[0] = 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_helmet_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_helmet_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_helmet_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_helmet_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 2){
		if (playerface == 1) {
		gfx_TransparentSprite(chain_helmet_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_helmet_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_helmet_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_helmet_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 3){
		if (playerface == 1) {
		gfx_TransparentSprite(steel_helmet_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_helmet_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_helmet_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_helmet_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 4){
		gfx_TransparentSprite(dragon_helmet_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_helmet_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_helmet_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_helmet_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
void drawchestplate(void) {
	if (player_setup[0] = 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_chestplate_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_chestplate_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_chestplate_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_chestplate_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 2){
	if (playerface == 1) {
		gfx_TransparentSprite(chain_chestplate_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_chestplate_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_chestplate_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_chestplate_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 3){
	if (playerface == 1) {
		gfx_TransparentSprite(steel_chestplate_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_chestplate_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_chestplate_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_chestplate_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 4){
	if (playerface == 1) {
		gfx_TransparentSprite(dragon_chestplate_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_chestplate_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_chestplate_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_chestplate_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
}
void drawboot(void) {
		if (player_setup[0] = 1){
	if (playerface == 1) {
		gfx_TransparentSprite(leather_boots_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(leather_boots_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(leather_boots_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(leather_boots_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 2){
		if (playerface == 1) {
		gfx_TransparentSprite(chain_boots_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(chain_boots_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(chain_boots_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(chain_boots_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 3){
		if (playerface == 1) {
		gfx_TransparentSprite(steel_boots_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(steel_boots_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(steel_boots_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(steel_boots_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
	else if (player_setup[0] = 4){
	if (playerface == 1) {
		gfx_TransparentSprite(dragon_boots_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 2) {
		gfx_TransparentSprite(dragon_boots_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 3) {
		gfx_TransparentSprite(dragon_boots_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface == 4) {
		gfx_TransparentSprite(dragon_boots_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	}
}

void drawplayerattack(void){}
void drawenemies(void){}
