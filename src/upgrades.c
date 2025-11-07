#include <stddef.h>
#include <stdlib.h>
#include "types.h"

#include "upgrades.h"

char *upgrade_types[23] = {
	"Cursor", "Mouse", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple", 
	"Wizard tower", "Shipment", "Alchemy lab", "Portal", "Time machine", 
    "Antimatter condenser", "Prism", "Chancemaker", "Fractal engine", "Javascript console", 
    "Idleverse", "Cortex baker", "You", "Golden cookie", "Flavored cookies"
};

char *upgrade_descriptions[21] = {
	"", "", "Grandmas are twice as efficient.", "Farms are twice as efficient.", 
    "Mines are twice as efficient.", "Factorys are twice as efficient.", 
    "Banks are twice as efficient.", "Temples are twice as efficient.", 
	"Wizard towers are twice as efficient.", 
    "Shipments are twice as efficient.", 
    "Alchemy labs are twice as efficient.", "Portals are twice as efficient.", 
	"Time machines are twice as efficient.", 
    "Antimatter condensers are twice as efficient.", 
    "Prisms are twice as efficient.", "Chancemakers are twice as efficient.", 
	"Fractal engines are twice as efficient.", 
    "Javascript consoles are twice as efficient.", 
    "Idleverses are twice as efficient.", 
    "Cortex bakers are twice as efficient.", "You are twice as efficient."
};

char *grandma_descriptions[21] = {
    "", "", "", "Grandmas are twice as efficient.\nFarms gain +1% CpS per grandma.", 
    "Grandmas are twice as efficient.\nMines gain +1% CpS per 2 grandmas.", 
    "Grandmas are twice as efficient.\nFactories gain +1% CpS per 3 grandmas.", 
    "Grandmas are twice as efficient.\nBanks gain +1% CpS per 4 grandmas.", 
    "Grandmas are twice as efficient.\nTemples gain +1% CpS per 5 grandmas.", 
    "Grandmas are twice as efficient.\nWizard towers gain +1% CpS per 6 grandmas.", 
    "Grandmas are twice as efficient.\nShipments gain +1% CpS per 7 grandmas.", 
    "Grandmas are twice as efficient.\nAlchemy labs gain +1% CpS per 8 grandmas.", 
    "Grandmas are twice as efficient.\nPortals gain +1% CpS per 9 grandmas.", 
    "Grandmas are twice as efficient.\nTime machines gain +1% CpS per 10 grandmas.", 
    "Grandmas are twice as efficient.\nAntimatter condensers gain +1% CpS per 11 grandmas.", 
    "Grandmas are twice as efficient.\nPrisms gain +1% CpS per 12 grandmas.", 
    "Grandmas are twice as efficient.\nChancemakers gain +1% CpS per 13 grandmas.", 
    "Grandmas are twice as efficient.\nFractal engines gain +1% CpS per 14 grandmas.", 
    "Grandmas are twice as efficient.\nJavascript consoles gain +1% CpS per 15 grandmas.", 
    "Grandmas are twice as efficient.\nIdleverses gain +1% CpS per 16 grandmas.", 
    "Grandmas are twice as efficient.\nCortex bakers gain +1% CpS per 17 grandmas.", 
    "Grandmas are twice as efficient.\nYou gain +1% CpS per 18 grandmas."
};

