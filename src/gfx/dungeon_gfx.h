// convpng v7.1
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __dungeon_gfx__
#define __dungeon_gfx__
#include <stdint.h>

#define dungeon_gfx_transparent_color_index 0

#define mainmenulogo_width 127
#define mainmenulogo_height 45
#define mainmenulogo_size 5717
extern uint8_t mainmenulogo_data[5717];
#define mainmenulogo ((gfx_sprite_t*)mainmenulogo_data)
#define knight_green_width 32
#define knight_green_height 32
#define knight_green_size 1026
extern uint8_t knight_green_data[1026];
#define knight_green ((gfx_sprite_t*)knight_green_data)
#define knight_red_width 32
#define knight_red_height 32
#define knight_red_size 1026
extern uint8_t knight_red_data[1026];
#define knight_red ((gfx_sprite_t*)knight_red_data)
#define sizeof_dungeon_gfx_pal 512
extern uint16_t dungeon_gfx_pal[256];

#endif
