#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fxcg\display.h"
#include "charmap.h"
#include "math1.h"

#include "draw.h"

int rgb_color(int r, int g, int b) {
  	return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

void fill_scr(color_t color) {
    unsigned int temp_color = (unsigned int)(color << 16) | color;
    for(int i = 0; i < LCD_WIDTH_PX*LCD_HEIGHT_PX / 2; i++) {
        *((int *) GetVRAMAddress() + i) = temp_color;
    }
}

void plot(int x0, int y0, int color) {
    char* VRAM = (char*) GetVRAMAddress();
    VRAM += 2 * (y0 * LCD_WIDTH_PX + x0);
    *(VRAM++) = (color&0x0000FF00) >> 8;
    *(VRAM++) = (color&0x000000FF);
    return;
}

void fill_area(int x, int y, int width, int height, int color) {
    //only use lower two bytes of color
    char *VRAM = (char *) GetVRAMAddress();
    VRAM += 2 * (LCD_WIDTH_PX * y + x);
    for(int j = y; j < y + height; j++) {
        for(int i = x; i < x + width;  i++) {
            *(VRAM++) = (color & 0x0000FF00) >> 8;
            *(VRAM++) = (color & 0x000000FF);
        }
        VRAM += 2 * (LCD_WIDTH_PX - width);
    }
}

void copy_sprite(const void* datar, int x, int y, int width, int height) {
   color_t *data = (color_t *) datar;
   color_t *VRAM = (color_t *) GetVRAMAddress();
   VRAM += LCD_WIDTH_PX * y + x;
   for(int j = y; j < y + height; j++) {
      for(int i = x; i<x + width; i++) {
         *(VRAM++) = *(data++);
     }
     VRAM += LCD_WIDTH_PX - width;
   }
}

void copy_sprite_masked(const void *datar, int x, int y, int width, int height, int maskcolor) {
   color_t *data = (color_t *) datar;
   color_t *VRAM = (color_t *) GetVRAMAddress();
   VRAM += LCD_WIDTH_PX * y + x;
   for(int j = y; j < y + height; j++) {
      for(int i = x; i < x + width;  i++) {
         if (*(data) != maskcolor) {
            *(VRAM++) = *(data++);
         } else { VRAM++; data++; }
      }
      VRAM += LCD_WIDTH_PX - width;
   }
}

void copy_sprite_scaled(const color_t *in, unsigned x, unsigned y, unsigned w1, unsigned h1, unsigned w2, unsigned h2, bool overlay, color_t overlay_color) {
	color_t* VRAM = (color_t *) GetVRAMAddress();
   	VRAM += (LCD_WIDTH_PX * y + x);
	unsigned x_ratio = ((w1 << 16) / w2) + 1;   
	unsigned y_ratio = ((h1 << 16) / h2) + 1;   
	unsigned x2, y2, i, j;
	for (i = 0; i < h2; ++i) {
		for (j = 0; j < w2; ++j) {   
			x2 = ((j * x_ratio) >> 16);
			y2 = ((i * y_ratio) >> 16);
			color_t p = in[(y2 * w1) + x2];
			if(i >= 0 && i <= 216 && j >= 0 && j <= 384 && p != COLOR_RED)
				*(VRAM)++ = overlay ? 0x0000 : p;
			else
				VRAM++;
		} 
		VRAM += LCD_WIDTH_PX - w2; 
	}
}

void draw_circle(int xs, int ys, int radius, int color) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	plot(xs, ys + radius, color);
	plot(xs, ys - radius, color);
	plot(xs + radius, ys, color);
	plot(xs - radius, ys, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		plot(xs + x, ys + y, color);
		plot(xs - x, ys + y, color);
		plot(xs + x, ys - y, color);
		plot(xs - x, ys - y, color);
		plot(xs + y, ys + x, color);
		plot(xs - y, ys + x, color);
		plot(xs + y, ys - x, color);
		plot(xs - y, ys - x, color);
	}
}

