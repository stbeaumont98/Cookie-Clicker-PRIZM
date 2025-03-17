#include "types.h"

#include "upgrades.h"

char *upgrade_types[22] = {
	"Cursor", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple",
	"Wizard tower", "Shipment", "Alchemy lab", "Portal",
	"Time machine", "Antimatter condenser", "Prism", "Chancemaker",
	"Fractal engine", "Javascript console", "Idleverse", "Cortex baker", "You",
    "Mouse", "Golden cookie"
};

char *upgrade_descriptions[20] = {
	"", "Grandmas are twice as efficient.", "Farms are twice as efficient.",
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

const struct Upgrade upgrades[] = {
    // cursors
    {1.0E2,   "Reinforced index finger"},
    {5.0E2,   "Carpal tunnel prevention cream"},
    {1.0E4,   "Ambidextrous"},
    {1.0E5,   "Thousand fingers"},
    {1.0E7,   "Million fingers"},
    {1.0E8,   "Billion fingers"},
    {1.0E9,   "Trillion fingers"},
    {1.0E10,  "Quadrillion fingers"},
    {1.0E13,  "Quintillion fingers"},
    {1.0E16,  "Sextillion fingers"},
    {1.0E19,  "Septillion fingers"},
    {1.0E22,  "Octillion fingers"},
    {1.0E25,  "Nonillion fingers"},
    {1.0E28,  "Decillion fingers"},
    {1.0E31,  "Undecillion fingers"},

    // grandmas
    {1.0E3,   "Forwards from grandma"},
    {5.0E3,   "Steel-plated rolling pins"},
    {5.0E4,   "Lubricated dentures"},
    {5.0E6,   "Prune juice"},
    {5.0E8,   "Double-thick glasses"},
    {5.0E10,  "Aging agents"},
    {5.0E13,  "Xtreme walkers"},
    {5.0E16,  "The Unbridling"},
    {5.0E19,  "Reverse dementia"},
    {5.0E22,  "Timeproof hair dyes"},
    {5.0E26,  "Good manners"},
    {5.0E30,  "Generation degeneration"},
    {5.0E34,  "Visits"},
    {5.0E38,  "Kitchen cabinets"},
    {5.0E42,  "Foam-tipped canes"},

    // farms
    {1.1E4,   "Cheap hoes"},
    {5.5E4,   "Fertilizer"},
    {5.5E5,   "Cookie trees"},
    {5.5E7,   "Genetically-modified cookies"},
    {5.5E9,   "Gingerbread scarecrows"},
    {5.5E11,  "Pulsar sprinklers"},
    {5.5E14,  "Fudge fungus"},
    {5.5E17,  "Wheat triffids"},
    {5.5E20,  "Humane pesticides"},
    {5.5E23,  "Barnstars"},
    {5.5E27,  "Lindworms"},
    {5.5E31,  "Global seed vault"},
    {5.5E35,  "Reverse-veganism"},
    {5.5E39,  "Cookie mulch"},
    {5.5E43,  "Self-driving tractors"},

    //mines
    {1.2E5,   "Sugar gas"},
    {6.0E5,   "Megadrill"},
    {6.0E6,   "Ultradrill"},
    {6.0E8,   "Ultimadrill"},
    {6.0E10,  "H-bomb mining"},
    {6.0E12,  "Coreforge"},
    {6.0E15,  "Planetsplitters"},
    {6.0E18,  "Canola oil wells"},
    {6.0E21,  "Mole people"},
    {6.0E24,  "Mine canaries"},
    {6.0E28,  "Bore again"},
    {6.0E32,  "Air mining"},
    {6.0E36,  "Caramel alloys"},
    {6.0E40,  "Delicious mineralogy"},
    {6.0E44,  "Mineshaft supports"},

    // factories
    {1.3E6,   "Sturdier conveyor belts"},
    {6.5E6,   "Child labor"},
    {6.5E7,   "Sweatshop"},
    {6.5E9,   "Radium reactors"},
    {6.5E11,  "Recombobulators"},
    {6.5E13,  "Deep-bake process"},
    {6.5E16,  "Cyborg workforce"},
    {6.5E19,  "78-hour days"},
    {6.5E22,  "Machine learning"},
    {6.5E25,  "Brownie point system"},
    {6.5E29,  "\"Volunteer\' interns"},
    {6.5E33,  "Behavioral reframing"},
    {6.5E37,  "The infinity engine"},
    {6.5E41,  "N-dimensional assembly lines"},
    {6.5E45,  "Universal automation"},

    // banks
    {1.4E7,   "Taller tellers"},
    {7.0E7,   "Scissor-resistant credit cards"},
    {7.0E8,   "Acid-proof vaults"},
    {7.0E10,  "Chocolate coins"},
    {7.0E12,  "Exponential interest rates"},
    {7.0E14,  "Financial zen"},
    {7.0E17,  "Way of the wallet"},
    {7.0E20,  "The stuff rationale"},
    {7.0E23,  "Edible money"},
    {7.0E26,  "Grand supercycle"},
    {7.0E30,  "Rules of aquisition"},
    {7.0E34,  "Altruistic loop"},
    {7.0E38,  "Diminishing tax returns"},
    {7.0E42,  "Cookie Points"},
    {7.0E46,  "The big shortcake"},

    // temples
    {2.0E8,   "Golden idols"},
    {1.0E9,   "Sacrifices"},
    {1.0E10,  "Delicious blessing"},
    {1.0E12,  "Sun festival"},
    {1.0E14,  "Enlarged pantheon"},
    {1.0E16,  "Great Baker in the sky"},
    {1.0E19,  "Creation myth"},
    {1.0E22,  "Theocracy"},
    {1.0E25,  "Sick rap prayers"},
    {1.0E28,  "Psalm-reading"},
    {1.0E32,  "War of the gods"},
    {1.0E36,  "A novel idea"},
    {1.0E40,  "Apparitions"},
    {1.0E44,  "Negatheism"},
    {1.0E48,  "Temple traps"},

    // wizard towers
    {3.3E9,   "Pointier hats"},
    {1.65E10, "Beardlier beards"},
    {1.65E11, "Ancient grimoires"},
    {1.65E13, "Kitchen curses"},
    {1.65E15, "School of sorcery"},
    {1.65E17, "Dark formulas"},
    {1.65E20, "Cookiemancy"},
    {1.65E23, "Rabbit trick"},
    {1.65E26, "Deluxe tailored wands"},
    {1.65E29, "Immobile spellcasting"},
    {1.65E33, "Electricity"},
    {1.65E37, "Spelling bees"},
    {1.65E41, "Wizard basements"},
    {1.65E45, "Magical realism"},
    {1.65E49, "Polymorphism"},

    // shipments
    {5.1E10,  "Vanilla nebulae"},
    {2.55E11, "Wormholes"},
    {2.55E12, "Frequent flyer"},
    {2.55E14, "Warp drive"},
    {2.55E16, "Chocolate monoliths"},
    {2.55E18, "Generation ship"},
    {2.55E21, "Dyson sphere"},
    {2.55E24, "The final frontier"},
    {2.55E27, "Autopilot"},
    {2.55E30, "Restaurants at the end of\nthe universe"},
    {2.55E34, "Universal alphabet"},
    {2.55E38, "Toroid universe"},
    {2.55E42, "Prime directive"},
    {2.55E46, "Cosmic foreground radiation"},
    {2.55E50, "At your doorstep in 30 minutes\nor your money back"},

    // alchemy labs
    {7.5E11,  "Antimony"},
    {3.75E12, "Essence of dough"},
    {3.75E13, "True chocolate"},
    {3.75E15, "Ambrosia"},
    {3.75E17, "Aqua crustulae"},
    {3.75E19, "Origin crucible"},
    {3.75E22, "Theory of atomic fluidity"},
    {3.75E25, "Beige goo"},
    {3.75E28, "The advent of chemistry"},
    {3.75E31, "On second thought"},
    {3.75E35, "Public betterment"},
    {3.75E39, "Hermetic reconciliation"},
    {3.75E43, "Chromatic cycling"},
    {3.75E47, "Arcanized glassware"},
    {3.75E51, "The dose makes the poison"},

    // portals
    {1.0E13,  "Ancient tablet"},
    {5.0E13,  "Insane oatling workers"},
    {5.0E14,  "Soul bond"},
    {5.0E16,  "Sanity dance"},
    {5.0E18,  "Brane transplant"},
    {5.0E20,  "Deity-sized portals"},
    {5.0E23,  "End of times back-up plan"},
    {5.0E26,  "Madedening chants"},
    {5.0E29,  "The real world"},
    {5.0E32,  "Dimensional garbage gulper"},
    {5.0E36,  "Embedded microportals"},
    {5.0E40,  "His advent"},
    {5.0E44,  "Domestic rifts"},
    {5.0E48,  "Portal guns"},
    {5.0E52,  "A way home"},

    // time machines
    {1.4E14,  "Flux capacitors"},
    {7.0E14,  "Time paradox resolver"},
    {7.0E15,  "Quantum conundrum"},
    {7.0E17,  "Causality enforcer"},
    {7.0E19,  "Yestermorrow comparators"},
    {7.0E21,  "Far future enactment"},
    {7.0E24,  "Great loop hypothesis"},
    {7.0E27,  "Cookietopian moments of\nmaybe"},
    {7.0E30,  "Second seconds"},
    {7.0E33,  "Additional clock hands"},
    {7.0E37,  "Nostalgia"},
    {7.0E41,  "Split seconds"},
    {7.0E45,  "Patience abolished"},
    {7.0E49,  "Timeproof upholstery"},
    {7.0E53,  "Rectifying a mistake"},

    // antimatter condensers
    {1.7E15,  "Sugar bosons"},
    {8.5E15,  "String theory"},
    {8.5E16,  "Large macaron collider"},
    {8.5E18,  "Big bang bake"},
    {8.5E20,  "Reverse cyclotrons"},
    {8.5E22,  "Nanocosmics"},
    {8.5E25,  "The Pulse"},
    {8.5E28,  "Some other super-tiny\nfundamental particle? Probably?"},
    {8.5E31,  "Quantum comb"},
    {8.5E34,  "Baking Nobel prize"},
    {8.5E38,  "The definite molecule"},
    {8.5E42,  "Flavor itself"},
    {8.5E46,  "Delicious pull"},
    {8.5E50,  "Employee minification"},
    {8.5E54,  "Candied atoms"},

    // prisms
    {2.1E16,  "Gem polish"},
    {1.05E17, "9th color"},
    {1.05E18, "Chocolate light"},
    {1.05E20, "Grainbow"},
    {1.05E22, "Pure cosmic light"},
    {1.05E24, "Glow-in-the-dark"},
    {1.05E27, "Lux sanctorum"},
    {1.05E30, "Reverse shadows"},
    {1.05E33, "Crystal mirrors"},
    {1.05E36, "Reverse theory of light"},
    {1.05E40, "Light capture measures"},
    {1.05E44, "Light speed limit"},
    {1.05E48, "Occam's laser"},
    {1.05E52, "Hyperblack paint"},
    {1.05E56, "Lab goggles but like cool shades"},

    // chancemakers
    {2.6E17,  "Your lucky cookie"},
    {1.3E18,  "\"All Bets Are Off\' magic coin"},
    {1.3E19,  "Winning lottery ticket"},
    {1.3E21,  "Four-leaf clover field"},
    {1.3E23,  "A recipe book about books"},
    {1.3E25,  "Leprechaun village"},
    {1.3E28,  "Improbability drive"},
    {1.3E31,  "Antisuperstistronics"},
    {1.3E34,  "Bunnypedes"},
    {1.3E37,  "Revised probabilistics"},
    {1.3E41,  "0-sided dice"},
    {1.3E45,  "A touch of determinism"},
    {1.3E49,  "On a streak"},
    {1.3E53,  "Silver lining maximization"},
    {1.3E57,  "Gambler's fallacy fallacy"},

    // fractal engines
    {3.1E18,  "Metabakeries"},
    {1.55E19, "Mandelbrown sugar"},
    {1.55E20, "Fractoids"},
    {1.55E22, "Nested universe theory"},
    {1.55E24, "Menger sponge cake"},
    {1.55E26, "One particularly good-\nhumored cow"},
    {1.55E29, "Chocolate ouroboros"},
    {1.55E32, "Nested"},
    {1.55E35, "Space-filling fibers"},
    {1.55E38, "Endless book of prose"},
    {1.55E42, "The set of all sets"},
    {1.55E46, "This upgrade"},
    {1.55E50, "A box"},
    {1.55E54, "Multiscale profiling"},
    {1.55E58, "The more they stay the same"},

    // javascript consoles
    {7.1E20,  "The JavaScript console for\ndummies"},
    {3.55E21, "64bit arrays"},
    {3.55E22, "Stack overflow"},
    {3.55E24, "Enterprise compiler"},
    {3.55E26, "Syntactic sugar"},
    {3.55E28, "A nice cup of coffee"},
    {3.55E31, "Just-in-time baking"},
    {3.55E34, "cookies++"},
    {3.55E37, "Software updates"},
    {3.55E40, "Game.Loop"},
    {3.55E44, "eval()"},
    {3.55E48, "Your biggest fans"},
    {3.55E52, "Hacker shades"},
    {3.55E56, "PHP containment vats"},
    {3.55E60, "Simulation failsafes"},

    // idleverses
    {1.2E23,  "Manifest destiny"},
    {6.0E23,  "The multiverse in a nutshell"},
    {6.0E24,  "All-conversion"},
    {6.0E26,  "Multiverse agents"},
    {6.0E28,  "Escape plan"},
    {6.0E30,  "Game design"},
    {6.0E33,  "Sandbox universes"},
    {6.0E36,  "Multiverse wars"},
    {6.0E39,  "Mobile ports"},
    {6.0E42,  "Encapsulated realities"},
    {6.0E46,  "Extrinsic clicking"},
    {6.0E50,  "Universal idling"},
    {6.0E54,  "Break the fifth wall"},
    {6.0E58,  "Opposite universe"},
    {6.0E62,  "The other routes to Rome"},

    // cortex bakers
    {1.9E25,  "Principled neural shackles"},
    {9.5E25,  "Obey"},
    {9.5E26,  "A sprinkle of irrationality"},
    {9.5E28,  "Front and back hemispheres"},
    {9.5E30,  "Neural networking"},
    {9.5E32,  "Cosmic brainstorms"},
    {9.5E35,  "Megatherapy"},
    {9.5E38,  "Synaptic lubricant"},
    {9.5E41,  "Psychokinesis"},
    {9.5E44,  "Spines"},
    {9.5E48,  "Neuraforming"},
    {9.5E52,  "Epistemological trickery"},
    {9.5E56,  "Every possible idea"},
    {9.5E60,  "The land of dreams"},
    {9.5E64,  "Intellectual property theft"},

    // you
    {5.4E27,  "Cloning vats"},
    {2.7E28,  "Energized nutrients"},
    {2.7E29,  "Stunt doubles"},
    {2.7E31,  "Clone recycling plant"},
    {2.7E33,  "Free-range clones"},
    {2.7E35,  "Genetic tailoring"},
    {2.7E38,  "Power in diversity"},
    {2.7E41,  "Self-betterment"},
    {2.7E44,  "Source control"},
    {2.7E47,  "United workforce"},
    {2.7E51,  "Safety patrols"},
    {2.7E55,  "Clone rights"},
    {2.7E59,  "One big family"},
    {2.7E63,  "Fine-tuned body plans"},
    {2.7E67,  "Reading your clones bedtime\nstories"},

    // mouse
    {5.0E4, "Plastic mouse"},
    {5.0E6, "Iron mouse"},
    {5.0E8, "Titanium mouse"},
    {5.0E10, "Adamantium mouse"},
    {5.0E12, "Unobtainium mouse"},
    {5.0E14, "Eludium mouse"},
    {5.0E16, "Wishalloy mouse"},
    {5.0E18, "Fantasteel mouse"},
    {5.0E20, "Nevercrack mouse"},
    {5.0E22, "Armythril mouse"},
    {5.0E24, "Technobsidian mouse"},
    {5.0E26, "Plasmarble mouse"},
    {5.0E28, "Miraculite mouse"},
    {5.0E30, "Aetherice mouse"},
    {5.0E32, "Omniplast mouse"},

    // golden cookies
    {7.77778E8, "Lucky day"},
    {7.77778E10, "Serendipity"},
    {7.77778E13, "Get lucky"}
};

void unlock_upgrades(struct CookieData *data) {

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
        if (data->buildings[TYPE_CURSOR].owned >= 50)
            data->upgrades_unlocked[4] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 100)
            data->upgrades_unlocked[5] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 150)
            data->upgrades_unlocked[6] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 200)
            data->upgrades_unlocked[7] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 250)
            data->upgrades_unlocked[8] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 300)
            data->upgrades_unlocked[9] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 350)
            data->upgrades_unlocked[10] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 400)
            data->upgrades_unlocked[11] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 450)
            data->upgrades_unlocked[12] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 500)
            data->upgrades_unlocked[13] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 550)
            data->upgrades_unlocked[14] = true;
    }

    // other building upgrades

    for (int i = 1; i < 20; i++) {
        if (data->buildings[i].owned >= 1)
            data->upgrades_unlocked[(i * 15)] = true;
        if (data->buildings[i].owned >= 5)
            data->upgrades_unlocked[(i * 15) + 1] = true;
        if (data->buildings[i].owned >= 25)
            data->upgrades_unlocked[(i * 15) + 2] = true;
        if (data->buildings[i].owned >= 50)
            data->upgrades_unlocked[(i * 15) + 3] = true;
        if (data->buildings[i].owned >= 100)
            data->upgrades_unlocked[(i * 15) + 4] = true;
        if (data->buildings[i].owned >= 150)
            data->upgrades_unlocked[(i * 15) + 5] = true;
        if (data->buildings[i].owned >= 200)
            data->upgrades_unlocked[(i * 15) + 6] = true;
        if (data->buildings[i].owned >= 250)
            data->upgrades_unlocked[(i * 15) + 7] = true;
        if (data->buildings[i].owned >= 300)
            data->upgrades_unlocked[(i * 15) + 8] = true;
        if (data->buildings[i].owned >= 350)
            data->upgrades_unlocked[(i * 15) + 9] = true;
        if (data->buildings[i].owned >= 400)
            data->upgrades_unlocked[(i * 15) + 10] = true;
        if (data->buildings[i].owned >= 450)
            data->upgrades_unlocked[(i * 15) + 11] = true;
        if (data->buildings[i].owned >= 500)
            data->upgrades_unlocked[(i * 15) + 12] = true;
        if (data->buildings[i].owned >= 550)
            data->upgrades_unlocked[(i * 15) + 13] = true;
        if (data->buildings[i].owned >= 600)
            data->upgrades_unlocked[(i * 15) + 14] = true;
    }

    // mouse upgrades

    if (data->handmade_cookies >= 1E3)
        data->upgrades_unlocked[(TYPE_MOUSE * 15)] = true;
    if (data->handmade_cookies >= 1E5)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 1] = true;
    if (data->handmade_cookies >= 1E7)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 2] = true;
    if (data->handmade_cookies >= 1E9)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 3] = true;
    if (data->handmade_cookies >= 1E11)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 4] = true;
    if (data->handmade_cookies >= 1E13)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 5] = true;
    if (data->handmade_cookies >= 1E15)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 6] = true;
    if (data->handmade_cookies >= 1E17)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 7] = true;
    if (data->handmade_cookies >= 1E19)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 8] = true;
    if (data->handmade_cookies >= 1E21)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 9] = true;
    if (data->handmade_cookies >= 1E23)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 10] = true;
    if (data->handmade_cookies >= 1E25)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 11] = true;
    if (data->handmade_cookies >= 1E27)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 12] = true;
    if (data->handmade_cookies >= 1E29)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 13] = true;
    if (data->handmade_cookies >= 1E31)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 14] = true;

    // golden cookie upgrades

    if (data->gold_click_count >= 7)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15)] = true;
    if (data->gold_click_count >= 27)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15) + 1] = true;
    if (data->gold_click_count >= 77)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15) + 2] = true;
}

void enable_upgrade(struct CookieData *data, struct GoldenData *gold, int id) {

    uint8_t building_id = id / 15;

    if (id == 3)
        // Thousand fingers
        data->buildings[TYPE_CURSOR].modifier += 0.1;
    else if (id == 4)
        // Million fingers
        data->buildings[TYPE_CURSOR].modifier *= 5.0;
    else if (id == 5)
        // Billion fingers
        data->buildings[TYPE_CURSOR].modifier *= 10.0;
    else if (id > 5 && id <= 14)
        // Trillion - Undecillion fingers
        data->buildings[TYPE_CURSOR].modifier *= 20.0;
    else if (id < 3 || (id > 14 && id < 300))
        // multiply building cps by 2
        data->buildings[building_id].multiplier *= 2.0;
    else if (id >= 300 && id < 315)
        // Clicking gains +1% of your CpS.
        data->buildings[TYPE_CURSOR].percent_cps += 0.01;
    else if (id >= 315 && id < 317)
        // Golden cookies appear twice as often and last twice as long on screen.
        gold->time_modifier *= 2;
    else if (id == 317)
        // Golden cookie effects last twice as long.
        gold->effect_modifier *= 2;
}