#ifndef DATA_H_
#define DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include <fxcg/display.h>

struct Cheats {
	bool on;	// cheats toggle
	bool acg;	// auto-click golden cookies
	bool hc;	// press and hold to click continuously
	bool fb;	// all buildings are free
	bool fu;	// all upgrades are free
};

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
	int32_t time;
	int32_t frenzy_time;
	double cps_multiplier;
	int32_t click_frenzy_time;
	double click_multiplier;
	int32_t boost_time;
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
	uint16_t upgrades_count;
	double multiplier;
	struct Cheats cheats;
};

struct Message {
	char header[40];
	char body[150];
	int32_t time;
};

extern const double MAX_FRENZY;
extern const double MAX_CLICK_FRENZY;
extern const double MAX_BOOST;

extern const char *building_types[20];
extern const char *building_specials[20];
extern const char *buildings[20];

extern const double base_prices[20];
extern const double base_cps[20];

extern const char *stats[9];
extern const char *blab[39];

extern const char *suffixes[25];
extern const char *suffixes_abrev[25];

double get_cps(const struct CookieData data);
double get_cpc(const struct CookieData data, double cps);
void reset_buildings(struct CookieData *data);
void reset_gold(struct GoldenData *data);
void set_msg(struct Message *msg, const char *header, const char *body, uint8_t time);

#endif