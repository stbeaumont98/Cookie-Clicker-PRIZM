#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "math1.h"

#include "convert.h"

char *get_display_val(double val, bool disp_dec, bool abrev) {
	double disp_val = 0;
	char *val_buf = malloc(30);
	char *suffix = malloc(15);
	int dec = 0;

	if (val < 1E6) {
		disp_val = val;
	} else if (val >= 1E6 && val < 1E9) {
		disp_val = val * 1E-6;
		strcpy(suffix, abrev ? " M" : " million");
	} else if (val >= 1E9 && val < 1E12) {
		disp_val = val * 1E-9;
		strcpy(suffix, abrev ? " B" : " billion");
	} else if (val >= 1E12 && val < 1E15) {
		disp_val = val * 1E-12;
		strcpy(suffix, abrev ? " T" : " trillion");
	} else if (val >= 1E15 && val < 1E18) {
		disp_val = val * 1E-15;
		strcpy(suffix, abrev ? " Qa" : " quadrillion");
	} else if (val >= 1E18 && val < 1E21) {
		disp_val = val * 1E-18;
		strcpy(suffix, abrev ? " Qi" : " quintillion");
	} else if (val >= 1E21 && val < 1E24) {
		disp_val = val * 1E-21;
		strcpy(suffix, abrev ? " Sx" : " sextillion");
	} else if (val >= 1E24 && val < 1E27) {
		disp_val = val * 1E-24;
		strcpy(suffix, abrev ? " Sp" : " septillion");
	} else if (val >= 1E27 && val < 1E30) {
		disp_val = val * 1E-27;
		strcpy(suffix, abrev ? " Oc" : " octillion");
	} else if (val >= 1E30 && val < 1E33) {
		disp_val = val * 1E-30;
		strcpy(suffix, abrev ? " No" : " nonillion");
	} else if (val >= 1E33 && val < 1E36) {
		disp_val = val * 1E-33;
		strcpy(suffix, abrev ? " Dc" : " decillion");
	} else if (val >= 1E36 && val < 1E39) {
		disp_val = val * 1E-36;
		strcpy(suffix, abrev ? " Udc" : " undecillion");
	} else if (val >= 1E39 && val < 1E42) {
		disp_val = val * 1E-39;
		strcpy(suffix, abrev ? " Ddc" : " duodecillion");
	} else if (val >= 1E42 && val < 1E45) {
		disp_val = val * 1E-42;
		strcpy(suffix, abrev ? " Tdc" : " tredecillion");
	} else if (val >= 1E45 && val < 1E48) {
		disp_val = val * 1E-45;
		strcpy(suffix, abrev ? " Qadc" : " quattuordecillion");
	} else if (val >= 1E48 && val < 1E51) {
		disp_val = val * 1E-48;
		strcpy(suffix, abrev ? " Qidc" : " quindecillion");
	} else if (val >= 1E51 && val < 1E54) {
		disp_val = val * 1E-51;
		strcpy(suffix, abrev ? " Sxdc" : " sexdecillion");
	} else if (val >= 1E54 && val < 1E57) {
		disp_val = val * 1E-54;
		strcpy(suffix, abrev ? " Spdc" : " septendecillion");
	} else if (val >= 1E57 && val < 1E60) {
		disp_val = val * 1E-57;
		strcpy(suffix, abrev ? " Ocdc" : " octodecillion");
	} else if (val >= 1E60 && val < 1E63) {
		disp_val = val * 1E-60;
		strcpy(suffix, abrev ? " Nodc" : " novemdecillion");
	} else if (val >= 1E63 && val < 1E66) {
		disp_val = val * 1E-63;
		strcpy(suffix, abrev ? " Vg" : " vigintillion");
	}

	if (val < 1E6 && disp_dec)
		dec = 10;
	else if (val < 1E6 && !disp_dec)
		dec = 0;
	else
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

	int32_t integer = (int32_t) floor2(val);


	if (integer >= 1000) {
		char *tmp = disp_comma(integer);
		strcpy(buffer, tmp);
		free(tmp);
	} else
		itoa(integer, buffer);
	
	if (dec_pnt != 0) {
		int32_t decimal = round2((val - integer) * dec_pnt);

		if (decimal != 0) {

			char tmp[9];
			itoa(decimal, tmp);
			int dec_len = strlen(tmp);

			while (decimal % 10 == 0)
				decimal /= 10;
				
			itoa(decimal, tmp);
			
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
		itoa(val, buffer);
		return buffer;
	}

	int16_t front = (int16_t) floor2((double) val / 1000.);
	int16_t back = round2(val - (front * 1000));

	itoa(front, buffer);

	strcat(buffer, ",");

	char *back_buf = malloc(5);

	itoa(back, back_buf);

	for (int i = 0; i < 3 - strlen(back_buf); i++)
		strcat(buffer, "0");
	
	strcat(buffer, back_buf);

	free(back_buf);

	return buffer;
}