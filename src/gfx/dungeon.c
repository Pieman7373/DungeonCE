// Converted using ConvPNG
#include <stdint.h>
#include "dungeon.h"

#include <fileioc.h>
uint8_t *dungeon[56] = {
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
 (uint8_t*)0,
};

bool dungeon_init(void) {
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("dungeon", "r");
    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)dungeon[0];
    for (i = 0; i < dungeon_num; i++) {
        dungeon[i] += data;
    }

    ti_CloseAll();

    return (bool)appvar;
}
