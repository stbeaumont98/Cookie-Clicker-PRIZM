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

int get_time(){
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

	fill_area(box_x, box_y, box_width, box_height, rgb_color(16, 16, 16));
	draw_rect(box_x - 2, box_y - 2, box_width + 3, box_height + 3, rgb_color(135, 86, 38), 1);

	disp_string(box_x + 5, box_y + 4, has_header ? msg.header : msg.body, rgb_color(169, 169, 169));
	
	if (has_header) {
		draw_line(box_x + 5, box_y + 22, box_x + width + 3, box_y + 22, rgb_color(100, 100, 100), 0);
		disp_string(box_x + 5, box_y + 26, msg.body, rgb_color(169, 169, 169));
	}
}

void draw_background(){
    fill_scr(rgb_color(35, 94, 128));
	for(int i = 0; i < 12; i++){
		if(i % 2 != 0)
			fill_area(i * 32, 0, 32, 216, rgb_color(44, 108, 143));
	}
	copy_sprite_scaled(panel_vertical, 170, 0, 8, 108, 16, 216, false, 0);
	copy_sprite_scaled(panel_horizontal, 186, 32, 99, 8, 198, 16, false, 0);
}

void draw_store_tile(uint16_t x, uint8_t y) {
	fill_area(x, y, 198, 42, 0xad73);
	fill_area(x + 2, y, 196, 2, 0x7bac);
	fill_area(x + 4, y + 2, 194, 2, 0x7bac);
	fill_area(x, y, 2, 40, 0xbdd5);
	fill_area(x + 2, y + 2, 2, 36, 0xbdd5);
	fill_area(x + 2, y + 38, 196, 2, 0x39c5);
	fill_area(x, y + 40, 198, 2, 0x39c5);
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
	
	int sel = 0;
	int sel_offset = 0;

	bool stats_toggle = false;

	while(1) {
        int key = PRGM_GetKey();
        if(key == KEY_PRGM_MENU) {
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

		if (stats_toggle) {
			fill_scr(0x0000);
			draw_line(148, 23, 236, 23, rgb_color(100, 100, 100), 0);
			disp_string(150, 30, "STATISTICS", 0xFFFF);
			draw_line(148, 47, 236, 47, rgb_color(100, 100, 100), 0);

			copy_sprite_scaled(panel_horizontal, 0, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_horizontal, 198, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_vertical, 0, 0, 8, 108, 16, 216, false, 0);
			copy_sprite_scaled(panel_vertical, 368, 0, 8, 108, 16, 216, false, 0);
			
			disp_string(21, 57, "Cookies in bank:\nCookies baked (all time):\nBuildings owned:\nCookies per second:\nRaw cookies per second:\nCookie clicks:\nHand-made cookies:\nGolden cookie clicks:", rgb_color(150, 150, 150));
			
			copy_sprite_masked(money, 152, 57, 14, 14, COLOR_RED);
			copy_sprite_masked(money, 214, 75, 14, 14, COLOR_RED);

			bool is_abrev = (data.cookies >= 1E45 && data.cookies < 1E48);
			char *tmp = get_display_val(data.cookies, false, false);
			disp_string(170, 57, tmp, 0xFFFF);
			free(tmp);

			is_abrev = (data.cookies_all_time >= 1E15 && data.cookies_all_time < 1E27) || (data.cookies_all_time >= 1E30 && data.cookies_all_time < 1E33) || data.cookies_all_time > 1E36;
			tmp = get_display_val(data.cookies_all_time, false, is_abrev);
			disp_string(232, 75, tmp, 0xFFFF);
			free(tmp);

			int num_buildings = 0;
			for (int i = 0; i < 20; i++)
				num_buildings += data.buildings[i].owned;

			tmp = disp_comma(num_buildings);
			disp_string(156, 93, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val((data.cps * gold.cps_multiplier) + (data.cps * gold.cps_multiplier * gold.boost_multiplier), true, false);
			disp_string(177, 111, tmp, 0xFFFF);
			free(tmp);
			
			is_abrev = (data.cps >= 1E15 && data.cps < 1E27) || (data.cps >= 1E30 && data.cps < 1E33) || data.cps > 1E36;
			tmp = get_display_val(data.cps, true, is_abrev);
			disp_string(213, 129, tmp, 0xFFFF);
			free(tmp);

			tmp = disp_comma(data.click_count);
			disp_string(130, 147, tmp, 0xFFFF);
			free(tmp);

			tmp = get_display_val(data.handmade_cookies, false, false);
			disp_string(180, 165, tmp, 0xFFFF);
			free(tmp);

			tmp = disp_comma(data.gold_click_count);
			disp_string(185, 183, tmp, 0xFFFF);
			free(tmp);

			if(keydownlast(KEY_PRGM_EXIT) && !keydownhold(KEY_PRGM_EXIT))
					stats_toggle = false;

		} else {

			draw_background();

			// start store code

			fill_area(186, 0, 198, 32, 0x0000);

			disp_string(265, 10, "Store", 0xffff);

			int store_size = (data.buildings_unlocked < 4) ? data.buildings_unlocked : 4;

			for(int i = 0; i < store_size; i++) {
				draw_store_tile(186, 48 + i * 42);
				copy_sprite_scaled(icons[i + sel_offset], 186, 48 + i * 42, 21, 21, 42, 42, data.buildings[i + sel_offset].hidden, 0x0000);
				copy_sprite_masked(money, 229, 70 + i * 42, 14, 14, COLOR_RED);
				char *price_buf = get_display_val(data.buildings[i + sel_offset].price, false, false);
				disp_string(246, 70 + i * 42, price_buf, (data.cookies >= data.buildings[i + sel_offset].price) ? 0x67ec : COLOR_RED);
				free(price_buf);

				char owned_buf[5];
				itoa(data.buildings[i+sel_offset].owned, owned_buf, 10);
				disp_string(380 - text_width(owned_buf), 62 + i * 42, owned_buf, 0x0000);

				char type[18];
				if (!data.buildings[i + sel_offset].hidden)
					strcpy(type, building_types[i + sel_offset]);
				else
					strcpy(type, "???");
				disp_string(229, 54 + i * 42, type, 0xffff);
			}

			draw_rect(187, 49 + sel * 42, 195, 39, 0xff80, 1);

			if((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) && sel < store_size - 1) {
				sel++;
			} else if((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) && sel == 3 && data.buildings_unlocked > 4 && sel_offset < data.buildings_unlocked - 4){
				sel_offset++;
			}
			if((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) && sel > 0) {
				sel--;
			} else if((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) && sel == 0 && sel_offset > 0){
				sel_offset--;
			}
			if((keydownlast(KEY_PRGM_ALPHA) && !keydownhold(KEY_PRGM_ALPHA)) && data.cookies >= data.buildings[sel + sel_offset].price) {
				data.cookies -= data.buildings[sel + sel_offset].price;
				data.buildings[sel + sel_offset].owned++;
				data.buildings[sel + sel_offset].price += round2(data.buildings[sel + sel_offset].price * .15);
			}

			// end store code

			if(keydownlast(KEY_PRGM_SHIFT) && !keydownhold(KEY_PRGM_SHIFT)) {
				scale_w = 112;
				scale_h = 114;
				data.cookies += gold.click_multiplier;
				data.cookies_all_time += gold.click_multiplier;
				data.handmade_cookies += gold.click_multiplier;
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

			data.cps = tmp_cps;

			if (key == 0) {
				scale_w = 124;
				scale_h = 126;
			}
			
			copy_sprite_scaled(perfect_cookie, (scale_w < 124) ? 29 : 23, (scale_h < 126) ? 86 : 80, 62, 63, scale_w, scale_h, false, 0);
			fill_area(0, 10, 170, 60, 0x0000);
			
			char cps_buf[30];

			strcpy(cps_buf, "CpS: ");

			char *tmp = get_display_val((data.cps * gold.cps_multiplier) + (data.cps * gold.cps_multiplier * gold.boost_multiplier), true, true);
			strcat(cps_buf, tmp);
			free(tmp);

			char *cookie_buf = get_display_val(data.cookies, false, data.cookies >= 1E48);
			disp_string((170 - text_width(cookie_buf)) / 2, 17, cookie_buf, 0xffff);
			free(cookie_buf);

			disp_string(59, 34, "cookies", 0xffff);

			disp_string((170 - text_width(cps_buf)) / 2, 51, cps_buf, 0xffff);

			if (msg.time > 0) {
				display_msg(msg);
				if(keydownlast(KEY_PRGM_EXIT) && !keydownhold(KEY_PRGM_EXIT))
					msg.time = 0;
			}
			
			if((keydownlast(f_buttons[gold.x]) && !keydownhold(f_buttons[gold.x])) && gold.time <= 13) {
				data.gold_click_count++;
				if(gold.effect > 0 && gold.effect <= 425) {
					// Lucky!
					double earned = (data.cookies >= data.cps * gold.cps_multiplier * 6000) ?
						(max(data.cookies * 0.15, data.cps * gold.cps_multiplier * 900) + 13) :
						(min(data.cookies * 0.15, data.cps * gold.cps_multiplier * 900) + 13);

					char msg_buf[30];
					strcpy(msg_buf, "+");
					char *tmp = get_display_val(earned, false, false);
					strcat(msg_buf, tmp);
					free(tmp);
					strcat(msg_buf, " cookies!");
					set_message(&msg, "Lucky!", msg_buf, 4);

					data.cookies_all_time += earned;
					data.cookies += earned;
				} else if(gold.effect > 425 && gold.effect <= 850) {
					// Frenzy
					set_message(&msg, "Frenzy", "Cookie production x7 for 77 seconds!", 5);
					gold.cps_multiplier = 7;
					gold.frenzy_time = 77;
				} else if(gold.effect > 850 && gold.effect <= 893) {
					// Click Frenzy
					set_message(&msg, "Click Frenzy", "Clicking power x777 for 13 seconds!", 5);
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
						strcat(msg_buf, "your CpS!");
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
						double earned = (data.cookies >= data.cps * gold.cps_multiplier * 6000) ?
							(max(data.cookies * 0.15, data.cps * gold.cps_multiplier * 900) + 13) :
							(min(data.cookies * 0.15, data.cps * gold.cps_multiplier * 900) + 13);

						char msg_buf[30];
						strcpy(msg_buf, "+");
						char *tmp = get_display_val(earned, false, false);
						strcat(msg_buf, tmp);
						free(tmp);
						strcat(msg_buf, " cookies!");
						set_message(&msg, "Lucky!", msg_buf, 4);

						data.cookies_all_time += earned;
						data.cookies += earned;
					}

				} else if(gold.effect > 996) {
					int rblab = random() % 39;
					set_message(&msg, "", blab[rblab], 6);
				}
				reset_gold(&gold);
			}
		}
		
		if (gold.time <= 13) {
			if (!stats_toggle)
				copy_sprite_scaled(gold_cookie, 4 + gold.x * 66 + (23 - (gold.scale / 2)), gold.y + (23 - (gold.scale / 2)) , 23, 23, gold.scale, gold.scale, false, 0);

			if (gold.time > 0 && gold.scale < 46)
				gold.scale++;
			else if (gold.time <= 0 && gold.scale >= 2)
				gold.scale--;
			
			if (gold.time <= 0 && gold.scale <= 2)
				reset_gold(&gold);
		}

		if(keydownlast(KEY_PRGM_VARS) && !keydownhold(KEY_PRGM_VARS))
			stats_toggle = !stats_toggle;

		if (one_second) {
			data.cookies += (data.cps * gold.cps_multiplier) + (data.cps * gold.cps_multiplier * gold.boost_multiplier);
			data.cookies_all_time += (data.cps * gold.cps_multiplier) + (data.cps * gold.cps_multiplier * gold.boost_multiplier);

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

		if (gold.frenzy_time <= 0)
			gold.cps_multiplier = 1;

		if (gold.click_frenzy_time <= 0)
			gold.click_multiplier = 1;

		if (gold.boost_time <= 0) 
			gold.boost_multiplier = 0;

        Bdisp_PutDisp_DD();
        Bdisp_AllClr_VRAM();
	}
	return 0;
}
