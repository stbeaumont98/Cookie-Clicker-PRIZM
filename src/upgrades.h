#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

#define MODE_MULTIPLY 0
#define MODE_ADD 1
#define MODE_MODIFY 2
#define MODE_CPS_PERCENT 3

#define TYPE_CURSOR 0
#define TYPE_GRANDMA 1
#define TYPE_FARM 2
#define TYPE_MINE 3
#define TYPE_FACTORY 4
#define TYPE_BANK 5
#define TYPE_TEMPLE 6
#define TYPE_WIZARD_TOWER 7
#define TYPE_SHIPMENT 8
#define TYPE_ALCHEMY_LAB 9
#define TYPE_PORTAL 10
#define TYPE_TIME_MACHINE 11
#define TYPE_ANTIMATTER_CONDENSER 12
#define TYPE_PRISM 13
#define TYPE_CHANCEMAKER 14
#define TYPE_FRACTAL_ENGINE 15
#define TYPE_JAVASCRIPT_CONSOLE 16
#define TYPE_IDLEVERSE 17
#define TYPE_CORTEX_BAKER 18
#define TYPE_YOU 19
#define TYPE_MOUSE 20
#define TYPE_GOLDEN 21

extern char *upgrade_types[22];
extern char *upgrade_descriptions[20];
extern const struct Upgrade upgrades[];

void unlock_upgrades(struct CookieData *data);
void enable_upgrade(struct CookieData *data, struct GoldenData *gold, int id);

#endif