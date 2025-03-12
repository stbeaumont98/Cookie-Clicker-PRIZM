#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

static struct Upgrade upgrades[716] = {
    [0] = {1.0E2, false, false, "Reinforced index finger", "The mouse and cursors are twice as efficient.", 2},
    [1] = {5.0E2, false, false, "Carpal tunnel prevention cream", "The mouse and cursors are twice as efficient.", 2},
    [2] = {1.0E4, false, false, "Ambidextrous", "The mouse and cursors are twice as efficient.", 2},
    [3] = {1.0E5, false, false, "Thousand fingers", "The mouse and cursors gain +0.1 cookies for each non-cursor object\nowned.", 2},
    [4] = {1.0E7, false, false, "Million fingers", "Multiplies the gain from Thousand fingers by 5.", 5},
    [5] = {1.0E8, false, false, "Billion fingers", "Multiplies the gain from Thousand fingers by 10.", 10},
    [6] = {1.0E9, false, false, "Trillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20},
    [7] = {1.0E3, false, false, "Forwards from grandma", "Grandmas are twice as efficient", 2},
    [8] = {5.0E3, false, false, "Steel-plated rolling pins", "Grandmas are twice as efficient", 2},
    [9] = {5.0E4, false, false, "Lubricated dentures", "Grandmas are twice as efficient", 2},
    [10] = {1.1E4, false, false, "Cheap hoes", "Farms are twice as efficient", 2},
    [11] = {5.5E4, false, false, "Fertilizer", "Farms are twice as efficient", 2},
    [12] = {5.5E5, false, false, "Cookie trees", "Farms are twice as efficient", 2}
};

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades);

#endif