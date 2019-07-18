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
extern int showminimap;
gfx_sprite_t *minimaptile;

void minimap(void){

	int minimapx;
	int minitilex = 5;
	int minimapx_initial;
	int minimapy;
	int minitiley = 5;
	int minimapy_initial;
	int i;
	gfx_UninitedSprite(minimaptile, 5, 5);
	gfx_UninitedSprite(sprite_out, 5, 5);
	int tile;
	
	if (showminimap == 1) {
		gfx_SetColor(0x00);
		gfx_FillRectangle(3,3,100,70);
		/*
		playertilex - (whatever makes the minimap 20x14)
		playertiley
			for loop that iterates over the tilemap around the player, drawing the corresponding mini-tile in the correct corner of the map
			*/
		playertilex = minimapx_initial;
		minimapx = minimapx_initial;
		playertiley = minimapy_initial;
		minimapy = minimapy_initial;
		
		//sprite_out->width = 5;
		//sprite_out->height = 5;
		
		for (i = 0; i < 280; i++) {
			//get the tile 
			tile = (gfx_TilePtr(&tilemap,(minimapx*32),(minimapy*32)));
			
			//shrink to 5x5
			gfx_ScaleSprite(tile, minimaptile);
			
			//draw mini tile
			gfx_Sprite(minimaptile, minitilex, minitiley);
			
			//move on to next tile
			minimapx++;
			minitilex = (minitilex + 5);
				
			if (minimapx > minimapx_initial) {
				minimapx = minimapx_initial;
				minitilex = 5;
				minimapy = (minimapy + 1);
				minitiley = (minitiley + 5);
			}
			if (minimapy > minimapy_initial) {
				minimapy = minimapy_initial;
				minimapy = 5;
			}
		}
	}	
}