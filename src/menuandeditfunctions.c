#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "enemymovement.h"
//#include "gfx/dungeon.h"
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
	 

extern int i;
extern int menuoption;
extern int menuyes;
extern int textcolor;
extern int menucolor;
extern int submenucolor;
extern int accentcolor;
extern int transcolor;
extern int playerface;
int editweaponx = 90;
int editweapony = 0;
int editweaponsmallx = 66;
int editweaponsmally = 152;
int editscale = 6;
int editscalep = 12;
int editpx = 140;
int editpy = 10;
int mainmenuleftX;
int mainmenurightX;
int mainmenuY;
int mainmenuposition;
int enemyHPbarlength;
extern unsigned int tmap_pxl_x_offset;
extern unsigned int tmap_pxl_y_offset;
int mmhotkey;
extern int damagenumbers;

/*
uint8_t enemytype;
int deadset;
uint24_t enemyx;
uint24_t enemyy;
int enemyhealth;
*/

int drawhealth = 1;
int lifebar_maxlen = 30;
extern signed int setnumber;
extern uint24_t player_setup[];

extern int mapstartx;
extern int mapstarty;
extern int tileoffsetx;
extern int tileoffsety;
extern kb_key_t key;
extern int showminimap;

extern uint16_t defaultenemy_movelist[];
extern uint16_t defaultenemy_typelist[];
extern uint16_t defaultenemy_xlist[];
extern uint16_t defaultenemy_ylist[];
extern uint16_t default_relicxlist[];
extern uint16_t default_relicylist[];
extern uint16_t defaultboss_type[];
extern uint16_t defaultboss_xlist[];
extern uint16_t defaultboss_ylist[];

gfx_sprite_t *enemySprite;

int ii;
int redcolor = 0xE8;
int selectedcolor = (0xE3);
int purchased[22];
//int purchased[22] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//int inventory[22];
//int inventory[22] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int inv_contents[22];
int equipped[4] = {0,0,0,0};
int tilespace = 28;

extern int num_p;

extern int minimapposition;

void keywait(void) {
	while (kb_AnyKey()); 
	kb_SetMode(MODE_3_CONTINUOUS);
}