const struct Upgrade upgrades[] = {
    // cursors
    {0, 1.0E2,   "Reinforced index finger", cursor[0], cursor_pal},
    {1, 5.0E2,   "Carpal tunnel prevention cream", cursor[1], tier[1]},
    {2, 1.0E4,   "Ambidextrous", cursor[1], tier[2]},
    {3, 1.0E5,   "Thousand fingers", cursor[2], tier[3]},
    {4, 1.0E7,   "Million fingers", cursor[2], tier[4]},
    {5, 1.0E8,   "Billion fingers", cursor[3], tier[5]},
    {6, 1.0E9,   "Trillion fingers", cursor[4], tier[6]},
    {7, 1.0E10,  "Quadrillion fingers", cursor[4], tier[7]},
    {8, 1.0E13,  "Quintillion fingers", cursor[2], tier[8]},
    {9, 1.0E16,  "Sextillion fingers", cursor[2], tier[9]},
    {10, 1.0E19,  "Septillion fingers", cursor[5], tier[10]},
    {11, 1.0E22,  "Octillion fingers", cursor[5], tier[11]},
    {12, 1.0E25,  "Nonillion fingers", cursor[6], tier[12]},
    {13, 1.0E28,  "Decillion fingers", cursor[7], tier[13]},
    {14, 1.0E31,  "Undecillion fingers", cursor[7], tier[14]},   // 14
    
    // mouse
    {15, 5.0E4, "Plastic mouse", mouse[0], cursor_pal},
    {16, 5.0E6, "Iron mouse", mouse[1], tier[1]},
    {17, 5.0E8, "Titanium mouse", mouse[1], tier[2]},
    {18, 5.0E10, "Adamantium mouse", mouse[2], tier[3]},
    {19, 5.0E12, "Unobtainium mouse", mouse[2], tier[4]},
    {20, 5.0E14, "Eludium mouse", mouse[3], tier[5]},
    {21, 5.0E16, "Wishalloy mouse", mouse[4], tier[6]},
    {22, 5.0E18, "Fantasteel mouse", mouse[4], tier[7]},
    {23, 5.0E20, "Nevercrack mouse", mouse[2], tier[8]},
    {24, 5.0E22, "Armythril mouse", mouse[2], tier[9]},
    {25, 5.0E24, "Technobsidian mouse", mouse[5], tier[10]},
    {26, 5.0E26, "Plasmarble mouse", mouse[5], tier[11]},
    {27, 5.0E28, "Miraculite mouse", mouse[6], tier[12]},
    {28, 5.0E30, "Aetherice mouse", mouse[7], tier[13]},
    {29, 5.0E32, "Omniplast mouse", mouse[7], tier[14]},        // 29

    // grandmas
    {30, 1.0E3,   "Forwards from grandma", grandma[0], grandma_pal},
    {31, 5.0E3,   "Steel-plated rolling pins", grandma[1], tier[1]},
    {32, 5.0E4,   "Lubricated dentures", grandma[1], tier[2]},
    {33, 5.0E6,   "Prune juice", grandma[2], tier[3]},
    {34, 5.0E8,   "Double-thick glasses", grandma[2], tier[4]},
    {35, 5.0E10,  "Aging agents", grandma[3], tier[5]},
    {36, 5.0E13,  "Xtreme walkers", grandma[4], tier[6]},
    {37, 5.0E16,  "The Unbridling", grandma[4], tier[7]},
    {38, 5.0E19,  "Reverse dementia", grandma[2], tier[8]},
    {39, 5.0E22,  "Timeproof hair dyes", grandma[2], tier[9]},
    {40, 5.0E26,  "Good manners", grandma[5], tier[10]},
    {41, 5.0E30,  "Generation degeneration", grandma[5], tier[11]},
    {42, 5.0E34,  "Visits", grandma[6], tier[12]},
    {43, 5.0E38,  "Kitchen cabinets", grandma[7], tier[13]},
    {44, 5.0E42,  "Foam-tipped canes", grandma[7], tier[14]},     // 44

    // farms
    {45, 1.1E4,   "Cheap hoes", farm[0], farm_pal},
    {46, 5.5E4,   "Fertilizer", farm[1], tier[1]},
    {47, 5.5E5,   "Cookie trees", farm[1], tier[2]},
    {48, 5.5E7,   "Genetically-modified\ncookies", farm[2], tier[3]},
    {49, 5.5E9,   "Gingerbread scarecrows", farm[2], tier[4]},
    {50, 5.5E11,  "Pulsar sprinklers", farm[3], tier[5]},
    {51, 5.5E14,  "Fudge fungus", farm[4], tier[6]},
    {52, 5.5E17,  "Wheat triffids", farm[4], tier[7]},
    {53, 5.5E20,  "Humane pesticides", farm[2], tier[8]},
    {54, 5.5E23,  "Barnstars", farm[2], tier[9]},
    {55, 5.5E27,  "Lindworms", farm[5], tier[10]},
    {56, 5.5E31,  "Global seed vault", farm[5], tier[11]},
    {57, 5.5E35,  "Reverse-veganism", farm[6], tier[12]},
    {58, 5.5E39,  "Cookie mulch", farm[7], tier[13]},
    {59, 5.5E43,  "Self-driving tractors", farm[7], tier[14]},
    {60, 5.5E4,   "Farmer grandmas", gma, gma_pal},       // 60

    //mines
    {61, 1.2E5,   "Sugar gas", mine[0], mine_pal},
    {62, 6.0E5,   "Megadrill", mine[1], tier[1]},
    {63, 6.0E6,   "Ultradrill", mine[1], tier[2]},
    {64, 6.0E8,   "Ultimadrill", mine[2], tier[3]},
    {65, 6.0E10,  "H-bomb mining", mine[2], tier[4]},
    {66, 6.0E12,  "Coreforge", mine[3], tier[5]},
    {67, 6.0E15,  "Planetsplitters", mine[4], tier[6]},
    {68, 6.0E18,  "Canola oil wells", mine[4], tier[7]},
    {69, 6.0E21,  "Mole people", mine[2], tier[8]},
    {70, 6.0E24,  "Mine canaries", mine[2], tier[9]},
    {71, 6.0E28,  "Bore again", mine[5], tier[10]},
    {72, 6.0E32,  "Air mining", mine[5], tier[11]},
    {73, 6.0E36,  "Caramel alloys", mine[6], tier[12]},
    {74, 6.0E40,  "Delicious mineralogy", mine[7], tier[13]},
    {75, 6.0E44,  "Mineshaft supports", mine[7], tier[14]},
    {76, 6.0E5,   "Miner grandmas", gma, gma_pal},        // 76

    // factories
    {77, 1.3E6,   "Sturdier conveyor belts", factory[0], factory_pal},
    {78, 6.5E6,   "Child labor", factory[1], tier[1]},
    {79, 6.5E7,   "Sweatshop", factory[1], tier[2]},
    {80, 6.5E9,   "Radium reactors", factory[2], tier[3]},
    {81, 6.5E11,  "Recombobulators", factory[2], tier[4]},
    {82, 6.5E13,  "Deep-bake process", factory[3], tier[5]},
    {83, 6.5E16,  "Cyborg workforce", factory[4], tier[6]},
    {84, 6.5E19,  "78-hour days", factory[4], tier[7]},
    {85, 6.5E22,  "Machine learning", factory[2], tier[8]},
    {86, 6.5E25,  "Brownie point system", factory[2], tier[9]},
    {87, 6.5E29,  "\"Volunteer\" interns", factory[5], tier[10]},
    {88, 6.5E33,  "Behavioral reframing", factory[5], tier[11]},
    {89, 6.5E37,  "The infinity engine", factory[6], tier[12]},
    {90, 6.5E41,  "N-dimensional assembly\nlines", factory[7], tier[13]},
    {91, 6.5E45,  "Universal automation", factory[7], tier[14]},
    {92, 6.5E6,   "Worker grandmas", gma, gma_pal},       // 92

    // banks
    {93, 1.4E7,   "Taller tellers", bank[0], bank_pal},
    {94, 7.0E7,   "Scissor-resistant credit\ncards", bank[1], tier[1]},
    {95, 7.0E8,   "Acid-proof vaults", bank[1], tier[2]},
    {96, 7.0E10,  "Chocolate coins", bank[2], tier[3]},
    {97, 7.0E12,  "Exponential interest rates", bank[2], tier[4]},
    {98, 7.0E14,  "Financial zen", bank[3], tier[5]},
    {99, 7.0E17,  "Way of the wallet", bank[4], tier[6]},
    {100, 7.0E20,  "The stuff rationale", bank[4], tier[7]},
    {101, 7.0E23,  "Edible money", bank[2], tier[8]},
    {102, 7.0E26,  "Grand supercycle", bank[2], tier[9]},
    {103, 7.0E30,  "Rules of aquisition", bank[5], tier[10]},
    {104, 7.0E34,  "Altruistic loop", bank[5], tier[11]},
    {105, 7.0E38,  "Diminishing tax returns", bank[6], tier[12]},
    {106, 7.0E42,  "Cookie Points", bank[7], tier[13]},
    {107, 7.0E46,  "The big shortcake", bank[7], tier[14]},
    {108, 7.0E7,   "Banker grandmas", gma, gma_pal},       // 108

    // temples
    {109, 2.0E8,   "Golden idols", temple[0], temple_pal},
    {110, 1.0E9,   "Sacrifices", temple[1], tier[1]},
    {111, 1.0E10,  "Delicious blessing", temple[1], tier[2]},
    {112, 1.0E12,  "Sun festival", temple[2], tier[3]},
    {113, 1.0E14,  "Enlarged pantheon", temple[2], tier[4]},
    {114, 1.0E16,  "Great Baker in the sky", temple[3], tier[5]},
    {115, 1.0E19,  "Creation myth", temple[4], tier[6]},
    {116, 1.0E22,  "Theocracy", temple[4], tier[7]},
    {117, 1.0E25,  "Sick rap prayers", temple[2], tier[8]},
    {118, 1.0E28,  "Psalm-reading", temple[2], tier[9]},
    {119, 1.0E32,  "War of the gods", temple[5], tier[10]},
    {120, 1.0E36,  "A novel idea", temple[5], tier[11]},
    {121, 1.0E40,  "Apparitions", temple[6], tier[12]},
    {122, 1.0E44,  "Negatheism", temple[7], tier[13]},
    {123, 1.0E48,  "Temple traps", temple[7], tier[14]},
    {124, 1.0E9,   "Priestess grandmas", gma, gma_pal},    // 124

    // wizard towers
    {125, 3.3E9,   "Pointier hats", wizard[0], wizard_pal},
    {126, 1.65E10, "Beardlier beards", wizard[1], tier[1]},
    {127, 1.65E11, "Ancient grimoires", wizard[1], tier[2]},
    {128, 1.65E13, "Kitchen curses", wizard[2], tier[3]},
    {129, 1.65E15, "School of sorcery", wizard[2], tier[4]},
    {130, 1.65E17, "Dark formulas", wizard[3], tier[5]},
    {131, 1.65E20, "Cookiemancy", wizard[4], tier[6]},
    {132, 1.65E23, "Rabbit trick", wizard[4], tier[7]},
    {133, 1.65E26, "Deluxe tailored wands", wizard[2], tier[8]},
    {134, 1.65E29, "Immobile spellcasting", wizard[2], tier[9]},
    {135, 1.65E33, "Electricity", wizard[5], tier[10]},
    {136, 1.65E37, "Spelling bees", wizard[5], tier[11]},
    {137, 1.65E41, "Wizard basements", wizard[6], tier[12]},
    {138, 1.65E45, "Magical realism", wizard[7], tier[13]},
    {139, 1.65E49, "Polymorphism", wizard[7], tier[14]},
    {140, 1.65E10, "Witch grandmas", gma, gma_pal},        // 140

    // shipments
    {141, 5.1E10,  "Vanilla nebulae", shipment[0], shipment_pal},
    {142, 2.55E11, "Wormholes", shipment[1], tier[1]},
    {143, 2.55E12, "Frequent flyer", shipment[1], tier[2]},
    {144, 2.55E14, "Warp drive", shipment[2], tier[3]},
    {145, 2.55E16, "Chocolate monoliths", shipment[2], tier[4]},
    {146, 2.55E18, "Generation ship", shipment[3], tier[5]},
    {147, 2.55E21, "Dyson sphere", shipment[4], tier[6]},
    {148, 2.55E24, "The final frontier", shipment[4], tier[7]},
    {149, 2.55E27, "Autopilot", shipment[2], tier[8]},
    {150, 2.55E30, "Restaurants at the end of\nthe universe", shipment[2], tier[9]},
    {151, 2.55E34, "Universal alphabet", shipment[5], tier[10]},
    {152, 2.55E38, "Toroid universe", shipment[5], tier[11]},
    {153, 2.55E42, "Prime directive", shipment[6], tier[12]},
    {154, 2.55E46, "Cosmic foreground\nradiation", shipment[7], tier[13]},
    {155, 2.55E50, "At your doorstep in 30\nminutes or your money back", shipment[7], tier[14]},
    {156, 2.55E11, "Cosmic grandmas", gma, gma_pal},       // 156

    // alchemy labs
    {157, 7.5E11,  "Antimony", alchemy[0], alchemy_pal},
    {158, 3.75E12, "Essence of dough", alchemy[1], tier[1]},
    {159, 3.75E13, "True chocolate", alchemy[1], tier[2]},
    {160, 3.75E15, "Ambrosia", alchemy[2], tier[3]},
    {161, 3.75E17, "Aqua crustulae", alchemy[2], tier[4]},
    {162, 3.75E19, "Origin crucible", alchemy[3], tier[5]},
    {163, 3.75E22, "Theory of atomic fluidity", alchemy[4], tier[6]},
    {164, 3.75E25, "Beige goo", alchemy[4], tier[7]},
    {165, 3.75E28, "The advent of chemistry", alchemy[2], tier[8]},
    {166, 3.75E31, "On second thought", alchemy[2], tier[9]},
    {167, 3.75E35, "Public betterment", alchemy[5], tier[10]},
    {168, 3.75E39, "Hermetic reconciliation", alchemy[5], tier[11]},
    {169, 3.75E43, "Chromatic cycling", alchemy[6], tier[12]},
    {170, 3.75E47, "Arcanized glassware", alchemy[7], tier[13]},
    {171, 3.75E51, "The dose makes the poison", alchemy[7], tier[14]},
    {172, 3.75E12, "Transmuted grandmas", gma, gma_pal},   // 172

    // portals
    {173, 1.0E13,  "Ancient tablet", portal[0], portal_pal},
    {174, 5.0E13,  "Insane oatling workers", portal[1], tier[1]},
    {175, 5.0E14,  "Soul bond", portal[1], tier[2]},
    {176, 5.0E16,  "Sanity dance", portal[2], tier[3]},
    {177, 5.0E18,  "Brane transplant", portal[2], tier[4]},
    {178, 5.0E20,  "Deity-sized portals", portal[3], tier[5]},
    {179, 5.0E23,  "End of times back-up plan", portal[4], tier[6]},
    {180, 5.0E26,  "Madedening chants", portal[4], tier[7]},
    {181, 5.0E29,  "The real world", portal[2], tier[8]},
    {182, 5.0E32,  "Dimensional garbage gulper", portal[2], tier[9]},
    {183, 5.0E36,  "Embedded microportals", portal[5], tier[10]},
    {184, 5.0E40,  "His advent", portal[5], tier[11]},
    {185, 5.0E44,  "Domestic rifts", portal[6], tier[12]},
    {186, 5.0E48,  "Portal guns", portal[7], tier[13]},
    {187, 5.0E52,  "A way home", portal[7], tier[14]},
    {188, 5.0E13,  "Altered grandmas", gma, gma_pal},      // 188

    // time machines
    {189, 1.4E14,  "Flux capacitors", time[0], time_pal},
    {190, 7.0E14,  "Time paradox resolver", time[1], tier[1]},
    {191, 7.0E15,  "Quantum conundrum", time[1], tier[2]},
    {192, 7.0E17,  "Causality enforcer", time[2], tier[3]},
    {193, 7.0E19,  "Yestermorrow comparators", time[2], tier[4]},
    {194, 7.0E21,  "Far future enactment", time[3], tier[5]},
    {195, 7.0E24,  "Great loop hypothesis", time[4], tier[6]},
    {196, 7.0E27,  "Cookietopian moments of\nmaybe", time[4], tier[7]},
    {197, 7.0E30,  "Second seconds", time[2], tier[8]},
    {198, 7.0E33,  "Additional clock hands", time[2], tier[9]},
    {199, 7.0E37,  "Nostalgia", time[5], tier[10]},
    {200, 7.0E41,  "Split seconds", time[5], tier[11]},
    {201, 7.0E45,  "Patience abolished", time[6], tier[12]},
    {202, 7.0E49,  "Timeproof upholstery", time[7], tier[13]},
    {203, 7.0E53,  "Rectifying a mistake", time[7], tier[14]},
    {204, 7.0E14,  "Grandmas\' grandmas", gma, gma_pal},   // 204

    // antimatter condensers
    {205, 1.7E15,  "Sugar bosons", antimatter[0], antimatter_pal},
    {206, 8.5E15,  "String theory", antimatter[1], tier[1]},
    {207, 8.5E16,  "Large macaron collider", antimatter[1], tier[2]},
    {208, 8.5E18,  "Big bang bake", antimatter[2], tier[3]},
    {209, 8.5E20,  "Reverse cyclotrons", antimatter[2], tier[4]},
    {210, 8.5E22,  "Nanocosmics", antimatter[3], tier[5]},
    {211, 8.5E25,  "The Pulse", antimatter[4], tier[6]},
    {212, 8.5E28,  "Some other super-tiny\nfundamental particle? Probably?", antimatter[4], tier[7]},
    {213, 8.5E31,  "Quantum comb", antimatter[2], tier[8]},
    {214, 8.5E34,  "Baking Nobel prize", antimatter[2], tier[9]},
    {215, 8.5E38,  "The definite molecule", antimatter[5], tier[10]},
    {216, 8.5E42,  "Flavor itself", antimatter[5], tier[11]},
    {217, 8.5E46,  "Delicious pull", antimatter[6], tier[12]},
    {218, 8.5E50,  "Employee minification", antimatter[7], tier[13]},
    {219, 8.5E54,  "Candied atoms", antimatter[7], tier[14]},
    {220, 8.5E15,  "Antigrandmas", gma, gma_pal},          // 220

    // prisms
    {221, 2.1E16,  "Gem polish", prism[0], prism_pal},
    {222, 1.05E17, "9th color", prism[1], tier[1]},
    {223, 1.05E18, "Chocolate light", prism[1], tier[2]},
    {224, 1.05E20, "Grainbow", prism[2], tier[3]},
    {225, 1.05E22, "Pure cosmic light", prism[2], tier[4]},
    {226, 1.05E24, "Glow-in-the-dark", prism[3], tier[5]},
    {227, 1.05E27, "Lux sanctorum", prism[4], tier[6]},
    {228, 1.05E30, "Reverse shadows", prism[4], tier[7]},
    {229, 1.05E33, "Crystal mirrors", prism[2], tier[8]},
    {230, 1.05E36, "Reverse theory of light", prism[2], tier[9]},
    {231, 1.05E40, "Light capture measures", prism[5], tier[10]},
    {232, 1.05E44, "Light speed limit", prism[5], tier[11]},
    {233, 1.05E48, "Occam's laser", prism[6], tier[12]},
    {234, 1.05E52, "Hyperblack paint", prism[7], tier[13]},
    {235, 1.05E56, "Lab goggles but like cool\nshades", prism[7], tier[14]},
    {236, 1.05E17, "Rainbow grandmas", gma, gma_pal},      // 236

    // chancemakers
    {237, 2.6E17,  "Your lucky cookie", chancemaker[0], chancemaker_pal},
    {238, 1.3E18,  "\"All Bets Are Off\" magic coin", chancemaker[1], tier[1]},
    {239, 1.3E19,  "Winning lottery ticket", chancemaker[1], tier[2]},
    {240, 1.3E21,  "Four-leaf clover field", chancemaker[2], tier[3]},
    {241, 1.3E23,  "A recipe book about books", chancemaker[2], tier[4]},
    {242, 1.3E25,  "Leprechaun village", chancemaker[3], tier[5]},
    {243, 1.3E28,  "Improbability drive", chancemaker[4], tier[6]},
    {244, 1.3E31,  "Antisuperstistronics", chancemaker[4], tier[7]},
    {245, 1.3E34,  "Bunnypedes", chancemaker[2], tier[8]},
    {246, 1.3E37,  "Revised probabilistics", chancemaker[2], tier[9]},
    {247, 1.3E41,  "0-sided dice", chancemaker[5], tier[10]},
    {248, 1.3E45,  "A touch of determinism", chancemaker[5], tier[11]},
    {249, 1.3E49,  "On a streak", chancemaker[6], tier[12]},
    {250, 1.3E53,  "Silver lining maximization", chancemaker[7], tier[13]},
    {251, 1.3E57,  "Gambler's fallacy fallacy", chancemaker[7], tier[14]},
    {252, 1.3E18,  "Lucky grandmas", gma, gma_pal},        // 252

    // fractal engines
    {253, 3.1E18,  "Metabakeries", fractal[0], fractal_pal},
    {254, 1.55E19, "Mandelbrown sugar", fractal[1], tier[1]},
    {255, 1.55E20, "Fractoids", fractal[1], tier[2]},
    {256, 1.55E22, "Nested universe theory", fractal[2], tier[3]},
    {257, 1.55E24, "Menger sponge cake", fractal[2], tier[4]},
    {258, 1.55E26, "One particularly good-\nhumored cow", fractal[3], tier[5]},
    {259, 1.55E29, "Chocolate ouroboros", fractal[4], tier[6]},
    {260, 1.55E32, "Nested", fractal[4], tier[7]},
    {261, 1.55E35, "Space-filling fibers", fractal[2], tier[8]},
    {262, 1.55E38, "Endless book of prose", fractal[2], tier[9]},
    {263, 1.55E42, "The set of all sets", fractal[5], tier[10]},
    {264, 1.55E46, "This upgrade", fractal[5], tier[11]},
    {265, 1.55E50, "A box", fractal[6], tier[12]},
    {266, 1.55E54, "Multiscale profiling", fractal[7], tier[13]},
    {267, 1.55E58, "The more they stay the\nsame", fractal[7], tier[14]},
    {268, 1.55E19, "Metagrandmas", gma, gma_pal},          // 268

    // javascript consoles
    {269, 7.1E20,  "The JavaScript console for\ndummies", javascript[0], javascript_pal},
    {270, 3.55E21, "64bit arrays", javascript[1], tier[1]},
    {271, 3.55E22, "Stack overflow", javascript[1], tier[2]},
    {272, 3.55E24, "Enterprise compiler", javascript[2], tier[3]},
    {273, 3.55E26, "Syntactic sugar", javascript[2], tier[4]},
    {274, 3.55E28, "A nice cup of coffee", javascript[3], tier[5]},
    {275, 3.55E31, "Just-in-time baking", javascript[4], tier[6]},
    {276, 3.55E34, "cookies++", javascript[4], tier[7]},
    {277, 3.55E37, "Software updates", javascript[2], tier[8]},
    {278, 3.55E40, "Game.Loop", javascript[2], tier[9]},
    {279, 3.55E44, "eval()", javascript[5], tier[10]},
    {280, 3.55E48, "Your biggest fans", javascript[5], tier[11]},
    {281, 3.55E52, "Hacker shades", javascript[6], tier[12]},
    {282, 3.55E56, "PHP containment vats", javascript[7], tier[13]},
    {283, 3.55E60, "Simulation failsafes", javascript[7], tier[14]},
    {284, 3.55E21, "Binary grandmas", gma, gma_pal},       // 284

    // idleverses
    {285, 1.2E23,  "Manifest destiny", idleverse[0], idleverse_pal},
    {286, 6.0E23,  "The multiverse in a\nnutshell", idleverse[1], tier[1]},
    {287, 6.0E24,  "All-conversion", idleverse[1], tier[2]},
    {288, 6.0E26,  "Multiverse agents", idleverse[2], tier[3]},
    {289, 6.0E28,  "Escape plan", idleverse[2], tier[4]},
    {290, 6.0E30,  "Game design", idleverse[3], tier[5]},
    {291, 6.0E33,  "Sandbox universes", idleverse[4], tier[6]},
    {292, 6.0E36,  "Multiverse wars", idleverse[4], tier[7]},
    {293, 6.0E39,  "Mobile ports", idleverse[2], tier[8]},
    {294, 6.0E42,  "Encapsulated realities", idleverse[2], tier[9]},
    {295, 6.0E46,  "Extrinsic clicking", idleverse[5], tier[10]},
    {296, 6.0E50,  "Universal idling", idleverse[5], tier[11]},
    {297, 6.0E54,  "Break the fifth wall", idleverse[6], tier[12]},
    {298, 6.0E58,  "Opposite universe", idleverse[7], tier[13]},
    {299, 6.0E62,  "The other routes to Rome", idleverse[7], tier[14]},
    {300, 6.0E23,  "Alternate grandmas", gma, gma_pal},    // 300

    // cortex bakers
    {301, 1.9E25,  "Principled neural shackles", cortex[0], cortex_pal},
    {302, 9.5E25,  "Obey", cortex[1], tier[1]},
    {303, 9.5E26,  "A sprinkle of irrationality", cortex[1], tier[2]},
    {304, 9.5E28,  "Front and back hemispheres", cortex[2], tier[3]},
    {305, 9.5E30,  "Neural networking", cortex[2], tier[4]},
    {306, 9.5E32,  "Cosmic brainstorms", cortex[3], tier[5]},
    {307, 9.5E35,  "Megatherapy", cortex[4], tier[6]},
    {308, 9.5E38,  "Synaptic lubricant", cortex[4], tier[7]},
    {309, 9.5E41,  "Psychokinesis", cortex[2], tier[8]},
    {310, 9.5E44,  "Spines", cortex[2], tier[9]},
    {311, 9.5E48,  "Neuraforming", cortex[5], tier[10]},
    {312, 9.5E52,  "Epistemological trickery", cortex[5], tier[11]},
    {313, 9.5E56,  "Every possible idea", cortex[6], tier[12]},
    {314, 9.5E60,  "The land of dreams", cortex[7], tier[13]},
    {315, 9.5E64,  "Intellectual property theft", cortex[7], tier[14]},
    {316, 9.5E25,  "Brainy grandmas", gma, gma_pal},       // 316

    // you
    {317, 5.4E27,  "Cloning vats", you[0], you_pal},
    {318, 2.7E28,  "Energized nutrients", you[1], tier[1]},
    {319, 2.7E29,  "Stunt doubles", you[1], tier[2]},
    {320, 2.7E31,  "Clone recycling plant", you[2], tier[3]},
    {321, 2.7E33,  "Free-range clones", you[2], tier[4]},
    {322, 2.7E35,  "Genetic tailoring", you[3], tier[5]},
    {323, 2.7E38,  "Power in diversity", you[4], tier[6]},
    {324, 2.7E41,  "Self-betterment", you[4], tier[7]},
    {325, 2.7E44,  "Source control", you[2], tier[8]},
    {326, 2.7E47,  "United workforce", you[2], tier[9]},
    {327, 2.7E51,  "Safety patrols", you[5], tier[10]},
    {328, 2.7E55,  "Clone rights", you[5], tier[11]},
    {329, 2.7E59,  "One big family", you[6], tier[12]},
    {330, 2.7E63,  "Fine-tuned body plans", you[7], tier[13]},
    {331, 2.7E67,  "Reading your clones bedtime\nstories", you[7], tier[14]},
    {332, 2.7E28,  "Clone grandmas", gma, gma_pal},        // 332

    // golden cookies
    {333, 7.77778E8, "Lucky day", golden, golden_pal},
    {334, 7.77778E10, "Serendipity", golden, golden_pal},
    {335, 7.77778E13, "Get lucky", golden, golden_pal},          // 335

    // flavored cookies
    {336, 9.99999E5, "Plain cookies", cookie[0], cookie_pal[0]},
    {337, 5.0E6, "Sugar cookies", cookie[1], cookie_pal[1]},
    {338, 1.0E7, "Oatmeal raisin cookies", cookie[2], cookie_pal[2]},
    {339, 5.0E7, "Peanut butter cookies", cookie[3], cookie_pal[3]},
    {340, 1.0E8, "Coconut cookies", cookie[4], cookie_pal[4]},
    {341, 1.0E8, "Macadamia nut cookies", cookie[5], cookie_pal[5]},
    {342, 1.0E8, "Almond cookies", cookie[6], cookie_pal[6]},
    {343, 1.0E8, "Hazelnut cookies", cookie[7], cookie_pal[7]},
    {344, 1.0E8, "Walnut cookies", cookie[8], cookie_pal[8]},
    {345, 1.0E8, "Cashew cookies", cookie[9], cookie_pal[9]},
    {346, 5.0E8, "White chocolate cookies", cookie[10], cookie_pal[10]},
    {347, 5.0E8, "Milk chocolate cookies", cookie[11], cookie_pal[11]},
    {348, 5.0E9, "Double-chip cookies", cookie[12], cookie_pal[12]},
    {349, 1.0E10, "White chocolate macadamia\nnut cookies", cookie[13], cookie_pal[13]},
    {350, 5.0E10, "All-chocolate cookies", cookie[14], cookie_pal[14]},
    {351, 1.0E11, "Dark chocolate-coated\ncookies", cookie[15], cookie_pal[15]},
    {352, 1.0E11, "White chocolate-coated\ncookies", cookie[16], cookie_pal[16]},
    {353, 5.0E11, "Eclipse cookies", cookie[17], cookie_pal[17]},
    {354, 1.0E12, "Zebra cookies", cookie[18], cookie_pal[18]},
    {355, 5.0E12, "Snickerdoodles", cookie[19], cookie_pal[19]},
    {356, 1.0E13, "Stroopwafels", cookie[20], cookie_pal[20]},
    {357, 5.0E13, "Macaroons", cookie[21], cookie_pal[21]},
    {358, 1.0E14, "Empire biscuits", cookie[22], cookie_pal[22]},
    {359, 5.0E14, "Madeleines", cookie[23], cookie_pal[23]},
    {360, 5.0E14, "Palmiers", cookie[24], cookie_pal[24]},
    {361, 1.0E15, "Palets", cookie[25], cookie_pal[25]},
    {362, 1.0E15, "Sabl`s", cookie[26], cookie_pal[26]},
    {363, 1.0E16, "Gingerbread men", cookie[27], cookie_pal[27]},
    {364, 1.0E16, "Gingerbread trees", cookie[28], cookie_pal[28]},
    {365, 5.0E16, "Pure black chocolate\ncookies", cookie[29], cookie_pal[29]},
    {366, 5.0E16, "Pure white chocolate\ncookies", cookie[30], cookie_pal[30]},
    {367, 1.0E17, "Ladyfingers", cookie[31], cookie_pal[31]},
    {368, 5.0E17, "Tuiles", cookie[32], cookie_pal[32]},
    {369, 1.0E18, "Chocolate-stuffed biscuits", cookie[33], cookie_pal[33]},
    {370, 5.0E18, "Checker cookies", cookie[34], cookie_pal[34]},
    {371, 1.0E19, "Butter cookies", cookie[35], cookie_pal[35]},
    {372, 5.0E19, "Cream cookies", cookie[36], cookie_pal[36]},
    {373, 1.0E20, "Gingersnaps", cookie[37], cookie_pal[37]},
    {374, 5.0E20, "Cinnamon cookies", cookie[38], cookie_pal[38]},
    {375, 1.0E21, "Vanity cookies", cookie[39], cookie_pal[39]},
    {376, 5.0E21, "Cigars", cookie[40], cookie_pal[40]},
    {377, 1.0E22, "Pinwheel cookies", cookie[41], cookie_pal[41]},
    {378, 5.0E22, "Fudge squares", cookie[42], cookie_pal[42]},
    {379, 1.0E23, "Shortbread biscuits", cookie[43], cookie_pal[43]},
    {380, 5.0E23, "Millionaires' shortbreads", cookie[44], cookie_pal[44]},
    {381, 1.0E24, "Caramel cookies", cookie[45], cookie_pal[45]},
    {382, 5.0E24, "Pecan sandies", cookie[46], cookie_pal[46]},
    {383, 1.0E25, "Moravian spice cookies", cookie[47], cookie_pal[47]},
    {384, 5.0E25, "Anzac biscuits", cookie[48], cookie_pal[48]},
    {385, 1.0E26, "Buttercakes", cookie[49], cookie_pal[49]},
    {386, 5.0E26, "Ice cream sandwiches", cookie[50], cookie_pal[50]},
    {387, 1.0E27, "Pink biscuits", cookie[51], cookie_pal[51]},
    {388, 5.0E27, "Whole grain cookies", cookie[52], cookie_pal[52]},
    {389, 1.0E28, "Candy cookies", cookie[53], cookie_pal[53]},
    {390, 5.0E28, "Big chip cookies", cookie[54], cookie_pal[54]},
    {391, 1.0E29, "One chip cookies", cookie[55], cookie_pal[55]},
    {392, 5.0E29, "Sprinkles cookies", cookie[56], cookie_pal[56]},
    {393, 1.0E30, "Peanut butter blossoms", cookie[57], cookie_pal[57]},
    {394, 5.0E30, "No-bake cookies", cookie[58], cookie_pal[58]},
    {395, 1.0E31, "Florentines", cookie[59], cookie_pal[59]},
    {396, 5.0E31, "Chocolate crinkles", cookie[60], cookie_pal[60]},
    {397, 1.0E32, "Maple cookies", cookie[61], cookie_pal[61]},
    {398, 5.0E32, "Persian rice cookies", cookie[62], cookie_pal[62]},
    {399, 1.0E33, "Norwegian cookies", cookie[63], cookie_pal[63]},
    {400, 5.0E33, "Crispy rice cookies", cookie[64], cookie_pal[64]},
    {401, 1.0E34, "Ube cookies", cookie[65], cookie_pal[65]},
    {402, 5.0E34, "Butterscotch cookies", cookie[66], cookie_pal[66]},
    {403, 1.0E35, "Speculaas", cookie[67], cookie_pal[67]},
    {404, 5.0E35, "Chocolate oatmeal cookies", cookie[68], cookie_pal[68]},
    {405, 1.0E36, "Molasses cookies", cookie[69], cookie_pal[69]},
    {406, 5.0E36, "Biscotti", cookie[70], cookie_pal[70]},
    {407, 1.0E37, "Waffle cookies", cookie[71], cookie_pal[71]},
    {408, 5.0E37, "Custard creams", cookie[72], cookie_pal[72]},
    {409, 1.0E38, "Bourbon biscuits", cookie[73], cookie_pal[73]},
    {410, 5.0E38, "Mini-cookies", cookie[74], cookie_pal[74]},
    {411, 1.0E39, "Whoopie pies", cookie[75], cookie_pal[75]},
    {412, 3.162E39, "Caramel wafer biscuits", cookie[76], cookie_pal[76]},
    {413, 1.0E40, "Chocolate chip mocha cookies", cookie[77], cookie_pal[77]},
    {414, 3.1622E40, "Earl Grey cookies", cookie[78], cookie_pal[78]},
    {415, 3.1622E40, "Chai tea cookies", cookie[79], cookie_pal[79]},
    {416, 1.0E41, "Corn syrup cookies", cookie[80], cookie_pal[80]},
    {417, 3.16227E41, "Icebox cookies", cookie[81], cookie_pal[81]},
    {418, 1.0E42, "Graham crackers", cookie[82], cookie_pal[82]},
    {419, 3.162E42, "Hardtack", cookie[83], cookie_pal[83]},
    {420, 1.0E43, "Cornflake cookies", cookie[84], cookie_pal[84]},
    {421, 3.1622E43, "Tofu cookies", cookie[85], cookie_pal[85]},
    {422, 3.1622E43, "Gluten-free cookies", cookie[86], cookie_pal[86]},
    {423, 1.0E44, "Russian bread cookies", cookie[87], cookie_pal[87]},
    {424, 3.16227E44, "Lebkuchen", cookie[88], cookie_pal[88]},
    {425, 1.0E45, "Aachener Printen", cookie[89], cookie_pal[89]},
    {426, 3.162E45, "Canistrelli", cookie[90], cookie_pal[90]},
    {427, 1.0E46, "Nice biscuits", cookie[91], cookie_pal[91]},
    {428, 3.1622E46, "French pure butter\ncookies", cookie[92], cookie_pal[92]},
    {429, 3.1622E46, "Petit beurre", cookie[93], cookie_pal[93]},
    {430, 1.0E47, "Nanaimo bars", cookie[94], cookie_pal[94]},
    {431, 3.16227E47, "Berger cookies", cookie[95], cookie_pal[95]},
    {432, 1.0E48, "Chinsuko", cookie[96], cookie_pal[96]},
    {433, 1.0E48, "Panda koala biscuits", cookie[97], cookie_pal[97]},
    {434, 3.162E48, "Putri salju", cookie[98], cookie_pal[98]},
    {435, 1.0E49, "Milk cookies", cookie[99], cookie_pal[99]},
    {436, 3.1622E49, "Kruidnoten", cookie[100], cookie_pal[100]},
    {437, 1.0E50, "Marie biscuits", cookie[101], cookie_pal[101]},
    {438, 3.16227E50, "Meringue cookies", cookie[102], cookie_pal[102]},
    {439, 1.0E51, "Yogurt cookies", cookie[103], cookie_pal[103]},
    {440, 3.162E51, "Thumbprint cookies", cookie[104], cookie_pal[104]},
    {441, 1.0E52, "Pizzelle", cookie[105], cookie_pal[105]},
    {442, 3.1622E52, "Granola cookies", cookie[106], cookie_pal[106]},
    {443, 1.0E53, "Ricotta cookies", cookie[107], cookie_pal[107]},
    {444, 3.16227E53, "Roze koeken", cookie[108], cookie_pal[108]},
    {445, 1.0E54, "Peanut butter cup cookies", cookie[109], cookie_pal[109]},
    {446, 3.162E54, "Sesame cookies", cookie[110], cookie_pal[110]},
    {447, 1.0E55, "Taiyaki", cookie[111], cookie_pal[111]},
    {448, 3.1622E55, "Vanillekipferl", cookie[112], cookie_pal[112]},
    {449, 1.0E56, "Battenberg biscuits", cookie[113], cookie_pal[113]},
    {450, 3.16227E56, "Rosette cookies", cookie[114], cookie_pal[114]},
    {451, 1.0E57, "Gangmakers", cookie[115], cookie_pal[115]},
    {452, 3.1622E57, "Welsh cookies", cookie[116], cookie_pal[116]},
    {453, 1.0E58, "Raspberry cheesecake\ncookies", cookie[117], cookie_pal[117]},
    {454, 3.1622E58, "Bokkenpootjes", cookie[118], cookie_pal[118]},
    {455, 1.0E59, "Fat rascals", cookie[119], cookie_pal[119]},
    {456, 3.16227E59, "Ischler cookies", cookie[120], cookie_pal[120]},
    {457, 3.16227E59, "Matcha cookies", cookie[121], cookie_pal[121]},
    {458, 1.0E60, "Dalgona cookies", cookie[122], cookie_pal[122]},
    {459, 3.162E60, "Spicy cookies", cookie[123], cookie_pal[123]},
    {460, 1.0E61, "Smile cookies", cookie[124], cookie_pal[124]},
    {461, 3.1622E61, "Kolachy cookies", cookie[125], cookie_pal[125]},
    {462, 1.0E62, "Gomma cookies", cookie[126], cookie_pal[126]},
    {463, 3.16228E62, "Vegan cookies", cookie[127], cookie_pal[127]},
    {464, 1.0E63, "Coyotas", cookie[128], cookie_pal[128]},
    {465, 3.162E63, "Frosted sugar cookies", cookie[129], cookie_pal[129]},
    {466, 1.0E64, "Marshmallow sandwich\ncookies", cookie[130], cookie_pal[130]},
    {467, 3.1623E64, "Calculator cookies", cookie[131], cookie_pal[131]},
    {468, 1.0E65, "Havreflarn", cookie[132], cookie_pal[132]},
    {469, 3.16228E65, "Alfajores", cookie[133], cookie_pal[133]},
    {470, 1.0E66, "Gaufrettes", cookie[134], cookie_pal[134]},
    {471, 3.162E66, "Cookie bars", cookie[135], cookie_pal[135]},
    {472, 1.0E67, "Snowball cookies", cookie[136], cookie_pal[136]},
    {473, 3.1623E67, "Sequilhos", cookie[137], cookie_pal[137]},
    {474, 1.0E68, "Hazelnut swirlies", cookie[138], cookie_pal[138]},
    {475, 3.16228E68, "Spritz cookies", cookie[139], cookie_pal[139]},
    {476, 1.0E69, "Mbatata cookies", cookie[140], cookie_pal[140]},
    {477, 3.162E69, "Springerles", cookie[141], cookie_pal[141]}
};

