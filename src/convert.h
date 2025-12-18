#ifndef CONVERT_H_
#define CONVERT_H_

char *get_display_val(double val, bool disp_dec, bool abrev);
char *get_save_val(double val);
char *disp_decimal(double val, int dec_pnt);
char *disp_comma(uint32_t val);

#endif