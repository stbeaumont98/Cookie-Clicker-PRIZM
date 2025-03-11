#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

static const struct Upgrade upgrades[716] = {
    [0] = {1.0E2, true, false, "Reinforced index finger", "The mouse and cursors are twice as efficient.", 2},
    [1] = {5.0E2, false, false, "Carpal tunnel prevention cream", "The mouse and cursors are twice as efficient.", 2},
    [2] = {1.0E4, false, false, "Ambidextrous", "The mouse and cursors are twice as efficient.", 2},
    [3] = {1.0E5, false, false, "Thousand fingers", "The mouse and cursors gain +0.1 cookies for each non-cursor object owned.", 2},
    [4] = {1.0E7, false, false, "Million fingers", "Multiplies the gain from Thousand fingers by 5.", 2},
    [5] = {1.0E8, false, false, "Billion fingers", "Multiplies the gain from Thousand fingers by 10.", 2},
    [6] = {1.0E9, false, false, "Trillion fingers", "Multiplies the gain from Thousand fingers by 20.", 2}
};

#endif