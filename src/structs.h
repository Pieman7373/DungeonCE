#include <stdint.h>

#ifndef STRUCTS_H
#define STRUCTS_H


#define NUM_ENEMIES  100
#define TYPE         
#define DEAD         
#define X			 
#define Y            
#define HEALTH
#define MAXHEALTH
#define MOVE
typedef struct enemy {
	uint8_t type;
	int dead;
	uint24_t x; 
	uint24_t y; 
	int health;
	int maxhealth;
	int move;
} enemy_t;
extern enemy_t enemy[];



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
extern pots_t pots[];


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
extern money_t money[];


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
extern relic_t relic[];

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
extern boss_t boss[];

#define PURCHASED
#define TYPE
#define ORDER
typedef struct inventory {
	int purchased;
	int type;
	int order;
}inv_t;
extern inv_t inventory[];

#define P_TYPE
#define P_ALIVE
#define P_DIRECTION
#define P_SPEED
#define P_VX
#define P_VY
#define P_X
#define P_Y
typedef struct projectile {
	int p_type;
	int p_alive;
	int p_direction;
	int p_speed;
	int p_vx;
	int p_vy;
	int p_x;
	int p_y;
} projectile_t;
extern projectile_t projectile[];

#endif