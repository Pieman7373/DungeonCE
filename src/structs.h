#ifndef STRUCTS_H
#define STRUCTS_H


#define NUM_ENEMIES  100
#define TYPE         
#define DEAD         
#define X			 
#define Y            
#define HEALTH
#define MOVE
typedef struct enemy {
	uint8_t type;
	int dead;
	uint24_t x; 
	uint24_t y; 
	int health;
	int move;
} enemy_t;



#define NUM_POTS  100
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


#define MONEYVALUE
#define MONEYDEAD
#define M_X
#define M_Y
typedef struct money {
	uint8_t moneyvalue;
	int moneydead;
	uint24_t m_x;
	uint24_t m_y;
} money_t;

#define RELICNUMBER
#define RELICTAKEN
#define R_X
#define R_Y
typedef struct relic {
	int relicnumber;
	int relictaken;
	uint24_t r_x;
	uint24_t r_y;
} relic_t;
	

#endif