void mainmenu(void) {
	
mainmenuY = 113;
mainmenuleftX = 72;
mainmenurightX = 242;
mainmenuposition = 1;
	
do{
	
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
    gfx_ScaledTransparentSprite_NoClip(mainmenulogo,33,10,2,2);
	gfx_SetTextScale(2,2);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("Load Game",95,110);
	gfx_PrintStringXY("New Game",102,138);
	gfx_PrintStringXY("Free Play",97,164);
	gfx_PrintStringXY("Edit Player",85,194);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("By: Pieman7373   2019",6,228);
	
	menuyes = 0;
	menuoption = 0;
	
	gfx_TransparentSprite(menuarrowL,mainmenuleftX,mainmenuY);
	gfx_TransparentSprite(menuarrowR,mainmenurightX,mainmenuY);
	
	if (kb_Data[7] & kb_Down){
		switch(mainmenuposition) {
			case 1 :
				mainmenuposition = 2;
				mainmenuY = 141;
				mainmenuleftX = 82;
				mainmenurightX = 230;
			break;
			case 2 :
				mainmenuposition = 3;
				mainmenuY = 167;
				mainmenuleftX = 77;
				mainmenurightX = 240;
			break;
			case 3 :
				mainmenuposition = 4;
				mainmenuY = 197;
				mainmenuleftX = 65;
				mainmenurightX = 250;
			break;
			case 4 :
				mainmenuposition = 1;
				mainmenuY = 113;
				mainmenuleftX = 72;
				mainmenurightX = 242;
			break;
		}		
	}
	if (kb_Data[7] & kb_Up){
		switch(mainmenuposition) {
			case 3 :
				mainmenuposition = 2;
				mainmenuY = 141;
				mainmenuleftX = 82;
				mainmenurightX = 230;
			break;
			case 4 :
				mainmenuposition = 3;
				mainmenuY = 167;
				mainmenuleftX = 77;
				mainmenurightX = 240;
			break;
			case 1 :
				mainmenuposition = 4;
				mainmenuY = 197;
				mainmenuleftX = 65;
				mainmenurightX = 250;
			break;
			case 2 :
				mainmenuposition = 1;
				mainmenuY = 113;
				mainmenuleftX = 72;
				mainmenurightX = 242;
			break;
		}		
	}
	if (kb_Data[1] & kb_2nd){
		menuyes = 1;
		menuoption = mainmenuposition;
	}
	
	gfx_SwapDraw();
	
	keywait();
	
	
} while (!((menuoption) || (kb_Data[6] & kb_Clear)));
 
}
void drawsavemenu(void){
	
	gfx_SetDrawBuffer();
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(0,154,108,66);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,154,108,66);
	gfx_Rectangle(2,156,104,62);
	submenubottombar();
	gfx_PrintStringXY("1. Save",5,160);
	gfx_SwapDraw();
	do {
		if (kb_Data[3] & kb_1) {savegame();}
	} while (!(kb_Data[1] & kb_Window));
}
void drawstore(void) {
		//0
		int price_leather_helmet = 10;
		//1
		int price_leather_tunic = 10;
		//2
		int price_leather_boots = 10;
		//3
		int price_iron_helmet = 50;
		//4
		int price_chain_shirt = 50;
		//5
		int price_chain_boots = 50;
		//6
		int price_steel_helmet = 100;
		//7
		int price_steel_chestplate = 100;
		//8
		int price_steel_boots = 100;
		//9
		int price_dragon_helmet = 500;
		//10
		int price_dragon_chestplate = 500;
		//11
		int price_dragon_boots = 500;
		//12
		int price_club = 10;
		//13
		int price_iron_sword = 50;
		//14
		int price_steel_sword = 100;
		//15
		int price_dragon_sword = 500;
		//16
		int price_basic_bow = 10;
		//17
		int price_recurve_bow = 50;
		//18
		int price_compound_bow = 100;
		//19
		int price_dragon_bow = 500;
		//20
		int price_small_potion = 10;
		//21
		int price_medium_potion = 50;
		//22
		int price_large_potion = 150;
	
	
	int graycolor = (0xAC);
	int cursorposition = 1;
	int storepage = 1;
	int storepane = 1;
	int windowpress = 0;
	extern int greencolor;
	do {
		gfx_SetDrawBuffer();
		gfx_SetColor(submenucolor);
		gfx_FillRectangle(140,125,150,95);
		gfx_SetColor(accentcolor);
		gfx_Rectangle(140,125,150,95);
		gfx_Rectangle(142,127,146,91);
		submenubottombar();
		windowpress = 0;
		gfx_SetTextFGColor(textcolor);
		gfx_PrintStringXY("Money:  ",150,207);
		gfx_PrintUInt(player_setup[7],sizeof(player_setup[7]));
			gfx_PrintStringXY("<",160,228);
			gfx_PrintStringXY(">",288,228);
		if (storepane == 1){
			gfx_PrintStringXY("ARMOR",208,228);
			if (storepage == 1){				
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_leather_helmet > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[0] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Leather Helmet    ",150,132);
					gfx_PrintInt(price_leather_helmet,2);
		
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_leather_tunic > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[1] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Leather Tunic    ",150,147);
					gfx_PrintInt(price_leather_tunic,2);
			
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor);
				if (price_leather_boots > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[2] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Leather Boots    ",150,162);
					gfx_PrintInt(price_leather_boots,2);
	
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor);	
					if (price_iron_helmet > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[3] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Iron Helmet    ",150,177);
					gfx_PrintInt(price_iron_helmet,2);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_chain_shirt > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[4] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Chain Shirt    ",150,192);
					gfx_PrintInt(price_chain_shirt,2);
			}
			if (storepage == 2){				
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_chain_boots > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[5] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Chain Boots    ",150,132);
					gfx_PrintInt(price_chain_boots,2);
			
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_steel_helmet > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[6] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Steel Helmet    ",150,147);
					gfx_PrintInt(price_steel_helmet,3);
			
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_steel_chestplate > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[7] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Steel Chest   ",150,162);
					gfx_PrintInt(price_steel_chestplate,3);
	
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_steel_boots > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[8] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Steel Boots    ",150,177);
					gfx_PrintInt(price_steel_boots,3);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_dragon_helmet > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[9] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Dragon Helmet    ",150,192);
			}		gfx_PrintInt(price_dragon_helmet,3);
			if (storepage == 3){				
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_dragon_chestplate > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[10] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Dragon Chest    ",150,132);
					gfx_PrintInt(price_dragon_chestplate,3);
		
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else { 
				gfx_SetTextFGColor(textcolor); 
				if (price_dragon_boots > player_setup[7]){
					gfx_SetTextFGColor(redcolor);
				}
				if (purchased[11] == 1){
					gfx_SetTextFGColor(greencolor);
				}
			}
					gfx_PrintStringXY("Dragon Boots    ",150,147);
					gfx_PrintInt(price_dragon_boots,3);
			
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,162);
	
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,177);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,192);
			}
		}
		if (storepane == 2){
			gfx_PrintStringXY("WEAPONS",203,228);
			if (storepage == 1){
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_club > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[12] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Club    ",150,132);
					gfx_PrintInt(price_club,2);
				
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_iron_sword > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[13] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Iron Sword    ",150,147);
					gfx_PrintInt(price_iron_sword,2);
				
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_steel_sword > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[14] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Steel Sword    ",150,162);
					gfx_PrintInt(price_steel_sword,3);
	
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_dragon_sword > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[15] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Dragon Sword    ",150,177);
					gfx_PrintInt(price_dragon_sword,4);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_basic_bow > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[16] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Basic Bow    ",150,192);
					gfx_PrintInt(price_basic_bow,2);
			}
			if (storepage == 2){
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_recurve_bow > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[17] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Recurve Bow    ",150,132);
					gfx_PrintInt(price_recurve_bow,2);
				
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_compound_bow > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[18] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Compound Bow    ",150,147);
					gfx_PrintInt(price_compound_bow,3);
				
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_dragon_bow > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
					if (purchased[19] == 1){
						gfx_SetTextFGColor(greencolor);
					}
				}
					gfx_PrintStringXY("Dragon Bow    ",150,162);
					gfx_PrintInt(price_dragon_bow,3);
				
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,177);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,192);
			}
		}
		if (storepane == 3){
			gfx_PrintStringXY("ITEMS",208,228);
			if (storepage == 1){
				if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_small_potion > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
				}
					gfx_PrintStringXY("Small Potion    ",150,132);
					gfx_PrintInt(price_small_potion,2);
				
				if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_medium_potion > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
				}
					gfx_PrintStringXY("Med. Potion    ",150,147);
					gfx_PrintInt(price_medium_potion,2);
				
				if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
				else {
					gfx_SetTextFGColor(textcolor);
					if (price_large_potion > player_setup[7]){
						gfx_SetTextFGColor(redcolor);
					}
				}
					gfx_PrintStringXY("Large Potion    ",150,162);
					gfx_PrintInt(price_large_potion,3);
				
				if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,177);

				if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(graycolor);}
					gfx_PrintStringXY("--------",150,192);
			}
		}
	
		gfx_SwapDraw();

	if (kb_Data[1] & kb_Window) {
		windowpress = 1;
	}
	if ((kb_Data[1] & kb_Zoom)||(kb_Data[7] & kb_Left)) {
		storepane--;
		storepage = 1;
		cursorposition = 1;
		if (storepane == 0) {
			storepane = 3;
		}
	}
	if ((kb_Data[1] & kb_Graph)||(kb_Data[7] & kb_Right)) {
		storepane++;
		storepage = 1;
		cursorposition = 1;
		if (storepane == 4) {
			storepane = 1;
		}
	}
	if (kb_Data[7] & kb_Down) {
		cursorposition++;
		if (cursorposition == 6) {
			cursorposition = 1;
			if (storepane == 1){
				if (storepage == 1){storepage = 2;}
				else if (storepage == 2){storepage = 3;}
				else if (storepage == 3){storepage = 1;}
			}
			if (storepane == 2){
				if (storepage == 1){storepage = 2;}
				else if (storepage == 2){storepage = 1;}
			}
		}
	}
	if (kb_Data[7] & kb_Up) {
		cursorposition = (cursorposition - 1);
		if (cursorposition == 0) {
			cursorposition = 5;
			if (storepane == 1){
				if (storepage == 2){storepage = 1;}
				else if (storepage == 3){storepage = 2;}
				else if (storepage == 1){storepage = 3;}
			}
			if (storepane == 2){
				if (storepage == 2){storepage = 1;}
				else if (storepage == 1){storepage = 2;}
			}
		}
	}
	if (kb_Data[1] & kb_2nd) {
		if (storepane == 1){
			if (storepage == 1){
				if (cursorposition == 1){
					if (player_setup[7] >= price_leather_helmet){
						player_setup[7] = (player_setup[7] - price_leather_helmet);
						purchased[0] = 1;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_leather_tunic){
						player_setup[7] = (player_setup[7] - price_leather_tunic);
						purchased[1] = 1;
					}
				}
				if (cursorposition == 3){
					if (player_setup[7] >= price_leather_boots){
						player_setup[7] = (player_setup[7] - price_leather_boots);
						purchased[2] = 1;
					}
				}
				if (cursorposition == 4){
					if (player_setup[7] >= price_iron_helmet){
						player_setup[7] = (player_setup[7] - price_iron_helmet);
						purchased[3] = 1;
					}
				}
				if (cursorposition == 5){
					if (player_setup[7] >= price_chain_shirt){
						player_setup[7] = (player_setup[7] - price_chain_shirt);
						purchased[4] = 1;
					}
				}
				
			}
			if (storepage == 2){
				if (cursorposition == 1){
					if (player_setup[7] >= price_chain_boots){
						player_setup[7] = (player_setup[7] - price_chain_boots);
						purchased[5] = 1;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_steel_helmet){
						player_setup[7] = (player_setup[7] - price_steel_helmet);
						purchased[6] = 1;
					}
				}
				if (cursorposition == 3){
					if (player_setup[7] >= price_steel_chestplate){
						player_setup[7] = (player_setup[7] - price_steel_chestplate);
						purchased[7] = 1;
					}
				}
				if (cursorposition == 4){
					if (player_setup[7] >= price_steel_boots){
						player_setup[7] = (player_setup[7] - price_steel_boots);
						purchased[8] = 1;
					}
				}
				if (cursorposition == 5){
					if (player_setup[7] >= price_dragon_helmet){
						player_setup[7] = (player_setup[7] - price_dragon_helmet);
						purchased[9] = 1;
					}
				}
			}
			if (storepage == 3){
				if (cursorposition == 1){
					if (player_setup[7] >= price_dragon_chestplate){
						player_setup[7] = (player_setup[7] - price_dragon_chestplate);
						purchased[10] = 1;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_dragon_boots){
						player_setup[7] = (player_setup[7] - price_dragon_boots);
						purchased[11] = 1;
					}
				}
			}
		}
		if (storepane == 2){
			if (storepage == 1){
				if (cursorposition == 1){
					if (player_setup[7] >= price_club){
						player_setup[7] = (player_setup[7] - price_club);
						purchased[12] = 1;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_iron_sword){
						player_setup[7] = (player_setup[7] - price_iron_sword);
						purchased[13] = 1;
					}
				}
				if (cursorposition == 3){
					if (player_setup[7] >= price_steel_sword){
						player_setup[7] = (player_setup[7] - price_steel_sword);
						purchased[14] = 1;
					}
				}
				if (cursorposition == 4){
					if (player_setup[7] >= price_dragon_sword){
						player_setup[7] = (player_setup[7] - price_dragon_sword);
						purchased[15] = 1;
					}
				}
				if (cursorposition == 5){
					if (player_setup[7] >= price_basic_bow){
						player_setup[7] = (player_setup[7] - price_basic_bow);
						purchased[16] = 1;
					}
				}
			}
			if (storepage == 2){
				if (cursorposition == 1){
					if (player_setup[7] >= price_recurve_bow){
						player_setup[7] = (player_setup[7] - price_recurve_bow);
						purchased[17] = 1;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_compound_bow){
						player_setup[7] = (player_setup[7] - price_compound_bow);
						purchased[18] = 1;
					}
				}
				if (cursorposition == 3){
					if (player_setup[7] >= price_dragon_bow){
						player_setup[7] = (player_setup[7] - price_dragon_bow);
						purchased[19] = 1;
					}
				}
			}
		}
		if (storepane == 3){
			if (storepage == 1){
				if (cursorposition == 1){
					if (player_setup[7] >= price_small_potion){
						player_setup[7] = (player_setup[7] - price_small_potion);
						purchased[20]++;
					}
				}
				if (cursorposition == 2){
					if (player_setup[7] >= price_medium_potion){
						player_setup[7] = (player_setup[7] - price_medium_potion);
						purchased[21]++;
					}
				}
				if (cursorposition == 5){
					if (player_setup[7] >= price_large_potion){
						player_setup[7] = (player_setup[7] - price_large_potion);
						purchased[22]++;
					}
				}
			}
		}
	}
		
