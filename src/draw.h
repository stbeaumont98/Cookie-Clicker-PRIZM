#ifndef DRAW_H_
#define DRAW_H_

#include "fxcg\display.h"

int rgb_color(int r, int g, int b);
void fill_scr(color_t color);
void plot(int x0, int y0, int color);
void fill_area(int x, int y, int width, int height, int color);
void copy_sprite(const void* datar, int x, int y, int width, int height);
void copy_sprite_masked(const void *datar, int x, int y, int width, int height, int maskcolor);
void copy_sprite_masked_alpha(const void *datar, unsigned x, unsigned y, unsigned width, unsigned height, unsigned maskcolor, unsigned alpha);
void copy_sprite_scaled(const color_t *in, unsigned x, unsigned y, unsigned w1, unsigned h1, unsigned w2, unsigned h2, bool overlay, color_t overlay_color);
void draw_circle(int xs, int ys, int radius, int color);
void draw_line(int x1, int y1, int x2, int y2, int color, int thickness);
void draw_rect(int x, int y, int width, int height, int color, int thickness);
void copy_sprite_1bit(const unsigned char* data, int x, int y, int width, int height, const color_t* palette, color_t c);
void copy_sprite_4bit(const unsigned char* data, unsigned x, unsigned y, unsigned w, unsigned h, color_t* palette);
void disp_string(unsigned x, unsigned y, const char* message, int color);
int text_width(const char *msg);
int text_height(const char *msg);
void small_disp_string(unsigned x, unsigned y, const char* message, int color, bool caps);
int small_text_width(const char *msg, bool caps);
int small_text_height(const char *msg);

#endif