#include <string.h>

#include "types.h"

void reset_buildings(struct CookieData *data) {
	for(int i = 0; i < 20; i++) {
		data->buildings[i].price = base_prices[i];
		data->buildings[i].owned = 0;
		data->buildings[i].locked = !(strcmp(building_types[i], "Cursor") == 0 || strcmp(building_types[i], "Grandm*a") == 0);
		data->buildings[i].hidden = true;
	}
}