keywait();
kb_SetMode(MODE_3_CONTINUOUS);
	} while (!(windowpress));
	kb_SetMode(MODE_3_CONTINUOUS);
}
void drawstatsmenu(void) {
extern int dmgmultiplier;
extern int blockchance;
extern int playerdamage;
extern int walkspeed;


	gfx_SetDrawBuffer();
	gfx_SetColor(submenucolor);
	gfx_FillRectangle(140,115,150,105);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(140,115,150,105);
	gfx_Rectangle(142,117,146,101);
	submenubottombar();
	gfx_PrintStringXY("Money:  ",150,122);
	gfx_PrintUInt(player_setup[7],sizeof(player_setup[7]));
	gfx_PrintStringXY("Player Damage:  ",150,137);
	gfx_PrintInt(playerdamage,2);
	gfx_PrintStringXY("Damage Mult. :  ",150,152);
	gfx_PrintInt(dmgmultiplier,2);
	gfx_PrintStringXY("Block % Chance:  ",150,167);
	gfx_PrintInt(blockchance,2);
	gfx_PrintString("%");
	gfx_PrintStringXY("Health:  ",150,182);
	gfx_PrintInt(player_setup[6],sizeof(player_setup[6]));
	
	//gfx_PrintStringXY("Walk Speed:  ",150,197);
	//gfx_PrintInt(walkspeed,2);
	
	gfx_SwapDraw();
	do {
	} while (!(kb_Data[1] & kb_Window));
}
void drawoptions(void) {
	int selectedcolor = (0xE3);
	int cursorposition = 1;
	int optionspage = 1;
	int windowpress = 0;
	do {
		gfx_SetDrawBuffer();
		gfx_SetColor(submenucolor);
		gfx_FillRectangle(140,125,150,95);
		gfx_SetColor(accentcolor);
		gfx_Rectangle(140,125,150,95);
		gfx_Rectangle(142,127,146,91);
		submenubottombar();
		windowpress = 0;
		if (optionspage == 1){
			
			
			if (cursorposition == 1) {gfx_SetTextFGColor(selectedcolor); }
			else { gfx_SetTextFGColor(textcolor); }		
				gfx_PrintStringXY("Toggle Minimap",145,132);
					if (showminimap == 1) {gfx_PrintStringXY("<ON>",258,132); }
					if (showminimap == 0) {gfx_PrintStringXY("<OFF>",250,132); }
		
			if (cursorposition == 2) {gfx_SetTextFGColor(selectedcolor); }
			else {gfx_SetTextFGColor(textcolor); }
					if (showminimap == 0) {gfx_SetTextFGColor(redcolor); }
				gfx_PrintStringXY("MM Position: ",145,147);
					if (minimapposition == 1) {gfx_PrintStringXY("<Top L>",239,148); }
					if (minimapposition == 2) {gfx_PrintStringXY("<Top R>",239,148); }
					if (minimapposition == 3) {gfx_PrintStringXY("<Btm L>",240,148); }
					if (minimapposition == 4) {gfx_PrintStringXY("<Btm R>",240,148); }

			if (cursorposition == 3) {gfx_SetTextFGColor(selectedcolor); }
			else {gfx_SetTextFGColor(textcolor); }
				gfx_PrintStringXY("MM Hotkey",145,162);
					if (mmhotkey == 0) {gfx_PrintStringXY("<None>",242,162);}
					if (mmhotkey == 1) {gfx_PrintStringXY("<[alpha]>",227,162);}
					if (mmhotkey == 2) {gfx_PrintStringXY("<[mode]>",232,162);}
					if (mmhotkey == 3) {gfx_PrintStringXY("<[del]>",243,162);}
			
	
			if (cursorposition == 4) {gfx_SetTextFGColor(selectedcolor); }
				else {gfx_SetTextFGColor(textcolor); }
				gfx_PrintStringXY("Enemy HP bar",145,177);
					if (drawhealth == 1) {gfx_PrintStringXY("<ON>",258,177); }
					if (drawhealth == 0) {gfx_PrintStringXY("<OFF>",250,177); }

			if (cursorposition == 5) {gfx_SetTextFGColor(selectedcolor); }
			else {gfx_SetTextFGColor(textcolor); }
				gfx_PrintStringXY("Damage Nums.",145,192);
					if (damagenumbers == 1) {gfx_PrintStringXY("<ON>",258,192); }
					if (damagenumbers == 0) {gfx_PrintStringXY("<OFF>",250,192); }

			if (cursorposition == 6) {gfx_SetTextFGColor(selectedcolor); }
			else {gfx_SetTextFGColor(textcolor); }
				gfx_PrintStringXY("[2nd] to SAVE",145,207);
		}
	
		gfx_SwapDraw();
		
	if (kb_Data[1] & kb_Window) {
		windowpress = 1;
	}
	if (kb_Data[7] & kb_Left) {
		if (optionspage == 1) {
			if (cursorposition == 1) {
				if (showminimap == 1) {
					showminimap = 0;
				}
				else if (showminimap == 0) {
					showminimap = 1;
				}
			}
			if (cursorposition == 2) {
				minimapposition =  (minimapposition - 1);
				if (minimapposition <= 0) {minimapposition = 4; }
			}
			if (cursorposition == 3) {
				mmhotkey++;
					if (mmhotkey > 3){
						mmhotkey = 0;
					}
			}
			if (cursorposition == 4) {
				if (drawhealth == 1) {
					drawhealth = 0;
				}
				else if (drawhealth == 0) {
					drawhealth = 1;
				}
			}
			if (cursorposition == 5) {
				if (damagenumbers == 1) {
					damagenumbers = 0;
				}
				else if (damagenumbers == 0) {
					damagenumbers = 1;
				}
			}
		}
	}
	if (kb_Data[7] & kb_Right) {
		if (optionspage == 1) {
			if (cursorposition == 1) {
				if (showminimap == 1) {
					showminimap = 0;
				}
				else if (showminimap == 0) {
					showminimap = 1;
				}
			}
			if (cursorposition == 2) {
				minimapposition =  (minimapposition + 1);
				if (minimapposition > 4) {minimapposition = 1; }
			}
			if (cursorposition == 3) {
				mmhotkey--;
					if (mmhotkey < 0){
						mmhotkey = 3;
					}
			}
			if (cursorposition == 4) {
				if (drawhealth == 1) {
					drawhealth = 0;
				}
				else if (drawhealth == 0) {
					drawhealth = 1;
				}
			}
			if (cursorposition == 5) {
				if (damagenumbers == 1) {
					damagenumbers = 0;
				}
				else if (damagenumbers == 0) {
					damagenumbers = 1;
				}
			}
		}
	}
	if (kb_Data[7] & kb_Down) {
		cursorposition++;
			if (cursorposition == 2) {
				if (showminimap == 0) {
					cursorposition = 3;
				}
			}
			if (cursorposition == 7) {
				cursorposition = 1;
			}
	}
	if (kb_Data[7] & kb_Up) {
		cursorposition = (cursorposition - 1);
			if (cursorposition == 2) {
				if (showminimap == 0) {
				cursorposition = 1;
				}
			}
			if (cursorposition == 0) {
				cursorposition = 6;
			}
	}
	if (kb_Data[1] & kb_2nd) {
		if (optionspage == 1){
			if (cursorposition == 6) {
				//drawsavemenu();
			}
		}
	}
keywait();
kb_SetMode(MODE_3_CONTINUOUS);
	} while (!(windowpress));
	kb_SetMode(MODE_3_CONTINUOUS);
}
void drawpouch(void){
int windowpress = 0;
int i_cursor_x = 14;
int i_cursor_y = 74;
int cursorcolor = redcolor;


do {
	gfx_SetDrawBuffer();
	gfx_FillScreen(submenucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,224);
	gfx_Rectangle(2,2,316,220);
	
	
	player_setup[0] = equipped[0];
	player_setup[1] = equipped[1];
	player_setup[2] = equipped[2];
	player_setup[3] = equipped[3];
	
	
	gfx_SetColor(submenucolor);
	submenubottombar();
	
	updateinventory();
	
	gfx_SetColor(cursorcolor);
	gfx_Rectangle(i_cursor_x,i_cursor_y,26,26);
	
	gfx_SwapDraw();
	
	
	windowpress = 0;

	
	
if (kb_Data[1] & kb_Window) {
	windowpress = 1;
}
	
if (kb_Data[7] & kb_Left){
	i_cursor_x = (i_cursor_x - tilespace);
}
if (kb_Data[7] & kb_Up){
	i_cursor_y = (i_cursor_y - tilespace);
}
if (kb_Data[7] & kb_Right){
	i_cursor_x = (i_cursor_x + tilespace);
}
if (kb_Data[7] & kb_Down){
	i_cursor_y = (i_cursor_y + tilespace);
}
	
if (kb_Data[1] & kb_2nd) {
	cursorcolor = selectedcolor;
}
else {
	cursorcolor = redcolor;
}
	
	
keywait();
kb_SetMode(MODE_3_CONTINUOUS);
	} while (!(windowpress));
kb_SetMode(MODE_3_CONTINUOUS);
}
void updateinventory(void){
	int i;
	int i_num = 0;
	int contents_num = 0;
	int inv_x = 17;
	int inv_y = 77;
	int i_tilex;
	int i_tiley;
	int columns = 0;
	int order = 0;
	gfx_UninitedSprite(i_tile,32,32);
	gfx_UninitedSprite(i_tile_alt,32,32);
	for(i = 0;i < 23;i++){
		if (purchased[i] != 0) {
			inventory[i].purchased = purchased[i];
			inventory[i].type = i;
			inventory[i].order = order;
			order++;
		}
	}
	for (i = 0;i < 23;i++){
		gfx_SetColor(0x00);
		gfx_FillRectangle(inv_x - 2,inv_y - 2,24,24);
		gfx_SetColor(0xAB);
		gfx_FillRectangle((inv_x),(inv_y),20,20);
		
		if (inventory[i].purchased != 0){
			if (inventory[i].order == contents_num){
				inv_contents[contents_num] = i;
				contents_num++;
				i_tilex = inv_x;
				i_tiley = inv_y;
				//resize and draw tile
				if (inventory[i].type == 0){
				i_tile = leather_helmet_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 1){
				i_tile = leather_chestplate_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley - 12;
			}
				if (inventory[i].type == 2){
				i_tile = leather_boots_down;
			}
				if (inventory[i].type == 3){
				i_tile = chain_helmet_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 4){
				i_tile = chain_chestplate_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley - 12;
			}
				if (inventory[i].type == 5){
				i_tile = chain_boots_down;
			}
				if (inventory[i].type == 6){
				i_tile = steel_helmet_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 7){
				i_tile = steel_chestplate_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley - 12;
			}
				if (inventory[i].type == 8){
				i_tile = steel_boots_down;
			}
				if (inventory[i].type == 9){
				i_tile = dragon_helmet_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 10){
				i_tile = dragon_chestplate_down;
				i_tilex = i_tilex - 6;
				i_tiley = i_tiley - 12;
			}
				if (inventory[i].type == 11){
				i_tile = dragon_boots_down;
			}
				if (inventory[i].type == 12){
				i_tile = club_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 13){
				i_tile = iron_sword_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 14){
				i_tile = steel_sword_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 15){
				i_tile = dragon_sword_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 16){
				i_tile = bow_basic_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 17){
				i_tile = bow_recurve_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 18){
				i_tile = bow_compound_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 19){
				i_tile = bow_dragon_inv;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 20){
				i_tile = potion_red;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 21){
				i_tile = potion_green;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				if (inventory[i].type == 22){
				i_tile = potion_purple;
				i_tilex = i_tilex + 2;
				i_tiley = i_tiley + 2;
			}
				//gfx_ScaleSprite(i_tile,i_tile_small);
				//i_tile_small = i_tile;
				gfx_TransparentSprite(i_tile,i_tilex,i_tiley);
			}
			
		}
		
		columns++;
		inv_x = (inv_x + tilespace);
		if (columns == 5){
			inv_y = (inv_y + tilespace);
			columns = 0;
			inv_x = 17;
		}
	}
}
void submenubottombar(void){
	gfx_SetColor(0x00);
	gfx_FillRectangle(0,224,320,16);
	gfx_SetTextFGColor(textcolor);
	gfx_PrintStringXY("[Close]",80,228);
}
void savegame(void) {
	//save player_setup to Appvar
}
void loadsave(void) {
	//load player_setup from Appvar
	mapstartx = player_setup[4];
	mapstarty = player_setup[5];
}
void newgame(void) {
	tmap_pxl_x_offset = mapstartx * 32;
	tmap_pxl_y_offset = mapstarty * 32;
	player_setup[6] = 100;
	player_setup[7] = 0;
	playerface = 4;
	for (i=0;i<23;i++){
		purchased[i] = 0;
	}
	drawhealth = 1;
	showminimap = 1;
	minimapposition = 1;
	num_p = 0;
	mmhotkey = 0;
	resetmoney();
	resetenemies();
	resetpots();
	
	resetrelics();
	resetbosses();
}
void playercreate(void) {
	int keypress;
	do{
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_HorizLine(0,223,320);
	gfx_HorizLine(0,221,320);
	gfx_SetTextTransparentColor(transcolor);
	gfx_SetTextFGColor(textcolor);
    gfx_SetTextBGColor(transcolor);
	gfx_SetTextScale(2,3);
	gfx_PrintStringXY("1.",40,20);
	gfx_PrintStringXY("2.",40,79);
	gfx_PrintStringXY("3.",40,137);
	gfx_PrintStringXY("4.",40,197);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("f(1-5) = change set, # = select item, del = back",8,227);
	gfx_SetTextFGColor(redcolor);
	gfx_PrintStringXY("This character is for Free Play only!",4,4);
		
	drawequipment();
	gfx_SetColor(0x00);
	draweditedplayer();
	gfx_SwapDraw();
		
		do {
			keypress = 0;
				if (kb_Data[1] & kb_Yequ) {
					(setnumber = 0);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Window) {
					(setnumber = 1);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Zoom) {
					(setnumber = 2);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Trace) {
					(setnumber = 3);
					keypress = 1;
					}
				else if (kb_Data[1] & kb_Graph) {
					(setnumber = 4);
					keypress = 1;
					}
			
				if (kb_Data[3] & kb_1){
					(player_setup[0] = setnumber);
					keypress = 1;
				}
				if (kb_Data[4] & kb_2) {
					(player_setup[1] = setnumber);
					keypress = 1;
				}
				if (kb_Data[5] & kb_3) {
					(player_setup[2] = setnumber);
					keypress = 1;
				}
				if (kb_Data[3] & kb_4) {
					(player_setup[3] = setnumber);
					keypress = 1;
				}
				if (kb_Data[1] & kb_Del) {keypress = 1;}
		}	while (keypress == 0);
		
	}	while (!(kb_Data[1] & kb_Del));
	
	(menuyes = 3);
}
void draweditedplayer(void) {
	gfx_FillRectangle(editpx,editpy + 2,((editscale * 32)-15),(editscale * 32));
	gfx_ScaledTransparentSprite_NoClip(player_naked_down,editpx,editpy,editscale,editscale);
	if (player_setup [0] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 1) {gfx_ScaledTransparentSprite_NoClip(leather_boots_down,editpx,editpy + (27 * editscale),editscale,editscale);}
	if (player_setup [3] == 1) {gfx_ScaledTransparentSprite_NoClip(club,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 2) {gfx_ScaledTransparentSprite_NoClip(chain_boots_down,editpx,editpy + (27 * editscale),editscale,editscale);}
	if (player_setup [3] == 2) {gfx_ScaledTransparentSprite_NoClip(iron_sword,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_boots_down,editpx,editpy + (27 * editscale),editscale,editscale);}
	if (player_setup [3] == 3) {gfx_ScaledTransparentSprite_NoClip(steel_sword,editweaponx,editweapony,editscale-1,editscale-1);}
	
	if (player_setup [0] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_helmet_down,editpx,editpy,editscale,editscale);}
	if (player_setup [1] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_chestplate_down,editpx,editpy,editscale,editscale);}
	if (player_setup [2] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_boots_down,editpx,editpy + (27 * editscale),editscale,editscale);}
	if (player_setup [3] == 4) {gfx_ScaledTransparentSprite_NoClip(dragon_sword,editweaponx,editweapony,editscale-1,editscale-1);}
}
void drawequipment(void) {
	gfx_SetColor(0x00);
	gfx_FillRectangle(65,12,96,208);
	if (setnumber == 1) {
		gfx_ScaledTransparentSprite_NoClip(leather_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(leather_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(leather_boots_down,50,142,3,3);
		gfx_ScaledTransparentSprite_NoClip(club,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 2) {
		gfx_ScaledTransparentSprite_NoClip(chain_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(chain_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(chain_boots_down,50,142,3,3);
		gfx_ScaledTransparentSprite_NoClip(iron_sword,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 3) {
		gfx_ScaledTransparentSprite_NoClip(steel_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_boots_down,50,142,3,3);
		gfx_ScaledTransparentSprite_NoClip(steel_sword,editweaponsmallx,editweaponsmally,2,2);
	}
	if (setnumber == 4) {
		gfx_ScaledTransparentSprite_NoClip(dragon_helmet_down,50,15,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_chestplate_down,50,25,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_boots_down,50,142,3,3);
		gfx_ScaledTransparentSprite_NoClip(dragon_sword,editweaponsmallx,editweaponsmally,2,2);
	}
}
void menubkgnd(void) {
	/*
	gfx_SetDrawBuffer();
	gfx_FillScreen(menucolor);
	gfx_SetColor(accentcolor);
	gfx_Rectangle(0,0,320,240);
	gfx_Rectangle(2,2,316,236);
	gfx_SwapDraw();
	*/
}
void resetenemies(void) {
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemy[i].type = defaultenemy_typelist[i];
		enemy[i].dead = 0;
		enemy[i].x = defaultenemy_xlist[i]*32;
		enemy[i].y = defaultenemy_ylist[i]*32;
		enemy[i].move = defaultenemy_movelist[i];
		enemy[i].health = ((enemy[i].type + 1) * 10);
		enemy[i].maxhealth = enemy[i].health;
	}
}
void resetmoney(void){
	for (i=0; i < NUM_POTS; i++) {
		money[i].moneydead = 1;
	}
}
void resetrelics(void) {
	for (i = 0; i < NUM_RELICS; i++) {
		relic[i].relicshow = 0;
		relic[i].relictaken = 0;
		relic[i].relicnumber = i;
	}
}
void resetbosses(void) {
	for (i = 0; i < NUM_BOSS; i++) {
		boss[i].boss_type = defaultboss_type[i];
		boss[i].boss_dead = 0;
		boss[i].boss_health = ((boss[i].boss_type + 1) * 100);
		boss[i].boss_relicnum = i;
		boss[i].b_x = defaultboss_xlist[i];
		boss[i].b_y = defaultboss_ylist[i];
	}
}
void updateenemies(void) {
	int randcheck = 20;
	for (ii = 0; ii < NUM_ENEMIES; ii++) {
		if ((enemy[ii].type) == 0) {enemySprite = slime_blue;}
		if ((enemy[ii].type) == 1) {enemySprite = slime_green;}
		if ((enemy[ii].type) == 2) {enemySprite = slime_red;}
		if ((enemy[ii].type) == 3) {enemySprite = bokoblin_light;}
		if ((enemy[ii].type) == 4) {enemySprite = bokoblin_dark;}
		if ((enemy[ii].type) == 5) {enemySprite = knight_green;}
		if ((enemy[ii].type) == 6) {enemySprite = knight_red;}
		
		//if within current screen view
		if (enemy[ii].health <= 0) {
			if (enemy[ii].dead == 0){
				enemy[ii].dead = 1;
			
				money[ii].m_x = enemy[ii].x;
				money[ii].m_y = enemy[ii].y;
				money[ii].moneydead = 0;
				money[ii].moneyvalue = 1;
				randcheck = 30;
				if (randcheck >= randInt(0,300)) {
					money[ii].moneyvalue = 5;
				}
				randcheck = 20;
				if (randcheck >= randInt(0,300)) {
					money[ii].moneyvalue = 10;
				}
				randcheck = 10;
				if (randcheck >= randInt(0,300)) {
					money[ii].moneyvalue = 20;
				}
				randcheck = 1;
				if (randcheck >= randInt(0,300)) {
					money[ii].moneyvalue = 100;
				}
			}
			
		}
		if ((enemy[ii].dead) == 0) {
			if (tmap_pxl_x_offset <= (enemy[ii].x)){
				if ((enemy[ii].x) <= (tmap_pxl_x_offset + 320)){
					if (tmap_pxl_y_offset <= (enemy[ii].y)) {
						if  ((enemy[ii].y) <= (tmap_pxl_y_offset + 240)) {
							if (enemy[ii].move == 1) {
								if (randcheck >= randInt(0,100)) {
									enemymove();
								}
							}
						}
						renderenemy(&enemy[ii]);
					}
				}
			}
		}		
	}
}
void renderenemy(enemy_t *enemy) {
		gfx_TransparentSprite(enemySprite, enemy->x - tmap_pxl_x_offset, enemy->y - tmap_pxl_y_offset); 
		if (drawhealth == 1) {
			gfx_SetColor(redcolor);
			//enemyHPbarlength = (((100/enemy->maxhealth)*enemy->health/10)*3);
			enemyHPbarlength =  (lifebar_maxlen * enemy->health) / enemy->maxhealth;
			//thank you Iambian for this algorithm
			gfx_FillRectangle((enemy->x - tmap_pxl_x_offset)+1, (enemy->y - tmap_pxl_y_offset)-4,enemyHPbarlength,3);
			
			//gfx_SetTextFGColor(0x3C);
			//gfx_SetTextXY(enemy->x - tmap_pxl_x_offset, enemy->y - tmap_pxl_y_offset);
			//gfx_PrintUInt(enemy->health,2);
		}	
	/*
		if (drawhealth == 1) {
			gfx_SetTextXY(enemy->x - tmap_pxl_x_offset, enemy->y - tmap_pxl_y_offset);
			gfx_PrintUInt(enemy->health,2);
		}
	*/
	
		/*only for debug
		gfx_PrintString("---");
		gfx_PrintUInt((enemy->x)/32,3);
		gfx_PrintString("-");
		gfx_PrintUInt((enemy->y)/32,3);
		*/
	
		enemyattack();
	}
