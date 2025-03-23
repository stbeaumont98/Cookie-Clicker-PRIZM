#ifndef CONVERT_H_
#define CONVERT_H_

char *get_display_val(double val, bool disp_dec, bool abrev);
char *disp_decimal(double val, uint32_t dec_pnt);
char *disp_comma(uint32_t val);

#endif