void draw_line(int x1, int y1, int x2, int y2, int color, int thickness) {
    signed char ix;
    signed char iy;

    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x = (x2 > x1 ? (ix = 1, x2 - x1) : (ix = -1, x1 - x2)) << 1;
    int delta_y = (y2 > y1 ? (iy = 1, y2 - y1) : (iy = -1, y1 - y2)) << 1;

   	draw_circle(x1, y1, thickness, color);
    if (delta_x >= delta_y) {
        int error = delta_y - (delta_x >> 1);        // error may go below zero
        while (x1 != x2) {
            if (error >= 0) {
                if (error || (ix > 0)) {
                    y1 += iy;
                    error -= delta_x;
                }                           // else do nothing
         }                              // else do nothing
            x1 += ix;
            error += delta_y;
            draw_circle(x1, y1, thickness, color);
        }
    } else {
        int error = delta_x - (delta_y >> 1);      // error may go below zero
        while (y1 != y2) {
            if (error >= 0) {
                if (error || (iy > 0)) {
                    x1 += ix;
                    error -= delta_y;
                }                           // else do nothing
            }                              // else do nothing
            y1 += iy;
            error += delta_x;
            draw_circle(x1, y1, thickness, color);
        }
    }
}

void draw_rect(int x, int y, int width, int height, int color, int thickness) {
    draw_line(x, y, x + width, y, color, thickness);
    draw_line(x, y, x, y + height, color, thickness);
    draw_line(x + width, y, x + width, y + height, color, thickness);
    draw_line(x, y + height, x + width, y + height, color, thickness);
    return;
}

void copy_sprite_1bit(const unsigned char* data, int x, int y, int width, int height, const color_t* palette, color_t c) {
    color_t* VRAM = (color_t*) GetVRAMAddress();
    VRAM += (LCD_WIDTH_PX * y + x);
    int x_offset = 0;
    unsigned char buf;
    for(int j = y; j < y + height; j++) {
        int availbits = 0;
        for(int i = x; i < x + width;  i++) {
            if (!availbits) {
                buf = data[x_offset++];
                availbits = 8;
            }
            color_t this = ((color_t) buf >> 7);
            color_t color = palette[this];
            if(color != COLOR_RED) {
                *VRAM = c;
            }
            VRAM++;
            buf <<= 1;
            availbits -= 1;
        }
        VRAM += (LCD_WIDTH_PX - width);
    }
}

void copy_sprite_4bit(const unsigned char* data, unsigned x, unsigned y, unsigned w, unsigned h, color_t* palette) {
    color_t* VRAM = (color_t*) GetVRAMAddress();
    VRAM += (LCD_WIDTH_PX * y + x);
    int offset = 0;
    unsigned char buf;
    for(int j = y; j < y + h; j++) {
        int availbits = 0;
        for(int i = x; i < x + w; i++) {
            if (!availbits) {
                buf = data[offset++];
                availbits = 8;
            }
            color_t this = ((color_t) buf >> 4);
            color_t color = palette[(color_t) this];
            if (i >= 0 && i <= 216 && j >= 0 && j <= 384 && color != COLOR_RED)
                *VRAM = color;
            VRAM++;
            buf <<= 4;
            availbits -= 4;
        }
        VRAM += (LCD_WIDTH_PX - w);
    }
}

// normal font

void disp_string(unsigned x, unsigned y, const char* message, int color) {
    int l = strlen(message);
    int i;
    unsigned line = 0;
    int x_offset = 0;
    int y_offset = 0;
    char c;
    bool quote = false;
    for (i = 0; i < l; i++) {
        c = message[i];
        int w = char_width[(int) c];
        int h = char_height[(int) c];
        if (c == '\n') {
            x_offset = 0;
            ++line;
        }
        else if (c == '\t') {}
            //x_offset += 20;
        else {
            switch (c) {
                case '\"':
                case '\'':
                    y_offset = -2;
                    break;
                case '(':
                case ')':
                    y_offset = -1;
                    break;
                case 'j':
                case 'J':
                case 'Q':
                    y_offset = 0;
                    break;
                case '4':
                case '5':
                    y_offset = 1;
                    break;
                case '3':
                case '7':
                case '9':
                    y_offset = 2;
                    break;
                case ';':
                case 'g':
                case 'p':
                case 'q':
                case 'y':
                    y_offset = 3;
                    break;
                case '+':
                    y_offset = 4;
                    break;
                case '-':
                    y_offset = 7;
                    break;
                case ',':
                    y_offset = 9;
                    break;
                default:
                    y_offset = 11 - h;
                    break;
            }
            copy_sprite_1bit((c == '\"' && quote) ? r_quote : charmap[(int) c],
                x + x_offset, y + y_offset + (line * 13), w, h, charmap_palette, color);
            x_offset += (c == ' ') ? 5 : (w + (c == 'Q' ? -1 : 1) + (c == '(' || c == ')' ? 1 : 0));
            if (c == '\"')
                quote = !quote;
        }
        if (x + x_offset >= 384) {
            x_offset = 0;
            ++line;
        }
        if (y + y_offset + (line * h) >= 216)
            break;
    }
}

