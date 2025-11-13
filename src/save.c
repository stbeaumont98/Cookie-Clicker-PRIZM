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

const char path[20] = "\\\\fls0\\cookies.sav";
const char bak_path[24] = "\\\\fls0\\cookies.sav.bak";

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
	int i;

    unsigned short p_file[sizeof(path) * 2];

    Bfile_StrToName_ncpy(p_file, path, sizeof(path));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
        size_t size = 0x320;
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

	char save_buf[0x320];

	char *tmp = get_save_val(data.cookies_all_time);
    strcpy(save_buf, tmp);
	free(tmp);

	tmp = get_save_val(data.cookies);
    strcat(save_buf, tmp);
	free(tmp);

	tmp = get_save_val(data.handmade_cookies);
    strcat(save_buf, tmp);
	free(tmp);

    tmp = malloc(4);
    for (i = 0; i < 20; i++) {
        itoa(data.buildings[i].owned, tmp, 10);
        strcat(save_buf, tmp);
		strcat(save_buf, "\n");
    }
    free(tmp);

	tmp = malloc(12);
	itoa(data.click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(6);
	itoa(data.gold_click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	// save GoldenData

	tmp = malloc(4);
	itoa(gold.x, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(4);
	itoa(gold.y, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(4);
	itoa(gold.scale, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(5);
	itoa(gold.effect, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(7);
	itoa(gold.time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = malloc(6);
	itoa(gold.frenzy_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = get_save_val(gold.cps_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	tmp = malloc(6);
	itoa(gold.click_frenzy_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = get_save_val(gold.click_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	tmp = malloc(6);
	itoa(gold.boost_time, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	tmp = get_save_val(gold.boost_multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	tmp = get_save_val(data.multiplier);
	strcat(save_buf, tmp);
	free(tmp);

	tmp = malloc(2);
	for (i = 0; i < 478; i++) {
		itoa(data.upgrades[i], tmp, 10);
		strcat(save_buf, tmp);
	}
	strcat(save_buf, "\n");
	free(tmp);

    Bfile_WriteFile_OS(h_file, save_buf, strlen(save_buf));

    Bfile_CloseFile_OS(h_file);
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
	gold->time_modifier = 1;
	gold->effect_modifier = 1;
	reset_gold(gold);

    int i, j;

	data->buildings_unlocked = 2;

	for (i = 0; i < 478; i++) {
		data->upgrades[i] = false;
		data->upgrades_unlocked[i] = false;
	}

	data->multiplier = 1.0;

	char *buf = malloc(0x320);
	
    unsigned short p_file[sizeof(path) * 2];
    Bfile_StrToName_ncpy(p_file, path, sizeof(path));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
		data->cookies_all_time = 0.0;
		data->cookies = 0.0;
		data->handmade_cookies = 0.0;
		data->click_count = 0;
		data->gold_click_count = 0;
		for (i = 0; i < 20; i ++) {
			data->buildings[i].multiplier = 1.0;
			data->buildings[i].modifier = 0.0;
			data->buildings[i].percent = 0.0;
			data->buildings[i].gma = false;
		}
		data->total_buildings = 0;
		gold->frenzy_time = 0;
		gold->cps_multiplier = 1.0;
		gold->click_frenzy_time = 0;
		gold->click_multiplier = 1.0;
		gold->boost_time = 0;
		gold->boost_multiplier = 0.0;
		return;
	}
	
	Bfile_ReadFile_OS(h_file, buf, 0x320, 0);

	char *all_time = strtok(buf, "\n");
	char *cookies = strtok(NULL, "\n");
	char *handmade = strtok(NULL, "\n");
	
	char *dec = strtok(all_time, "E");
	char *pow = strtok(NULL, "E");

	data->cookies_all_time = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(cookies, "E");
	pow = strtok(NULL, "E");

	data->cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(handmade, "E");
	pow = strtok(NULL, "E");

	data->handmade_cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

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

		data->buildings[i].multiplier = 1.0;
		data->buildings[i].modifier = 0.0;
		data->buildings[i].percent = 0.0;
		data->buildings[i].gma = false;
	}

	char *clicked = strtok(NULL, "\n");
	char *g_clicked = strtok(NULL, "\n");

	data->click_count = strtod(clicked, NULL);
	data->gold_click_count = strtod(g_clicked, NULL);

	gold->x = (uint16_t) strtod(strtok(NULL, "\n"), NULL);
	gold->y = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	gold->scale = (uint8_t) strtod(strtok(NULL, "\n"), NULL);
	gold->effect = (uint16_t) strtod(strtok(NULL, "\n"), NULL);
	gold->time = (int32_t) strtod(strtok(NULL, "\n"), NULL);
	gold->frenzy_time = (int32_t) strtod(strtok(NULL, "\n"), NULL);
	char *cps_multiplier = strtok(NULL, "\n");
	gold->click_frenzy_time = (int32_t) strtod(strtok(NULL, "\n"), NULL);
	char *click_multiplier = strtok(NULL, "\n");
	gold->boost_time = (int32_t) strtod(strtok(NULL, "\n"), NULL);
	char *boost_multiplier = strtok(NULL, "\n");
	char *multiplier = strtok(NULL, "\n");
	char *upgrades = strtok(NULL, "\n");

	dec = strtok(cps_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->cps_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(click_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->click_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(boost_multiplier, "E");
	pow = strtok(NULL, "E");

	gold->boost_multiplier = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	double tmp = strtod(multiplier, NULL); 
	if (tmp > 1.0)
		data->multiplier = tmp;

	if (strlen(upgrades) == 478) {
		for (i = 0; i < 478; i++) {
			bool isowned = (upgrades[i] == '1');
			data->upgrades[i] = isowned;
			data->upgrades_unlocked[i] = isowned;
			if (isowned && i < 336)
				enable_upgrade(data, gold, i);
		}
	}

	free(buf);

    Bfile_CloseFile_OS(h_file);
}

void backup_game() {
	unsigned short save[sizeof(path) * 2];
    unsigned short back[sizeof(bak_path) * 2];

    Bfile_StrToName_ncpy(save, path, sizeof(path));
    Bfile_StrToName_ncpy(back, bak_path, sizeof(bak_path));

	if(Bfile_RenameEntry(save, back) < 0) {
		Bfile_DeleteEntry(back);
		Bfile_RenameEntry(save, back);
	}
}

void restore_backup() {
	unsigned short save[sizeof(path) * 2];
    unsigned short back[sizeof(bak_path) * 2];

    Bfile_StrToName_ncpy(save, path, sizeof(path));
    Bfile_StrToName_ncpy(back, bak_path, sizeof(bak_path));

	if(Bfile_RenameEntry(back, save) < 0) {
		Bfile_DeleteEntry(save);
		Bfile_RenameEntry(back, save);
	}
}

void reset_game(struct CookieData *data, struct GoldenData *gold) {

	reset_buildings(data);
	gold->time_modifier = 1;
	gold->effect_modifier = 1;
	reset_gold(gold);

    int i;

	data->buildings_unlocked = 2;

	for (i = 0; i < 478; i++) {
		data->upgrades[i] = false;
		data->upgrades_unlocked[i] = false;
	}

	data->multiplier = 1.0;
	data->cookies_all_time = 0.0;
	data->cookies = 0.0;
	data->handmade_cookies = 0.0;
	data->click_count = 0;
	data->gold_click_count = 0;
	for (i = 0; i < 20; i ++) {
		data->buildings[i].multiplier = 1.0;
		data->buildings[i].modifier = 0.0;
		data->buildings[i].percent = 0.0;
		data->buildings[i].gma = false;
	}
	data->total_buildings = 0;
	gold->frenzy_time = 0;
	gold->cps_multiplier = 1.0;
	gold->click_frenzy_time = 0;
	gold->click_multiplier = 1.0;
	gold->boost_time = 0;
	gold->boost_multiplier = 0.0;

}