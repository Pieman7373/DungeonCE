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
uint16_t defaultenemy_movelist[NUM_ENEMIES] = {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint16_t defaultenemy_typelist[NUM_ENEMIES] = {0,1,2,3,4,5,6,2,2,2,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6};
uint16_t defaultenemy_xlist[NUM_ENEMIES] = {76,76,76,77,77,78,78,106,107,107,106,15,52,53,54,55,56,57,58,52,53,54,55,56,57,58,25,26,27,28,29,30,31};
uint16_t defaultenemy_ylist[NUM_ENEMIES] = {90,91,92,90,91,90,91,74,75,74,75,93,81,81,81,81,81,81,81,82,82,82,82,82,82,82,65,65,65,65,65,65,65};


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
uint16_t default_pottypelist[NUM_POTS];
//{0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}
uint16_t default_potxlist[NUM_POTS] = {77,78,106,107,14,15,16,14,15,16,52,53,54,55,56,57,58,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
uint16_t default_potylist[NUM_POTS] = {97,97,76,76,91,91,91,92,92,92,80,80,80,80,80,80,80,  71,71,71,71,71,71,71,71,71,71,71,71,71,71,72,72,72,72,72,72,72,72,72,72,72,72,72,72,73,73,73,73,73,73,73,73,73,73,73,73,73,73,74,74,74,74,74,74,74,74,74,74,74,74,74,74,75,75,75,75,75,75,75,75,75,75,75,75,75,75}; 

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

#endif