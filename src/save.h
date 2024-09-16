#ifndef SAVE_H_
#define SAVE_H_

#include "types.h"

char *get_save_val(double val);
void save_game(struct CookieData);
void load_game();

#endif