#include "menuandeditfunctions.h"
#include "xcollisiondetection.h"
#include "maingameloop.h"

//#include "gfx/dungeon2.h"
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
gfx_sprite_t *preflip;

int randcheck = 1;
int attackx;
int attacky;

extern uint24_t player_setup[];

void enemyattackhitcheck(void) {
	extern int attackx;
	extern int attacky;
	extern int player_mappxlx;
	extern int player_mappxly;
	int enemydamage;
	extern int blockchance;
	
	enemydamage = (((enemy[ii].type)+1)*5);
	if ((attackx == player_mappxlx)&(attacky == player_mappxly)){
		if (blockchance <= randInt(0,100)) {
			gfx_FillScreen(0xE0);
			player_setup[6] = (player_setup[6] - enemydamage);
			if (player_setup[6] > 100) {player_setup[6] = 0;}
		}
	}
}
void setattack(void) {
	
	if ((enemy[ii].type) == 0) {preflip = attack_blue;}
	if ((enemy[ii].type) == 1) {preflip = attack_green;}
	if ((enemy[ii].type) == 2) {preflip = attack_red;}
	if ((enemy[ii].type) == 3) {preflip = bokoblin_light;}
	if ((enemy[ii].type) == 4) {preflip = bokoblin_dark;}
	if ((enemy[ii].type) == 5) {preflip = knight_green;}
	if ((enemy[ii].type) == 6) {preflip = knight_red;}
}
void enemymove (void) {
	
	extern unsigned int tmap_pxl_x_offset;
	extern unsigned int tmap_pxl_y_offset;
	int enemystartx;
	int enemystarty;
	extern int goup;
	extern int goleft;
	extern int goright;
	extern int godown;
	extern int enemycoordx;
	extern int enemycoordy;
	extern int player_maptilex;
	extern int player_maptiley;
	extern int player;

	enemystartx = (enemy[ii].x/32);
	enemystarty = (enemy[ii].y/32);
	
	inputx = &enemystartx;
	inputy = &enemystarty;
	player = 2;
	
	collisionleft();
	collisionright();
	collisionup();
	collisiondown();
	
	if (goright == 1) {
		if (enemycoordx <= player_maptilex) {
			enemy[ii].x = (enemy[ii].x + 32);
		}
	}
	if (goleft == 1) {
		if (enemycoordx >= player_maptilex) {
			enemy[ii].x = (enemy[ii].x - 32);
		}
	}
	if (godown == 1) {
		if (enemycoordy <= player_maptiley) {
			enemy[ii].y = (enemy[ii].y + 32);
		}
	}
	if (goup == 1) {
		if (enemycoordy >= (player_maptiley + 5)) {
			enemy[ii].y = (enemy[ii].y - 32);
		}
	}
	
	/*
	gfx_PrintStringXY("-",enemy[ii].x - tmap_pxl_x_offset,(enemy[ii].y+36) - tmap_pxl_y_offset);
	gfx_PrintUInt(goleft,1);
	gfx_PrintString("-");
	gfx_PrintUInt(goup,1);
	gfx_PrintString("-");
	gfx_PrintUInt(goright,1);
	gfx_PrintString("-");
	gfx_PrintUInt(godown,1);

	
	gfx_SetTextXY(enemy[ii].x - tmap_pxl_x_offset,(enemy[ii].y+36) - tmap_pxl_y_offset);
	gfx_PrintInt(enemycoordx,3);
	gfx_PrintString("-");
	gfx_PrintInt(enemycoordy,3);
	gfx_SetTextXY(enemy[ii].x - tmap_pxl_x_offset,(enemy[ii].y+56) - tmap_pxl_y_offset);
	gfx_PrintInt(player_maptilex,3);
	gfx_PrintString("-");
	gfx_PrintInt(player_maptiley,3);
	*/
}
void enemyattack(void) {
	gfx_sprite_t *flippedattack;
	gfx_sprite_t *enemyAttack;
	extern unsigned int tmap_pxl_y_offset;
	extern unsigned int tmap_pxl_x_offset;
	extern int playerface;
	
	if (randcheck == randInt(0,14)) {
		gfx_UninitedSprite(flippedattack, 32,32);
		
		//attack goes in opposite direction of playerface
		if (playerface == 3) {
			//set left
			setattack();
			attackx = (enemy[ii].x - 32);
			attacky = enemy[ii].y;
			gfx_RotateSpriteCC(preflip,flippedattack);
			enemyAttack = flippedattack;
		}
		if (playerface == 4) {
			//set up
			setattack();
			attackx = enemy[ii].x;
			attacky = (enemy[ii].y - 32);
			enemyAttack = preflip;
		}
		if (playerface == 1) {
			//set right
			setattack();
			attackx = (enemy[ii].x + 32);
			attacky = enemy[ii].y;
			gfx_RotateSpriteC(preflip,flippedattack);
			enemyAttack = flippedattack;
		}
		if (playerface == 2) {
			//set down
				setattack();
			attackx = enemy[ii].x;
			attacky = (enemy[ii].y + 32);
			gfx_FlipSpriteX(preflip,flippedattack);
			enemyAttack = flippedattack;
		}
	
	gfx_TransparentSprite(enemyAttack,attackx - tmap_pxl_x_offset,attacky - tmap_pxl_y_offset);
	enemyattackhitcheck();
	}
}
