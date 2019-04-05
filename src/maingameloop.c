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


extern uint8_t tilemap_map[];
extern unsigned int x_offset;
extern unsigned int y_offset;

gfx_tilemap_t tilemap;


void maingameloop(void){
		
/* main with my way
	do{
		if (previousmapindex != currentmapindex) {
			(mappointer = currentmapindex);
			drawmap();
		}
		
		drawenemies();
		
		if ((previouscharx != currentcharx) || (previouschary != currentchary)){
			drawcharacter();
		}
		
	} while (!(kb_Data[6] & kb_Clear));
}
*/
drawmap();
	do{
	
	} while (!((kb_Data[6] & kb_Clear)||(kb_Data[1] & kb_Del)));
	return;
}


void drawmap(void) {
	
	gfx_SetDrawBuffer();
	gfx_SetPalette(tiles_gfx_pal, sizeof_tiles_gfx_pal, 0);
	gfx_SetColor(0x00);
	gfx_Tilemap(&tilemap, x_offset, y_offset);
	//gfx_PrintStringXY("x offset:", 8, 277);
	//gfx_PrintUInt(x_offset, 4);
	//gfx_PrintString(" y offset:");
	//gfx_PrintUInt(y_offset, 4);
	
	gfx_SwapDraw();
}

void drawcharacter(void) {}


void drawenemies(void) {}