// filter algorithm based on https://stackoverflow.com/a/50317973

struct Upgrade *filter_unlocked(struct CookieData *data, const struct Upgrade *upgrades, int *filtered_size) {
    struct Upgrade *filtered = malloc(478 * sizeof(struct Upgrade));
    for (int i = 0; i < 478; i++) {
        if (data->upgrades_unlocked[i])
            filtered[(*filtered_size)++] = upgrades[i];
    }
    return filtered;
}

// quicksort algorithm

void swap(struct Upgrade *a, struct Upgrade *b) {
    struct Upgrade tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(struct Upgrade arr[], int low, int high) {
    double pivot = arr[high].price;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].price <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void sort_prices(struct Upgrade arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        sort_prices(arr, low, pi - 1);
        sort_prices(arr, pi + 1, high);
    }
}

void unlock_upgrades(struct CookieData *data) {
    int i, j;

    // cursor upgrades

    if (data->buildings[TYPE_CURSOR].owned >= 1) {
        data->upgrades_unlocked[0] = true;
        data->upgrades_unlocked[1] = true;
    }
    if (data->buildings[TYPE_CURSOR].owned >= 10)
        data->upgrades_unlocked[2] = true;
    if (data->buildings[TYPE_CURSOR].owned >= 25)
        data->upgrades_unlocked[3] = true;

    if (data->upgrades[3]) {
        for (i = 0; i < 11; i++) {
            if (data->buildings[TYPE_CURSOR].owned >= (i + 1) * 50)
                data->upgrades_unlocked[i + 4] = true;
        }
    }

    // mouse upgrades
    for (i = 0; i < 15; i++) {
        int u_id = (TYPE_MOUSE * 15) + i;
        if (data->handmade_cookies >= (upgrades[u_id].price / 50.0))
            data->upgrades_unlocked[u_id] = true;
    }

    // grandma upgrades
    
    if (data->buildings[1].owned >= 1)
        data->upgrades_unlocked[(TYPE_GRANDMA * 15)] = true;
    if (data->buildings[1].owned >= 5)
        data->upgrades_unlocked[(TYPE_GRANDMA * 15) + 1] = true;
    if (data->buildings[1].owned >= 25)
        data->upgrades_unlocked[(TYPE_GRANDMA * 15) + 2] = true;
    
    for (i = 0; i < 12; i++) {
        if (data->buildings[1].owned >= (i + 1) * 50)
            data->upgrades_unlocked[(TYPE_GRANDMA * 15) + i + 3] = true;
    }

    // other building upgrades

    for (i = 3; i < 21; i++) {
        if (data->buildings[i - 1].owned >= 1)
            data->upgrades_unlocked[45 + ((i - 3) * 16)] = true;
        if (data->buildings[i - 1].owned >= 5)
            data->upgrades_unlocked[45 + ((i - 3) * 16) + 1] = true;
        if (data->buildings[i - 1].owned >= 25)
            data->upgrades_unlocked[45 + ((i - 3) * 16) + 2] = true;
        for (j = 0; j < 12; j++) {
            if (data->buildings[i - 1].owned >= (j + 1) * 50)
                data->upgrades_unlocked[45 + ((i - 3) * 16) + j + 3] = true;
        }
        if (data->buildings[i - 1].owned >= 15 && data->buildings[1].owned >= 1)
            data->upgrades_unlocked[45 + ((i - 3) * 16) + 15] = true;
    }

    // golden cookie upgrades

    if (data->gold_click_count >= 7)
        data->upgrades_unlocked[333] = true;
    if (data->gold_click_count >= 27)
        data->upgrades_unlocked[334] = true;
    if (data->gold_click_count >= 77)
        data->upgrades_unlocked[335] = true;

    // flavored cookie upgrades
    for (i = 0; i < 142; i++)
        if (data->cookies_all_time >= (upgrades[336 + i].price / 20.0))
            data->upgrades_unlocked[336 + i] = true;
}

