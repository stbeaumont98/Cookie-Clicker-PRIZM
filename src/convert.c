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
	char *val_buf = malloc(0x20);
	char *suffix = malloc(0x18);
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
		dec = 1;
	else if (val < 1E6 && !disp_dec) {
		dec = 0;
		disp_val = round2(disp_val);
	} else
		dec = 3;
	
	char *tmp = disp_decimal(disp_val, dec);
	strcpy(val_buf, tmp);
	free(tmp);
	
	strcat(val_buf, suffix);

	free(suffix);

	return val_buf;
}

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

	char *tmp = disp_decimal(val, 10);
	strcpy(val_buf, tmp);
	free(tmp);
	strcat(val_buf, suffix);
	strcat(val_buf, "\n");

	free(suffix);

	return val_buf;
}

char *disp_decimal(double val, int dec_pow) {
	char *buffer = malloc(16);

	uint32_t integer = (uint32_t) (val + 1E-9);

	if (integer >= 1000) {
		char *tmp = disp_comma(integer);
		strcpy(buffer, tmp);
		free(tmp);
	} else
		itoa(integer, buffer, 10);
	
	if (dec_pow != 0) {
		double remaining = val - (double) integer;
		double powten = ten_pow(dec_pow);
		uint64_t decimal = (uint64_t) round2(remaining * powten);

		if (decimal != 0) {

			int offset = 0;
			while (remaining < 0.1) {
				remaining *= 10.;
				offset++;
			}

			while (decimal % 10 == 0)
				decimal /= 10;

			char r_tmp[12];

			uint32_t first = (uint32_t) ((double) decimal / 100000.);
			uint32_t second = (uint32_t) (decimal % 100000);

			char tmp[12];

			if (first == 0 && second != 0) {
				itoa(second, tmp, 10);
				strcpy(r_tmp, tmp);
			} else if (first != 0 && second == 0) {
				itoa(first, tmp, 10);
				strcpy(r_tmp, tmp);
			} else if (first != 0 && second != 0) {
				itoa(first, tmp, 10);
				strcpy(r_tmp, tmp);
				itoa(second, tmp, 10);
				strcat(r_tmp, tmp);
			}
			
			strcat(buffer, ".");

			if (round2((val - (double) integer) * powten) < (powten / 10.)) {
				for (int i = 0; i < offset; i++)
					strcat(buffer, "0");
			}
			strcat(buffer, r_tmp);
		}
	}
	return buffer;
}

char *disp_comma(uint32_t val) {
	char *buffer = malloc(10);

	if (val < 1000) {
		itoa(val, buffer, 10);
		return buffer;
	}

	uint16_t front = val / 1000;
	uint16_t back = val - (front * 1000);

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