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


#define NUM_RELICS  5
#define RELICNUMBER
#define RELICSHOW
#define RELICTAKEN
#define R_X
#define R_Y
typedef struct relic {
	int relicnumber;
	int relicshow;
	int relictaken;
	uint24_t r_x;
	uint24_t r_y;
} relic_t;
	

#define NUM_BOSS  3
#define BOSS_TYPE
#define BOSS_DEAD
#define BOSS_HEALTH
#define BOSS_RELICNUM
#define B_X
#define B_Y
typedef struct boss {
	int boss_type;
	int boss_dead;
	int boss_health;
	int boss_relicnum;
	uint24_t b_x;
	uint24_t b_y;
} boss_t;

#endif