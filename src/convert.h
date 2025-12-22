#ifndef CONVERT_H_
#define CONVERT_H_

char *get_display_val(double val, bool disp_dec, bool abrev);
char *get_save_val(double val);
char *disp_decimal(double val, uint8_t dec_pnt);
char *disp_comma(uint32_t val);
char *time_to_str(double timestamp);

#endif