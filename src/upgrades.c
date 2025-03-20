#include <stddef.h>
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
    {1.0E2,   "Reinforced index finger", cursor_0, cursor_pal},
    {5.0E2,   "Carpal tunnel prevention cream", cursor_1, tier_1},
    {1.0E4,   "Ambidextrous", cursor_1, tier_2},
    {1.0E5,   "Thousand fingers", NULL, NULL},
    {1.0E7,   "Million fingers", NULL, NULL},
    {1.0E8,   "Billion fingers", NULL, NULL},
    {1.0E9,   "Trillion fingers", NULL, NULL},
    {1.0E10,  "Quadrillion fingers", NULL, NULL},
    {1.0E13,  "Quintillion fingers", NULL, NULL},
    {1.0E16,  "Sextillion fingers", NULL, NULL},
    {1.0E19,  "Septillion fingers", NULL, NULL},
    {1.0E22,  "Octillion fingers", NULL, NULL},
    {1.0E25,  "Nonillion fingers", NULL, NULL},
    {1.0E28,  "Decillion fingers", NULL, NULL},
    {1.0E31,  "Undecillion fingers", NULL, NULL},   // 14
    
    // mouse
    {5.0E4, "Plastic mouse", NULL, NULL},
    {5.0E6, "Iron mouse", NULL, NULL},
    {5.0E8, "Titanium mouse", NULL, NULL},
    {5.0E10, "Adamantium mouse", NULL, NULL},
    {5.0E12, "Unobtainium mouse", NULL, NULL},
    {5.0E14, "Eludium mouse", NULL, NULL},
    {5.0E16, "Wishalloy mouse", NULL, NULL},
    {5.0E18, "Fantasteel mouse", NULL, NULL},
    {5.0E20, "Nevercrack mouse", NULL, NULL},
    {5.0E22, "Armythril mouse", NULL, NULL},
    {5.0E24, "Technobsidian mouse", NULL, NULL},
    {5.0E26, "Plasmarble mouse", NULL, NULL},
    {5.0E28, "Miraculite mouse", NULL, NULL},
    {5.0E30, "Aetherice mouse", NULL, NULL},
    {5.0E32, "Omniplast mouse", NULL, NULL},        // 29

    // grandmas
    {1.0E3,   "Forwards from grandma", grandma_0, grandma_pal},
    {5.0E3,   "Steel-plated rolling pins", grandma_1, tier_1},
    {5.0E4,   "Lubricated dentures", grandma_1, tier_2},
    {5.0E6,   "Prune juice", NULL, NULL},
    {5.0E8,   "Double-thick glasses", NULL, NULL},
    {5.0E10,  "Aging agents", NULL, NULL},
    {5.0E13,  "Xtreme walkers", NULL, NULL},
    {5.0E16,  "The Unbridling", NULL, NULL},
    {5.0E19,  "Reverse dementia", NULL, NULL},
    {5.0E22,  "Timeproof hair dyes", NULL, NULL},
    {5.0E26,  "Good manners", NULL, NULL},
    {5.0E30,  "Generation degeneration", NULL, NULL},
    {5.0E34,  "Visits", NULL, NULL},
    {5.0E38,  "Kitchen cabinets", NULL, NULL},
    {5.0E42,  "Foam-tipped canes", NULL, NULL},     // 44

    // farms
    {1.1E4,   "Cheap hoes", NULL, NULL},
    {5.5E4,   "Fertilizer", NULL, NULL},
    {5.5E5,   "Cookie trees", NULL, NULL},
    {5.5E7,   "Genetically-modified\ncookies", NULL, NULL},
    {5.5E9,   "Gingerbread scarecrows", NULL, NULL},
    {5.5E11,  "Pulsar sprinklers", NULL, NULL},
    {5.5E14,  "Fudge fungus", NULL, NULL},
    {5.5E17,  "Wheat triffids", NULL, NULL},
    {5.5E20,  "Humane pesticides", NULL, NULL},
    {5.5E23,  "Barnstars", NULL, NULL},
    {5.5E27,  "Lindworms", NULL, NULL},
    {5.5E31,  "Global seed vault", NULL, NULL},
    {5.5E35,  "Reverse-veganism", NULL, NULL},
    {5.5E39,  "Cookie mulch", NULL, NULL},
    {5.5E43,  "Self-driving tractors", NULL, NULL},
    {5.5E4,   "Farmer grandmas", NULL, NULL},       // 60

    //mines
    {1.2E5,   "Sugar gas", NULL, NULL},
    {6.0E5,   "Megadrill", NULL, NULL},
    {6.0E6,   "Ultradrill", NULL, NULL},
    {6.0E8,   "Ultimadrill", NULL, NULL},
    {6.0E10,  "H-bomb mining", NULL, NULL},
    {6.0E12,  "Coreforge", NULL, NULL},
    {6.0E15,  "Planetsplitters", NULL, NULL},
    {6.0E18,  "Canola oil wells", NULL, NULL},
    {6.0E21,  "Mole people", NULL, NULL},
    {6.0E24,  "Mine canaries", NULL, NULL},
    {6.0E28,  "Bore again", NULL, NULL},
    {6.0E32,  "Air mining", NULL, NULL},
    {6.0E36,  "Caramel alloys", NULL, NULL},
    {6.0E40,  "Delicious mineralogy", NULL, NULL},
    {6.0E44,  "Mineshaft supports", NULL, NULL},
    {6.0E5,   "Miner grandmas", NULL, NULL},        // 76

    // factories
    {1.3E6,   "Sturdier conveyor belts", NULL, NULL},
    {6.5E6,   "Child labor", NULL, NULL},
    {6.5E7,   "Sweatshop", NULL, NULL},
    {6.5E9,   "Radium reactors", NULL, NULL},
    {6.5E11,  "Recombobulators", NULL, NULL},
    {6.5E13,  "Deep-bake process", NULL, NULL},
    {6.5E16,  "Cyborg workforce", NULL, NULL},
    {6.5E19,  "78-hour days", NULL, NULL},
    {6.5E22,  "Machine learning", NULL, NULL},
    {6.5E25,  "Brownie point system", NULL, NULL},
    {6.5E29,  "\"Volunteer\" interns", NULL, NULL},
    {6.5E33,  "Behavioral reframing", NULL, NULL},
    {6.5E37,  "The infinity engine", NULL, NULL},
    {6.5E41,  "N-dimensional assembly\nlines", NULL, NULL},
    {6.5E45,  "Universal automation", NULL, NULL},
    {6.5E6,   "Worker grandmas", NULL, NULL},       // 92

    // banks
    {1.4E7,   "Taller tellers", NULL, NULL},
    {7.0E7,   "Scissor-resistant credit\ncards", NULL, NULL},
    {7.0E8,   "Acid-proof vaults", NULL, NULL},
    {7.0E10,  "Chocolate coins", NULL, NULL},
    {7.0E12,  "Exponential interest rates", NULL, NULL},
    {7.0E14,  "Financial zen", NULL, NULL},
    {7.0E17,  "Way of the wallet", NULL, NULL},
    {7.0E20,  "The stuff rationale", NULL, NULL},
    {7.0E23,  "Edible money", NULL, NULL},
    {7.0E26,  "Grand supercycle", NULL, NULL},
    {7.0E30,  "Rules of aquisition", NULL, NULL},
    {7.0E34,  "Altruistic loop", NULL, NULL},
    {7.0E38,  "Diminishing tax returns", NULL, NULL},
    {7.0E42,  "Cookie Points", NULL, NULL},
    {7.0E46,  "The big shortcake", NULL, NULL},
    {7.0E7,   "Banker grandmas", NULL, NULL},       // 108

    // temples
    {2.0E8,   "Golden idols", NULL, NULL},
    {1.0E9,   "Sacrifices", NULL, NULL},
    {1.0E10,  "Delicious blessing", NULL, NULL},
    {1.0E12,  "Sun festival", NULL, NULL},
    {1.0E14,  "Enlarged pantheon", NULL, NULL},
    {1.0E16,  "Great Baker in the sky", NULL, NULL},
    {1.0E19,  "Creation myth", NULL, NULL},
    {1.0E22,  "Theocracy", NULL, NULL},
    {1.0E25,  "Sick rap prayers", NULL, NULL},
    {1.0E28,  "Psalm-reading", NULL, NULL},
    {1.0E32,  "War of the gods", NULL, NULL},
    {1.0E36,  "A novel idea", NULL, NULL},
    {1.0E40,  "Apparitions", NULL, NULL},
    {1.0E44,  "Negatheism", NULL, NULL},
    {1.0E48,  "Temple traps", NULL, NULL},
    {1.0E9,   "Priestess grandmas", NULL, NULL},    // 124

    // wizard towers
    {3.3E9,   "Pointier hats", NULL, NULL},
    {1.65E10, "Beardlier beards", NULL, NULL},
    {1.65E11, "Ancient grimoires", NULL, NULL},
    {1.65E13, "Kitchen curses", NULL, NULL},
    {1.65E15, "School of sorcery", NULL, NULL},
    {1.65E17, "Dark formulas", NULL, NULL},
    {1.65E20, "Cookiemancy", NULL, NULL},
    {1.65E23, "Rabbit trick", NULL, NULL},
    {1.65E26, "Deluxe tailored wands", NULL, NULL},
    {1.65E29, "Immobile spellcasting", NULL, NULL},
    {1.65E33, "Electricity", NULL, NULL},
    {1.65E37, "Spelling bees", NULL, NULL},
    {1.65E41, "Wizard basements", NULL, NULL},
    {1.65E45, "Magical realism", NULL, NULL},
    {1.65E49, "Polymorphism", NULL, NULL},
    {1.65E10, "Witch grandmas", NULL, NULL},        // 140

    // shipments
    {5.1E10,  "Vanilla nebulae", NULL, NULL},
    {2.55E11, "Wormholes", NULL, NULL},
    {2.55E12, "Frequent flyer", NULL, NULL},
    {2.55E14, "Warp drive", NULL, NULL},
    {2.55E16, "Chocolate monoliths", NULL, NULL},
    {2.55E18, "Generation ship", NULL, NULL},
    {2.55E21, "Dyson sphere", NULL, NULL},
    {2.55E24, "The final frontier", NULL, NULL},
    {2.55E27, "Autopilot", NULL, NULL},
    {2.55E30, "Restaurants at the end of\nthe universe", NULL, NULL},
    {2.55E34, "Universal alphabet", NULL, NULL},
    {2.55E38, "Toroid universe", NULL, NULL},
    {2.55E42, "Prime directive", NULL, NULL},
    {2.55E46, "Cosmic foreground\nradiation", NULL, NULL},
    {2.55E50, "At your doorstep in 30\nminutes or your money back", NULL, NULL},
    {2.55E11, "Cosmic grandmas", NULL, NULL},       // 156

    // alchemy labs
    {7.5E11,  "Antimony", NULL, NULL},
    {3.75E12, "Essence of dough", NULL, NULL},
    {3.75E13, "True chocolate", NULL, NULL},
    {3.75E15, "Ambrosia", NULL, NULL},
    {3.75E17, "Aqua crustulae", NULL, NULL},
    {3.75E19, "Origin crucible", NULL, NULL},
    {3.75E22, "Theory of atomic fluidity", NULL, NULL},
    {3.75E25, "Beige goo", NULL, NULL},
    {3.75E28, "The advent of chemistry", NULL, NULL},
    {3.75E31, "On second thought", NULL, NULL},
    {3.75E35, "Public betterment", NULL, NULL},
    {3.75E39, "Hermetic reconciliation", NULL, NULL},
    {3.75E43, "Chromatic cycling", NULL, NULL},
    {3.75E47, "Arcanized glassware", NULL, NULL},
    {3.75E51, "The dose makes the poison", NULL, NULL},
    {3.75E12, "Transmuted grandmas", NULL, NULL},   // 172

    // portals
    {1.0E13,  "Ancient tablet", NULL, NULL},
    {5.0E13,  "Insane oatling workers", NULL, NULL},
    {5.0E14,  "Soul bond", NULL, NULL},
    {5.0E16,  "Sanity dance", NULL, NULL},
    {5.0E18,  "Brane transplant", NULL, NULL},
    {5.0E20,  "Deity-sized portals", NULL, NULL},
    {5.0E23,  "End of times back-up plan", NULL, NULL},
    {5.0E26,  "Madedening chants", NULL, NULL},
    {5.0E29,  "The real world", NULL, NULL},
    {5.0E32,  "Dimensional garbage gulper", NULL, NULL},
    {5.0E36,  "Embedded microportals", NULL, NULL},
    {5.0E40,  "His advent", NULL, NULL},
    {5.0E44,  "Domestic rifts", NULL, NULL},
    {5.0E48,  "Portal guns", NULL, NULL},
    {5.0E52,  "A way home", NULL, NULL},
    {5.0E13,  "Altered grandmas", NULL, NULL},      // 188

    // time machines
    {1.4E14,  "Flux capacitors", NULL, NULL},
    {7.0E14,  "Time paradox resolver", NULL, NULL},
    {7.0E15,  "Quantum conundrum", NULL, NULL},
    {7.0E17,  "Causality enforcer", NULL, NULL},
    {7.0E19,  "Yestermorrow comparators", NULL, NULL},
    {7.0E21,  "Far future enactment", NULL, NULL},
    {7.0E24,  "Great loop hypothesis", NULL, NULL},
    {7.0E27,  "Cookietopian moments of\nmaybe", NULL, NULL},
    {7.0E30,  "Second seconds", NULL, NULL},
    {7.0E33,  "Additional clock hands", NULL, NULL},
    {7.0E37,  "Nostalgia", NULL, NULL},
    {7.0E41,  "Split seconds", NULL, NULL},
    {7.0E45,  "Patience abolished", NULL, NULL},
    {7.0E49,  "Timeproof upholstery", NULL, NULL},
    {7.0E53,  "Rectifying a mistake", NULL, NULL},
    {7.0E14,  "Grandmas\' grandmas", NULL, NULL},   // 204

    // antimatter condensers
    {1.7E15,  "Sugar bosons", NULL, NULL},
    {8.5E15,  "String theory", NULL, NULL},
    {8.5E16,  "Large macaron collider", NULL, NULL},
    {8.5E18,  "Big bang bake", NULL, NULL},
    {8.5E20,  "Reverse cyclotrons", NULL, NULL},
    {8.5E22,  "Nanocosmics", NULL, NULL},
    {8.5E25,  "The Pulse", NULL, NULL},
    {8.5E28,  "Some other super-tiny\nfundamental particle? Probably?", NULL, NULL},
    {8.5E31,  "Quantum comb", NULL, NULL},
    {8.5E34,  "Baking Nobel prize", NULL, NULL},
    {8.5E38,  "The definite molecule", NULL, NULL},
    {8.5E42,  "Flavor itself", NULL, NULL},
    {8.5E46,  "Delicious pull", NULL, NULL},
    {8.5E50,  "Employee minification", NULL, NULL},
    {8.5E54,  "Candied atoms", NULL, NULL},
    {8.5E15,  "Antigrandmas", NULL, NULL},          // 220

    // prisms
    {2.1E16,  "Gem polish", NULL, NULL},
    {1.05E17, "9th color", NULL, NULL},
    {1.05E18, "Chocolate light", NULL, NULL},
    {1.05E20, "Grainbow", NULL, NULL},
    {1.05E22, "Pure cosmic light", NULL, NULL},
    {1.05E24, "Glow-in-the-dark", NULL, NULL},
    {1.05E27, "Lux sanctorum", NULL, NULL},
    {1.05E30, "Reverse shadows", NULL, NULL},
    {1.05E33, "Crystal mirrors", NULL, NULL},
    {1.05E36, "Reverse theory of light", NULL, NULL},
    {1.05E40, "Light capture measures", NULL, NULL},
    {1.05E44, "Light speed limit", NULL, NULL},
    {1.05E48, "Occam's laser", NULL, NULL},
    {1.05E52, "Hyperblack paint", NULL, NULL},
    {1.05E56, "Lab goggles but like cool\nshades", NULL, NULL},
    {1.05E17, "Rainbow grandmas", NULL, NULL},      // 236

    // chancemakers
    {2.6E17,  "Your lucky cookie", NULL, NULL},
    {1.3E18,  "\"All Bets Are Off\" magic coin", NULL, NULL},
    {1.3E19,  "Winning lottery ticket", NULL, NULL},
    {1.3E21,  "Four-leaf clover field", NULL, NULL},
    {1.3E23,  "A recipe book about books", NULL, NULL},
    {1.3E25,  "Leprechaun village", NULL, NULL},
    {1.3E28,  "Improbability drive", NULL, NULL},
    {1.3E31,  "Antisuperstistronics", NULL, NULL},
    {1.3E34,  "Bunnypedes", NULL, NULL},
    {1.3E37,  "Revised probabilistics", NULL, NULL},
    {1.3E41,  "0-sided dice", NULL, NULL},
    {1.3E45,  "A touch of determinism", NULL, NULL},
    {1.3E49,  "On a streak", NULL, NULL},
    {1.3E53,  "Silver lining maximization", NULL, NULL},
    {1.3E57,  "Gambler's fallacy fallacy", NULL, NULL},
    {1.3E18,  "Lucky grandmas", NULL, NULL},        // 252

    // fractal engines
    {3.1E18,  "Metabakeries", NULL, NULL},
    {1.55E19, "Mandelbrown sugar", NULL, NULL},
    {1.55E20, "Fractoids", NULL, NULL},
    {1.55E22, "Nested universe theory", NULL, NULL},
    {1.55E24, "Menger sponge cake", NULL, NULL},
    {1.55E26, "One particularly good-\nhumored cow", NULL, NULL},
    {1.55E29, "Chocolate ouroboros", NULL, NULL},
    {1.55E32, "Nested", NULL, NULL},
    {1.55E35, "Space-filling fibers", NULL, NULL},
    {1.55E38, "Endless book of prose", NULL, NULL},
    {1.55E42, "The set of all sets", NULL, NULL},
    {1.55E46, "This upgrade", NULL, NULL},
    {1.55E50, "A box", NULL, NULL},
    {1.55E54, "Multiscale profiling", NULL, NULL},
    {1.55E58, "The more they stay the\nsame", NULL, NULL},
    {1.55E19, "Metagrandmas", NULL, NULL},          // 268

    // javascript consoles
    {7.1E20,  "The JavaScript console for\ndummies", NULL, NULL},
    {3.55E21, "64bit arrays", NULL, NULL},
    {3.55E22, "Stack overflow", NULL, NULL},
    {3.55E24, "Enterprise compiler", NULL, NULL},
    {3.55E26, "Syntactic sugar", NULL, NULL},
    {3.55E28, "A nice cup of coffee", NULL, NULL},
    {3.55E31, "Just-in-time baking", NULL, NULL},
    {3.55E34, "cookies++", NULL, NULL},
    {3.55E37, "Software updates", NULL, NULL},
    {3.55E40, "Game.Loop", NULL, NULL},
    {3.55E44, "eval()", NULL, NULL},
    {3.55E48, "Your biggest fans", NULL, NULL},
    {3.55E52, "Hacker shades", NULL, NULL},
    {3.55E56, "PHP containment vats", NULL, NULL},
    {3.55E60, "Simulation failsafes", NULL, NULL},
    {3.55E21, "Binary grandmas", NULL, NULL},       // 284

    // idleverses
    {1.2E23,  "Manifest destiny", NULL, NULL},
    {6.0E23,  "The multiverse in a\nnutshell", NULL, NULL},
    {6.0E24,  "All-conversion", NULL, NULL},
    {6.0E26,  "Multiverse agents", NULL, NULL},
    {6.0E28,  "Escape plan", NULL, NULL},
    {6.0E30,  "Game design", NULL, NULL},
    {6.0E33,  "Sandbox universes", NULL, NULL},
    {6.0E36,  "Multiverse wars", NULL, NULL},
    {6.0E39,  "Mobile ports", NULL, NULL},
    {6.0E42,  "Encapsulated realities", NULL, NULL},
    {6.0E46,  "Extrinsic clicking", NULL, NULL},
    {6.0E50,  "Universal idling", NULL, NULL},
    {6.0E54,  "Break the fifth wall", NULL, NULL},
    {6.0E58,  "Opposite universe", NULL, NULL},
    {6.0E62,  "The other routes to Rome", NULL, NULL},
    {6.0E23,  "Alternate grandmas", NULL, NULL},    // 300

    // cortex bakers
    {1.9E25,  "Principled neural shackles", NULL, NULL},
    {9.5E25,  "Obey", NULL, NULL},
    {9.5E26,  "A sprinkle of irrationality", NULL, NULL},
    {9.5E28,  "Front and back hemispheres", NULL, NULL},
    {9.5E30,  "Neural networking", NULL, NULL},
    {9.5E32,  "Cosmic brainstorms", NULL, NULL},
    {9.5E35,  "Megatherapy", NULL, NULL},
    {9.5E38,  "Synaptic lubricant", NULL, NULL},
    {9.5E41,  "Psychokinesis", NULL, NULL},
    {9.5E44,  "Spines", NULL, NULL},
    {9.5E48,  "Neuraforming", NULL, NULL},
    {9.5E52,  "Epistemological trickery", NULL, NULL},
    {9.5E56,  "Every possible idea", NULL, NULL},
    {9.5E60,  "The land of dreams", NULL, NULL},
    {9.5E64,  "Intellectual property theft", NULL, NULL},
    {9.5E25,  "Brainy grandmas", NULL, NULL},       // 316

    // you
    {5.4E27,  "Cloning vats", NULL, NULL},
    {2.7E28,  "Energized nutrients", NULL, NULL},
    {2.7E29,  "Stunt doubles", NULL, NULL},
    {2.7E31,  "Clone recycling plant", NULL, NULL},
    {2.7E33,  "Free-range clones", NULL, NULL},
    {2.7E35,  "Genetic tailoring", NULL, NULL},
    {2.7E38,  "Power in diversity", NULL, NULL},
    {2.7E41,  "Self-betterment", NULL, NULL},
    {2.7E44,  "Source control", NULL, NULL},
    {2.7E47,  "United workforce", NULL, NULL},
    {2.7E51,  "Safety patrols", NULL, NULL},
    {2.7E55,  "Clone rights", NULL, NULL},
    {2.7E59,  "One big family", NULL, NULL},
    {2.7E63,  "Fine-tuned body plans", NULL, NULL},
    {2.7E67,  "Reading your clones bedtime\nstories", NULL, NULL},
    {2.7E28,  "Clone grandmas", NULL, NULL},        // 332

    // golden cookies
    {7.77778E8, "Lucky day", NULL, NULL},
    {7.77778E10, "Serendipity", NULL, NULL},
    {7.77778E13, "Get lucky", NULL, NULL},          // 335

    // flavored cookies
    {9.99999E5, "Plain cookies", NULL, NULL},
    {5.0E6, "Sugar cookies", NULL, NULL},
    {1.0E7, "Oatmeal raisin cookies", NULL, NULL},
    {5.0E7, "Peanut butter cookies", NULL, NULL},
    {1.0E8, "Coconut cookies", NULL, NULL},
    {1.0E8, "Macadamia nut cookies", NULL, NULL},
    {1.0E8, "Almond cookies", NULL, NULL},
    {1.0E8, "Hazelnut cookies", NULL, NULL},
    {1.0E8, "Walnut cookies", NULL, NULL},
    {1.0E8, "Cashew cookies", NULL, NULL},
    {5.0E8, "White chocolate cookies", NULL, NULL},
    {5.0E8, "Milk chocolate cookies", NULL, NULL},
    {5.0E9, "Double-chip cookies", NULL, NULL},
    {1.0E10, "White chocolate macadamia\nnut cookies", NULL, NULL},
    {5.0E10, "All-chocolate cookies", NULL, NULL},
    {1.0E11, "Dark chocolate-coated\ncookies", NULL, NULL},
    {1.0E11, "White chocolate-coated\ncookies", NULL, NULL},
    {5.0E11, "Eclipse cookies", NULL, NULL},
    {1.0E12, "Zebra cookies", NULL, NULL},
    {5.0E12, "Snickerdoodles", NULL, NULL},
    {1.0E13, "Stroopwafels", NULL, NULL},
    {5.0E13, "Macaroons", NULL, NULL},
    {1.0E14, "Empire biscuits", NULL, NULL},
    {5.0E14, "Madeleines", NULL, NULL},
    {5.0E14, "Palmiers", NULL, NULL},
    {1.0E15, "Palets", NULL, NULL},
    {1.0E15, "Sabl`s", NULL, NULL},
    {1.0E16, "Gingerbread men", NULL, NULL},
    {1.0E16, "Gingerbread trees", NULL, NULL},
    {5.0E16, "Pure black chocolate\ncookies", NULL, NULL},
    {5.0E16, "Pure white chocolate\ncookies", NULL, NULL},
    {1.0E17, "Ladyfingers", NULL, NULL},
    {5.0E17, "Tuiles", NULL, NULL},
    {1.0E18, "Chocolate-stuffed biscuits", NULL, NULL},
    {5.0E18, "Checker cookies", NULL, NULL},
    {1.0E19, "Butter cookies", NULL, NULL},
    {5.0E19, "Cream cookies", NULL, NULL},
    {1.0E20, "Gingersnaps", NULL, NULL},
    {5.0E20, "Cinnamon cookies", NULL, NULL},
    {1.0E21, "Vanity cookies", NULL, NULL},
    {5.0E21, "Cigars", NULL, NULL},
    {1.0E22, "Pinwheel cookies", NULL, NULL},
    {5.0E22, "Fudge squares", NULL, NULL},
    {1.0E23, "Shortbread biscuits", NULL, NULL},
    {5.0E23, "Millionaires' shortbreads", NULL, NULL},
    {1.0E24, "Caramel cookies", NULL, NULL},
    {5.0E24, "Pecan sandies", NULL, NULL},
    {1.0E25, "Moravian spice cookies", NULL, NULL},
    {5.0E25, "Anzac biscuits", NULL, NULL},
    {1.0E26, "Buttercakes", NULL, NULL},
    {5.0E26, "Ice cream sandwiches", NULL, NULL},
    {1.0E27, "Pink biscuits", NULL, NULL},
    {5.0E27, "Whole grain cookies", NULL, NULL},
    {1.0E28, "Candy cookies", NULL, NULL},
    {5.0E28, "Big chip cookies", NULL, NULL},
    {1.0E29, "One chip cookies", NULL, NULL},
    {5.0E29, "Sprinkles cookies", NULL, NULL},
    {1.0E30, "Peanut butter blossoms", NULL, NULL},
    {5.0E30, "No-bake cookies", NULL, NULL},
    {1.0E31, "Florentines", NULL, NULL},
    {5.0E31, "Chocolate crinkles", NULL, NULL},
    {1.0E32, "Maple cookies", NULL, NULL},
    {5.0E32, "Persian rice cookies", NULL, NULL},
    {1.0E33, "Norwegian cookies", NULL, NULL},
    {5.0E33, "Crispy rice cookies", NULL, NULL},
    {1.0E34, "Ube cookies", NULL, NULL},
    {5.0E34, "Butterscotch cookies", NULL, NULL},
    {1.0E35, "Speculaas", NULL, NULL},
    {5.0E35, "Chocolate oatmeal cookies", NULL, NULL},
    {1.0E36, "Molasses cookies", NULL, NULL},
    {5.0E36, "Biscotti", NULL, NULL},
    {1.0E37, "Waffle cookies", NULL, NULL},
    {5.0E37, "Custard creams", NULL, NULL},
    {1.0E38, "Bourbon biscuits", NULL, NULL},
    {5.0E38, "Mini-cookies", NULL, NULL},
    {1.0E39, "Whoopie pies", NULL, NULL},
    {3.162E39, "Caramel wafer biscuits", NULL, NULL},
    {1.0E40, "Chocolate chip mocha cookies", NULL, NULL},
    {3.1622E40, "Earl Grey cookies", NULL, NULL},
    {3.1622E40, "Chai tea cookies", NULL, NULL},
    {1.0E41, "Corn syrup cookies", NULL, NULL},
    {3.16227E41, "Icebox cookies", NULL, NULL},
    {1.0E42, "Graham crackers", NULL, NULL},
    {3.162E42, "Hardtack", NULL, NULL},
    {1.0E43, "Cornflake cookies", NULL, NULL},
    {3.1622E43, "Tofu cookies", NULL, NULL},
    {3.1622E43, "Gluten-free cookies", NULL, NULL},
    {1.0E44, "Russian bread cookies", NULL, NULL},
    {3.16227E44, "Lebkuchen", NULL, NULL},
    {1.0E45, "Aachener Printen", NULL, NULL},
    {3.162E45, "Canistrelli", NULL, NULL},
    {1.0E46, "Nice biscuits", NULL, NULL},
    {3.1622E46, "French pure butter\ncookies", NULL, NULL},
    {3.1622E46, "Petit beurre", NULL, NULL},
    {1.0E47, "Nanaimo bars", NULL, NULL},
    {3.16227E47, "Berger cookies", NULL, NULL},
    {1.0E48, "Chinsuko", NULL, NULL},
    {1.0E48, "Panda koala biscuits", NULL, NULL},
    {3.162E48, "Putri salju", NULL, NULL},
    {1.0E49, "Milk cookies", NULL, NULL},
    {3.1622E49, "Kruidnoten", NULL, NULL},
    {1.0E50, "Marie biscuits", NULL, NULL},
    {3.16227E50, "Meringue cookies", NULL, NULL},
    {1.0E51, "Yogurt cookies", NULL, NULL},
    {3.162E51, "Thumbprint cookies", NULL, NULL},
    {1.0E52, "Pizzelle", NULL, NULL},
    {3.1622E52, "Granola cookies", NULL, NULL},
    {1.0E53, "Ricotta cookies", NULL, NULL},
    {3.16227E53, "Roze koeken", NULL, NULL},
    {1.0E54, "Peanut butter cup cookies", NULL, NULL},
    {3.162E54, "Sesame cookies", NULL, NULL},
    {1.0E55, "Taiyaki", NULL, NULL},
    {3.1622E55, "Vanillekipferl", NULL, NULL},
    {1.0E56, "Battenberg biscuits", NULL, NULL},
    {3.16227E56, "Rosette cookies", NULL, NULL},
    {1.0E57, "Gangmakers", NULL, NULL},
    {3.1622E57, "Welsh cookies", NULL, NULL},
    {1.0E58, "Raspberry cheesecake\ncookies", NULL, NULL},
    {3.1622E58, "Bokkenpootjes", NULL, NULL},
    {1.0E59, "Fat rascals", NULL, NULL},
    {3.16227E59, "Ischler cookies", NULL, NULL},
    {3.16227E59, "Matcha cookies", NULL, NULL},
    {1.0E60, "Dalgona cookies", NULL, NULL},
    {3.162E60, "Spicy cookies", NULL, NULL},
    {1.0E61, "Smile cookies", NULL, NULL},
    {3.1622E61, "Kolachy cookies", NULL, NULL},
    {1.0E62, "Gomma cookies", NULL, NULL},
    {3.16228E62, "Vegan cookies", NULL, NULL},
    {1.0E63, "Coyotas", NULL, NULL},
    {3.162E63, "Frosted sugar cookies", NULL, NULL},
    {1.0E64, "Marshmallow sandwich\ncookies", NULL, NULL},
    {3.1623E64, "Calculated cookies", NULL, NULL},
    {1.0E65, "Havreflarn", NULL, NULL},
    {3.16228E65, "Alfajores", NULL, NULL},
    {1.0E66, "Gaufrettes", NULL, NULL},
    {3.162E66, "Cookie bars", NULL, NULL},
    {1.0E67, "Snowball cookies", NULL, NULL},
    {3.1623E67, "Sequilhos", NULL, NULL},
    {1.0E68, "Hazelnut swirlies", NULL, NULL},
    {3.16228E68, "Spritz cookies", NULL, NULL},
    {1.0E69, "Mbatata cookies", NULL, NULL},
    {3.162E69, "Springerles", NULL, NULL}
};

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

    double cmp_val = 1E3;
    for (i = 0; i < 15; i++) {
        if (data->handmade_cookies >= cmp_val)
            data->upgrades_unlocked[(TYPE_MOUSE * 15 + i)] = true;
        cmp_val *= 1E2;
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