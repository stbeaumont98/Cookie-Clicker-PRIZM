#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdbool.h>

static const char *building_types[20] = {
	"Cursor", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple",
	"Wizard tower", "Shipment", "Alchemy lab", "Portal",
	"Time machine", "Antimatter con.", "Prism", "Chancemaker",
	"Fractal engine", "JS console", "Idleverse", "Cortex baker", "You"
};

static const double base_prices[20] = {
	1.5E1, 1E2, 1.1E3, 1.2E4, 1.3E5, 1.4E6, 2.0E7, 3.3E8, 5.1E9, 7.5E10, 1E12,
	1.4E13, 1.7E14, 2.1E15, 2.6E16, 3.1E17, 7.1E19, 1.2E22, 1.9E24, 5.4E26
};

static const double base_cps[20] = {
	0.1, 1.0, 8.0, 4.7E1, 2.6E2, 1.4E3, 7.8E3, 4.4E4, 2.6E5, 1.6E6, 1E7,
	6.5E7, 4.3E8, 2.9E9, 2.1E10, 1.5E11, 1.1E12, 8.3E12, 6.4E13, 5.1E14
};

struct Building {
	double price;
	double multiplier;
	int16_t owned;
	bool hidden;
	bool locked;
};

struct CookieData {
	double cookies_all_time;
	double cookies;
	double handmade_cookies;
	double cps;
	struct Building buildings[20];
	int16_t buildings_unlocked;
	uint32_t click_count;
	uint16_t gold_click_count;
};

struct GoldenData {
	uint16_t x;
	uint8_t y;
	uint8_t scale;
	uint8_t effect;
	uint8_t time;
};

struct Message {
	char *header;
	char *body;
	uint8_t time;
};

void reset_buildings(struct CookieData *data);

#endif