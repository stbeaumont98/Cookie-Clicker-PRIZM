#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "math1.h"

#include "convert.h"

const char *suffixes[25] = { " million", " billion", " trillion",
    " quadrillion", " quintillion", " sextillion", " septillion", " octillion",
    " nonillion", " decillion", " undecillion", " duodecillion", " tredecillion",
    " quattuordecillion", " quindecillion", " sexdecillion", " septendecillion",
    " octodecillion", " novemdecillion", " vigintillion", " unvigintillion",
	" duovigintillion", " trevigintillion", " quattuorvigintillion",
	" quinvigintillion"};

const char *suffixes_abrev[25] = { " mil.", " bil.", " tril.", " quad.",
    " quin.", " sext.", " sept.", " oct.", " non.", " dec.", " udc.", " ddc.",
    " tdc.", " qadc.", " qidc.", " sxdc.", " spdc.", " ocdc.", " nodc.", " vg.",
	" uvg.", " dvg.", " tvg.", " qavg.", " qivg." };

char *get_display_val(double val, bool disp_dec, bool abrev) {
	double disp_val = val;
	char *val_buf = malloc(30);
	char *suffix = malloc(20);
	int dec = 0;

	if (val >= 1E6) {
		disp_val *= 1E-6;
		for (int i = 0; i < 25; i++) {
			if (disp_val < 1000) {
				strcpy(suffix, abrev ? suffixes_abrev[i] : suffixes[i]);
				break;
			}
			disp_val *= 1E-3;
		}
	}

	if (val < 1E6 && disp_dec)
		dec = 10;
	else if (val < 1E6 && !disp_dec) {
		dec = 0;
		disp_val = round2(disp_val);
	} else
		dec = 1000;
	
	char *tmp = disp_decimal(disp_val, dec);
	strcpy(val_buf, tmp);
	free(tmp);
	
	strcat(val_buf, suffix);

	free(suffix);

	return val_buf;
}

char *disp_decimal(double val, int32_t dec_pnt) {
	char *buffer = malloc(12);

	int32_t integer = (int32_t) val;

	if (integer >= 1000) {
		char *tmp = disp_comma(integer);
		strcpy(buffer, tmp);
		free(tmp);
	} else
		itoa(integer, buffer, 10);
	
	if (dec_pnt != 0) {
		int32_t decimal = (int32_t) round2((val - integer) * dec_pnt);

		if (decimal != 0) {

			char tmp[9];
			itoa(decimal, tmp, 10);
			int dec_len = strlen(tmp);

			while (decimal % 10 == 0)
				decimal /= 10;
				
			itoa(decimal, tmp, 10);
			
			strcat(buffer, ".");

			int dec_pnt_cpy = dec_pnt, cnt = 0;
			while (dec_pnt_cpy % 10 == 0) {
				dec_pnt_cpy /= 10;
				cnt++;
			}

			if (round2((val - integer) * dec_pnt) < (dec_pnt / 10)) {
				for (int i = 0; i < cnt - dec_len; i++)
					strcat(buffer, "0");
			}
			strcat(buffer, tmp);
		}
	}
	return buffer;
}

char *disp_comma(int32_t val) {
	char *buffer = malloc(10);

	if (val < 1000) {
		itoa(val, buffer, 10);
		return buffer;
	}

	int16_t front = val / 1000;
	int16_t back = val - (front * 1000);

	itoa(front, buffer, 10);

	strcat(buffer, ",");

	char *back_buf = malloc(5);

	itoa(back, back_buf, 10);

	for (int i = 0; i < 3 - strlen(back_buf); i++)
		strcat(buffer, "0");
	
	strcat(buffer, back_buf);

	free(back_buf);

	return buffer;
}