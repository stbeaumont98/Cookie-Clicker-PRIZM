#include "fxcg\display.h"
#include "fxcg\keyboard.h"
#include "fxcg\rtc.h"
#include "keyboard_syscalls.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "sprites.h"

#include "types.h"
#include "draw.h"
#include "math1.h"
#include "keys.h"
#include "save.h"
#include "convert.h"
#include "upgrades.h"

static const double MAX_FRENZY = 77.;
static const double MAX_CLICK_FRENZY = 13.;
static const double MAX_BOOST = 30.;

static const char *stats[9] = {
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

static const char *building_specials[20] = {
	"High-five", "Congregation", "Luxuriant harvest", "Ore vein", "Oiled-up",
	"Juicy profits", "Fervent adoration", "Manabloom", "Delicious lifeforms",
	"Breakthrough", "Righteous cataclysm", "Golden ages", "Extra cycles",
	"Solar flare", "Winning streak", "Macrocosm", "Refactoring",
	"Cosmic nursery", "Brainstorm", "Deduplication"
};

static const char *buildings[20] = {
	" cursors ", " grandmas ", " farms ", " mines ", " factories ", " banks ",
	" temples ", " wizard towers ", " shipments ", " alchemy labs ",
	" portals ", " time machines ", " antimatter condensers ", " prisms ",
	" chancemakers ", " fractal engines ", " javascript consoles ",
	" idleverses ", " cortex bakers ", " You "
};

static const char *blab[39] = {
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
	"Why did you click that?", "Your cookies will never give you up."
};

int *screen;

int get_time() {
	return (int)(RTC_GetTicks() / 128);
}

void set_message(struct Message *msg, const char *header,
	const char *body, uint8_t time) {
	strcpy(msg->header, header);
	strcpy(msg->body, body);
	msg->time = time;
}

void display_msg(const struct Message msg) {
	bool has_header = strlen(msg.header) != 0;
	int width = max(text_width(msg.header), small_text_width(msg.body, false));
	int height = (text_height(msg.body) * 9) + 5;
	int box_width = width + 10;
	int box_height = height + (has_header ? 20 : 0);
	int box_x = (384 - box_width) / 2;
	int box_y =  213 - box_height;

	fill_area(box_x, box_y, box_width, box_height, 0x0000);
	draw_rect(box_x - 2, box_y - 2,
		box_width + 3, box_height + 3, 0x82a4, 1);
	
	if (has_header) {
		disp_string(box_x + 5, box_y + 4, msg.header, 0xad55);
		draw_line(box_x + 5, box_y + 19,
			box_x + width + 3, box_y + 19, 0x632c, 0);
		small_disp_string(box_x + 5, box_y + 24, msg.body, 0xad55, false);
	} else
		small_disp_string(box_x + 5, box_y + 4, msg.body, 0xad55, false);
}

void draw_background() {
    fill_scr(0x22f0);
	for (int i = 0; i < 12; i++) {
		if (i % 2 != 0)
			fill_area(i * 32, 0, 32, 216, 0x2b71);
	}
	copy_sprite_scaled(panel_v, 164, 0, 8, 108, 16, 216, false, 0);
	copy_sprite_scaled(panel_h, 180, 32, 99, 8, 198, 16, false, 0);
	copy_sprite_scaled(panel_h, 186, 32, 99, 8, 198, 16, false, 0);
}

void draw_store_tile(uint16_t x, uint8_t y) {
	fill_area(x, y, 204, 42, 0xad73);
	fill_area(x + 2, y, 202, 2, 0x7bac);
	fill_area(x + 4, y + 2, 200, 2, 0x7bac);
	fill_area(x, y, 2, 40, 0xbdd5);
	fill_area(x + 2, y + 2, 2, 36, 0xbdd5);
	fill_area(x + 2, y + 38, 202, 2, 0x39c5);
	fill_area(x, y + 40, 204, 2, 0x39c5);
}

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

char *get_upgrade_type(const struct CookieData data, uint16_t id) {
	if (id >= 336)
		return data.upgrades_unlocked[336] ? upgrade_types[TYPE_FLAVORED_COOKIES] : "???";
	else {
		uint8_t type = (id - (45 * (id >= 45))) / (15 + (id >= 45)) + 3 * (id >= 45);
		if ((type == TYPE_CURSOR && !data.buildings[type].hidden)
			|| (type >= 2 && type < 21 && !data.buildings[type - 1].hidden)
			|| (type == TYPE_MOUSE && data.upgrades_unlocked[type * 15])
			|| (id >= 333 && id < 336 && data.upgrades_unlocked[333]))
			return upgrade_types[type];
		else
			return "???";
	}
}

char *get_upgrade_description(const struct CookieData data, uint16_t id) {
	uint8_t type = (id - (45 * (id >= 45))) / (15 + (id >= 45)) + 3 * (id >= 45);
	if (!data.upgrades_unlocked[id])
		return "???";
	else {
		if (id == 333 || id == 334)
			return "Golden cookies appear twice as often and last twice as long\non screen.";
		else if (id == 335)
			return "Golden cookie effects last twice as long.";
		else if (id >= 336) {
			if (id < 339 || id == 391)
				return "Cookie production multiplier +1%.";
			else if ((id >= 339 && id < 351) || (id >= 353 && id < 365))
				return "Cookie production multiplier +2%.";
			else if ((id >= 367 && id < 373))
				return "Cookie production multiplier +3%.";
			else if ((id >= 373 && id < 391) || (id >= 392 && id < 410))
				return "Cookie production multiplier +4%.";
			else
				return "Cookie production multiplier +5%.";
		} else {
			switch (type) {
				case TYPE_CURSOR:
					switch (id) {
						case 0:
						case 1:
						case 2:
							return "The mouse and cursors are twice as efficient.";
							break;
						case 3:
							return "The mouse and cursors gain +0.1 cookies for each non-cursor\nobject owned.";
							break;
						case 4:
							return "Multiplies the gain from Thousand fingers by 5.";
							break;
						case 5:
							return "Multiplies the gain from Thousand fingers by 10.";
							break;
						default:
							return "Multiplies the gain from Thousand fingers by 20.";
							break;
					}
					break;
				case TYPE_MOUSE:
					return "Clicking gains +1% of your CpS.";
					break;
				default:
					return (id >= 45 && (id - 44) % 16 == 0) ? grandma_descriptions[type] : upgrade_descriptions[type];
					break;
			}
		}
	}
}

char *get_upgrade_name(const struct CookieData data, uint16_t id) {
	if (data.upgrades_unlocked[id])
		return upgrades[id].name;
	else
		return "???";
}

int main() {
	EnableStatusArea(3);
	EnableDisplayHeader(0, 0);
    Bdisp_EnableColor(1);
	srandom(RTC_GetTicks());
	DrawFrame(0x0000);
	
	int time = get_time(), old_time, one_second;

	struct GoldenData gold;

	struct CookieData data;

	load_game(&data, &gold);

	int f_buttons[6] = {
		KEY_PRGM_F1, KEY_PRGM_F2,
		KEY_PRGM_F3, KEY_PRGM_F4,
		KEY_PRGM_F5, KEY_PRGM_F6
	};

	struct Message msg;

	set_message(&msg, "", "", 0);
	
	int scale_w = 124, scale_h = 126;
	
	int b_sel = 0;
	int b_sel_offset = 0;

	int u_sel = 0;
	int u_sel_offset = 0;

	double raw_cps = get_cps(data);
	double current_cps = (raw_cps * gold.cps_multiplier) \
		+ (raw_cps * gold.cps_multiplier * gold.boost_multiplier);

	double current_cpc = get_cpc(data, current_cps) * gold.click_multiplier;

	char *tmp;
	char *cookie_buf;
	char *price_buf;
	char cps_buf[30];

	bool upgrades_toggle = false;
	bool stats_toggle = false;

	uint8_t autosave_time = 60;

	while (1) {
        int key = PRGM_GetKey();
		
		old_time = time;
		time = get_time();
		one_second = time - old_time;

		keyupdate();

		raw_cps = get_cps(data);
		current_cps = (raw_cps * gold.cps_multiplier) \
			+ (raw_cps * gold.cps_multiplier * gold.boost_multiplier);

		current_cpc =  get_cpc(data, current_cps) * gold.click_multiplier;

		if (stats_toggle) {
			fill_scr(0x0000);
			draw_line(148, 22, 236, 22, 0x632c, 0);
			disp_string(150, 29, "STATISTICS", 0xFFFF);
			draw_line(148, 46, 236, 46, 0x632c, 0);

			copy_sprite_scaled(panel_h, 0, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_h, 198, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_v, 0, 0, 8, 108, 16, 216, false, 0);
			copy_sprite_scaled(panel_v, 368, 0, 8, 108, 16, 216, false, 0);
			
			for (int i = 0; i < 9; i++)
				disp_string(21, 54 + i * 18, stats[i], 0x94b2);
			
			copy_sprite_masked(money, 152, 54, 14, 14, COLOR_RED);
			copy_sprite_masked(money, 214, 72, 14, 14, COLOR_RED);

			tmp = get_display_val(data.cookies, false, false);
			if (text_width(tmp) > 197) {
				free(tmp);
				tmp = get_display_val(data.cookies, false, true);
			}
			disp_string(170, 54, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(data.cookies_all_time, false, false);
			if (text_width(tmp) > 135) {
				free(tmp);
				tmp = get_display_val(data.cookies_all_time, false, true);
			}
			disp_string(232, 72, tmp, 0xFFFF);
			free(tmp);

			int num_buildings = 0;
			for (int i = 0; i < 20; i++)
				num_buildings += data.buildings[i].owned;

			tmp = disp_comma(num_buildings);
			disp_string(156, 90, tmp, 0xFFFF);
			free(tmp);
			
			char mult[10];
			double percent = (data.multiplier * 100.0 * gold.cps_multiplier) \
				+ (gold.boost_multiplier * 100.0);
			tmp = get_display_val(percent, false, false);
			strcpy(mult, "(");
			strcat(mult, tmp);
			free(tmp);
			strcat(mult, "%)");

			tmp = get_display_val(current_cps, (current_cps < 1E3), false);
			if (text_width(tmp) + small_text_width(mult, false) > 186) {
				free(tmp);
				tmp = get_display_val(current_cps, (current_cps < 1E3), true);
			}
			int cps_w = text_width(tmp);
			disp_string(177, 108, tmp, 0xFFFF);
			free(tmp);
			small_disp_string(180 + cps_w, 113, mult, 0xFFFF, false);
			
			tmp = get_display_val(raw_cps, (raw_cps < 1E3), false);
			if (text_width(tmp) > 154) {
				free(tmp);
				tmp = get_display_val(raw_cps, (raw_cps < 1E3), true);
			}
			disp_string(213, 126, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(current_cpc, (current_cpc < 1E3), false);
			if (text_width(tmp) > 207) {
				free(tmp);
				tmp = get_display_val(current_cpc, (current_cpc < 1E3), true);
			}
			disp_string(160, 144, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(data.click_count, false, false);
			disp_string(130, 162, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(data.handmade_cookies, false, false);
			if (text_width(tmp) > 187) {
				free(tmp);
				tmp = get_display_val(data.handmade_cookies, false, true);
			}
			disp_string(180, 180, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(data.gold_click_count, false, false);
			disp_string(185, 198, tmp, 0xFFFF);
			free(tmp);

			if (key_press(KEY_PRGM_EXIT))
				stats_toggle = false;
		} else {
			uint16_t x, color;
			uint8_t y;

			if (upgrades_toggle) {

				// upgrades store

				fill_scr(0x0000);
				
				copy_sprite_scaled(panel_h, 0, 32, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_h, 198, 32, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_v, 0, 0, 8, 108, 16, 216, false, 0);
				copy_sprite_scaled(panel_v, 368, 0, 8, 108, 16, 216, false, 0);
				
				disp_string(172, 10, "Store", 0xffff);
				small_disp_string(18, 37, "UPGRADES", 0xffff, true);

				small_disp_string(28, 5, "[OPTN]", 0xffff, true);
				copy_sprite_1bit(arrow[1], 20, 5, 6, 6, arrow_pal, 0xffff);

				char *b_type = get_upgrade_type(data, u_sel + u_sel_offset);
				x = 366 - small_text_width(b_type, true);
				small_disp_string(x, 37, b_type, 0xffff, true);

				cookie_buf = get_display_val(data.cookies, false, false);
				if (text_width(cookie_buf) > 162) {
					free(cookie_buf);
					cookie_buf = get_display_val(data.cookies, false, true);
				}
				x = 365 - small_text_width(cookie_buf, false);
				small_disp_string(x, 4, cookie_buf, 0xffff, false);
				free(cookie_buf);
				
				x = 365 - small_text_width("cookies", false);
				small_disp_string(x, 12, "cookies", 0xffff, false);

				strcpy(cps_buf, "CpS: ");

				tmp = get_display_val(current_cps, (current_cps < 1E3), false);
				if (text_width(tmp) > 126) {
					free(tmp);
					tmp = get_display_val(current_cps, (current_cps < 1E3), true);
				}
				strcat(cps_buf, tmp);
				free(tmp);

				x = 365 - small_text_width(cps_buf, false);
				small_disp_string(x, 22, cps_buf, 0xffff, false);

				for (int i = 0; i < 4; i++) {
					uint16_t u_id = i + u_sel_offset;

					if (u_id > 478)
						continue;

					copy_sprite_masked(upgrade_frame, 23, 54 + i * 42, 30, 30, COLOR_RED);
					if (upgrades[u_id].sprite != NULL) {
						copy_sprite_4bit(upgrades[u_id].sprite, 26, 57 + i * 42, 24, 24,
							upgrades[u_id].palette, !data.upgrades_unlocked[u_id], 0x4208);
						if (u_id >= 222 && u_id < 236)
							copy_sprite_4bit(rainbow, 26, 57 + i * 42, 24, 24,
								rainbow_pal, !data.upgrades_unlocked[u_id], 0x4208);
					}

					char *name = get_upgrade_name(data, u_id);
					char *desc = get_upgrade_description(data, u_id);

					int n_h = text_height(name), d_h = text_height(desc);

					y = (!data.upgrades_unlocked[u_id] || (n_h == 1 && d_h == 1) ?
						73 : (n_h > 1 ? 80 : 69)) + i * 42;
					color = data.upgrades_unlocked[u_id] ? (data.upgrades[u_id] ? 0x4208 : 0x8410) : 0x4208;

					small_disp_string(57, y, desc, color, false);
					
					y = (!data.upgrades_unlocked[u_id] || (n_h == 1 && d_h == 1) ? 57 : 53) + i * 42;
					color = data.upgrades_unlocked[u_id] ? (data.upgrades[u_id] ? 0x4208 : 0xffff) : 0x4208;
					
					disp_string(57, y, name, color);
					
					if (data.upgrades_unlocked[u_id]) {
						if (!data.upgrades[u_id]) {
							double p = upgrades[u_id].price;
							price_buf = get_display_val(p, false, p >= 1e12);
							x = 348 - text_width(price_buf), y =  53 + i * 42;
							copy_sprite_masked(money, x, y, 14, 14, COLOR_RED);
							x = 364 - text_width(price_buf), y = 54 + i * 42;
							color = (data.cookies >= upgrades[u_id].price) ? 0x67ec : COLOR_RED;
							disp_string(x, y, price_buf, color);
							free(price_buf);
						} else {
							x = 353, y = 53 + i * 42;
							copy_sprite_masked(check, x, y, 11, 10, COLOR_RED);
						}
					} else {
						x = 353, y = 53 + i * 42;
						copy_sprite_masked(lock, x, y, 10, 11, COLOR_RED);
					}
				}

				draw_rect(17, 49 + u_sel * 42, 349, 39, 0xff80, 1);

				if (key_press(KEY_PRGM_DOWN) && u_sel < 3)
					u_sel++;
				else if (key_press(KEY_PRGM_DOWN) && u_sel == 3 && u_sel_offset < 478 - 4)
					u_sel_offset++;

				if (key_press(KEY_PRGM_UP) && u_sel > 0)
					u_sel--;
				else if (key_press(KEY_PRGM_UP) && u_sel == 0 && u_sel_offset > 0)
					u_sel_offset--;

				uint16_t u_id = u_sel + u_sel_offset;

				if (key_press(KEY_PRGM_LEFT) && u_sel_offset >= 15)
					u_sel_offset -= (15 + (u_id > 59));
				else if (key_press(KEY_PRGM_LEFT) && u_sel_offset < 15) {
					u_sel = 0;
					u_sel_offset = 0;
				}

				if (key_press(KEY_PRGM_RIGHT) && u_sel_offset < 478 - 19)
					u_sel_offset += (15 + (u_id >= 44));
				else if (key_press(KEY_PRGM_RIGHT) && u_sel_offset >= 478 - 19) {
					u_sel = 3;
					u_sel_offset = 478 - 4;
				}

				if (key_press(KEY_PRGM_ALPHA)
					&& data.cookies >= upgrades[u_id].price
					&& !data.upgrades[u_id] && data.upgrades_unlocked[u_id]) {
					data.cookies -= upgrades[u_id].price;
					data.upgrades[u_id] = true;
					enable_upgrade(&data, &gold, u_id);
					unlock_upgrades(&data);
				}

			} else {
				draw_background();

				// buildings store

				fill_area(180, 0, 204, 32, 0x0000);

				disp_string(262, 10, "Store", 0xffff);
				small_disp_string(182, 37, "BUILDINGS", 0xffff, true);

				small_disp_string(339, 5, "[OPTN]", 0xffff, true);
				copy_sprite_1bit(arrow[0], 374, 5, 6, 6, arrow_pal, 0xffff);

				int store_size = (data.buildings_unlocked < 4) ? data.buildings_unlocked : 4;

				for (int i = 0; i < store_size; i++) {
					uint8_t b_id = i + b_sel_offset;

					x = 180, y = 48 + i * 42;
					draw_store_tile(x, y);
					copy_sprite_scaled(icons[b_id], x, y, 21, 21, 42, 42,
						data.buildings[b_id].hidden, 0x0000);

					x = 223, y = 70 + i * 42;
					copy_sprite_masked(money, x, y, 14, 14, COLOR_RED);

					price_buf = get_display_val(data.buildings[b_id].price, false, false);

					if ((text_width(price_buf) > 116 && data.buildings[b_id].owned >= 100)
						|| (text_width(price_buf) > 121 && data.buildings[b_id].owned >= 10)
						|| (text_width(price_buf) > 130)) {
						free(price_buf);
						price_buf = get_display_val(data.buildings[b_id].price, false, true);
					}

					x = 240;
					color = (data.cookies >= data.buildings[b_id].price) ? 0x67ec : COLOR_RED;
					disp_string(x, y, price_buf, color);
					free(price_buf);

					if (data.buildings[b_id].owned > 0) {
						char owned_buf[5];
						itoa(data.buildings[b_id].owned, owned_buf, 10);
						disp_string(380 - text_width(owned_buf), 62 + i * 42,
							owned_buf, 0x2924);
					}

					char type[18];
					if (!data.buildings[b_id].hidden)
						strcpy(type, building_types[b_id]);
					else
						strcpy(type, "???");
					disp_string(223, 54 + i * 42, type, 0xffff);
				}

				draw_rect(181, 49 + b_sel * 42, 201, 39, 0xff80, 1);

				if (key_press(KEY_PRGM_DOWN) && b_sel < store_size - 1)
					b_sel++;
				else if (key_press(KEY_PRGM_DOWN) && b_sel == 3 && data.buildings_unlocked > 4
					&& b_sel_offset < data.buildings_unlocked - 4)
					b_sel_offset++;

				if (key_press(KEY_PRGM_UP) && b_sel > 0)
					b_sel--;
				else if (key_press(KEY_PRGM_UP) && b_sel == 0 && b_sel_offset > 0)
					b_sel_offset--;

				uint8_t b_id = b_sel + b_sel_offset;
				if (key_press(KEY_PRGM_ALPHA)
					&& data.cookies >= data.buildings[b_id].price) {
					data.cookies -= data.buildings[b_id].price;
					data.buildings[b_id].owned++;
					data.buildings[b_id].price += (data.buildings[b_id].price * .15);
					data.total_buildings++;
				}

				// end store code

				if (key_press(KEY_PRGM_SHIFT)) {
					scale_w = 112;
					scale_h = 114;
					data.cookies += current_cpc;
					data.cookies_all_time += current_cpc;
					data.handmade_cookies += current_cpc;
					data.click_count++;
				}

				for (int i = 0; i < 20; i++) {
					if (data.cookies_all_time >= base_prices[i])
						data.buildings[i].hidden = false;
					if (i >= 2) {
						if (data.buildings[i].locked && (data.cookies_all_time >= base_prices[i - 2])) {
							data.buildings[i].locked = false;
							data.buildings_unlocked++;
						}
					}
				}

				if (key == 0) {
					scale_w = 124;
					scale_h = 126;
				}
				
				x = (scale_w < 124) ? 26 : 20, y = (scale_h < 126) ? 84 : 78;
				copy_sprite_scaled(perfect_cookie, x, y, 62, 63, scale_w, scale_h, false, 0);

				fill_area(0, 13, 164, 53, 0x0000);

				strcpy(cps_buf, "per sec: ");

				tmp = get_display_val(current_cps, (current_cps < 1E3), false);
				if (text_width(tmp) > 126) {
					free(tmp);
					tmp = get_display_val(current_cps, (current_cps < 1E3), true);
				}
				strcat(cps_buf, tmp);
				free(tmp);

				cookie_buf = get_display_val(data.cookies, false, false);
				if (text_width(cookie_buf) > 162) {
					free(cookie_buf);
					cookie_buf = get_display_val(data.cookies, false, true);
				}

				x = ((164 - text_width(cookie_buf)) / 2) + 1;
				disp_string(x, 19, cookie_buf, 0xffff);
				free(cookie_buf);

				disp_string(53, 36, "cookies", 0xffff);

				x = ((164 - small_text_width(cps_buf, false)) / 2) + 1;
				small_disp_string(x, 53, cps_buf, 0xffff, false);

				double f = (double) gold.frenzy_time / (MAX_FRENZY * gold.effect_modifier);
				double cf = (double) gold.click_frenzy_time / (MAX_CLICK_FRENZY * gold.effect_modifier);
				double b = (double) gold.boost_time / (MAX_BOOST * gold.effect_modifier);

				if (gold.frenzy_time > 0) {
					y = (f < cf && f > b) || (f < b && f > cf) ? 3 : (f < cf && f < b) ? 6 : 0;
					fill_area(0, y, round2(164. * f), 3, 0xddeb);
				}

				if (gold.click_frenzy_time > 0) {
					y = (cf < f && cf > b) || (cf < b && cf > f) ? 3 : (cf < f && cf < b) ? 6 : 0;
					fill_area(0, y, round2(164. * cf), 3, 0xddeb);
				}

				if (gold.boost_time > 0) {
					y = (b < f && b > cf) || (b < cf && b > f) ? 3 : (b < f && b < cf) ? 6 : 0;
					fill_area(0, y, round2(164. * b), 3, 0xddeb);
				}
			}
	
			if (key_press(KEY_PRGM_OPTN)) {
				if (!upgrades_toggle)
					unlock_upgrades(&data);
				upgrades_toggle = !upgrades_toggle;
			}
		}

		// manual save
		if (key_press(KEY_PRGM_EXP)) {
			save_game(data, gold);
			set_message(&msg, "", "Game saved", 2);
		}

		if (gold.frenzy_time <= 0)
			gold.cps_multiplier = 1;
			
		if (gold.click_frenzy_time <= 0)
			gold.click_multiplier = 1;

		if (gold.boost_time <= 0) 
			gold.boost_multiplier = 0;
		
		if (key_press(KEY_PRGM_VARS))
			stats_toggle = !stats_toggle;

		if (msg.time > 0) {
			display_msg(msg);
			if (key_press(KEY_PRGM_EXIT))
				msg.time = 0;
		}
		
		if (key_press(f_buttons[gold.x]) && gold.time <= (13 * gold.time_modifier)) {
			data.gold_click_count++;
			if (gold.effect > 0 && gold.effect <= 425) {
				// Lucky!
				double earned = (data.cookies >= current_cps * 6000) ?
					(max(data.cookies * 0.15, current_cps * 900) + 13) :
					(min(data.cookies * 0.15, current_cps * 900) + 13);
				char msg_buf[30];
				strcpy(msg_buf, "+");
				tmp = get_display_val(earned, false, false);
				strcat(msg_buf, tmp);
				free(tmp);
				strcat(msg_buf, " cookies!");
				set_message(&msg, "Lucky!", msg_buf, 6);

				data.cookies_all_time += earned;
				data.cookies += earned;
			} else if (gold.effect > 425 && gold.effect <= 850) {
				// Frenzy
				gold.frenzy_time = 77 * gold.effect_modifier;
				gold.cps_multiplier = 7;

				char msg_buf[40];
				strcpy(msg_buf, "Cookie production x7 for ");

				tmp = malloc(3);
				itoa(gold.frenzy_time, tmp, 10);
				strcat(msg_buf, tmp);
				free(tmp);

				strcat(msg_buf, " seconds!");

				set_message(&msg, "Frenzy", msg_buf, 6);
			} else if (gold.effect > 850 && gold.effect <= 893) {
				// Click Frenzy
				gold.click_frenzy_time = 13 * gold.effect_modifier;
				gold.click_multiplier = 777;

				char msg_buf[40];
				strcpy(msg_buf, "Clicking power x777 for ");

				tmp = malloc(3);
				itoa(gold.click_frenzy_time, tmp, 10);
				strcat(msg_buf, tmp);
				free(tmp);

				strcat(msg_buf, " seconds!");

				set_message(&msg, "Click Frenzy", msg_buf, 6);
			} else if (gold.effect > 893 && gold.effect <= 996) {
				// Building special
				int cnt = 0;
				for (int i = 0; i < 20; i++) {
					if (data.buildings[i].owned >= 10)
						cnt++;
				}
				if (cnt > 0) {
					
					gold.boost_time = 30 * gold.effect_modifier;

					int r_b = random() % 20; 
					while (data.buildings[r_b].owned < 10)
						r_b = random() % 20;

					gold.boost_multiplier = data.buildings[r_b].owned / 10.0;

					char msg_buf[150];

					strcpy(msg_buf, "Your ");

					char * tmp = malloc(6);
					itoa(data.buildings[r_b].owned, tmp, 10);
					strcat(msg_buf, tmp);
					free(tmp);

					strcat(msg_buf, buildings[r_b]);
					strcat(msg_buf, "are boosting your CpS!\nCookie production +");

					tmp = malloc(6);
					itoa((data.buildings[r_b].owned * 10), tmp, 10);
					strcat(msg_buf, tmp);
					free(tmp);

					strcat(msg_buf, "% for ");

					tmp = malloc(3);
					itoa(gold.boost_time, tmp, 10);
					strcat(msg_buf, tmp);
					free(tmp);

					strcat(msg_buf, " seconds!");

					set_message(&msg, building_specials[r_b], msg_buf, 6);
				} else {
					// Lucky!
					double earned = (data.cookies >= current_cps * 6000) ? \
						(max(data.cookies * 0.15, current_cps * 900) + 13) : \
						(min(data.cookies * 0.15, current_cps * 900) + 13);
					char msg_buf[30];
					strcpy(msg_buf, "+");
					tmp = get_display_val(earned, false, false);
					strcat(msg_buf, tmp);
					free(tmp);
					strcat(msg_buf, " cookies!");
					set_message(&msg, "Lucky!", msg_buf, 6);

					data.cookies_all_time += earned;
					data.cookies += earned;
				}

			} else if (gold.effect > 996) {
				int rblab = random() % 39;
				set_message(&msg, "", blab[rblab], 6);
			}
			reset_gold(&gold);
		}
		
		if (gold.time <= (13 * gold.time_modifier)) {
			
			uint16_t x = 4 + gold.x * 66 + (23 - (gold.scale / 2));
			uint8_t y = gold.y + (23 - (gold.scale / 2));
			copy_sprite_scaled(gold_cookie, x, y, 23, 23,
				gold.scale, gold.scale, false, 0);

			if (gold.time > 0 && gold.scale < 46)
				gold.scale += 2;
			else if (gold.time <= 0 && gold.scale >= 2)
				gold.scale -= 2;
			
			if (gold.time <= 0 && gold.scale <= 2)
				reset_gold(&gold);
		}

		// autosave when the time runs out
		if (autosave_time == 0) {
			save_game(data, gold);
			set_message(&msg, "", "Game saved", 2);
			autosave_time = 60;
		}

		if (one_second) {
			data.cookies += current_cps;
			data.cookies_all_time += current_cps;

			if (gold.frenzy_time > 0)
				gold.frenzy_time--;
			if (gold.click_frenzy_time > 0)
				gold.click_frenzy_time--;
			if (gold.boost_time > 0)
				gold.boost_time--;
			if (msg.time > 0)
				msg.time--;
			if (gold.time > 0)
				gold.time--;
			if (autosave_time > 0)
				autosave_time--;
		}

        if (key == KEY_PRGM_MENU) {
			GetKey(&key);
			DrawFrame(0x0000);
		}

        Bdisp_PutDisp_DD();
        Bdisp_AllClr_VRAM();
	}
	return 0;
}
