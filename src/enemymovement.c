#include "menuandeditfunctions.h"
#include "xcollisiondetection.h"
#include "maingameloop.h"
#include "gfx/dungeon.h"
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
extern enemy_t enemy[];
extern uint8_t enemytype;
extern int deadset;
extern uint24_t enemyx;
extern uint24_t enemyy;
extern int enemyhealth;
extern int *inputx;
extern int *inputy;
extern int ii;

void enemymove (void) {
	
	extern unsigned int x_offset;
	extern unsigned int y_offset;
	int enemystartx;
	int enemystarty;
	extern int goup;
	extern int goleft;
	extern int goright;
	extern int godown;
	int randcheck = 1;
	enemystartx = (enemy[ii].x/32);
	enemystarty = (enemy[ii].y/32);
	inputx = &enemystartx;
	inputy = &enemystarty;
	
	collisionleft();
	collisionright();
	collisionup();
	collisiondown();
	
	if (goleft == 1) {
		if (randcheck == randInt(0,10)){
			enemy[ii].x = (enemy[ii].x - 32);
		}
	}
	if (goup == 1) {
		if (randcheck == randInt(0,10)){
			enemy[ii].y = (enemy[ii].y - 32);
		}
	}
	if (goright == 1) {
		if (randcheck == randInt(0,10)){
			enemy[ii].x = (enemy[ii].x + 32);
		}
	}
	if (godown == 1) {
		if (randcheck == randInt(0,10)){
			enemy[ii].y = (enemy[ii].y + 32);
		}
	}
	/* only for debug
	gfx_PrintStringXY("-",enemy[ii].x - x_offset,(enemy[ii].y+15) - y_offset);
	gfx_PrintUInt(goleft,1);
	gfx_PrintString("-");
	gfx_PrintUInt(goup,1);
	gfx_PrintString("-");
	gfx_PrintUInt(goright,1);
	gfx_PrintString("-");
	gfx_PrintUInt(godown,1);
	*/
	
	
	
	//check if it is onscreen
	//do collision testing
	//add or subtract 32 to the x or y coordinate 
}