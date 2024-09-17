#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "fxcg\file.h"
#include "fxcg\display.h"
#include "types.h"
#include "convert.h"

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

void save_game(struct CookieData data) {
	char *heading = "Saving...";

	ProgressBar2((unsigned char *) heading, 0, 28);
    int i;

    unsigned short p_file[sizeof(PATH) * 2];

    Bfile_StrToName_ncpy(p_file, (unsigned char *) PATH, sizeof(PATH));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
        size_t size = 500;
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
	ProgressBar2((unsigned char *) heading, 1, 28);

	char save_buf[500];

	char *tmp = get_save_val(data.cookies_all_time);
    strcpy(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 2, 28);

	tmp = get_save_val(data.cookies);
    strcat(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 3, 28);

	tmp = get_save_val(data.handmade_cookies);
    strcat(save_buf, tmp);
	free(tmp);
	
	ProgressBar2((unsigned char *) heading, 4, 28);

	tmp = malloc(12);
	itoa(data.click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 5, 28);

	tmp = malloc(6);
	itoa(data.gold_click_count, tmp, 10);
	strcat(save_buf, tmp);
	strcat(save_buf, "\n");
	free(tmp);

	ProgressBar2((unsigned char *) heading, 6, 28);

    tmp = malloc(4);
	strcpy(tmp, "");
    for (i = 0; i < 20; i++) {
        itoa(data.buildings[i].owned, tmp, 10);
        strcat(save_buf, tmp);
		strcat(save_buf, "\n");
		ProgressBar2((unsigned char *) heading, 7 + i, 28);
    }

    free(tmp);

    Bfile_WriteFile_OS(h_file, save_buf, strlen(save_buf));
	
	ProgressBar2((unsigned char *) heading, 27, 28);

    Bfile_CloseFile_OS(h_file);

	ProgressBar2((unsigned char *) heading, 28, 28);

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


void load_game(struct CookieData *data) {
	reset_buildings(data);
	data->buildings_unlocked = 2;

    int i, j;
    unsigned short p_file[sizeof(PATH) * 2];
	char *buf = malloc(0xFF);
    Bfile_StrToName_ncpy(p_file, (unsigned char *) PATH, sizeof(PATH));

    int h_file = Bfile_OpenFile_OS(p_file, 3, 0);

    if (h_file < 0) {
		data->cookies_all_time = 0;
		data->cookies = 0;
		data->handmade_cookies = 0;
		data->cps = 0;
		data->click_count = 0;
		data->gold_click_count = 0;
		return;
	}
	
	Bfile_ReadFile_OS(h_file, buf, 0xFF, 0);

	char *all_time = strtok(buf, "\n");
	char *cookies = strtok(NULL, "\n");
	char *handmade = strtok(NULL, "\n");
	char *clicked = strtok(NULL, "\n");
	char *g_clicked = strtok(NULL, "\n");

	data->click_count = strtod(clicked, NULL);
	data->gold_click_count = strtod(g_clicked, NULL);

	for (i = 0; i < 20; i++) {

		data->buildings[i].owned = (int16_t) strtod(strtok(NULL, "\n"), NULL);
		data->cps += data->buildings[i].owned * data->buildings[i].b_cps;

		for (j = 0; j < data->buildings[i].owned; j++)
			data->buildings[i].price += data->buildings[i].price * 0.15;

		
		if (data->cookies_all_time >= base_prices[i])
			data->buildings[i].hidden = false;
		
		if (i >= 2) {
			if (data->buildings[i].locked && (data->cookies_all_time >= base_prices[i - 2])) {
				data->buildings[i].locked = false;
				data->buildings_unlocked++;
			}
		}
	}
	
	char *dec = strtok(all_time, "E");
	char *pow = strtok(NULL, "E");

	data->cookies_all_time = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(cookies, "E");
	pow = strtok(NULL, "E");

	data->cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	dec = strtok(handmade, "E");
	pow = strtok(NULL, "E");

	data->handmade_cookies = strtod(dec, NULL) * ten_pow(strtod(pow, NULL));

	free(buf);

    Bfile_CloseFile_OS(h_file);
}