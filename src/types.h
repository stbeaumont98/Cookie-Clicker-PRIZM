#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <fxcg/display.h>

extern const char *building_types[20];
extern const double base_prices[20];
extern const double base_cps[20];

struct Building {
	double price;
	double multiplier;
	double modifier;
	double percent;
	int16_t owned;
	bool hidden;
	bool locked;
	double cps;
	bool gma;
};

struct Upgrade {
	uint16_t id;
	double price;
	char *name;
	const unsigned char *sprite;
	const color_t *palette;
};

struct GoldenData {
	uint16_t x;
	uint8_t y;
	uint8_t scale;
	uint16_t effect;
	uint16_t time;
	uint8_t frenzy_time;
	double cps_multiplier;
	uint8_t click_frenzy_time;
	double click_multiplier;
	uint8_t boost_time;
	double boost_multiplier;
	uint8_t time_modifier;
	uint8_t effect_modifier;
};

struct CookieData {
	double cookies_all_time;
	double cookies;
	double handmade_cookies;
	struct Building buildings[20];
	int16_t buildings_unlocked;
	uint32_t click_count;
	uint16_t gold_click_count;
	uint16_t total_buildings;
	bool upgrades[478];
	bool upgrades_unlocked[478];
	double multiplier;
};

struct Message {
	char header[30];
	char body[150];
	uint8_t time;
};

void reset_buildings(struct CookieData *data);
void reset_gold(struct GoldenData *data);

#endif