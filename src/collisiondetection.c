#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "gfx/dungeon_gfx.h"
#include "gfx/tiles_gfx.h"

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

extern int goup;
extern int godown;
extern int goleft;
extern int goright;



//check mapshift away
void collisionleft(void) {
	(goleft = 1);
}


//check mapshift+32 away
void collisionright(void) {
	(goright = 1);
}


//check mapshift away
void collisionup(void) {
	(goup = 1);
}


//check mapshift+32 away
void collisiondown(void) {
	(godown = 1);
}