int text_width(const char *msg) {
    int total = 0, max_total = 0;
	for (int i = 0; i < strlen(msg); i++) {
        if (msg[i] == '\n') {
            max_total = max(total, max_total);
            total = 0;
        } else {
            int w = char_width[(int) msg[i]];
            switch (msg[i]) {
                case ' ':
                    total += 5;
                    break;
                case 'Q':
                    total += (w - 1);
                    break;
                default:
                    total += (w + 1);
                    break;
            }
        }
	}
	return max(total, max_total);
}

int text_height(const char *msg) {
    if (strlen(msg) == 0)
        return 0;
    
    int total = 1;
    for (int i = 0; i < strlen(msg); i++) {
        if (msg[i] == '\n')
            total++;
    }
    return total;
}

// small font

void small_disp_string(unsigned x, unsigned y, const char* message, int color, bool caps) {
    int l = strlen(message);
    int i;
    unsigned line = 0;
    int x_offset = 0;
    int y_offset = 0;
    char c;
    for (i = 0; i < l; i++) {
        c = message[i] - ((caps && message[i] > 0x60 && message[i] < 0x7b) ? 0x20 : 0);
        int w = small_char_width[(int) c];
        int h = small_char_height[(int) c];
        if (c == '\n') {
            x_offset = 0;
            ++line;
        }
        else if (c == '\t') {}
            //x_offset += 20;
        else {
            switch (c) {
                case '[':
                case ']':
                    y_offset = -1;
                    break;
                case '(':
                case ')':
                case 'j':
                case 'J':
                case 'Q':
                    y_offset = 0;
                    break;
                case '+':
                case ';':
                case 'g':
                case 'p':
                case 'q':
                case 'y':
                    y_offset = 2;
                    break;
                case '-':
                    y_offset = 3;
                    break;
                case ',':
                    y_offset = 4;
                    break;
                default:
                    y_offset = 6 - h;
                    break;
            } 
            copy_sprite_1bit(small_charmap[(int) c], x + x_offset, y + y_offset + (line * 9),\
                w, h, charmap_palette, color);
            x_offset += (c == ' ') ? 3 : (w + (c == '(' || c == ')' ? 2 : 1));
        }
        if (x + x_offset >= 384) {
            x_offset = 0;
            ++line;
        }
        if (y + y_offset + (line * h) >= 216)
            break;
    }
}

int small_text_width(const char *msg, bool caps) {
    int total = 0, max_total = 0;
    char c;
	for (int i = 0; i < strlen(msg); i++) {
        c = msg[i] - ((caps && msg[i] > 0x60 && msg[i] < 0x7b) ? 0x20 : 0);
        if (c == '\n') {
            max_total = max(total, max_total);
            total = 0;
        } else {
            int w = small_char_width[(int) c];
            switch (c) {
                case ' ':
                    total += 3;
                    break;
                default:
                    total += (w + 1);
                    break;
            }
        }
	}
	return max(total, max_total);
}

int small_text_height(const char *msg) {
    if (strlen(msg) == 0)
        return 0;
    
    int total = 1;
    for (int i = 0; i < strlen(msg); i++) {
        if (msg[i] == '\n')
            total ++;
    }
    return total;
}