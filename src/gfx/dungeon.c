// convpng v7.1
#include <stdint.h>
#include "dungeon.h"

#include <fileioc.h>
uint8_t *dungeon[88] = {
 (uint8_t*)0,
 (uint8_t*)1026,
 (uint8_t*)2052,
 (uint8_t*)3078,
 (uint8_t*)4104,
 (uint8_t*)4266,
 (uint8_t*)4428,
 (uint8_t*)4590,
 (uint8_t*)5616,
 (uint8_t*)6642,
 (uint8_t*)7668,
 (uint8_t*)8022,
 (uint8_t*)8376,
 (uint8_t*)8730,
 (uint8_t*)8892,
 (uint8_t*)9054,
 (uint8_t*)9216,
 (uint8_t*)10242,
 (uint8_t*)11268,
 (uint8_t*)12294,
 (uint8_t*)12808,
 (uint8_t*)13322,
 (uint8_t*)13836,
 (uint8_t*)13998,
 (uint8_t*)14160,
 (uint8_t*)14322,
 (uint8_t*)15348,
 (uint8_t*)16374,
 (uint8_t*)17400,
 (uint8_t*)17946,
 (uint8_t*)18492,
 (uint8_t*)19038,
 (uint8_t*)20064,
 (uint8_t*)20322,
 (uint8_t*)20484,
 (uint8_t*)20646,
 (uint8_t*)20808,
 (uint8_t*)21834,
 (uint8_t*)22860,
 (uint8_t*)23886,
 (uint8_t*)24400,
 (uint8_t*)24914,
 (uint8_t*)25428,
 (uint8_t*)26454,
 (uint8_t*)26712,
 (uint8_t*)27738,
 (uint8_t*)28764,
 (uint8_t*)29022,
 (uint8_t*)30048,
 (uint8_t*)30306,
 (uint8_t*)31332,
 (uint8_t*)31558,
 (uint8_t*)31816,
 (uint8_t*)32042,
 (uint8_t*)32300,
 (uint8_t*)32526,
 (uint8_t*)32784,
 (uint8_t*)33010,
 (uint8_t*)33268,
 (uint8_t*)33526,
 (uint8_t*)33784,
 (uint8_t*)34042,
 (uint8_t*)35068,
 (uint8_t*)36094,
 (uint8_t*)36950,
 (uint8_t*)37806,
 (uint8_t*)38832,
 (uint8_t*)39858,
 (uint8_t*)40884,
 (uint8_t*)41910,
 (uint8_t*)42936,
 (uint8_t*)43962,
 (uint8_t*)44988,
 (uint8_t*)46014,
 (uint8_t*)46176,
 (uint8_t*)46203,
 (uint8_t*)47229,
 (uint8_t*)48255,
 (uint8_t*)49281,
 (uint8_t*)50307,
 (uint8_t*)51333,
 (uint8_t*)52359,
 (uint8_t*)52386,
 (uint8_t*)52413,
 (uint8_t*)52440,
 (uint8_t*)52467,
 (uint8_t*)52533,
 (uint8_t*)52599,
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
