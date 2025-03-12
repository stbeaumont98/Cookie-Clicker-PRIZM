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

#define MODE_DEFAULT 0
#define MODE_UPGRADES 1
#define MODE_STATS 2

static const double MAX_FRENZY = 77.;
static const double MAX_CLICK_FRENZY = 13.;
static const double MAX_BOOST = 30.;

static const char *building_specials[20] = {
	"High-five", "Congregation", "Luxuriant harvest", "Ore vein", "Oiled-up",
	"Juicy profits", "Fervent adoration", "Manabloom", "Delicious lifeforms",
	"Breakthrough", "Righteous cataclysm", "Golden ages", "Extra cycles",
	"Solar flare", "Winning streak", "Macrocosm", "Refactoring",
	"Cosmic nursery", "Brainstorm", "Deduplication"
};

static const char *buildings[20] = {
	" cursors ", " grandmas ", " farms ", " mines ", " factories ", " banks ", " temples ",
	" wizard towers ", " shipments ", " alchemy labs ", " portals ", " time machines ",
	" antimatter condensers ", " prisms ", " chancemakers ", " fractal engines ",
	" javascript consoles ", " idleverses ", " cortex bakers ", " You "
};

static const char *blab[39] = {
	"Cookie crumbliness x3 for 60 seconds!", "Chocolatiness x7 for 77 seconds!",
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

void set_message(struct Message *msg, const char *header, const char *body, uint8_t time) {
	strcpy(msg->header, header);
	strcpy(msg->body, body);
	msg->time = time;
}

void display_msg(const struct Message msg) {
	bool has_header = strlen(msg.header) != 0;
	int width = max(text_width(msg.header), text_width(msg.body));
	int height = text_height(msg.body) * 19;
	int box_width = width + 11;
	int box_height = height + (has_header ? 23 : 0);
	int box_x = (384 - box_width) / 2;
	int box_y =  213 - box_height;

	fill_area(box_x, box_y, box_width, box_height, 0x0000);
	draw_rect(box_x - 2, box_y - 2, box_width + 3, box_height + 3, rgb_color(135, 86, 38), 1);

	disp_string(box_x + 5, box_y + 4, has_header ? msg.header : msg.body, rgb_color(169, 169, 169));
	
	if (has_header) {
		draw_line(box_x + 5, box_y + 22, box_x + width + 3, box_y + 22, rgb_color(100, 100, 100), 0);
		disp_string(box_x + 5, box_y + 26, msg.body, rgb_color(169, 169, 169));
	}
}

void draw_background() {
    fill_scr(rgb_color(35, 94, 128));
	for (int i = 0; i < 12; i++) {
		if (i % 2 != 0)
			fill_area(i * 32, 0, 32, 216, rgb_color(44, 108, 143));
	}
	copy_sprite_scaled(panel_vertical, 164, 0, 8, 108, 16, 216, false, 0);
	copy_sprite_scaled(panel_horizontal, 180, 32, 99, 8, 198, 16, false, 0);
	copy_sprite_scaled(panel_horizontal, 186, 32, 99, 8, 198, 16, false, 0);
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

double get_cps(struct CookieData data) {
	double raw_cps = 0;
	for (int i = 0; i < 20; i++) {
		raw_cps += (base_cps[i] * data.buildings[i].owned) * data.buildings[i].multiplier + data.buildings[i].modifier;
	}
	return raw_cps;
}

int main() {
    Bdisp_EnableColor(1);
	srandom(RTC_GetTicks());
	DrawFrame(0x0000);
	
	int time = get_time(), old_time, one_second;

	struct GoldenData gold;

	struct CookieData data;
	load_game(&data, &gold);

	int f_buttons[6] = {KEY_PRGM_F1, KEY_PRGM_F2, KEY_PRGM_F3, KEY_PRGM_F4, KEY_PRGM_F5, KEY_PRGM_F6};

	struct Message msg;

	msg.header = malloc(30);
	msg.body = malloc(150);
	
	int scale_w = 124, scale_h = 126;
	
	int b_sel = 0;
	int b_sel_offset = 0;

	int u_sel = 0;
	int u_sel_offset = 0;

	int mode = 0;

	double raw_cps = get_cps(data);
	double current_cps = (raw_cps * gold.cps_multiplier) + (raw_cps * gold.cps_multiplier * gold.boost_multiplier);

	double cpc = data.buildings[BUILDING_CURSOR].multiplier + data.buildings[BUILDING_CURSOR].modifier;

	while (1) {
        int key = PRGM_GetKey();
        if (key == KEY_PRGM_MENU) {
			save_game(data, gold);
			GetKey(&key);
			free(msg.header);
			free(msg.body);
			return 0;
		}
		
		old_time = time;
		time = get_time();
		one_second = time - old_time;

		keyupdate();

		raw_cps = get_cps(data);
		cpc = data.buildings[BUILDING_CURSOR].multiplier + data.buildings[BUILDING_CURSOR].modifier;

		current_cps = (raw_cps * gold.cps_multiplier) + (raw_cps * gold.cps_multiplier * gold.boost_multiplier);

		switch (mode) {
			case MODE_STATS:
				fill_scr(0x0000);
				draw_line(148, 22, 236, 22, rgb_color(100, 100, 100), 0);
				disp_string(150, 29, "STATISTICS", 0xFFFF);
				draw_line(148, 46, 236, 46, rgb_color(100, 100, 100), 0);

				copy_sprite_scaled(panel_horizontal, 0, 0, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_horizontal, 198, 0, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_vertical, 0, 0, 8, 108, 16, 216, false, 0);
				copy_sprite_scaled(panel_vertical, 368, 0, 8, 108, 16, 216, false, 0);
				
				disp_string(21, 54, "Cookies in bank:\nCookies baked (all time):\nBuildings owned:\nCookies per second:\nRaw cookies per second:\nCookies per click:\nCookie clicks:\nHand-made cookies:\nGolden cookie clicks:", rgb_color(150, 150, 150));
				
				copy_sprite_masked(money, 152, 54, 14, 14, COLOR_RED);
				copy_sprite_masked(money, 214, 72, 14, 14, COLOR_RED);

				char *tmp = get_display_val(data.cookies, false, false);
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

				tmp = get_display_val(current_cps, true, false);
				if (text_width(tmp) > 190) {
					free(tmp);
					tmp = get_display_val(current_cps, true, true);
				}
				disp_string(177, 108, tmp, 0xFFFF);
				free(tmp);
				
				tmp = get_display_val(raw_cps, true, false);
				if (text_width(tmp) > 154) {
					free(tmp);
					tmp = get_display_val(raw_cps, true, true);
				}
				disp_string(213, 126, tmp, 0xFFFF);
				free(tmp);

				tmp = get_display_val(cpc * gold.click_multiplier, true, true);
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

				if ((keydownlast(KEY_PRGM_EXIT) && !keydownhold(KEY_PRGM_EXIT)) || key == KEY_PRGM_EXIT)
						mode = MODE_DEFAULT;
				break;
			case MODE_UPGRADES:

				// upgrades store

				fill_scr(0x0000);
				
				copy_sprite_scaled(panel_horizontal, 0, 32, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_horizontal, 198, 32, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_vertical, 0, 0, 8, 108, 16, 216, false, 0);
				copy_sprite_scaled(panel_vertical, 368, 0, 8, 108, 16, 216, false, 0);
				
				disp_string(172, 10, "Store", 0xffff);
				small_disp_string(18, 37, "UPGRADES", 0xf6d7);

				for (int i = 0; i < 4; i++) {
					char name[0x80];
					strcpy(name, upgrades[i + u_sel_offset].name);
					char desc[0xff];
					strcpy(desc, upgrades[i + u_sel_offset].description);
					disp_string(21, 54 + i * 42, upgrades[i + u_sel_offset].unlocked ? name : "???", upgrades[i + u_sel_offset].unlocked ? 0xffff : 0x4208);
					small_disp_string(21, 70 + i * 42, upgrades[i + u_sel_offset].unlocked ? desc : "???", upgrades[i + u_sel_offset].unlocked ? 0x8410 : 0x4208);
					if (upgrades[i + u_sel_offset].unlocked) {
					char *price_buf = get_display_val(upgrades[i + u_sel_offset].price, false, false);
						copy_sprite_masked(money, 348 - text_width(price_buf), 53 + i * 42, 14, 14, COLOR_RED);
						disp_string(364 - text_width(price_buf), 54 + i * 42, price_buf, (data.cookies >= upgrades[i + u_sel_offset].price) ? 0x67ec : COLOR_RED);
						free(price_buf);
					} else {
						copy_sprite_masked(lock, 353, 53 + i * 42, 10, 11, COLOR_RED);
					}
				}

				draw_rect(17, 49 + u_sel * 42, 349, 39, 0xff80, 1);
				
				if (((keydownlast(KEY_PRGM_LEFT) && !keydownhold(KEY_PRGM_LEFT)) || key == KEY_PRGM_LEFT) && mode == MODE_UPGRADES)
					mode = MODE_DEFAULT;

				if (((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) || key == KEY_PRGM_DOWN) && u_sel < 3) {
					u_sel++;
				} else if (((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) || key == KEY_PRGM_DOWN) && u_sel == 3) {
					u_sel_offset++;
				}
				if (((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) || key == KEY_PRGM_UP) && u_sel > 0) {
					u_sel--;
				} else if (((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) || key == KEY_PRGM_UP) && u_sel == 0 && u_sel_offset > 0) {
					u_sel_offset--;
				}

				if (((keydownlast(KEY_PRGM_ALPHA) && !keydownhold(KEY_PRGM_ALPHA)) || key == KEY_PRGM_ALPHA) && data.cookies >= upgrades[u_sel + u_sel_offset].price && !upgrades[u_sel + u_sel_offset].owned) {
					data.cookies -= upgrades[u_sel + u_sel_offset].price;
					upgrades[u_sel + u_sel_offset].owned = true;
					enable_upgrade(&data, u_sel + u_sel_offset);
				}

				break;
			default:
				draw_background();

				// start store code

				fill_area(180, 0, 204, 32, 0x0000);

				disp_string(262, 10, "Store", 0xffff);
				small_disp_string(182, 37, "BUILDINGS", 0xf6d7);

				int store_size = (data.buildings_unlocked < 4) ? data.buildings_unlocked : 4;

				for (int i = 0; i < store_size; i++) {
					draw_store_tile(180, 48 + i * 42);
					copy_sprite_scaled(icons[i + b_sel_offset], 180, 48 + i * 42, 21, 21, 42, 42, data.buildings[i + b_sel_offset].hidden, 0x0000);
					copy_sprite_masked(money, 223, 70 + i * 42, 14, 14, COLOR_RED);
					char *price_buf = get_display_val(data.buildings[i + b_sel_offset].price, false, false);
					if ((text_width(price_buf) > 116 && data.buildings[i + b_sel_offset].owned >= 100) ||
						(text_width(price_buf) > 121 && data.buildings[i + b_sel_offset].owned >= 10) ||
						(text_width(price_buf) > 130)) {
						free(price_buf);
						price_buf = get_display_val(data.buildings[i + b_sel_offset].price, false, true);
					}
					disp_string(240, 70 + i * 42, price_buf, (data.cookies >= data.buildings[i + b_sel_offset].price) ? 0x67ec : COLOR_RED);
					free(price_buf);

					char owned_buf[5];
					itoa(data.buildings[i+b_sel_offset].owned, owned_buf, 10);
					disp_string(380 - text_width(owned_buf), 62 + i * 42, owned_buf, 0x0000);

					char type[18];
					if (!data.buildings[i + b_sel_offset].hidden)
						strcpy(type, building_types[i + b_sel_offset]);
					else
						strcpy(type, "???");
					disp_string(223, 54 + i * 42, type, 0xffff);
				}

				draw_rect(181, 49 + b_sel * 42, 201, 39, 0xff80, 1);

				if (((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) || key == KEY_PRGM_DOWN) && b_sel < store_size - 1) {
					b_sel++;
				} else if (((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) || key == KEY_PRGM_DOWN) && b_sel == 3 && data.buildings_unlocked > 4 && b_sel_offset < data.buildings_unlocked - 4) {
					b_sel_offset++;
				}
				if (((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) || key == KEY_PRGM_UP) && b_sel > 0) {
					b_sel--;
				} else if (((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) || key == KEY_PRGM_UP) && b_sel == 0 && b_sel_offset > 0) {
					b_sel_offset--;
				}
				if (((keydownlast(KEY_PRGM_ALPHA) && !keydownhold(KEY_PRGM_ALPHA)) || key == KEY_PRGM_ALPHA) && data.cookies >= data.buildings[b_sel + b_sel_offset].price) {
					data.cookies -= data.buildings[b_sel + b_sel_offset].price;
					data.buildings[b_sel + b_sel_offset].owned++;
					data.buildings[b_sel + b_sel_offset].price += (data.buildings[b_sel + b_sel_offset].price * .15);
				}

				// end store code

				if (((keydownlast(KEY_PRGM_RIGHT) && !keydownhold(KEY_PRGM_RIGHT)) || key == KEY_PRGM_RIGHT) && mode == MODE_DEFAULT) {
					unlock_upgrades(data, upgrades);
					mode = MODE_UPGRADES;
				}

				if ((keydownlast(KEY_PRGM_SHIFT) && !keydownhold(KEY_PRGM_SHIFT)) || key == KEY_PRGM_SHIFT) {
					scale_w = 112;
					scale_h = 114;
					data.cookies += cpc * gold.click_multiplier;
					data.cookies_all_time += cpc * gold.click_multiplier;
					data.handmade_cookies += cpc * gold.click_multiplier;
					data.click_count++;
				}

				double tmp_cps = 0;
				for (int i = 0; i < 20; i++) {
					tmp_cps += data.buildings[i].owned * base_cps[i];

					if (data.cookies_all_time >= base_prices[i])
						data.buildings[i].hidden = false;
					if (i >= 2) {
						if (data.buildings[i].locked && (data.cookies_all_time >= base_prices[i - 2])) {
							data.buildings[i].locked = false;
							data.buildings_unlocked++;
						}
					}
				}

				raw_cps = tmp_cps;

				if (key == 0) {
					scale_w = 124;
					scale_h = 126;
				}
				
				copy_sprite_scaled(perfect_cookie, (scale_w < 124) ? 26 : 20, (scale_h < 126) ? 86 : 80, 62, 63, scale_w, scale_h, false, 0);
				fill_area(0, 10, 164, 60, 0x0000);
				
				char cps_buf[30];

				strcpy(cps_buf, "CpS: ");

				tmp = get_display_val(current_cps, true, false);
				if (text_width(tmp) > 126) {
					free(tmp);
					tmp = get_display_val(current_cps, true, true);
				}
				strcat(cps_buf, tmp);
				free(tmp);

				char *cookie_buf = get_display_val(data.cookies, false, false);
				if (text_width(cookie_buf) > 162) {
					free(cookie_buf);
					cookie_buf = get_display_val(data.cookies, false, true);
				}
				disp_string(((164 - text_width(cookie_buf)) / 2) + 1, 17, cookie_buf, 0xffff);
				free(cookie_buf);

				disp_string(53, 34, "cookies", 0xffff);

				disp_string(((164 - text_width(cps_buf)) / 2) + 1, 51, cps_buf, 0xffff);

				if (msg.time > 0) {
					display_msg(msg);
					if ((keydownlast(KEY_PRGM_EXIT) && !keydownhold(KEY_PRGM_EXIT)) || key == KEY_PRGM_EXIT)
						msg.time = 0;
				}
				
				if (((keydownlast(f_buttons[gold.x]) && !keydownhold(f_buttons[gold.x])) || key == f_buttons[gold.x]) && gold.time <= 13) {
					data.gold_click_count++;
					if (gold.effect > 0 && gold.effect <= 425) {
						// Lucky!
						double earned = (data.cookies >= current_cps * 6000) ?
							(max(data.cookies * 0.15, current_cps * 900) + 13) :
							(min(data.cookies * 0.15, current_cps * 900) + 13);
						char msg_buf[30];
						strcpy(msg_buf, "+");
						char *tmp = get_display_val(earned, false, false);
						strcat(msg_buf, tmp);
						free(tmp);
						strcat(msg_buf, " cookies!");
						set_message(&msg, "Lucky!", msg_buf, 6);

						data.cookies_all_time += earned;
						data.cookies += earned;
					} else if (gold.effect > 425 && gold.effect <= 850) {
						// Frenzy
						set_message(&msg, "Frenzy", "Cookie production x7 for 77 seconds!", 6);
						gold.cps_multiplier = 7;
						gold.frenzy_time = 77;
					} else if (gold.effect > 850 && gold.effect <= 893) {
						// Click Frenzy
						set_message(&msg, "Click Frenzy", "Clicking power x777 for 13 seconds!", 6);
						gold.click_multiplier = 777;
						gold.click_frenzy_time = 13;
					} else if (gold.effect > 893 && gold.effect <= 996) {
						// Building special
						int cnt = 0;
						for (int i = 0; i < 20; i++) {
							if (data.buildings[i].owned >= 10)
								cnt++;
						}
						if (cnt > 0) {
							int r_b = random() % 20; 
							while (data.buildings[r_b].owned < 10)
								r_b = random() % 20;

							char msg_buf[150];

							strcpy(msg_buf, "Your ");

							char * tmp = malloc(6);
							itoa(data.buildings[r_b].owned, tmp, 10);
							strcat(msg_buf, tmp);
							free(tmp);

							strcat(msg_buf, buildings[r_b]);
							strcat(msg_buf, "are boosting");
							strcat(msg_buf, strlen(buildings[r_b]) >= 15 ? "\n" : " ");
							strcat(msg_buf, "your raw_cps!");
							strcat(msg_buf, strlen(buildings[r_b]) >= 15 ? " " : "\n");
							strcat(msg_buf, "Cookie production +");

							tmp = malloc(6);
							itoa((data.buildings[r_b].owned * 10), tmp, 10);
							strcat(msg_buf, tmp);
							free(tmp);

							strcat(msg_buf, "% for");
							strcat(msg_buf, strlen(buildings[r_b]) >= 15 ? "\n" : " ");
							strcat(msg_buf, "30 seconds!");

							set_message(&msg, building_specials[r_b], msg_buf, 6);

							gold.boost_multiplier = data.buildings[r_b].owned / 10.0;
							gold.boost_time = 30;
						} else {
							// Lucky!
							double earned = (data.cookies >= current_cps * 6000) ?
								(max(data.cookies * 0.15, current_cps * 900) + 13) :
								(min(data.cookies * 0.15, current_cps * 900) + 13);
							char msg_buf[30];
							strcpy(msg_buf, "+");
							char *tmp = get_display_val(earned, false, false);
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
				
				if (gold.frenzy_time <= 0)
					gold.cps_multiplier = 1;
				else
					fill_area(0,
						(((double) gold.frenzy_time / MAX_FRENZY) < ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) && ((double) gold.frenzy_time / MAX_FRENZY) > ((double) gold.boost_time / MAX_BOOST)) || 
						(((double) gold.frenzy_time / MAX_FRENZY) < ((double) gold.boost_time / MAX_BOOST) && ((double) gold.frenzy_time / MAX_FRENZY) > ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY)) ? 3 :
						(((double) gold.frenzy_time / MAX_FRENZY) < ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) && ((double) gold.frenzy_time / MAX_FRENZY) < ((double) gold.boost_time / MAX_BOOST)) ? 6 : 0,
						round2(164. * ((double) gold.frenzy_time / MAX_FRENZY)), 3, 0xddeb);

				if (gold.click_frenzy_time <= 0)
					gold.click_multiplier = 1;
				else
					fill_area(0,
						(((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) < ((double) gold.frenzy_time / MAX_FRENZY) && ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) > ((double) gold.boost_time / MAX_BOOST)) || 
						(((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) < ((double) gold.boost_time / MAX_BOOST) && ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) > ((double) gold.frenzy_time / MAX_FRENZY)) ? 3 :
						(((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) < ((double) gold.frenzy_time / MAX_FRENZY) && ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) < ((double) gold.boost_time / MAX_BOOST)) ? 6 : 0,
						round2(164. * ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY)), 3, 0xddeb);

				if (gold.boost_time <= 0) 
					gold.boost_multiplier = 0;
				else
					fill_area(0,
						(((double) gold.boost_time / MAX_BOOST) < ((double) gold.frenzy_time / MAX_FRENZY) && ((double) gold.boost_time / MAX_BOOST) > ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY)) || 
						(((double) gold.boost_time / MAX_BOOST) < ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY) && ((double) gold.boost_time / MAX_BOOST) > ((double) gold.frenzy_time / MAX_FRENZY)) ? 3 :
						(((double) gold.boost_time / MAX_BOOST) < ((double) gold.frenzy_time / MAX_FRENZY) && ((double) gold.boost_time / MAX_BOOST) < ((double) gold.click_frenzy_time / MAX_CLICK_FRENZY)) ? 6 : 0,
						round2(164. * ((double) gold.boost_time / MAX_BOOST)), 3, 0xddeb);
				break;
		}
		
		copy_sprite_scaled(arrow[mode], mode ? 20 : 374, 11, 3, 5, 6, 10, false, 0);
		
		if (gold.time <= 13) {
			if (mode != MODE_STATS)
				copy_sprite_scaled(gold_cookie, 4 + gold.x * 66 + (23 - (gold.scale / 2)), gold.y + (23 - (gold.scale / 2)) , 23, 23, gold.scale, gold.scale, false, 0);

			if (gold.time > 0 && gold.scale < 46)
				gold.scale += 2;
			else if (gold.time <= 0 && gold.scale >= 2)
				gold.scale -= 2;
			
			if (gold.time <= 0 && gold.scale <= 2)
				reset_gold(&gold);
		}

		if ((keydownlast(KEY_PRGM_VARS) && !keydownhold(KEY_PRGM_VARS)) || key == KEY_PRGM_VARS)
			mode = mode == MODE_STATS ? MODE_DEFAULT : MODE_STATS;

		if (key == KEY_PRGM_7)
			set_message(&msg, "Test", "This is a test message", 6);

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
		}

        Bdisp_PutDisp_DD();
        Bdisp_AllClr_VRAM();
	}
	return 0;
}
