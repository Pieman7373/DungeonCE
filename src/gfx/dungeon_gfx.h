// Converted using ConvPNG
// This file contains all the graphics sources for easier inclusion in a project
#ifndef __dungeon_gfx__
#define __dungeon_gfx__
#include <stdint.h>

#define dungeon_gfx_transparent_color_index 0

#define optionsmenu_width 171
#define optionsmenu_height 90
#define optionsmenu_size 15392
extern uint8_t optionsmenu_data[15392];
#define optionsmenu ((gfx_sprite_t*)optionsmenu_data)
#define editmenunumbers_width 24
#define editmenunumbers_height 200
#define editmenunumbers_size 4802
extern uint8_t editmenunumbers_data[4802];
#define editmenunumbers ((gfx_sprite_t*)editmenunumbers_data)
#define mainmenulogo_width 253
#define mainmenulogo_height 90
#define mainmenulogo_size 22772
extern uint8_t mainmenulogo_data[22772];
#define mainmenulogo ((gfx_sprite_t*)mainmenulogo_data)
#define menuwords_width 100
#define menuwords_height 50
#define menuwords_size 5002
extern uint8_t menuwords_data[5002];
#define menuwords ((gfx_sprite_t*)menuwords_data)
#define sizeof_dungeon_gfx_pal 512
extern uint16_t dungeon_gfx_pal[256];

#endif
