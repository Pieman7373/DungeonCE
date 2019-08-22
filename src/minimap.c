
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
extern int player_mappxlx;
extern int player_mappxly;
extern int showminimap;
extern gfx_tilemap_t minimapTilemap;
extern int playerface;
extern int minimapposition;

void minimap(void) {
	gfx_sprite_t *playerarrow;
		int xOffset;
		int yOffset;
		int minimapMaxDrawX;
		int minimapMaxDrawY;
		int minimapx = 3;
		int minimapy = 3;
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

		xOffset = ((player_mappxlx / TILEMAP_TILE_SIZE) - (MINIMAP_COLS / 2)) * MINIMAP_TILE_SIZE;
		yOffset = ((player_mappxly / TILEMAP_TILE_SIZE) - (MINIMAP_ROWS / 2)) * MINIMAP_TILE_SIZE;
		
		if (minimapposition == 1) {
			minimapx = 3;
			minimapy = 3;
		}
		if (minimapposition == 2) {
			minimapx = 217;
			minimapy = 3;
		}
		if (minimapposition == 3) {
			minimapx = 3;
			minimapy = 151;
		}
		if (minimapposition == 4) {
			minimapx = 217;
			minimapy = 151;
		}
		
		minimapMaxDrawX = minimapx + MINIMAP_WIDTH;
		minimapMaxDrawY = minimapy + MINIMAP_HEIGHT;

		if (xOffset < 0) {
			minimapTilemap.x_loc = minimapx - xOffset;
			xOffset = 0;
		} else {
			minimapTilemap.x_loc = minimapx;
		}

		if (yOffset < 0) {
			minimapTilemap.y_loc = minimapy - yOffset;
			yOffset = 0;
		} else {
			minimapTilemap.y_loc = minimapy;
		}

		if (MINIMAP_MAX_X - xOffset < MINIMAP_WIDTH) {
			minimapMaxDrawX -= MINIMAP_WIDTH - (MINIMAP_MAX_X - xOffset);
		}
		if (MINIMAP_MAX_Y - yOffset < MINIMAP_HEIGHT) {
			minimapMaxDrawY -= MINIMAP_HEIGHT - (MINIMAP_MAX_Y - yOffset);
		}


		// limit the area we can draw within
		gfx_SetClipRegion(minimapx, minimapy, minimapMaxDrawX, minimapMaxDrawY);

		// draw the area for where the minimap will be drawn. This is necessary 
		// so that there is a background for tiles that aren't drawn (outside of the world)
		gfx_SetColor(0x18);
		gfx_FillRectangle_NoClip(minimapx - 2, minimapy - 2, MINIMAP_WIDTH + 4, MINIMAP_HEIGHT + 4);
		gfx_SetColor(0x00);
		gfx_FillRectangle_NoClip(minimapx, minimapy, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		
		
		// draw the minimap
		gfx_Tilemap(&minimapTilemap, xOffset, yOffset);
		
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
			gfx_TransparentSprite(playerarrow , minimapx + 50, minimapy + 35);
								  
		// reset the clipping window
		gfx_SetClipRegion(0, 0, LCD_WIDTH, LCD_HEIGHT);
	}
}
