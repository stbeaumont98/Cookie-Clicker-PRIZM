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
		disp_val = (double) round2(disp_val);
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

	int cnt = 0;
	if (val < 1) {
		if (val != 0) {
			while (val < 1) {
				val *= 10;
				cnt--;
			}
		}
	} else {
		while (val >= 10) {
			val *= 0.1;
			cnt++;
		}
	}

	char s_tmp[3];
	itoa(cnt, s_tmp, 10);
	strcat(suffix, s_tmp);

	char *tmp = disp_decimal(val, 7);
	strcpy(val_buf, tmp);
	free(tmp);
	strcat(val_buf, suffix);
	strcat(val_buf, "\n");

	free(suffix);

	return val_buf;
}

void pad_zeros(char *buffer, uint32_t val, uint8_t pow) {
	char tmp[0xF];

	itoa(val, tmp, 10);

	if (val < (ten_pow(pow) / 10.)) {
		for (int i = 0; i < pow - strlen(tmp); i++)
			strcat(buffer, "0");
	}
}

char *disp_decimal(double val, uint8_t dec_pow) {
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
		uint64_t decimal = (uint64_t) round2(remaining * ten_pow(dec_pow));

		if (decimal != 0) {
			
			strcat(buffer, ".");

			while (decimal % 10 == 0) {
				decimal /= 10;
				dec_pow--;
			}

			uint8_t half_pow = dec_pow / 2;
			
			uint32_t first = (uint32_t) ((double) decimal / ten_pow(half_pow));
			uint32_t second = (uint32_t) (decimal % (uint32_t) ten_pow(half_pow));

			char r_tmp[20];
			char tmp[10];

			pad_zeros(r_tmp, first, dec_pow - half_pow);
			itoa(first, tmp, 10);
			strcat(r_tmp, tmp);

			if (second != 0) {
				pad_zeros(r_tmp, second, half_pow);
				itoa(second, tmp, 10);
				strcat(r_tmp, tmp);
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

char *time_to_str(double timestamp) {
    char *buffer = malloc(16);
	char tmp[10];

	uint32_t integer = (uint32_t) (timestamp / ten_pow(6));
	uint32_t remaining = (uint32_t) (timestamp - ((double) integer * ten_pow(6)));

	itoa(integer, tmp, 10);
	strcpy(buffer, tmp);

	pad_zeros(buffer, remaining, 6);

    itoa(remaining, tmp, 10);
	strcat(buffer, tmp);
    
    return buffer;
}