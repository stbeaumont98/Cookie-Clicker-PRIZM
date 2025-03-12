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
    [43] = {1.0E10, false, false, "Quadrillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [82] = {1.0E13, false, false, "Quintillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [109] = {1.0E16, false, false, "Sextillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [188] = {1.0E19, false, false, "Septillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [189] = {1.0E22, false, false, "Octillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [660] = {1.0E25, false, false, "Nonillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [764] = {1.0E28, false, false, "Decillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},
    [873] = {1.0E31, false, false, "Undecillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR},

    [7] = {1.0E3, false, false, "Forwards from grandma", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [8] = {5.0E3, false, false, "Steel-plated rolling pins", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [9] = {5.0E4, false, false, "Lubricated dentures", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [44] = {5.0E6, false, false, "Prune juice", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [110] = {5.0E8, false, false, "Double-thick glasses", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [192] = {5.0E10, false, false, "Aging agents", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [294] = {5.0E13, false, false, "Xtreme walkers", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [307] = {5.0E16, false, false, "The Unbridling", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [428] = {5.0E19, false, false, "Reverse dementia", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [480] = {5.0E22, false, false, "Timeproof hair dyes", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [506] = {5.0E25, false, false, "Good manners", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [662] = {5.0E28, false, false, "Generation degeneration", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [700] = {5.0E31, false, false, "Visits", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [743] = {5.0E34, false, false, "Kitchen cabinets", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},
    [840] = {5.0E37, false, false, "Foam-tipped canes", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA},

    [10] = {1.1E4, false, false, "Cheap hoes", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM},
    [11] = {5.5E4, false, false, "Fertilizer", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM},
    [12] = {5.5E5, false, false, "Cookie trees", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM},

    [13] = {1.3E6, false, false, "Sturdier conveyor belts", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY},
    [14] = {6.5E6, false, false, "Child labor", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY},
    [15] = {6.5E7, false, false, "Sweatshop", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY},

    [16] = {1.2E5, false, false, "Sugar gas", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE},
    [17] = {6.0E5, false, false, "Megadrill", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE},
    [18] = {6.0E6, false, false, "Ultradrill", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE},

    [19] = {5.1E10, false, false, "Vanilla nebulae", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT},
    [20] = {2.55E11, false, false, "Wormholes", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT},
    [21] = {2.55E12, false, false, "Frequent flyer", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT},

    [22] = {7.5E11, false, false, "Antimony", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB},
    [23] = {3.75E12, false, false, "Essence of dough", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB},
    [24] = {3.75E13, false, false, "True chocolate", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB},
    
    [25] = {1.0E13, false, false, "Ancient tablet", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL},
    [26] = {5.0E13, false, false, "Insane oatling workers", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL},
    [27] = {5.0E14, false, false, "Soul bond", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL},
    
    [28] = {1.0E13, false, false, "Flux capacitors", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE},
    [29] = {5.0E13, false, false, "Time paradox resolver", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE},
    [30] = {5.0E14, false, false, "Quantum conundrum", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE},
};

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades);
void enable_upgrade(struct CookieData *data, int id);

#endif