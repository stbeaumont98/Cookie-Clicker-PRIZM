#include <stdint.h>
#include <string.h>
#include "math1.h"
#include "time.h"
#include "upgrades.h"

#include "data.h"

const double MAX_FRENZY = 77.;
const double MAX_CLICK_FRENZY = 13.;
const double MAX_BOOST = 30.;

const char *building_types[20] = {
	"Cursor", "Grandma", "Farm", "Mine", "Factory", "Bank", "Temple",
	"Wizard tower", "Shipment", "Alchemy lab", "Portal",
	"Time machine", "Antimatter cond.", "Prism", "Chancemaker",
	"Fractal engine", "Javascript cons.", "Idleverse", "Cortex baker", "You"
};

const char *building_specials[20] = {
	"High-five", "Congregation", "Luxuriant harvest", "Ore vein", "Oiled-up",
	"Juicy profits", "Fervent adoration", "Manabloom", "Delicious lifeforms",
	"Breakthrough", "Righteous cataclysm", "Golden ages", "Extra cycles",
	"Solar flare", "Winning streak", "Macrocosm", "Refactoring",
	"Cosmic nursery", "Brainstorm", "Deduplication"
};

const char *buildings[20] = {
	" cursors ", " grandmas ", " farms ", " mines ", " factories ", " banks ",
	" temples ", " wizard towers ", " shipments ", " alchemy labs ",
	" portals ", " time machines ", " antimatter condensers ", " prisms ",
	" chancemakers ", " fractal engines ", " javascript consoles ",
	" idleverses ", " cortex bakers ", " You "
};

const double base_prices[20] = {
	1.5E1, 1E2, 1.1E3, 1.2E4, 1.3E5, 1.4E6, 2.0E7, 3.3E8, 5.1E9, 7.5E10, 1E12,
	1.4E13, 1.7E14, 2.1E15, 2.6E16, 3.1E17, 7.1E19, 1.2E22, 1.9E24, 5.4E26
};

const double base_cps[20] = {
	0.1, 1.0, 8.0, 4.7E1, 2.6E2, 1.4E3, 7.8E3, 4.4E4, 2.6E5, 1.6E6, 1E7,
	6.5E7, 4.3E8, 2.9E9, 2.1E10, 1.5E11, 1.1E12, 8.3E12, 6.4E13, 5.1E14
};

const char *stats[9] = {
	"Cookies in bank:",
	"Cookies baked (all time):",
	"Buildings owned:",
	"Cookies per second:",
	"Raw cookies per second:",
	"Cookies per click:",
	"Cookie clicks:",
	"Hand-made cookies:",
	"Golden cookie clicks:"
};

const char *blab[39] = {
	"Cookie crumbliness x3 for 60 seconds!",
	"Chocolatiness x7 for 77 seconds!",
	"Dough elasticity halved for 66 seconds!",
	"Golden cookie shininess doubled for 3 seconds!",
	"World economy halved for 30 seconds!",
	"Grandma kisses 23% stingier for 45 seconds!", "Thanks for clicking!",
	"Fooled you! This one was just a test.", "Golden cookies clicked +1!",
	"Your click has been registered.\nThank you for your cooperation.",
	"Thanks! That hit the spot!", "Thank you. A team has been dispatched.",
	"They know.",
	"Oops. This was just a chocolate\ncookie with shiny aluminium foil.",
	"Eschaton immanentized!", "Oh, that tickled!", "Again.",
	"You've made a grave mistake.", "Chocolate chips reshuffled!",
	"Randomized chance card outcome!", "Mouse acceleration +0.03%!",
	"Gained 1 extra!", "Sorry, better luck next time!", "I felt that.",
	"Nice try, but no.", "Wait, sorry, I wasn't ready yet.", "Yippee!",
	"Bones removed.", "Organs added.", "Did you just click that?",
	"Huh? Oh, there was nothing there.", "You saw nothing.",
	"It seems you hallucinated that cookie.",
	"This golden cookie was a complete fabrication.",
	"In theory there is no wrong way of clicking\na golden cookie, but you did that, somehow.",
	"All cookies multiplied by 999!\nAll cookies divided by 999!", "Why?",
	"Why did you click that?", "Your cookies are never gonna give you up."
};

const double price_mult[3] = {1., 20.303718238, 7828749.671335256};

double get_cps(const struct CookieData data) {
	uint16_t non_cursors = data.total_buildings - data.buildings[TYPE_CURSOR].owned;
	double raw_cps = (base_cps[TYPE_CURSOR] * (double) data.buildings[TYPE_CURSOR].owned \
		* data.buildings[TYPE_CURSOR].multiplier) + \
		(data.buildings[TYPE_CURSOR].modifier * (double) data.buildings[TYPE_CURSOR].owned * (double) non_cursors);
	raw_cps += base_cps[1] * (double) data.buildings[1].owned * data.buildings[1].multiplier;
	for (int i = 2; i < 20; i++)
		raw_cps += (base_cps[i] * (double) data.buildings[i].owned * data.buildings[i].multiplier) \
			* (1.0 + ((data.buildings[i].gma ? 0.01 : 0.0) * ((double) data.buildings[1].owned / (double) (i - 1))));
	return raw_cps * data.multiplier;
}

double get_cpc(const struct CookieData data, double cps) {
	uint16_t non_cursors = data.total_buildings - data.buildings[TYPE_CURSOR].owned;
	return data.buildings[TYPE_CURSOR].multiplier \
		+ (data.buildings[TYPE_CURSOR].modifier * (double) non_cursors) \
		+ (data.buildings[TYPE_CURSOR].percent * cps);
}


void reset_buildings(struct CookieData *data) {
	for(int i = 0; i < 20; i++) {
		data->buildings[i].price = base_prices[i];
		data->buildings[i].owned = 0;
		data->buildings[i].locked = !(strcmp(building_types[i], "Cursor") == 0 \
			|| strcmp(building_types[i], "Grandma") == 0);
		data->buildings[i].hidden = true;
	}
}

void rand_gold(struct GoldenData *data) {
	data->x = random() % 6;
	data->y = random() % 171;
	data->scale = 2;
	data->effect = random() % 1000 + 1;
	data->time = random() % ((600 / data->time_modifier) * 128) \
		+ ((300 / data->time_modifier) * 128) + (13 * data->time_modifier * 128) + 128;
}

void set_msg(struct Message *msg, const char *header,
	const char *body, uint8_t time) {
	strcpy(msg->header, header);
	strcpy(msg->body, body);
	msg->time = ticks(time);
}

void push_note(struct Message notes[3], const char *header,
	const char *body, uint8_t time, uint8_t *notes_cnt) {

	for (int i = 0; i < 3; i++) {
		if (notes[i].time <= 0) {
			set_msg(&notes[i], header, body, time);
			(*notes_cnt)++;
			return;
		}
	}
	// copy values from index 1 to index 0
	set_msg(&notes[0], notes[1].header, notes[1].body, secs(notes[1].time));
	// copy values from index 2 to index 1
	set_msg(&notes[1], notes[2].header, notes[2].body, secs(notes[2].time));
	// copy new message into index 2
	set_msg(&notes[2], header, body, time);
}