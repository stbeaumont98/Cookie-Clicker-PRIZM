#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

#define MODE_MULTIPLY 0
#define MODE_ADD 1
#define MODE_MODIFY 2

static struct Upgrade upgrades[] = {
    {1.0E2, false, false, "Reinforced index finger", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR, cursor_0, cursor_pal},
    {5.0E2, false, false, "Carpal tunnel prevention cream", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR, cursor_1, tier_1},
    {1.0E4, false, false, "Ambidextrous", "The mouse and cursors are twice as efficient.", 2, MODE_MULTIPLY, BUILDING_CURSOR, cursor_1, tier_2},
    {1.0E5, false, false, "Thousand fingers", "The mouse and cursors gain +0.1 cookies for each non-cursor\nobject owned.", 0.1, MODE_ADD, BUILDING_CURSOR, NULL, NULL},
    {1.0E7, false, false, "Million fingers", "Multiplies the gain from Thousand fingers by 5.", 5, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E8, false, false, "Billion fingers", "Multiplies the gain from Thousand fingers by 10.", 10, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E9, false, false, "Trillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E10, false, false, "Quadrillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E13, false, false, "Quintillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E16, false, false, "Sextillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E19, false, false, "Septillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E22, false, false, "Octillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E25, false, false, "Nonillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E28, false, false, "Decillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},
    {1.0E31, false, false, "Undecillion fingers", "Multiplies the gain from Thousand fingers by 20.", 20, MODE_MODIFY, BUILDING_CURSOR, NULL, NULL},

    {1.0E3, false, false, "Forwards from grandma", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E3, false, false, "Steel-plated rolling pins", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E4, false, false, "Lubricated dentures", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E6, false, false, "Prune juice", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E8, false, false, "Double-thick glasses", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E10, false, false, "Aging agents", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E13, false, false, "Xtreme walkers", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E16, false, false, "The Unbridling", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E19, false, false, "Reverse dementia", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E22, false, false, "Timeproof hair dyes", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E25, false, false, "Good manners", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E28, false, false, "Generation degeneration", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E31, false, false, "Visits", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E34, false, false, "Kitchen cabinets", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},
    {5.0E37, false, false, "Foam-tipped canes", "Grandmas are twice as efficient", 2, MODE_MULTIPLY, BUILDING_GRANDMA, NULL, NULL},

    {1.1E4, false, false, "Cheap hoes", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E4, false, false, "Fertilizer", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E5, false, false, "Cookie trees", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E7, false, false, "Genetically-modified cookies", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E9, false, false, "Gingerbread scarecrows", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E11, false, false, "Pulsar sprinklers", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E14, false, false, "Fudge fungus", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E17, false, false, "Wheat triffids", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E20, false, false, "Humane pesticides", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E23, false, false, "Barnstars", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E27, false, false, "Lindworms", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E31, false, false, "Global seed vault", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E34, false, false, "Reverse-veganism", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E39, false, false, "Cookie mulch", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},
    {5.5E43, false, false, "Self-driving tractors", "Farms are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FARM, NULL, NULL},

    {1.2E5, false, false, "Sugar gas", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E5, false, false, "Megadrill", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E6, false, false, "Ultradrill", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E8, false, false, "Ultimadrill", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E10, false, false, "H-bomb mining", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E12, false, false, "Coreforge", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E15, false, false, "Planetsplitters", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E18, false, false, "Canola oil wells", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E21, false, false, "Mole people", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E24, false, false, "Mine canaries", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E28, false, false, "Bore again", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E32, false, false, "Air mining", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E36, false, false, "Caramel alloys", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E40, false, false, "Delicious mineralogy", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},
    {6.0E44, false, false, "Mineshaft supports", "Mines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_MINE, NULL, NULL},

    {1.3E6, false, false, "Sturdier conveyor belts", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E6, false, false, "Child labor", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E7, false, false, "Sweatshop", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E9, false, false, "Radium reactors", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E11, false, false, "Recombobulators", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E13, false, false, "Deep-bake process", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E16, false, false, "Cyborg workforce", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E19, false, false, "78-hour days", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E22, false, false, "Machine learning", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E25, false, false, "Brownie point system", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E29, false, false, "\"Volunteer\" interns", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E33, false, false, "Behavioral reframing", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E37, false, false, "The infinity engine", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E41, false, false, "N-dimensional assembly lines", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},
    {6.5E45, false, false, "Universal automation", "Factories are twice as efficient", 2, MODE_MULTIPLY, BUILDING_FACTORY, NULL, NULL},

    {1.4E7, false, false, "Taller tellers", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E7, false, false, "Scissor-resistant credit cards", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E8, false, false, "Acid-proof vaults", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E10, false, false, "Chocolate coins", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E12, false, false, "Exponential interest rates", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E14, false, false, "Financial zen", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E17, false, false, "Way of the wallet", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E20, false, false, "The stuff rationale", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E23, false, false, "Edible money", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E26, false, false, "Grand supercycle", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E30, false, false, "Rules of aquisition", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E34, false, false, "Altruistic loop", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E38, false, false, "Diminishing tax returns", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E42, false, false, "Cookie Points", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},
    {7.0E46, false, false, "The big shortcake", "Banks are twice as efficient", 2, MODE_MULTIPLY, BUILDING_BANK, NULL, NULL},

    {2.0E8,  false, false, "Golden idols", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E9,  false, false, "Sacrifices", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E10, false, false, "Delicious blessing", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E12, false, false, "Sun festival", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E14, false, false, "Enlarged pantheon", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E16, false, false, "Great Baker in the sky", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E19, false, false, "Creation myth", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E22, false, false, "Theocracy", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E25, false, false, "Sick rap prayers", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E28, false, false, "Psalm-reading", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E32, false, false, "War of the gods", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E36, false, false, "A novel idea", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E40, false, false, "Apparitions", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E44, false, false, "Negatheism", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},
    {1.0E48, false, false, "Temple traps", "Temples are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TEMPLE, NULL, NULL},

    {5.1E10, false, false, "Vanilla nebulae", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT, NULL, NULL},
    {2.55E11, false, false, "Wormholes", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT, NULL, NULL},
    {2.55E12, false, false, "Frequent flyer", "Shipments are twice as efficient", 2, MODE_MULTIPLY, BUILDING_SHIPMENT, NULL, NULL},

    {7.5E11, false, false, "Antimony", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB, NULL, NULL},
    {3.75E12, false, false, "Essence of dough", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB, NULL, NULL},
    {3.75E13, false, false, "True chocolate", "Alchemy labs are twice as efficient", 2, MODE_MULTIPLY, BUILDING_ALCHEMY_LAB, NULL, NULL},
    
    {1.0E13, false, false, "Ancient tablet", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL, NULL, NULL},
    {5.0E13, false, false, "Insane oatling workers", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL, NULL, NULL},
    {5.0E14, false, false, "Soul bond", "Portals are twice as efficient", 2, MODE_MULTIPLY, BUILDING_PORTAL, NULL, NULL},
    
    {1.0E13, false, false, "Flux capacitors", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE, NULL, NULL},
    {5.0E13, false, false, "Time paradox resolver", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE, NULL, NULL},
    {5.0E14, false, false, "Quantum conundrum", "Time machines are twice as efficient", 2, MODE_MULTIPLY, BUILDING_TIME_MACHINE, NULL, NULL}
};

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades);
void enable_upgrade(struct CookieData *data, int id);

#endif