#ifndef STRUCTS_H
#define STRUCTS_H

#define NUM_ENEMIES  50
#define TYPE         
#define DEAD         
#define X			 
#define Y            
#define HEALTH	
typedef struct enemy {
	uint8_t type;
	int dead;
	uint24_t x; 
	uint24_t y; 
	int health;
} enemy_t;


#define NUM_POTS  50
#define POTTYPE         
#define POTDEAD
#define P_X
#define P_Y  
typedef struct pots { 
	uint8_t pottype;
	int potdead;
	uint24_t p_x; 
	uint24_t p_y; 
} pots_t;

#endif