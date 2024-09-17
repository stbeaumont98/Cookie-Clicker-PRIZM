#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "math1.h"

#include "convert.h"

char *get_display_val(double val, bool disp_dec, bool abrev) {
	char *val_buf = malloc(30);
	char *suffix = malloc(15);

	int cnt = 0;

	double disp_val = val;

	if (disp_val < 1) {
		if (disp_val != 0) {
			while (disp_val < 1) {
				disp_val *= 10;
				cnt--;
			}
		}
	} else {
		while (disp_val >= 1000 || cnt % 3 != 0) {
			disp_val *= 0.1;
			cnt++;
		}
	}

	switch (cnt) {
		case 6:
			strcpy(suffix, abrev ? " mil." : " million");
			break;
		case 9:
			strcpy(suffix, abrev ? " bil." : " billion");
			break;
		case 12:
			strcpy(suffix, abrev ? " tril." : " trillion");
			break;
		case 15:
			strcpy(suffix, abrev ? " quad." : " quadrillion");
			break;
		case 18:
			strcpy(suffix, abrev ? " quin." : " quintillion");
			break;
		case 21:
			strcpy(suffix, abrev ? " sext." : " sextillion");
			break;
		case 24:
			strcpy(suffix, abrev ? " sept." : " septillion");
			break;
		case 27:
			strcpy(suffix, abrev ? " oct." : " octillion");
			break;
		case 30:
			strcpy(suffix, abrev ? " non." : " nonillion");
			break;
		case 33:
			strcpy(suffix, abrev ? " dec." : " decillion");
			break;
		case 36:
			strcpy(suffix, abrev ? " udc." : " undecillion");
			break;
		case 39:
			strcpy(suffix, abrev ? " ddc." : " duodecillion");
			break;
		case 42:
			strcpy(suffix, abrev ? " tdc." : " tredecillion");
			break;
		case 45:
			strcpy(suffix, abrev ? " qadc." : " quattuordecillion");
			break;
		case 48:
			strcpy(suffix, abrev ? " qidc." : " quindecillion");
			break;
		case 51:
			strcpy(suffix, abrev ? " sxdc." : " sexdecillion");
			break;
		case 54:
			strcpy(suffix, abrev ? " spdc." : " septendecillion");
			break;
		case 57:
			strcpy(suffix, abrev ? " ocdc." : " octodecillion");
			break;
		case 60:
			strcpy(suffix, abrev ? " nodc." : " novemdecillion");
			break;
		case 63:
			strcpy(suffix, abrev ? " vg." : " vigintillion");
			break;
		default:
			disp_val = val;
			break;
	}
	
	int dec = 0;

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