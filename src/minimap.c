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

#include <debug.h>

#include "main.h"
// include its own header file for the defines
#include "minimap.h"

extern gfx_tilemap_t tilemap;
extern int playertilex;
extern int playertiley;
extern int showminimap;
extern gfx_tilemap_t minimapTilemap;
extern int playerface;

void minimap(void) {
	gfx_sprite_t *playerarrow;
	//	                /           /                                               
	//                 /' .,,,,  ./                                                 
	//                /';'     ,/                                                   
	//               / /   ,,//,`'`                                                 
	//              ( ,, '_,  ,,,' ``                                               
	//              |    /@  ,,, ;" `                                               
	//             /    .   ,''/' `,``                                              
	//            /   .     ./, `,, ` ;                                             
	//         ,./  .   ,-,',` ,,/''\,'                                             
	//        |   /; ./,,'`,,'' |   |                                               
	// RAWR!  |     /   ','    /    |                                               
	//         \___/'   '     |     |                                               
	//           `,,'  |      /     `\                                              
	//                /      |        ~\                                            
	//               '       (                                                      
	//              :                                                               
	//             ; .         \--                                                  
	//           :   \         ;
	// KryptonicDragon was here!
	// ascii art by Ooyamaneko, according to the internet
	if (showminimap == 1) {
		int xOffset;
		int yOffset;
		int minimapMaxDrawX;
		int minimapMaxDrawY;

		xOffset = ((playertilex / TILEMAP_TILE_SIZE) - (MINIMAP_COLS / 2)) * MINIMAP_TILE_SIZE;
		yOffset = ((playertiley / TILEMAP_TILE_SIZE) - (MINIMAP_ROWS / 2)) * MINIMAP_TILE_SIZE;

		minimapMaxDrawX = MINIMAP_X + MINIMAP_WIDTH;
		minimapMaxDrawY = MINIMAP_Y + MINIMAP_HEIGHT;

		if (xOffset < 0) {
			minimapTilemap.x_loc = MINIMAP_X - xOffset;
			xOffset = 0;
		} else {
			minimapTilemap.x_loc = MINIMAP_X;
		}

		if (yOffset < 0) {
			minimapTilemap.y_loc = MINIMAP_Y - yOffset;
			yOffset = 0;
		} else {
			minimapTilemap.y_loc = MINIMAP_Y;
		}

		if (MINIMAP_MAX_X - xOffset < MINIMAP_WIDTH) {
			minimapMaxDrawX -= MINIMAP_WIDTH - (MINIMAP_MAX_X - xOffset);
		}
		if (MINIMAP_MAX_Y - yOffset < MINIMAP_HEIGHT) {
			minimapMaxDrawY -= MINIMAP_HEIGHT - (MINIMAP_MAX_Y - yOffset);
		}


		// limit the area we can draw within
		gfx_SetClipRegion(MINIMAP_X, MINIMAP_Y, minimapMaxDrawX, minimapMaxDrawY);

		// draw the area for where the minimap will be drawn. This is necessary 
		// so that there is a background for tiles that aren't drawn (outside of the world)
		gfx_SetColor(0x18);
		gfx_FillRectangle_NoClip(MINIMAP_X - 2, MINIMAP_Y - 2, MINIMAP_WIDTH + 4, MINIMAP_HEIGHT + 4);
		gfx_SetColor(0x00);
		gfx_FillRectangle_NoClip(MINIMAP_X, MINIMAP_Y, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		
		
		// draw the minimap
		gfx_Tilemap(&minimapTilemap, xOffset, yOffset);
		//11x8
		if (playerface == 1) {
			playerarrow = player_arrow_left;
		}
		if (playerface == 2) {
			playerarrow = player_arrow_up;
		}
		if (playerface == 3) {
			playerarrow = player_arrow_right;
		}
		if (playerface == 4) {
			playerarrow = player_arrow_down;
		}
			gfx_TransparentSprite(playerarrow , MINIMAP_X + 50, MINIMAP_Y + 35);
								  
		// reset the clipping window
		gfx_SetClipRegion(0, 0, LCD_WIDTH, LCD_HEIGHT);
	}
}
