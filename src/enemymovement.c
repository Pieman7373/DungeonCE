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
gfx_sprite_t *preflip;

int randcheck = 1;
int attackx;
int attacky;


void enemyattackhitcheck(void) {
	extern int attackx;
	extern int attacky;
}
void setattack(void) {
	
	if ((enemy[ii].type) == 0) {preflip = attack_blue;}
	if ((enemy[ii].type) == 1) {preflip = attack_green;}
	if ((enemy[ii].type) == 2) {preflip = attack_red;}
	if ((enemy[ii].type) == 3) {preflip = bokoblin_light;}
	if ((enemy[ii].type) == 4) {preflip = bokoblin_dark;}
	//if ((enemy[ii].type) == 5) {preflip = knight_green;}
	//if ((enemy[ii].type) == 6) {preflip = knight_red;}
}
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
}
void enemyattack(void) {
	gfx_sprite_t *flippedattack;
	gfx_sprite_t *enemyAttack;
	extern int y_offset;
	extern int x_offset;
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
	
	gfx_TransparentSprite(enemyAttack,attackx - x_offset,attacky - y_offset);
	enemyattackhitcheck();
	}
}
