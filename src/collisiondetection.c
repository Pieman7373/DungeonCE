#include "menuandeditfunctions.h"
#include "maingameloop.h"
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

#include "gfx/Dungeon.h"

extern int playertilex;
extern int playertiley;
extern int playerface;
extern int goup;
extern int godown;
extern int goleft;
extern int goright;
extern gfx_tilemap_t tilemap;
extern gfx_tilemap_t enemytilemap;
int replacex;
int replacey;
int hit;



void collisionleft(void) {
	if (((gfx_GetTile(&tilemap,playertilex-32,playertiley)) >= 18)||((gfx_GetTile(&enemytilemap,playertilex-32,playertiley)) >= 36)) {
	goleft = 0;
	}
	else {(goleft = 1);}
}
void collisionright(void) {
	if (((gfx_GetTile(&tilemap,playertilex+32,playertiley)) >= 18)||((gfx_GetTile(&enemytilemap,playertilex+32,playertiley)) >= 36)) {
	goright = 0;
	}
	else {(goright = 1);}
}
void collisionup(void) {
	if (((gfx_GetTile(&tilemap,playertilex,playertiley-32)) >= 18)||((gfx_GetTile(&enemytilemap,playertilex,playertiley-32)) >= 36)) {
	goup = 0;
	}
	else {(goup = 1);}
}
void collisiondown(void) {
	if (((gfx_GetTile(&tilemap,playertilex,playertiley+32)) >= 18)||((gfx_GetTile(&enemytilemap,playertilex,playertiley+32)) >= 36)) {
	godown = 0;
	}
	else {(godown = 1);}
}


void playerattackhitcheck(void) {
///*
	hit = 0;
	if (playerface == 1){
		if ((gfx_GetTile(&enemytilemap,playertilex-32,playertiley)) >= 36) {
			hit = 1;
			replacex = playertilex-32;
			replacey = playertiley;
		}
	}
	if (playerface == 2){
		if ((gfx_GetTile(&enemytilemap,playertilex,playertiley-32)) >= 36) {
			hit = 1;
			replacex = playertilex;
			replacey = playertiley-32;
		}
	}
	if (playerface == 3){
		if ((gfx_GetTile(&enemytilemap,playertilex+32,playertiley)) >= 36) {
			hit = 1;
			replacex = playertilex+32;
			replacey = playertiley;
		}
	}
	if (playerface == 4){
		if ((gfx_GetTile(&enemytilemap,playertilex,playertiley+32)) >= 36) {
			hit = 1;
			replacex = playertilex;
			replacey = playertiley+32;
		}
	}
	if (hit == 1) {
		gfx_SetTile(&enemytilemap,replacex,replacey,8);
		}
//*/
}
