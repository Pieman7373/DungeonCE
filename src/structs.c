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

#include "structs.h"
#include "menuandeditfunctions.h"

//ENEMIES
uint16_t defaultenemy_movelist[NUM_ENEMIES] = {0,0,0,0,0};
//from test map {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

uint16_t defaultenemy_typelist[NUM_ENEMIES] = {0,1,2,3,4,5,6};
//from test map {0,1,2,3,4,5,6,2,2,2,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6}

uint16_t defaultenemy_xlist[NUM_ENEMIES] = {12 ,13 ,14 ,15 ,16 ,17 ,18 };
//from test map {76,76,76,77,77,78,78,106,107,107,106,15,52,53,54,55,56,57,58,52,53,54,55,56,57,58,25,26,27,28,29,30,31}

uint16_t defaultenemy_ylist[NUM_ENEMIES] = {187,187,187,187,187,187,187};
//from test map {90,91,92,90,91,90,91,74,75,74,75,93,81,81,81,81,81,81,81,82,82,82,82,82,82,82,65,65,65,65,65,65,65}



//POTS
uint16_t default_pottypelist[NUM_POTS];
//{0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}

uint16_t default_potxlist[NUM_POTS] = {18 ,22 };
//from test map {77,78,106,107,14,15,16,14,15,16,52,53,54,55,56,57,58,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34}

uint16_t default_potylist[NUM_POTS] = {194,194};
//from test map {97,97, 76, 76,91,91,91,92,92,92,80,80,80,80,80,80,80,71,71,71,71,71,71,71,71,71,71,71,71,71,71,72,72,72,72,72,72,72,72,72,72,72,72,72,72,73,73,73,73,73,73,73,73,73,73,73,73,73,73,74,74,74,74,74,74,74,74,74,74,74,74,74,74,75,75,75,75,75,75,75,75,75,75,75,75,75,75}



//RELICS



//boss_t boss[];
//relic_t relic[];

//BOSSES
uint16_t defaultboss_type[NUM_BOSS] = {1,2,3};
uint16_t defaultboss_relicnum[NUM_BOSS] = {0,1,2};
uint16_t defaultboss_xlist[NUM_BOSS] = {5,6,7};
uint16_t defaultboss_ylist[NUM_BOSS] = {5,6,7};