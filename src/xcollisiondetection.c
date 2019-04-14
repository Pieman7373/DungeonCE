#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "gfx/tiles_gfx.h"
#include "xcollisiondetection.h"
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
#include "gfx/Dungeon.h"

int playerdamage;
extern int i;
extern uint8_t player_setup[];
extern int playertilex;
extern int playertiley;
extern int playerface;
extern int goup;
extern int godown;
extern int goleft;
extern int goright;
extern gfx_tilemap_t tilemap;
int replacex;
int replacey;
int hit;
int dmgmultiplyer = 1;

extern enemy_t enemy[];
extern uint8_t enemytype;
extern int deadset;
extern uint24_t enemyx;
extern uint24_t enemyy;
extern int enemyhealth;

extern pots_t pots[];
extern uint8_t pottype;
extern int potdeadset;
extern uint24_t potx;
extern uint24_t poty;
int enemytilemapx;
int enemytilemapy;
int pottilemapx;
int pottilemapy;
extern int playertilex;
extern int playertiley;
extern int playertilemapx;
extern int playertilemapy;

int healthincrement = 10;

void collisionleft(void) {
	
	if (((gfx_GetTile(&tilemap,playertilex-32,playertiley)) >= 18)) {
	goleft = 0;
	}
	else {goleft = 1;}
}
void collisionright(void) {
	
	if (((gfx_GetTile(&tilemap,playertilex+32,playertiley)) >= 18)) {
	goright = 0;
	}
	else {(goright = 1);}
}
void collisionup(void) {
	
	if (((gfx_GetTile(&tilemap,playertilex,playertiley-32)) >= 18)) {
	goup = 0;
	}
	else {(goup = 1);}
}
void collisiondown(void) {
	
	if (((gfx_GetTile(&tilemap,playertilex,playertiley+32)) >= 18)) {
	godown = 0;
	}
	else {(godown = 1);}
}


void playerattackhitcheck(void) {

if (player_setup[3] == 0) {playerdamage = 1;}
if (player_setup[3] == 1) {playerdamage = 2;}
if (player_setup[3] == 2) {playerdamage = 3;}
if (player_setup[3] == 3) {playerdamage = 4;}
if (player_setup[3] == 4) {playerdamage = 5;}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		hit = 0;
		if (playerface == 1){
			if (((playertilemapx-1) == enemytilemapx) & (playertilemapy == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((playertilemapx == enemytilemapx) & ((playertilemapy-1) == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((playertilemapx+1) == enemytilemapx) & (playertilemapy == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((playertilemapx == enemytilemapx) & ((playertilemapy+1) == enemytilemapy)){
				hit = 1;
			}
		}
		if (hit == 1) {
			(enemy[i].health) = ((enemy[i].health ) - (playerdamage * dmgmultiplyer));
		}
	}	
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		hit = 0;
		if (playerface == 1){
			if (((playertilemapx-1) == pottilemapx) & (playertilemapy == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((playertilemapx == pottilemapx) & ((playertilemapy-1) == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((playertilemapx+1) == pottilemapx) & (playertilemapy == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((playertilemapx == pottilemapx) & ((playertilemapy+1) == pottilemapy)){
				hit = 1;
			}
		}
		if (hit == 1) {
			pots[i].potdead = 1;
			if (pots[i].pottype == 1){
				player_setup[6] = (player_setup[6] + healthincrement);
			}
		}
	}
}