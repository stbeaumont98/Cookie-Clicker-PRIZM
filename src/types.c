#include <stdint.h>
#include <string.h>
#include "math1.h"

#include "types.h"

const char *building_types[20] = {
	"Cursor", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple",
	"Wizard tower", "Shipment", "Alchemy lab", "Portal",
	"Time machine", "Antimatter cond.", "Prism", "Chancemaker",
	"Fractal engine", "Javascript cons.", "Idleverse", "Cortex baker", "You"
};

const double base_prices[20] = {
	1.5E1, 1E2, 1.1E3, 1.2E4, 1.3E5, 1.4E6, 2.0E7, 3.3E8, 5.1E9, 7.5E10, 1E12,
	1.4E13, 1.7E14, 2.1E15, 2.6E16, 3.1E17, 7.1E19, 1.2E22, 1.9E24, 5.4E26
};

const double base_cps[20] = {
	0.1, 1.0, 8.0, 4.7E1, 2.6E2, 1.4E3, 7.8E3, 4.4E4, 2.6E5, 1.6E6, 1E7,
	6.5E7, 4.3E8, 2.9E9, 2.1E10, 1.5E11, 1.1E12, 8.3E12, 6.4E13, 5.1E14
};

void reset_buildings(struct CookieData *data) {
	for(int i = 0; i < 20; i++) {
		data->buildings[i].price = base_prices[i];
		data->buildings[i].owned = 0;
		data->buildings[i].locked = !(strcmp(building_types[i], "Cursor") == 0 \
			|| strcmp(building_types[i], "Grandma") == 0);
		data->buildings[i].hidden = true;
	}
}

void reset_gold(struct GoldenData *data) {
	data->x = random() % 6;
	data->y = random() % 171;
	data->scale = 2;
	data->effect = random() % 1000 + 1;
	data->time = random() % (600 / data->time_modifier) \
		+ (300 / data->time_modifier) + (13 * data->time_modifier) + 1;
}