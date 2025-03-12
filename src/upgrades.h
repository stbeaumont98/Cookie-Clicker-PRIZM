#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

#define MODE_MULTIPLY 0
#define MODE_ADD 1
#define MODE_MODIFY 2

static struct Upgrade upgrades[716] = {
    [0] = {1.0E2, false, false, "Reinforced index finger", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR},
    [1] = {5.0E2, false, false, "Carpal tunnel prevention cream", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR},
    [2] = {1.0E4, false, false, "Ambidextrous", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR},
    [3] = {1.0E5, false, false, "Thousand fingers", "The mouse and cursors gain +0.1 cookies for each non-cursor object\nowned.", 0.1, MODE_ADD, BUILDING_CURSOR},
    [4] = {1.0E7, false, false, "Million fingers", "Multiplies the gain from Thousand fingers by 5.", 5, MODE_MODIFY, BUILDING_CURSOR},
    [5] = {1.0E8, false, false, "Billion fingers", "Multiplies the gain from Thousand fingers by 10.", 10, MODE_MODIFY, BUILDING_CURSOR},
    [6] = {1.0E9, false, false, "Trillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [7] = {1.0E3, false, false, "Forwards from grandma", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [8] = {5.0E3, false, false, "Steel-plated rolling pins", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [9] = {5.0E4, false, false, "Lubricated dentures", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [10] = {1.1E4, false, false, "Cheap hoes", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM},
    [11] = {5.5E4, false, false, "Fertilizer", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM},
    [12] = {5.5E5, false, false, "Cookie trees", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM}
};

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades);
void enable_upgrade(struct CookieData *data, int id);

#endif