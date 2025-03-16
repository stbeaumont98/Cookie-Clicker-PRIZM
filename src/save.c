#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "fxcg\file.h"
#include "fxcg\display.h"
#include "types.h"
#include "convert.h"
#include "math1.h"
#include "upgrades.h"

#include "save.h"

#define PATH "\\\\fls0\\cookies.sav"

char *get_save_val(double val) {
	char *val_buf = malloc(20);
	char *suffix = malloc(5);

	strcpy(suffix, "E");

	if (val < 1) {
		int cnt = 0;
		if (val != 0) {
			while (val < 1) {
				val *= 10;
				cnt++;
			}
			strcat(suffix, "-");
		}
		char tmp[3];
		itoa(cnt, tmp, 10);
		strcat(suffix, tmp);
	} else {
		int cnt = 0;
		while (val >= 10) {
			val *= 0.1;
			cnt++;
		}
		char tmp[3];
		itoa(cnt, tmp, 10);
		strcat(suffix, tmp);
	}

	char *tmp = disp_decimal(val, 1000000);
	strcpy(val_buf, tmp);
	free(tmp);
	strcat(val_buf, suffix);
	strcat(val_buf, "\n");

	free(suffix);

	return val_buf;
}

void save_game(const struct CookieData data, const struct GoldenData gold) {
	char *heading = "Saving...";
	int i;

	ProgressBar2((unsigned char *) heading, 0, 21);

    unsigned short p_file[sizeof(PATH) * 2];

    Bfile_StrToName_ncpy(p_file, (unsigned char *) PATH, sizeof(PATH));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
        size_t size = 0x200;
        if (Bfile_CreateEntry_OS(p_file, 1, &size) >= 0) {
            h_file = Bfile_OpenFile_OS(p_file, 3, 0);
            if (h_file < 0) {
                // FAILURE
				DisplayMessageBox((unsigned char *) "FAILED TO CREATE & OPEN FILE");
				
            }
        } else {
            // FAILURE
			DisplayMessageBox((unsigned char *) "FAILED TO CREATE FILE");
        }
	}
	ProgressBar2((unsigned char *) heading, 1, 21);

	char save_buf[0x200];

	char *tmp = get_save_val(data.cookies_all_time);
    strcpy(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 2, 21);

	tmp = get_save_val(data.cookies);
    strcat(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 3, 21);

	tmp = get_save_val(data.handmade_cookies);
    strcat(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 4, 21);

    tmp = malloc(4);
    for (i = 0; i < 20; i++) {
        itoa(data.buildings[i].owned, tmp, 10);
        strcat(save_buf, tmp);
		strcat(save_buf, "\n");
    }
    free(tmp);

	ProgressBar2((unsigned char *) heading, 5, 21);

	tmp = malloc(12);
	itoa(data.click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 6, 21);

	tmp = malloc(6);
	itoa(data.gold_click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 7, 21);

	// save GoldenData

	tmp = malloc(4);
	itoa(gold.x, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 8, 21);

	tmp = malloc(4);
	itoa(gold.y, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 9, 21);

	tmp = malloc(4);
	itoa(gold.scale, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 10, 21);

	tmp = malloc(5);
	itoa(gold.effect, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 11, 21);

	tmp = malloc(5);
	itoa(gold.time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 12, 21);

	tmp = malloc(4);
	itoa(gold.frenzy_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 13, 21);

	tmp = get_save_val(gold.cps_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	ProgressBar2((unsigned char *) heading, 14, 21);

	tmp = malloc(4);
	itoa(gold.click_frenzy_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 15, 21);

	tmp = get_save_val(gold.click_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	ProgressBar2((unsigned char *) heading, 16, 21);

	tmp = malloc(4);
	itoa(gold.boost_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 17, 21);

	tmp = get_save_val(gold.boost_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	ProgressBar2((unsigned char *) heading, 18, 21);

	tmp = malloc(2);
	for (i = 0; i < 318; i++) {
		itoa(data.upgrades[i], tmp, 10);
		strcat(save_buf, tmp);
	}
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 19, 21);

    Bfile_WriteFile_OS(h_file, save_buf, strlen(save_buf));
	
	ProgressBar2((unsigned char *) heading, 20, 21);

    Bfile_CloseFile_OS(h_file);

	ProgressBar2((unsigned char *) heading, 21, 21);

	MsgBoxPop();

	PrintXY(1, 2, "  Game saved!", 0, 0);
	PrintXY(1, 5, "  Press any key to", 0, 0);
	PrintXY(1, 6, "  quit.", 0, 0);

    Bdisp_PutDisp_DD();
}


double ten_pow(int16_t n) {
	double x = 10;
    double pow = 1;

    for (int i = 0; i < abs(n); i++) {
		if (n < 0)
			pow /= x;
		else
        	pow *= x;
    }

	return pow;
}

void load_game(struct CookieData *data, struct GoldenData *gold) {
	reset_buildings(data);
	reset_gold(gold);

	data->buildings_unlocked = 2;

    int i, j;
    unsigned short p_file[sizeof(PATH) * 2];
	char *buf = malloc(0x400);
    Bfile_StrToName_ncpy(p_file, (unsigned char *) PATH, sizeof(PATH));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
		data->cookies_all_time = 0;
		data->cookies = 0;
		data->handmade_cookies = 0;
		data->click_count = 0;
		data->gold_click_count = 0;
		for (i = 0; i < 20; i ++) {
			data->buildings[i].multiplier = 1;
			data->buildings[i].modifier = 0;
			data->buildings[i].percent_cps = 0;
		}
		data->total_buildings = 0;
		for (i = 0; i < 318; i++) {
			data->upgrades[i] = false;
			data->upgrades_unlocked[i] = false;
		}
		gold->frenzy_time = 0;
		gold->cps_multiplier = 1;
		gold->click_frenzy_time = 0;
		gold->click_multiplier = 1;
		gold->boost_time = 0;
		gold->boost_multiplier = 0;
		return;
	}
	
	Bfile_ReadFile_OS(h_file, buf, 0x400, 0);

	char *all_time = strtok(buf, "\n");
	char *cookies = strtok(NULL, "\n");
	char *handmade = strtok(NULL, "\n");

	for (i = 0; i < 20; i++) {
		uint16_t count = (int16_t) strtod(strtok(NULL, "\n"), NULL);

		data->buildings[i].owned = count;
		data->total_buildings += count;

		for (j = 0; j < data->buildings[i].owned; j++)
			data->buildings[i].price += (data->buildings[i].price * .15);

		
		if (data->cookies_all_time >= base_prices[i])
			data->buildings[i].hidden = false;
		
		if (i >= 2) {
			if (data->buildings[i].locked && (data->cookies_all_time >= base_prices[i - 2])) {
				data->buildings[i].locked = false;
				data->buildings_unlocked++;
			}
		}

		data->buildings[i].multiplier = 1;
		data->buildings[i].modifier = 0;
		data->buildings[i].percent_cps = 0;
	}

	char *clicked = strtok(NULL, "\n");
	char *g_clicked = strtok(NULL, "\n");

	data->click_count = strtod(clicked, NULL);
	data->gold_click_count = strtod(g_clicked, NULL);

	gold->x = (uint16_t) strtod(strtok(NULL, "\n"), NULL);
	gold->y = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	gold->scale = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	gold->effect = (uint16_t) strtod(strtok(NULL, "\n"), NULL);
	gold->time = (uint16_t) strtod(strtok(NULL, "\n"), NULL);
	gold->frenzy_time = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	char *cps_multiplier = strtok(NULL, "\n");
	gold->click_frenzy_time = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	char *click_multiplier = strtok(NULL, "\n");
	gold->boost_time = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	char *boost_multiplier = strtok(NULL, "\n");
	char *upgrades = strtok(NULL, "\n");
	
	char *dec = strtok(all_time, "E");
	char *pow = strtok(NULL, "E");

	data->cookies_all_time = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(cookies, "E");
	pow = strtok(NULL, "E");

	data->cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(handmade, "E");
	pow = strtok(NULL, "E");

	data->handmade_cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(cps_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->cps_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(click_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->click_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(boost_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->boost_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	if (strlen(upgrades) != 318) {
		for (i = 0; i < 318; i++) {
			data->upgrades[i] = false;
			data->upgrades_unlocked[i] = false;
		}
	} else {
		for (i = 0; i < 318; i++) {
			bool isowned = (upgrades[i] == '1');
			data->upgrades[i] = isowned;
			data->upgrades_unlocked[i] = isowned;
			if (isowned)
				enable_upgrade(data, i);
		}
	}

	free(buf);

    Bfile_CloseFile_OS(h_file);
}