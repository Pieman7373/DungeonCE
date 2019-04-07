// Converted using ConvPNG
// This file contains all the graphics sources for easier inclusion in a project
#ifndef __dungeon__
#define __dungeon__
#include <stdint.h>

#include <stdbool.h>

#define dungeon_num 56

extern uint8_t *dungeon[56];
#define player_naked_down ((gfx_sprite_t*)dungeon[0])
#define player_naked_up ((gfx_sprite_t*)dungeon[1])
#define player_naked_left ((gfx_sprite_t*)dungeon[2])
#define player_naked_right ((gfx_sprite_t*)dungeon[3])
#define leather_helmet_down ((gfx_sprite_t*)dungeon[4])
#define leather_helmet_up ((gfx_sprite_t*)dungeon[5])
#define leather_helmet_left ((gfx_sprite_t*)dungeon[6])
#define leather_helmet_right ((gfx_sprite_t*)dungeon[7])
#define chain_helmet_down ((gfx_sprite_t*)dungeon[8])
#define chain_helmet_up ((gfx_sprite_t*)dungeon[9])
#define chain_helmet_left ((gfx_sprite_t*)dungeon[10])
#define chain_helmet_right ((gfx_sprite_t*)dungeon[11])
#define steel_helmet_down ((gfx_sprite_t*)dungeon[12])
#define steel_helmet_up ((gfx_sprite_t*)dungeon[13])
#define steel_helmet_left ((gfx_sprite_t*)dungeon[14])
#define steel_helmet_right ((gfx_sprite_t*)dungeon[15])
#define dragon_helmet_down ((gfx_sprite_t*)dungeon[16])
#define dragon_helmet_up ((gfx_sprite_t*)dungeon[17])
#define dragon_helmet_left ((gfx_sprite_t*)dungeon[18])
#define dragon_helmet_right ((gfx_sprite_t*)dungeon[19])
#define leather_chestplate_down ((gfx_sprite_t*)dungeon[20])
#define leather_chestplate_up ((gfx_sprite_t*)dungeon[21])
#define leather_chestplate_left ((gfx_sprite_t*)dungeon[22])
#define leather_chestplate_right ((gfx_sprite_t*)dungeon[23])
#define chain_chestplate_down ((gfx_sprite_t*)dungeon[24])
#define chain_chestplate_up ((gfx_sprite_t*)dungeon[25])
#define chain_chestplate_left ((gfx_sprite_t*)dungeon[26])
#define chain_chestplate_right ((gfx_sprite_t*)dungeon[27])
#define steel_chestplate_down ((gfx_sprite_t*)dungeon[28])
#define steel_chestplate_up ((gfx_sprite_t*)dungeon[29])
#define steel_chestplate_left ((gfx_sprite_t*)dungeon[30])
#define steel_chestplate_right ((gfx_sprite_t*)dungeon[31])
#define dragon_chestplate_down ((gfx_sprite_t*)dungeon[32])
#define dragon_chestplate_up ((gfx_sprite_t*)dungeon[33])
#define dragon_chestplate_left ((gfx_sprite_t*)dungeon[34])
#define dragon_chestplate_right ((gfx_sprite_t*)dungeon[35])
#define leather_boots_down ((gfx_sprite_t*)dungeon[36])
#define leather_boots_up ((gfx_sprite_t*)dungeon[37])
#define leather_boots_left ((gfx_sprite_t*)dungeon[38])
#define leather_boots_right ((gfx_sprite_t*)dungeon[39])
#define chain_boots_down ((gfx_sprite_t*)dungeon[40])
#define chain_boots_up ((gfx_sprite_t*)dungeon[41])
#define chain_boots_left ((gfx_sprite_t*)dungeon[42])
#define chain_boots_right ((gfx_sprite_t*)dungeon[43])
#define steel_boots_down ((gfx_sprite_t*)dungeon[44])
#define steel_boots_up ((gfx_sprite_t*)dungeon[45])
#define steel_boots_left ((gfx_sprite_t*)dungeon[46])
#define steel_boots_right ((gfx_sprite_t*)dungeon[47])
#define dragon_boots_down ((gfx_sprite_t*)dungeon[48])
#define dragon_boots_up ((gfx_sprite_t*)dungeon[49])
#define dragon_boots_left ((gfx_sprite_t*)dungeon[50])
#define dragon_boots_right ((gfx_sprite_t*)dungeon[51])
#define club ((gfx_sprite_t*)dungeon[52])
#define iron_sword ((gfx_sprite_t*)dungeon[53])
#define steel_sword ((gfx_sprite_t*)dungeon[54])
#define dragon_sword ((gfx_sprite_t*)dungeon[55])
bool dungeon_init(void);

#endif
