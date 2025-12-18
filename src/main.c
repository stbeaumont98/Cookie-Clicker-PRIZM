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

#include "data.h"
#include "draw.h"
#include "math1.h"
#include "keys.h"
#include "save.h"
#include "convert.h"
#include "upgrades.h"
#include "time.h"

int main() {
	EnableStatusArea(3);
	EnableDisplayHeader(0, 0);
    Bdisp_EnableColor(1);
	srandom(RTC_GetTicks());
	DrawFrame(0x0000);

	struct GoldenData gold;

	struct CookieData data;

	double old_ts = load_game(&data, &gold);

	int f_buttons[6] = {
		KEY_PRGM_F1, KEY_PRGM_F2,
		KEY_PRGM_F3, KEY_PRGM_F4,
		KEY_PRGM_F5, KEY_PRGM_F6
	};

	struct Message notes[3];
	uint8_t notes_cnt = 0;

	for (int i = 0; i < 3; i++)
		set_msg(&notes[i], "", "", 0);
	
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
	char u_count_buf[15];

	bool upgrades_toggle = false;
	bool stats_toggle = false;
	bool options_toggle = false;
	bool x10_toggle = false;

	int16_t autosave_time = (int16_t) ticks(60.);

	bool sleep = false;
	bool key_held = false;

	int hold_ticks = RTC_GetTicks() + ticks(0.5);
	int old_ticks = RTC_GetTicks();

	int s_sel = 0;
	bool p_sel = true;
	bool prompt = false;

	int filtered_size = 0;
	struct Upgrade filtered_upgrades[478];

	filter_unlocked(filtered_upgrades, &data, upgrades, &filtered_size);
	sort_upgrades(filtered_upgrades, 0, filtered_size - 1, data.upgrades);

	// Handle idle cookies cheat
	double elapsed_sec = get_timestamp() - old_ts;
	if (data.cheats.on && data.cheats.ic && old_ts != 0.)  {
		double idle_earned = ((elapsed_sec < 0.) ? 0. : elapsed_sec) * raw_cps;
		data.cookies_all_time += idle_earned;
		data.cookies += idle_earned;

		// Tell the player how much they earned since they last played.
		char idle_msg[75];
		strcpy(idle_msg, "You earned ");
		tmp = get_display_val(idle_earned, false, false);
		strcat(idle_msg, tmp);
		free(tmp);
		strcat(idle_msg, " cookie");
		if (round2(idle_earned) != 1)
			strcat(idle_msg, "s");
		strcat(idle_msg, " while\nyou were away.");

		// tmp = get_save_val(get_timestamp());
		// strcpy(idle_msg, tmp);
		// free(tmp);

		// strcat(idle_msg, " - ");

		// tmp = get_save_val(old_ts);
		// strcat(idle_msg, tmp);
		// free(tmp);

		// strcat(idle_msg, " is ");

		// tmp = get_save_val(elapsed_sec);
		// strcat(idle_msg, tmp);
		// free(tmp);

		push_note(notes, "Welcome back!", idle_msg, 5, &notes_cnt);
	}

	while (1) {
        int key = PRGM_GetKey();

		keyupdate();

		raw_cps = get_cps(data);
		current_cps = (raw_cps * gold.cps_multiplier) \
			+ (raw_cps * gold.cps_multiplier * gold.boost_multiplier);

		current_cpc =  get_cpc(data, current_cps) * gold.click_multiplier;

		// handle time-based events

		int elapsed = elapsed_ticks(&old_ticks);
		double seconds = secs(elapsed);
		
		data.cookies += current_cps * seconds;
		data.cookies_all_time += current_cps * seconds;

		if (gold.frenzy_time > 0)
			gold.frenzy_time -= elapsed;
		if (gold.click_frenzy_time > 0)
			gold.click_frenzy_time -= elapsed;
		if (gold.boost_time > 0)
			gold.boost_time -= elapsed;
		for (int i = notes_cnt; i >= 0; i--) {
			if (notes[i].time > 0)
				notes[i].time -= elapsed;
		}
		if (gold.time > 0)
			gold.time -= elapsed;
		if (autosave_time > 0)
			autosave_time -= elapsed;

		key_held = (key != 0 && RTC_GetTicks() >= hold_ticks);

		if (key == 0)
			hold_ticks = RTC_GetTicks() + ticks(0.5);

		if (key_press(KEY_PRGM_ACON))
			sleep = !sleep;
			//PowerOff(0);

		if (options_toggle) {
			
			fill_scr(0x0000);
			draw_line(157, 22, 226, 22, 0x632c, 0);
			disp_string(161, 29, "OPTIONS", 0xFFFF, 0);
			draw_line(157, 46, 226, 46, 0x632c, 0);

			copy_sprite_scaled(panel_h, 0, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_h, 198, 0, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_h, 0, 53, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_h, 198, 53, 99, 8, 198, 16, false, 0);
			copy_sprite_scaled(panel_v, 0, 0, 8, 108, 16, 216, false, 0);
			copy_sprite_scaled(panel_v, 368, 0, 8, 108, 16, 216, false, 0);
			copy_sprite_scaled(panel_v, 184, 69, 8, 108, 16, 216, false, 0);

			draw_line(19, 73, 86, 73, 0x632c, 0);
			disp_string(21, 80, "General", 0xFFFF, 0);
			draw_line(19, 97, 86, 97, 0x632c, 0);
			
			if (data.cheats.on) {
				draw_line(203, 73, 273, 73, 0x632c, 0);
				disp_string(205, 80, "Cheating", 0xFFFF, 0);
				draw_line(203, 97, 273, 97, 0x632c, 0);
			}

			draw_button(23, 104, 110, "BACKUP SAVE", 0xFFFF, s_sel == 0);
			draw_button(23, 127, 110, "RESTORE BACKUP", 0xFFFF, s_sel == 1);

			char cheats_str[12];
			strcpy(cheats_str, "Cheats ");
			strcat(cheats_str, data.cheats.on ? "ON" : "OFF");
			draw_button(23, 150, 110, cheats_str, 0xFFFF, s_sel == 2);

			draw_button(66, 191, 110, "WIPE SAVE", COLOR_RED, s_sel == 3);

			if (data.cheats.on) {
				draw_toggle_box(210, 106, "Auto-click\ngolden cookies", s_sel == 4 ? 0xFFFF : dim_color(0xFFFF, 0.5), data.cheats.acg);
				draw_toggle_box(210, 129, "Press and hold\nto click", s_sel == 5 ? 0xFFFF : dim_color(0xFFFF, 0.5), data.cheats.hc);
				draw_toggle_box(210, 152, "Free Buildings", s_sel == 6 ? 0xFFFF : dim_color(0xFFFF, 0.5), data.cheats.fb);
				draw_toggle_box(210, 171, "Free Upgrades", s_sel == 7 ? 0xFFFF : dim_color(0xFFFF, 0.5), data.cheats.fu);
				draw_toggle_box(210, 190, "Idle CpS", s_sel == 8 ? 0xFFFF : dim_color(0xFFFF, 0.5), data.cheats.ic);
			}

			if (!prompt) {

				if ((key_press(KEY_PRGM_DOWN) || (key == KEY_PRGM_DOWN && key_held)) && s_sel < (data.cheats.on ? 8 : 3))
					s_sel++;
				if ((key_press(KEY_PRGM_UP) || (key == KEY_PRGM_UP && key_held)) && s_sel > 0)
					s_sel--;
				if (key_press(KEY_PRGM_RIGHT) || (key == KEY_PRGM_RIGHT && key_held))
					s_sel += (data.cheats.on && s_sel < 3) ? 4 : (data.cheats.on && s_sel == 3) ? 5 : 0;
				if (key_press(KEY_PRGM_LEFT) || (key == KEY_PRGM_LEFT && key_held))
					s_sel -= (s_sel > 3 && s_sel < 7) ? 4 : (s_sel > 3 && s_sel >= 7) ? 5 : 0;

				if (key_press(KEY_PRGM_SHIFT)) {
					switch (s_sel) {
						case 0:
						case 1:
						case 3:
							prompt = true;
							p_sel = true;
							break;
						case 2:
							if (!data.cheats.on) {
								prompt = true;
								p_sel = true;
							} else {
								data.cheats.on = false;
							}
							break;
						case 4:
							data.cheats.acg = !data.cheats.acg;
							break;
						case 5:
							data.cheats.hc = !data.cheats.hc;
							break;
						case 6:
							data.cheats.fb = !data.cheats.fb;
							if (!data.cheats.fb) {
								bool last_hide = true;
								for (int i = 19; i >= 0 && data.buildings[i].owned == 0; i--) {
									if (i >= 2) {
										if (data.cookies_all_time < base_prices[i - 2]) {
											data.buildings[i].locked = true;
											data.buildings_unlocked--;
										}
									}
									if (data.cookies_all_time >= base_prices[i])
										last_hide = false;
									if (data.cookies_all_time < base_prices[i] && last_hide)
										data.buildings[i].hidden = true;
								}
								if (b_sel + b_sel_offset > data.buildings_unlocked) {
									b_sel = 3;
									b_sel_offset = data.buildings_unlocked - 4;
								}
							}
							break;
						case 7:
							data.cheats.fu = !data.cheats.fu;
							break;
						case 8:
							data.cheats.ic = !data.cheats.ic;
							break;
						default:
							break;
					}
				}

				if (key_press(KEY_PRGM_EXIT))
					options_toggle = false;

				if (key_press(KEY_PRGM_VARS)) {
					options_toggle = false;
					stats_toggle = true;
				}

			} else {
				struct Message s_msg;

				switch (s_sel) {
					// Backup save
					case 0:
						strcpy(s_msg.header, "BACKUP");
						strcpy(s_msg.body, "Are you sure?\nAny previous backups will be\noverwritten!");
						break;
					// Restore backup
					case 1:
						strcpy(s_msg.header, "RESTORE");
						strcpy(s_msg.body, "Are you sure?\nCurrent save file will be\noverwritten!");
						break;
					// Enable cheating
					case 2:
						strcpy(s_msg.header, "CHEATING");
						strcpy(s_msg.body, "Do you REALLY want to\nenable cheats?\nCheated cookies taste awful.");
						break;
					// Wipe save
					case 3:
						strcpy(s_msg.header, "WIPE SAVE");
						strcpy(s_msg.body, "Do you REALLY want to\nwipe your save?\nYou will lose all your progress!");
						break;
					default:
						break;
				}

				disp_prompt(s_msg, p_sel);

				if (key_press(KEY_PRGM_RIGHT) && p_sel)
					p_sel = false;
				if (key_press(KEY_PRGM_LEFT) && !p_sel)
					p_sel = true;

				if (key_press(KEY_PRGM_SHIFT)) {
					if (p_sel) {
						switch (s_sel) {
							// Backup save
							case 0:
								backup_game();
								save_game(data, gold);
								push_note(notes, "", "Backup created", 3, &notes_cnt);
								break;
							// Restore backup
							case 1:
								if (restore_backup() < 0) {
									push_note(notes, "Restore Failed", "Unable to find backup file!", 3, &notes_cnt);
									break;
								}
								load_game(&data, &gold);
				
								filter_unlocked(filtered_upgrades, &data, upgrades, &filtered_size);
								sort_upgrades(filtered_upgrades, 0, filtered_size - 1, data.upgrades);
								u_sel = 0;
								u_sel_offset = 0;
								b_sel = 0;
								b_sel_offset = 0;

								// Create another copy of the backup.
								backup_game();
								save_game(data, gold);
								push_note(notes, "", "Backup restored", 3, &notes_cnt);
								break;
							// Enable cheating
							case 2:
								data.cheats.on = true;
								break;
							// Wipe save
							case 3:
								// Reset all variables.
								reset_game(&data, &gold);
								
								filter_unlocked(filtered_upgrades, &data, upgrades, &filtered_size);
								sort_upgrades(filtered_upgrades, 0, filtered_size - 1, data.upgrades);
								u_sel = 0;
								u_sel_offset = 0;
								b_sel = 0;
								b_sel_offset = 0;

								// Reset the cookies.sav file.
								save_game(data, gold);
								break;
							default:
								break;
						}
					}
					prompt = false;
				}

				if (key_press(KEY_PRGM_EXIT) || key_press(KEY_PRGM_ALPHA))
					prompt = false;
			}

		} else {

			if (stats_toggle) {
				fill_scr(0x0000);
				draw_line(148, 22, 236, 22, 0x632c, 0);
				disp_string(150, 29, "STATISTICS", 0xFFFF, 0);
				draw_line(148, 46, 236, 46, 0x632c, 0);

				copy_sprite_scaled(panel_h, 0, 0, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_h, 198, 0, 99, 8, 198, 16, false, 0);
				copy_sprite_scaled(panel_v, 0, 0, 8, 108, 16, 216, false, 0);
				copy_sprite_scaled(panel_v, 368, 0, 8, 108, 16, 216, false, 0);
				
				for (int i = 0; i < 9; i++)
					disp_string(21, 54 + i * 18, stats[i], 0x94b2, 0);
				
				copy_sprite_masked(money, 152, 54, 14, 14, COLOR_RED);
				copy_sprite_masked(money, 214, 72, 14, 14, COLOR_RED);

				tmp = get_display_val(data.cookies, false, false);
				if (text_width(tmp) > 197) {
					free(tmp);
					tmp = get_display_val(data.cookies, false, true);
				}
				disp_string(170, 54, tmp, 0xFFFF, 0);
				free(tmp);

				tmp = get_display_val(data.cookies_all_time, false, false);
				if (text_width(tmp) > 135) {
					free(tmp);
					tmp = get_display_val(data.cookies_all_time, false, true);
				}
				disp_string(232, 72, tmp, 0xFFFF, 0);
				free(tmp);

				int num_buildings = 0;
				for (int i = 0; i < 20; i++)
					num_buildings += data.buildings[i].owned;

				tmp = disp_comma(num_buildings);
				disp_string(156, 90, tmp, 0xFFFF, 0);
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
				if (text_width(tmp) + text_width_small(mult, false) > 186) {
					free(tmp);
					tmp = get_display_val(current_cps, (current_cps < 1E3), true);
				}
				int cps_w = text_width(tmp);
				disp_string(177, 108, tmp, 0xFFFF, 0);
				free(tmp);
				disp_string_small(180 + cps_w, 113, mult, 0xFFFF, false, 0);
				
				tmp = get_display_val(raw_cps, (raw_cps < 1E3), false);
				if (text_width(tmp) > 154) {
					free(tmp);
					tmp = get_display_val(raw_cps, (raw_cps < 1E3), true);
				}
				disp_string(213, 126, tmp, 0xFFFF, 0);
				free(tmp);

				tmp = get_display_val(current_cpc, (current_cpc < 1E3), false);
				if (text_width(tmp) > 207) {
					free(tmp);
					tmp = get_display_val(current_cpc, (current_cpc < 1E3), true);
				}
				disp_string(160, 144, tmp, 0xFFFF, 0);
				free(tmp);

				tmp = get_display_val(data.click_count, false, false);
				disp_string(130, 162, tmp, 0xFFFF, 0);
				free(tmp);

				tmp = get_display_val(data.handmade_cookies, false, false);
				if (text_width(tmp) > 187) {
					free(tmp);
					tmp = get_display_val(data.handmade_cookies, false, true);
				}
				disp_string(180, 180, tmp, 0xFFFF, 0);
				free(tmp);

				tmp = get_display_val(data.gold_click_count, false, false);
				disp_string(185, 198, tmp, 0xFFFF, 0);
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
					
					disp_string(172, 10, "Store", 0xffff, 0);
					disp_string_small(18, 37, "UPGRADES", 0xffff, true, 0);

					disp_string_small(28, 5, "[x  ]", 0xffff, false, 0);
					disp_string_small(28 + text_width_small("[x", false), 2, "2", 0xffff, false, 0);
					copy_sprite_1bit(arrow[1], 20, 5, 6, 6, one_bit_pal, 0xffff);

					char uc[4];
					itoa(data.upgrades_count, uc, 10);
					strcpy(u_count_buf, uc);
					strcat(u_count_buf, "/478 (");
					itoa((int) (((double) data.upgrades_count / 478.) * 100.), uc, 10);
					strcat(u_count_buf, uc);
					strcat(u_count_buf, "%)");
					disp_string_small(20, 22, u_count_buf, 0xffff, false, 0);

					cookie_buf = get_display_val(data.cookies, false, false);
					if (text_width(cookie_buf) > 162) {
						free(cookie_buf);
						cookie_buf = get_display_val(data.cookies, false, true);
					}
					x = 365 - text_width_small(cookie_buf, false);
					disp_string_small(x, 4, cookie_buf, 0xffff, false, 0);
					free(cookie_buf);
					
					x = 365 - text_width_small("cookies", false);
					disp_string_small(x, 12, "cookies", 0xffff, false, 0);

					strcpy(cps_buf, "CpS: ");

					tmp = get_display_val(current_cps, (current_cps < 1E3), false);
					if (text_width(tmp) > 126) {
						free(tmp);
						tmp = get_display_val(current_cps, (current_cps < 1E3), true);
					}
					strcat(cps_buf, tmp);
					free(tmp);

					x = 365 - text_width_small(cps_buf, false);
					disp_string_small(x, 22, cps_buf, 0xffff, false, 0);

					if (filtered_size > 0) {

						uint16_t u_id = u_sel + u_sel_offset;
						
						const char *b_type = get_upgrade_type(data, filtered_upgrades[u_id].id);
						x = 366 - text_width_small(b_type, true);
						disp_string_small(x, 37, b_type, 0xffff, true, 0);

						for (int i = 0; i < min(filtered_size, 4); i++) {
							uint16_t u_id = i + u_sel_offset;
							uint16_t f_id = filtered_upgrades[u_id].id;

							if (u_id > filtered_size)
								continue;

							copy_sprite_masked(upgrade_frame, 23, 54 + i * 42, 30, 30, COLOR_RED);
							if (filtered_upgrades[u_id].sprite != NULL) {
								copy_sprite_4bit(filtered_upgrades[u_id].sprite, 26, 57 + i * 42, 24, 24,
								filtered_upgrades[u_id].palette, false, 0x4208);
								if (f_id >= 222 && f_id < 236)
									copy_sprite_4bit(rainbow, 26, 57 + i * 42, 24, 24,
										rainbow_pal, false, 0x4208);
							}

							char *name =  filtered_upgrades[u_id].name;
							const char *desc = get_upgrade_description(data, f_id);

							int n_h = text_height(name), d_h = text_height(desc);

							y = (!data.upgrades_unlocked[f_id] || (n_h == 1 && d_h == 1) ?
								73 : (n_h > 1 ? 80 : 69)) + i * 42;
							color = data.upgrades[f_id] ? 0x4208 : 0x8410;

							disp_string_small(57, y, desc, color, false, 0);
							
							y = (!data.upgrades_unlocked[f_id] || (n_h == 1 && d_h == 1) ? 57 : 53) + i * 42;
							color = data.upgrades[f_id] ? 0x4208 : 0xffff;
							
							disp_string(57, y, name, color, 0);
							
							if (!data.upgrades[f_id]) {
								double p = !(data.cheats.on && data.cheats.fu) * filtered_upgrades[u_id].price;
								price_buf = get_display_val(p, false, p >= 1e12);
								x = 348 - text_width(price_buf), y =  53 + i * 42;
								copy_sprite_masked(money, x, y, 14, 14, COLOR_RED);
								x = 364 - text_width(price_buf), y = 54 + i * 42;
								color = (data.cookies >= p) ? 0x67ec : COLOR_RED;
								disp_string(x, y, price_buf, color, 0);
								free(price_buf);
							} else {
								x = 353, y = 53 + i * 42;
								copy_sprite_1bit(check, x, y, 11, 10, one_bit_pal, 0x4208);
							}
						}

						draw_rect(17, 49 + u_sel * 42, 349, 39, 0xff80, 1);

						if ((key_press(KEY_PRGM_DOWN) || (key == KEY_PRGM_DOWN && key_held)) && u_sel < min(filtered_size - 1, 3))
							u_sel++;
						else if ((key_press(KEY_PRGM_DOWN) || (key == KEY_PRGM_DOWN && key_held)) && u_sel == 3 && u_sel_offset < filtered_size - 4)
							u_sel_offset++;

						if ((key_press(KEY_PRGM_UP) || (key == KEY_PRGM_UP && key_held)) && u_sel > 0)
							u_sel--;
						else if ((key_press(KEY_PRGM_UP) || (key == KEY_PRGM_UP && key_held)) && u_sel == 0 && u_sel_offset > 0)
							u_sel_offset--;

						if ((key_press(KEY_PRGM_LEFT) || (key == KEY_PRGM_LEFT && key_held)) && u_sel_offset - 4 >= 0)
							u_sel_offset -= 4;
						else if ((key_press(KEY_PRGM_LEFT) || (key == KEY_PRGM_LEFT && key_held)) && u_sel_offset - 4 < 0) {
							u_sel = 0;
							u_sel_offset = 0;
						}

						if ((key_press(KEY_PRGM_RIGHT) || (key == KEY_PRGM_RIGHT && key_held)) && u_sel_offset + 4 <= filtered_size - 4)
							u_sel_offset += 4;
						else if ((key_press(KEY_PRGM_RIGHT) || (key == KEY_PRGM_RIGHT && key_held)) && u_sel_offset + 4 > filtered_size - 4) {
							u_sel = 3;
							u_sel_offset = filtered_size - 4;
						}

						uint16_t f_id = filtered_upgrades[u_id].id;

						if (key_press(KEY_PRGM_ALPHA)
							&& data.cookies >= (!(data.cheats.on && data.cheats.fu) * filtered_upgrades[u_id].price)
							&& !data.upgrades[f_id]) {
							data.cookies -= (!(data.cheats.on && data.cheats.fu) * filtered_upgrades[u_id].price);
							data.upgrades[f_id] = true;
							enable_upgrade(&data, &gold, f_id);
							data.upgrades_count++;
							unlock_upgrades(&data);
							
							filter_unlocked(filtered_upgrades, &data, upgrades, &filtered_size);
							sort_upgrades(filtered_upgrades, 0, filtered_size - 1, data.upgrades);
						}
					}

					if (key_press(KEY_PRGM_EXIT))
						upgrades_toggle = false;

				} else {
					draw_background();

					// buildings store

					fill_area(180, 0, 204, 32, 0x0000);

					disp_string(262, 10, "Store", 0xffff, 0);
					disp_string_small(182, 37, "BUILDINGS", 0xffff, true, 0);

					disp_string_small(352, 5, "[x  ]", 0xffff, true, 0);
					disp_string_small(353 + text_width_small("[x", false), 2, "2", 0xffff, true, 0);
					copy_sprite_1bit(arrow[0], 374, 5, 6, 6, one_bit_pal, 0xffff);

					if (x10_toggle) {
						disp_string_small(363, 38, "x", 0xffff, false, 0);
						disp_string(363 + text_width_small("x", false), 33, "10", 0xffff, 0);
					}

					int store_size = (data.buildings_unlocked < 4) ? data.buildings_unlocked : 4;

					for (int i = 0; i < store_size; i++) {
						uint8_t b_id = i + b_sel_offset;
						double p = !(data.cheats.on && data.cheats.fb) * (data.buildings[b_id].price * (x10_toggle ? 20.303718238 : 1.));

						x = 180, y = 48 + i * 42;
						draw_store_tile(x, y);
						copy_sprite_scaled(icons[b_id], x, y, 21, 21, 42, 42,
							data.buildings[b_id].hidden, 0x0000);

						x = 223, y = 70 + i * 42;
						copy_sprite_masked(money, x, y, 14, 14, COLOR_RED);

						price_buf = get_display_val(p, false, false);

						if ((text_width(price_buf) > 116 && data.buildings[b_id].owned >= 100)
							|| (text_width(price_buf) > 121 && data.buildings[b_id].owned >= 10)
							|| (text_width(price_buf) > 130)) {
							free(price_buf);
							price_buf = get_display_val(p, false, true);
						}

						x = 240;
						color = (data.cookies >= p) ? 0x67ec : COLOR_RED;
						disp_string(x, y, price_buf, color, 0);
						free(price_buf);

						if (data.buildings[b_id].owned > 0) {
							char owned_buf[5];
							itoa(data.buildings[b_id].owned, owned_buf, 10);
							disp_string(380 - text_width(owned_buf), 62 + i * 42,
								owned_buf, 0x2924, 0);
						}

						char type[18];
						if (!data.buildings[b_id].hidden)
							strcpy(type, building_types[b_id]);
						else
							strcpy(type, "???");
						disp_string(223, 54 + i * 42, type, 0xffff, 0);
					}

					draw_rect(181, 49 + b_sel * 42, 201, 39, 0xff80, 1);

					if ((key_press(KEY_PRGM_DOWN) || (key == KEY_PRGM_DOWN && key_held)) && b_sel < store_size - 1)
						b_sel++;
					else if ((key_press(KEY_PRGM_DOWN) || (key == KEY_PRGM_DOWN && key_held)) && b_sel == 3 && data.buildings_unlocked > 4
						&& b_sel_offset < data.buildings_unlocked - 4)
						b_sel_offset++;

					if ((key_press(KEY_PRGM_UP) || (key == KEY_PRGM_UP && key_held)) && b_sel > 0)
						b_sel--;
					else if ((key_press(KEY_PRGM_UP) || (key == KEY_PRGM_UP && key_held)) && b_sel == 0 && b_sel_offset > 0)
						b_sel_offset--;

					uint8_t b_id = b_sel + b_sel_offset;
					double p = !(data.cheats.on && data.cheats.fb) * (data.buildings[b_id].price * (x10_toggle ? 20.303718238 : 1.));
					if (key_press(KEY_PRGM_ALPHA)
						&& data.cookies >= p) {
						data.cookies -= p;
						data.buildings[b_id].owned += x10_toggle ? 10 : 1;
						data.buildings[b_id].price *= powInt(1.15, x10_toggle ? 10 : 1);
						data.total_buildings += x10_toggle ? 10 : 1;
					}

					// end store code

					if (key_press(KEY_PRGM_SHIFT) || (key_hold(KEY_PRGM_SHIFT) && data.cheats.on && data.cheats.hc)) {
						scale_w = 112;
						scale_h = 114;
						data.cookies += current_cpc;
						data.cookies_all_time += current_cpc;
						data.handmade_cookies += current_cpc;
						data.click_count++;
					}

					if (key_press(KEY_PRGM_X10))
						x10_toggle = !x10_toggle;

					for (int i = 0; i < 20; i++) {
						if (data.cookies_all_time >= base_prices[i] || (data.cheats.on && data.cheats.fb))
							data.buildings[i].hidden = false;

						if (i >= 2) {
							if (data.buildings[i].locked && ((data.cookies_all_time >= base_prices[i - 2]) || (data.cheats.on && data.cheats.fb))) {
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
					disp_string(x, 19, cookie_buf, 0xffff, 0);
					free(cookie_buf);

					disp_string(53, 36, "cookies", 0xffff, 0);

					x = ((164 - text_width_small(cps_buf, false)) / 2) + 1;
					disp_string_small(x, 53, cps_buf, 0xffff, false, 0);

					double f = (double) gold.frenzy_time / ticks(MAX_FRENZY * gold.effect_modifier);
					double cf = (double) gold.click_frenzy_time / ticks(MAX_CLICK_FRENZY * gold.effect_modifier);
					double b = (double) gold.boost_time / ticks(MAX_BOOST * gold.effect_modifier);

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

				if (key_press(KEY_PRGM_X2)) {
					if (!upgrades_toggle) {
						unlock_upgrades(&data);
						
						filter_unlocked(filtered_upgrades, &data, upgrades, &filtered_size);
						sort_upgrades(filtered_upgrades, 0, filtered_size - 1, data.upgrades);
					}
					

					upgrades_toggle = !upgrades_toggle;
				}
			}
			
			if (key_press(KEY_PRGM_VARS))
				stats_toggle = !stats_toggle;
		}

		// manual save
		if (key_press(KEY_PRGM_EXP)) {
			save_game(data, gold);
			push_note(notes, "", "Game saved", 2, &notes_cnt);
		}

		if (gold.frenzy_time <= 0)
			gold.cps_multiplier = 1;
			
		if (gold.click_frenzy_time <= 0)
			gold.click_multiplier = 1;

		if (gold.boost_time <= 0) 
			gold.boost_multiplier = 0;
		
		if (key_press(KEY_PRGM_OPTN)) {
			if (!options_toggle && stats_toggle)
				stats_toggle = false;
			options_toggle = !options_toggle;
			s_sel = 0;
		}

		uint8_t msg_offset = 0;
		for (int i = notes_cnt; i >= 0; i--) {
			if (notes[i].time > 0) {
				uint8_t tmp = disp_msg(notes[i], msg_offset);
				msg_offset += tmp;
			} else {
				if (i == 0) {
					// copy values from index 1 to index 0
					set_msg(&notes[0], notes[1].header, notes[1].body, secs(notes[1].time));
				}
				if (i == 0 || i == 1) {
					// copy values from index 2 to index 1
					set_msg(&notes[1], notes[2].header, notes[2].body, secs(notes[2].time));
				}
				// empty index 2
				set_msg(&notes[2], "", "", 0);
				if (notes_cnt > 0)
					notes_cnt--;
			}
		}

		if (notes[0].time > 0) {
			if (key_press(KEY_PRGM_EXIT)) {
				notes[0].time = 0;
			}
		}
		
		if ((key_press(f_buttons[gold.x]) || (data.cheats.acg && data.cheats.on)) && gold.time <= ticks(13 * gold.time_modifier)) {
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
				push_note(notes, "Lucky!", msg_buf, 6, &notes_cnt);

				data.cookies_all_time += earned;
				data.cookies += earned;
			} else if (gold.effect > 425 && gold.effect <= 850) {
				// Frenzy
				gold.frenzy_time = ticks(MAX_FRENZY * gold.effect_modifier);
				gold.cps_multiplier = 7;

				char msg_buf[40];
				strcpy(msg_buf, "Cookie production x7 for ");

				tmp = malloc(3);
				itoa(MAX_FRENZY * gold.effect_modifier, tmp, 10);
				strcat(msg_buf, tmp);
				free(tmp);

				strcat(msg_buf, " seconds!");

				push_note(notes, "Frenzy", msg_buf, 6, &notes_cnt);
			} else if (gold.effect > 850 && gold.effect <= 893) {
				// Click Frenzy
				gold.click_frenzy_time = ticks(MAX_CLICK_FRENZY * gold.effect_modifier);
				gold.click_multiplier = 777;

				char msg_buf[40];
				strcpy(msg_buf, "Clicking power x777 for ");

				tmp = malloc(3);
				itoa(MAX_CLICK_FRENZY * gold.effect_modifier, tmp, 10);
				strcat(msg_buf, tmp);
				free(tmp);

				strcat(msg_buf, " seconds!");

				push_note(notes, "Click Frenzy", msg_buf, 6, &notes_cnt);
			} else if (gold.effect > 893 && gold.effect <= 996) {
				// Building special
				int cnt = 0;
				for (int i = 0; i < 20; i++) {
					if (data.buildings[i].owned >= 10)
						cnt++;
				}
				if (cnt > 0) {
					
					gold.boost_time = ticks(MAX_BOOST * gold.effect_modifier);

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
					itoa(MAX_BOOST * gold.effect_modifier, tmp, 10);
					strcat(msg_buf, tmp);
					free(tmp);

					strcat(msg_buf, " seconds!");

					push_note(notes, building_specials[r_b], msg_buf, 6, &notes_cnt);
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
					push_note(notes, "Lucky!", msg_buf, 6, &notes_cnt);

					data.cookies_all_time += earned;
					data.cookies += earned;
				}

			} else if (gold.effect > 996) {
				int rblab = random() % 39;
				push_note(notes, "", blab[rblab], 6, &notes_cnt);
			}
			reset_gold(&gold);
		}
		
		if (gold.time <= ticks(13 * gold.time_modifier)) {
			
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
		if (autosave_time <= 0) {
			save_game(data, gold);
			push_note(notes, "", "Game saved", 2, &notes_cnt);
			autosave_time = ticks(60);
		}

		if (sleep)
			fill_scr(0x0000);
		
        if (key == KEY_PRGM_MENU) {
			GetKey(&key);
			DrawFrame(0x0000);
		}

		Bdisp_PutDisp_DD();
		Bdisp_AllClr_VRAM();
	}
	return 0;
}
