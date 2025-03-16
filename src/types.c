#include <stdint.h>
#include <string.h>
#include "math1.h"

#include "types.h"

void reset_buildings(struct CookieData *data) {
	for(int i = 0; i < 20; i++) {
		data->buildings[i].price = base_prices[i];
		data->buildings[i].owned = 0;
		data->buildings[i].locked = !(strcmp(building_types[i], "Cursor") == 0 || strcmp(building_types[i], "Grandma") == 0);
		data->buildings[i].hidden = true;
	}
}

void reset_gold(struct GoldenData *data) {
	data->x = random() % 6;
	data->y = random() % 171;
	data->scale = 2;
	data->effect = random() % 1000 + 1;
	data->time = random() % (600 / data->time_modifier) + (300 / data->time_modifier) + (13 * data->time_modifier) + 1;
}