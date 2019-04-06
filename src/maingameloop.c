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
int playerface;

extern int menuyes;
extern int textcolor;
extern uint8_t tilemap_map[];
extern unsigned int x_offset;
extern unsigned int y_offset;
extern int mapshift;
extern uint8_t player_setup [8];

extern gfx_tilemap_t tilemap;

void maingameloop(void){

	do{
		(goleft = 0);
		(goright = 0);
		(goup = 0);
		(godown = 0);
		
		setmapshift();
		
		drawmap();
		drawcharacter();
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
	gfx_PrintStringXY("x offset:", 8, 224);
	gfx_PrintUInt(x_offset, 4);
	gfx_PrintString("  y offset:");
	gfx_PrintUInt(y_offset, 4);
	gfx_PrintString("  pface");
	gfx_PrintInt(playerface,1);
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
			if (x_offset > 2880) { 
				(x_offset = 2880);
			}
		}
	}
	if (kb_Data[7] & kb_Up) {
			collisionup();
			if (goup == 1){
				(playerface = 2);
			(y_offset = (y_offset - mapshift));
			if (y_offset > 2016) {
				(y_offset = 0);
			}
		}
	}
	if (kb_Data[7] & kb_Down) {
			collisiondown();
			if (godown == 1){
				(playerface = 4);
			(y_offset = (y_offset + mapshift));
			if (y_offset > 2016) {
				(y_offset = 2016);
			}
		}
	}
	keywait();
}

void drawcharacter(void) {
	if (playerface = 1) {
		gfx_TransparentSprite(player_naked_left,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface = 2) {
		gfx_TransparentSprite(player_naked_up,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface = 3) {
		gfx_TransparentSprite(player_naked_right,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}
	else if (playerface = 4) {
		gfx_TransparentSprite(player_naked_down,(x_offset/x_offset)+spritexoffset,(y_offset/y_offset) + spriteyoffset);
	}

drawhelmet();
drawchestplate();
drawboot();
gfx_SwapDraw();
}



void drawhelmet(void) {}
void drawchestplate(void) {}
void drawboot(void) {}


void drawenemies(void) {}
