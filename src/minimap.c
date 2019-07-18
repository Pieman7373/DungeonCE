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

// include its own header file for the defines
#include "minimap.h"

extern gfx_tilemap_t tilemap;
extern int playertilex;
extern int playertiley;
extern int showminimap;

void minimap(void) {
	gfx_sprite_t *tile;
	gfx_UninitedSprite(minimapSprite, MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE);

	minimapSprite->width = MINIMAP_TILE_SIZE;
	minimapSprite->height = MINIMAP_TILE_SIZE;
	
	if (showminimap == 1) {
		uint8_t col;
		uint16_t drawX;
		int scanX;

		// draw the area for where the minimap will be drawn. This is necessary 
		// so that there is a background for tiles that aren't drawn (outside of the world)
		gfx_SetColor(0x00);
		gfx_FillRectangle_NoClip(MINIMAP_X, MINIMAP_Y, MINIMAP_WIDTH, MINIMAP_HEIGHT);

		for (scanX = playertilex, drawX = MINIMAP_X, col = 0; col < MINIMAP_COLS; scanX += 32, drawX += 5, col++) {
			uint8_t row;
			uint8_t drawY;
			int scanY;

			for (scanY = playertiley, drawY = MINIMAP_Y, row = 0; row < MINIMAP_ROWS; scanY += 32, drawY += 5, row++) {
				// ensure we don't scan outside of the world (please replace the magic numbers 12380 and 6400 with defines!)
				if (scanX >= 0 && scanX <= 12380 && scanY >= 0 && scanY <= 6400) {
					// grab the tile
					tile = tilemap.tiles[gfx_GetTile(&tilemap, scanX, scanY)];
					// scale it down
					gfx_ScaleSprite(tile, minimapSprite);
					// draw the scaled tile
					gfx_Sprite_NoClip(minimapSprite, drawX, drawY);
				}
			}
		}
	}	
}
