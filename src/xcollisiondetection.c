#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "gfx/tiles_gfx.h"
#include "xcollisiondetection.h"
#include "structs.h"
#include "enemymovement.h"

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
//#include "gfx/dungeon2.h"

int playerdamage;
extern int i;
extern uint24_t player_setup[];
extern int playerface;
extern int goup;
extern int godown;
extern int goleft;
extern int goright;
extern gfx_tilemap_t tilemap;
int replacex;
int replacey;
int hit;
extern int p_hit;
extern int num_p;
extern int dmgmultiplier;
extern int player;

int enemy_maptilex;
int enemy_maptiley;
int pot_maptilex;
int pot_maptiley;
extern int player_mappxlx;
extern int player_mappxly;
extern int player_maptilex;
extern int player_maptiley;
extern int *inputx;
extern int *inputy;
extern unsigned int tmap_pxl_x_offset;
extern unsigned int tmap_pxl_y_offset;
int enemycoordx;
int enemycoordy;
extern int ii;
int healthincrement = 10;

void collisionleft(void) {
enemycoordx = (enemy[ii].x/32);
enemycoordy = (enemy[ii].y/32);
	goleft = 1;
	if (player == 1) {
		if (((gfx_GetTile(&tilemap,player_mappxlx-32,player_mappxly)) >= 18)) {
			goleft = 0;
		}
	}
	if (player == 2) {
		gfx_SetTextXY(enemy[ii].x,enemy[ii].y);
		gfx_PrintInt(gfx_GetTile(&tilemap,enemycoordx-32,enemycoordy),3);
		gfx_PrintString("-");
		gfx_PrintInt(enemycoordx,3);
		if (((gfx_GetTile(&tilemap,enemycoordx-32,enemycoordy)) >= 18)) {
			goleft = 0;
		}
	}

	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy_maptilex = (enemy[i].x/32);
		enemy_maptiley = (enemy[i].y/32);
		if (tmap_pxl_x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (tmap_pxl_y_offset + 192)) {
						if (((*inputx-1) == enemy_maptilex) && (*inputy == enemy_maptiley)){
							if (enemy[i].dead == 0) {
								goleft = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pot_maptilex = (pots[i].p_x/32);
		pot_maptiley = (pots[i].p_y/32);
		if (tmap_pxl_x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (tmap_pxl_y_offset + 192)) {
						if (((*inputx-1) == pot_maptilex) && (*inputy == pot_maptiley)){
							if (pots[i].potdead == 0) {
								goleft = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisionright(void) {
enemycoordx = (enemy[ii].x/32);
enemycoordy = (enemy[ii].y/32);
	goright = 1;
	if (player == 1) {
		if (((gfx_GetTile(&tilemap,player_mappxlx+32,player_mappxly)) >= 18)) {
			goright = 0;
		}
	}
	if (player == 2) {
		if (((gfx_GetTile(&tilemap,enemycoordx+32,enemycoordy)) >= 18)) {
			goright = 0;
		}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy_maptilex = (enemy[i].x/32);
		enemy_maptiley = (enemy[i].y/32);
		if (tmap_pxl_x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (tmap_pxl_y_offset + 192)) {
						if (((*inputx+1) == enemy_maptilex) && (*inputy == enemy_maptiley)){
							if (enemy[i].dead == 0) {
								goright = 0;
							}
						}
					}
				}
			}
		}
		
	}
	for (i = 0; i < NUM_POTS; i++) {
		pot_maptilex = (pots[i].p_x/32);
		pot_maptiley = (pots[i].p_y/32);
		if (tmap_pxl_x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (tmap_pxl_y_offset + 192)) {
						if (((*inputx+1) == pot_maptilex) && (*inputy == pot_maptiley)){
							if (pots[i].potdead == 0) {
								goright = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisionup(void) {
enemycoordx = (enemy[ii].x/32);
enemycoordy = (enemy[ii].y/32);
	goup = 1;
	if (player == 1) {
		if (((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly-32)) >= 18)) {
			goup = 0;
		}
	}
	if (player == 2) {
		if (((gfx_GetTile(&tilemap,enemycoordx,enemycoordy-32)) >= 18)) {
			goup = 0;
		}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy_maptilex = (enemy[i].x/32);
		enemy_maptiley = (enemy[i].y/32);
		if (tmap_pxl_x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (tmap_pxl_y_offset + 192)) {
						if ((*inputx == enemy_maptilex) && ((*inputy-1) == enemy_maptiley)){
							if (enemy[i].dead == 0) {
								goup = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pot_maptilex = (pots[i].p_x/32);
		pot_maptiley = (pots[i].p_y/32);
		if (tmap_pxl_x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (tmap_pxl_y_offset + 192)) {
						if ((*inputx == pot_maptilex) && ((*inputy-1) == pot_maptiley)){
							if (pots[i].potdead == 0) {
								goup = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisiondown(void) {
enemycoordx = (enemy[ii].x/32);
enemycoordy = (enemy[ii].y/32);
	godown = 1;
	
	if (player == 1) {
		if (((gfx_GetTile(&tilemap,player_mappxlx,player_mappxly+32)) >= 18)) {
			godown = 0;
		}
	}	
	if (player == 2) {
		if (((gfx_GetTile(&tilemap,enemycoordx,enemycoordy+32)) >= 18)) {
			godown = 0;
		}
	}
	
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy_maptilex = (enemy[i].x/32);
		enemy_maptiley = (enemy[i].y/32);
		if (tmap_pxl_x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (tmap_pxl_y_offset + 192)) {
						if ((*inputx == enemy_maptilex) && ((*inputy+1) == enemy_maptiley)){
							if (enemy[i].dead == 0) {
								godown = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pot_maptilex = (pots[i].p_x/32);
		pot_maptiley = (pots[i].p_y/32);
		if (tmap_pxl_x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (tmap_pxl_x_offset + 288)){
				if (tmap_pxl_y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (tmap_pxl_y_offset + 192)) {
						if ((*inputx == pot_maptilex) && ((*inputy+1) == pot_maptiley)){
							if (pots[i].potdead == 0) {
								godown = 0;
							}
						}
					}
				}
			}
		}	
	}
}
void projectilemapcollision(void) {
		if (gfx_GetTile(&tilemap,projectile[i].p_x,projectile[i].p_y) >= 18){
			p_hit = 1;
		}
}
void projectileentitycollision(void) {
int randcheck;
//enemies
	for(ii = 0; ii < NUM_ENEMIES; ii++){
		if ((projectile[i].p_x / 32) == (enemy[ii].x / 32)) { 
			if ((projectile[i].p_y / 32) == (enemy[ii].y / 32)) {
				enemy[ii].health = (enemy[ii].health - projectile[i].p_type);
				p_hit = 1;
			}
		}
	}
//pots
	for(ii = 0; ii < NUM_POTS; ii++){
		if ((projectile[i].p_x / 32) == (pots[ii].p_x / 32)) {
			if ((projectile[i].p_y / 32) == (pots[ii].p_y / 32)) {
				if (pots[ii].potdead == 0){
				money[ii].m_x = pots[ii].p_x;
				money[ii].m_y = pots[ii].p_y;
				money[ii].moneydead = 0;
				money[ii].moneyvalue = 1;
				randcheck = 30;
					if (randcheck >= randInt(0,100)) {
						money[ii].moneyvalue = 5;
					}
				randcheck = 20;
					if (randcheck >= randInt(0,100)) {
						money[ii].moneyvalue = 10;
					}
				randcheck = 10;
					if (randcheck >= randInt(0,100)) {
						money[ii].moneyvalue = 20;
					}
				randcheck = 1;
					if (randcheck >= randInt(0,100)) {
						money[ii].moneyvalue = 100;
					}
			}
				pots[ii].potdead = 1;
				p_hit = 1;
			}
		}
	}
}
void playerattackhitcheck(void) {
int money_maptilex;
int money_maptiley;
int randcheck = 1;
///*money
	for (i = 0; i < NUM_POTS; i++) {
		money_maptilex = (money[i].m_x/32);
		money_maptiley = (money[i].m_y/32);
		hit = 0;
		if (playerface == 1){
			if (((player_maptilex-1) == money_maptilex) & (player_maptiley == money_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((player_maptilex == money_maptilex) & ((player_maptiley-1) == money_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((player_maptilex+1) == money_maptilex) & (player_maptiley == money_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((player_maptilex == money_maptilex) & ((player_maptiley+1) == money_maptiley)){
				hit = 1;
			}
		}
		
		if (hit == 1) {
			if (money[i].moneydead == 0){
					player_setup[7] = (player_setup[7] + money[i].moneyvalue);
					if (player_setup[7] > 99999){player_setup[7] = 99999;}
			}
			money[i].moneydead = 1;
		}
	}
//*/
//enemies
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy_maptilex = (enemy[i].x/32);
		enemy_maptiley = (enemy[i].y/32);
		hit = 0;
		if (playerface == 1){
			if (((player_maptilex-1) == enemy_maptilex) & (player_maptiley == enemy_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((player_maptilex == enemy_maptilex) & ((player_maptiley-1) == enemy_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((player_maptilex+1) == enemy_maptilex) & (player_maptiley == enemy_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((player_maptilex == enemy_maptilex) & ((player_maptiley+1) == enemy_maptiley)){
				hit = 1;
			}
		}
		if (hit == 1) {
			(enemy[i].health) = ((enemy[i].health ) - (playerdamage * dmgmultiplier));
		}
	}	
//pots
	for (i = 0; i < NUM_POTS; i++) {
		pot_maptilex = (pots[i].p_x/32);
		pot_maptiley = (pots[i].p_y/32);
		hit = 0;
		if (playerface == 1){
			if (((player_maptilex-1) == pot_maptilex) & (player_maptiley == pot_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((player_maptilex == pot_maptilex) & ((player_maptiley-1) == pot_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((player_maptilex+1) == pot_maptilex) & (player_maptiley == pot_maptiley)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((player_maptilex == pot_maptilex) & ((player_maptiley+1) == pot_maptiley)){
				hit = 1;
			}
		}
		if (hit == 1) {
			if (pots[i].potdead == 0){
				if (pots[i].pottype == 1){
					player_setup[6] = (player_setup[6] + healthincrement);
				}
				money[i].m_x = pots[i].p_x;
				money[i].m_y = pots[i].p_y;
				money[i].moneydead = 0;
				money[i].moneyvalue = 1;
				randcheck = 30;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 5;
					}
				randcheck = 20;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 10;
					}
				randcheck = 10;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 20;
					}
				randcheck = 1;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 100;
					}
			}
			pots[i].potdead = 1;
		}
	}
}