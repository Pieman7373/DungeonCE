/*
 *--------------------------------------
 * Program Name:CC22 Dungeon
 * Author:Pieman7373
 * License:
 * Description:
 *--------------------------------------
*/

/* Keep these headers */
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
#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "xcollisiondetection.h"

#include "gfx/dungeon.h"
//#include "gfx/dungeon2.h"
#include "gfx/tiles_gfx.h"
#include "main.h"

/* Put all your globals here */
	int menuyes;
	int menuoption;
	int textcolor = (0xE6);
	int accentcolor = (0x40);
	int menucolor = (0x00);
	int submenucolor = (0x4A);
	int transcolor = (0xF8);
	int editweaponx = 90;
	int editweapony = 0;
	int editweaponsmallx = 75;
	int editweaponsmally = 150;
	int editscale = 6;
	int editscalep = 12;
	int editpx = 140;
	int editpy = 10;
	

	int mapshift;
	//player is 5 away
	int mapstartx;
	//player is 4 away
	int mapstarty;
	
	//for tilemap stuff

	#define Y_OFFSET            0
	#define X_OFFSET            0
	
	unsigned int x_offset;
	unsigned int y_offset;
	
	extern uint8_t *dungeon[];
	
	extern uint8_t tilemap_map[];
	//extern uint8_t tilemap_enemies[];
	gfx_tilemap_t tilemap;
	
	
	//0=naked, 1=leather, 2=chain, 3=steel, 4=dragon
	signed int setnumber = 0;
	
	
	/*
	!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!
	RESET PLAYER STATS
	!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!
	*/
	//{0-helmet,1-chestplate,2-boots,3-weapon,4-x,5-y,6-health%,7-money}
	uint24_t player_setup[8] = {0,0,0,0,0,0,100,0};
	//3,2,2,4,0,0,100,0
	/*
	helmet and chestplate increase the chance of negating enemy damage
	boots make walking faster
	weapon increases damage dealt
	*/
	

void main(void) {

	kb_key_t key;
	

	if (!dungeon_init()) { abort(); }
	//if (!dungeon2_init()) { abort(); }

    /* Initialize the tilemap structure */
	tilemap.map         = tilemap_map;
    tilemap.tiles       = tileset_tiles;
    tilemap.type_width  = gfx_tile_32_pixel;
    tilemap.type_height = gfx_tile_32_pixel;
    tilemap.tile_height = TILEMAP_TILE_SIZE;
    tilemap.tile_width  = TILEMAP_TILE_SIZE;
    tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
    tilemap.draw_width  = TILEMAP_DRAW_WIDTH;
    tilemap.height      = TILEMAP_HEIGHT;
    tilemap.width       = TILEMAP_WIDTH;
    tilemap.y_loc       = Y_OFFSET;
    tilemap.x_loc       = X_OFFSET;
	
	gfx_SetPalette(tiles_gfx_pal, sizeof_tiles_gfx_pal, 0);
	gfx_SetTransparentColor(transcolor);
	gfx_Begin();
	kb_SetMode(MODE_3_CONTINUOUS);
	//gfx_SetTextConfig(1);
	
	mapstartx = ((TILEMAP_WIDTH/2) - 5);
	mapstarty = (TILEMAP_HEIGHT - 10);
	
	menuloop();

	gfx_End();
}

