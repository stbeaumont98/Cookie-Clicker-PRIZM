#ifndef DRAW_H_
#define DRAW_H_

#include "fxcg\display.h"

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

int rgb_color(int r, int g, int b);
color_t dim_color(color_t color, float f);
void fill_scr(color_t color);
void plot(int x0, int y0, int color);
void fill_area(int x, int y, int width, int height, int color);
void copy_sprite(const void* datar, int x, int y, int width, int height);
void copy_sprite_masked(const void *datar, int x, int y, int width, int height, int maskcolor);
void copy_sprite_scaled(const color_t *in, unsigned x, unsigned y, unsigned w1, unsigned h1, unsigned w2, unsigned h2, bool overlay, color_t overlay_color);
void draw_circle(int xs, int ys, int radius, int color);
void draw_line(int x1, int y1, int x2, int y2, int color, int thickness);
void draw_rect(int x, int y, int width, int height, int color, int thickness);
void copy_sprite_1bit(const unsigned char* data, int x, int y, int width, int height, const color_t* palette, color_t c);
void copy_sprite_4bit(const unsigned char* data, unsigned x, unsigned y, unsigned w, unsigned h, const color_t* palette, bool overlay, color_t c);
int text_height(const char *msg);
void disp_string(unsigned x, unsigned y, const char *message, int color, int alignment);
void disp_line(unsigned x, unsigned y, const char *message, int color);
int text_width(const char *msg);
void disp_string_small(unsigned x, unsigned y, const char *message, int color, bool caps, int alignment);
void disp_line_small(unsigned x, unsigned y, const char* message, int color, bool caps);
int text_width_small(const char *msg, bool caps);
void disp_msg(const struct Message msg);
void draw_background();
void draw_store_tile(uint16_t x, uint8_t y);
void draw_button(uint16_t x, uint8_t y, uint8_t w, char *message, color_t color, bool selected);
void disp_prompt(const struct Message msg, bool sel);
void draw_toggle_box(uint16_t x, uint8_t y, char *message, color_t color, bool toggle);

#endif