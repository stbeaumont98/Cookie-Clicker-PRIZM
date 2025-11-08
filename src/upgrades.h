#ifndef UPGRADES_H_
#define UPGRADES_H_

#include "types.h"
#include "icons.h"

#define MODE_MULTIPLY 0
#define MODE_ADD 1
#define MODE_MODIFY 2
#define MODE_CPS_PERCENT 3

#define TYPE_CURSOR 0
#define TYPE_MOUSE 1
#define TYPE_GRANDMA 2
#define TYPE_FARM 3
#define TYPE_MINE 4
#define TYPE_FACTORY 5
#define TYPE_BANK 6
#define TYPE_TEMPLE 7
#define TYPE_WIZARD_TOWER 8
#define TYPE_SHIPMENT 9
#define TYPE_ALCHEMY_LAB 10
#define TYPE_PORTAL 11
#define TYPE_TIME_MACHINE 12
#define TYPE_ANTIMATTER_CONDENSER 13
#define TYPE_PRISM 14
#define TYPE_CHANCEMAKER 15
#define TYPE_FRACTAL_ENGINE 16
#define TYPE_JAVASCRIPT_CONSOLE 17
#define TYPE_IDLEVERSE 18
#define TYPE_CORTEX_BAKER 19
#define TYPE_YOU 20
#define TYPE_GOLDEN 21
#define TYPE_FLAVORED_COOKIES 22

extern char *upgrade_types[23];
extern char *upgrade_descriptions[21];
extern char *grandma_descriptions[21];
extern const struct Upgrade upgrades[];

struct Upgrade *filter_unlocked(struct CookieData *data, const struct Upgrade *upgrades, int *filtered_size);
void sort_prices(struct Upgrade arr[], int low, int high, bool bought[]);

void unlock_upgrades(struct CookieData *data);
void enable_upgrade(struct CookieData *data, struct GoldenData *gold, uint16_t id);

#endif