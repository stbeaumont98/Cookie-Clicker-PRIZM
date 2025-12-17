#ifndef SAVE_H_
#define SAVE_H_

void save_game(const struct CookieData data, const struct GoldenData gold);
void load_game(struct CookieData *data, struct GoldenData *gold);

void backup_game();
void restore_backup();
void reset_game(struct CookieData *data, struct GoldenData *gold);

#endif