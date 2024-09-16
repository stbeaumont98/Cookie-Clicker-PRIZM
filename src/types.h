#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdbool.h>

static char *building_types[20] = {
	"Cursor", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple",
	"Wizard tower", "Shipment", "Alchemy lab", "Portal",
	"Time machine", "Antimatter con.", "Prism", "Chancemaker",
	"Fractal engine", "JS console", "Idleverse", "Cortex baker", "You"
};

static const double base_prices[20] = {
	1.5E-14, 1.0E-13, 1.1E-12, 1.2E-11, 1.3E-10, 1.4E-9, 2.0E-8, 3.3E-7,
	5.1E-6, 7.5E-5, 0.001, 0.014, 0.17, 2.1, 26, 310, 71000, 1.2E7, 1.9E9,
	5.4E11
};

static const double base_cps[20] = {
	1E-16, 1E-15, 8E-15, 4.7E-14, 2.6E-13, 1.4E-12, 7.8E-12, 4.4E-11,
	2.6E-10, 1.6E-9, 1E-8, 6.5E-8, 4.3E-7, 2.9E-6, 2.1E-5, 1.5E-4,
	0.0011, 0.0083, 0.064, 0.51
};

struct Building {
	double price;
	double b_cps;
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