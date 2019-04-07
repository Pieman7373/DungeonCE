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
extern int goup;
extern int godown;
extern int goleft;
extern int goright;
extern gfx_tilemap_t tilemap;



void collisionleft(void) {
	if ((gfx_GetTile(&tilemap,playertilex-32,playertiley)) >= 18) {
	goleft = 0;
	}
	else {(goleft = 1);}
}
void collisionright(void) {
	if ((gfx_GetTile(&tilemap,playertilex+32,playertiley)) >= 18) {
	goright = 0;
	}
	else {(goright = 1);}
}
void collisionup(void) {
	if ((gfx_GetTile(&tilemap,playertilex,playertiley-32)) >= 18) {
	goup = 0;
	}
	else {(goup = 1);}
}
void collisiondown(void) {
	if ((gfx_GetTile(&tilemap,playertilex,playertiley+32)) >= 18) {
	godown = 0;
	}
	else {(godown = 1);}
}



