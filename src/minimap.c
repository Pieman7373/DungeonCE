#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "xcollisiondetection.h"
#include "gfx/tiles_gfx.h"
#include "gfx/dungeon.h"
//#include "gfx/dungeon2.h"
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

extern gfx_tilemap_t tilemap;
extern int playertilex;
extern int playertiley;

void minimap(void){

	int minimapx;
	int minimapy;
	int i;
	/*
	playertilex - (whatever makes the minimap 20x14)
	playertiley
		for loop that iterates over the tilemap around the player, drawing the corresponding mini-tile in the correct corner of the map
		*/
	
	for (i = 0; i < 280; i++) {
	}
			
}