void enable_upgrade(struct CookieData *data, struct GoldenData *gold, uint16_t id) {
    uint8_t building_id = (id >= 45 ? ((id - 45) / 16) + 2 : (id / 15) - 1);

    if (id < 3)
        // multiply cursor cps by 2
        data->buildings[TYPE_CURSOR].multiplier *= 2.0;
    else if (id == 3)
        // Thousand fingers
        data->buildings[TYPE_CURSOR].modifier = 0.1;
    else if (id == 4)
        // Million fingers
        data->buildings[TYPE_CURSOR].modifier *= 5.0;
    else if (id == 5)
        // Billion fingers
        data->buildings[TYPE_CURSOR].modifier *= 10.0;
    else if (id >= 6 && id < 15)
        // Trillion - Undecillion fingers
        data->buildings[TYPE_CURSOR].modifier *= 20.0;
    else if (id >= 15 && id < 30)
        // Clicking gains +1% of your CpS.
        data->buildings[TYPE_CURSOR].percent += 0.01;
    else if (id >= 30 && id < 333) {
        if (id >= 45 && ((id - 44) % 16) == 0) {
            // Grandmas are twice as efficient.
            data->buildings[1].multiplier *= 2.0;
            // Buildings gain a percentage based on the number of grandmas.
            data->buildings[building_id].gma = true;
        } else
            // multiply building cps by 2
            data->buildings[building_id].multiplier *= 2.0;
    }
    else if (id >= 333 && id < 335)
        // Golden cookies appear twice as often and last twice as long on screen.
        gold->time_modifier *= 2;
    else if (id == 335)
        // Golden cookie effects last twice as long.
        gold->effect_modifier *= 2;
    else if ((id >= 336 && id < 339) || id == 391)
        // Cookie production multiplier +1%.
        data->multiplier += (0.01 * data->multiplier);
    else if ((id >= 339 && id < 351) || (id >= 353 && id < 365))
        //Cookie production multiplier +2%.
        data->multiplier += (0.02 * data->multiplier);
    else if ((id >= 367 && id < 373))
        // Cookie production multiplier +3%.
        data->multiplier += (0.03 * data->multiplier);
    else if ((id >= 373 && id < 391) || (id >= 392 && id < 410))
        // Cookie production multiplier +4%.
        data->multiplier += (0.04 * data->multiplier);
    else if ((id >= 351 && id < 353) || (id >= 365 && id < 367) || (id >= 410 && id < 478))
        // Cookie production multiplier +5%.
        data->multiplier += (0.05 * data->multiplier);
}