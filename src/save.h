#ifndef SAVE_H_
#define SAVE_H_

#include "types.h"

char *get_save_val(double val);
void save_game(const struct CookieData data, const struct GoldenData gold);
void load_game(struct CookieData *data, struct GoldenData *gold);

#endif