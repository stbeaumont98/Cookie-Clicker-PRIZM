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

/*Note it is up to the caller to ensure that alpha is in range of 1-31
 * For a value of 32 or greater just don't draw the image
 * For a value of 0 use a plain mask function that does not take into account alpha
 * Also make sure width is a multiple of two*/
void copy_sprite_masked_alpha(const void *datar, unsigned x, unsigned y, unsigned width, unsigned height, unsigned maskcolor, unsigned alpha){
    unsigned *data = (unsigned *) datar;
    unsigned short *v = (unsigned short *) GetVRAMAddress();
    unsigned *VRAM, w, alphai;
    width /= 2;
    v += 384 * y + x;
    VRAM = (unsigned *) v;
    alphai = 32 - alpha;
    maskcolor |= maskcolor << 16;/*Note I have decided to do a minor tradeoff for speed. Make sure your alpha pixels are multiple of two*/
    while(height--) {
        w = width;
        while(w--) {
            unsigned color1 = *data++;
            if(color1 != maskcolor) {
                /*Note this is based on the source code of Fblend's function fblend_rect_trans_16*/
                unsigned rbg_source, grb_source, temp1;
                /* Split up components to allow us to do operations on all of them at the same time */
                rbg_source = *VRAM & 0xF81F07E0,
                grb_source = *VRAM & 0x07E0F81F;

                /* Multiply the source by the factor */
                rbg_source = ((rbg_source >> 5) * alpha) & 0xF81F07E0;
                grb_source = ((grb_source * alpha) >> 5) & 0x07E0F81F;

                /* Split up RGB -> R-B and G */
                temp1 = color1 & 0x7E0F81F;
                color1 &= 0xF81F07E0;

                /* Multiply the source by the factor */
                color1 = ((((color1 >> 5) * alphai) & 0xF81F07E0) + rbg_source) & 0xF81F07E0;
                temp1  = ((((temp1 * alphai) >> 5)  & 0x07E0F81F) + grb_source) & 0x07E0F81F;

                color1 |= temp1;
                *VRAM++ = color1;
            }else
                ++VRAM;
        }
        VRAM += (384 / 2) - width;
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

void copy_sprite_nbit(const unsigned char* data, unsigned x, unsigned y, unsigned w1, unsigned h1, unsigned w2, unsigned h2, color_t* palette) {
    color_t* VRAM = (color_t*) GetVRAMAddress();
    VRAM += (LCD_WIDTH_PX * y + x);
	unsigned x_ratio = ((w1 << 16) / w2) + 1;
	unsigned y_ratio = ((h1 << 16) / h2) + 1;
	unsigned x2, y2;
    int offset = 0;
    unsigned char buf;
    for(int i = 0; i < h2; ++i) {
        int availbits = 0;
        for(int j = 0; j < w2; ++j) {
			x2 = ((j * x_ratio) >> 16);
			y2 = ((i * y_ratio) >> 16);
            if (!availbits) {
                buf = data[offset++];
                availbits = 8;
            }
            color_t this = ((color_t) buf >> 4);
            color_t color = palette[this];
            if (i >= 0 && i <= 216 && j >= 0 && j <= 384 && color != COLOR_RED)
                *VRAM = color;
            VRAM++;
            buf <<= 4;
            availbits -= 4;
        }
        VRAM += (LCD_WIDTH_PX - w2);
    }
} 

// normal font

void disp_string(unsigned x, unsigned y, const char* message, int color) {
    int l = strlen(message);
    int i;
    unsigned line = 0;
    int x_offset = 0;
    int y_offset = 0;
    for (i = 0; i < l; i++) {
        int w = char_width[(int) message[i]];
        int h = char_height[(int) message[i]];
        if (message[i] == '\n') {
            x_offset = 0;
            ++line;
        }
        else if (message[i] == '\t') {}
            //x_offset += 20;
        else {
            switch (message[i]) {
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
            copy_sprite_1bit(charmap[(int) message[i]], x + x_offset, y + y_offset + (line * 18), w, h, charmap_palette, color);
            x_offset += (message[i] == ' ') ? 5 : (w + (message[i] == 'Q' ? -1 : 1) + (message[i] == '(' || message[i] == ')' ? 1 : 0));
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
            total ++;
    }
    return total;
}

// small font

void small_disp_string(unsigned x, unsigned y, const char* message, int color) {
    int l = strlen(message);
    int i;
    unsigned line = 0;
    int x_offset = 0;
    int y_offset = 0;
    for (i = 0; i < l; i++) {
        int w = small_char_width[(int) message[i]];
        int h = small_char_height[(int) message[i]];
        if (message[i] == '\n') {
            x_offset = 0;
            ++line;
        }
        else if (message[i] == '\t') {}
            //x_offset += 20;
        else {
            switch (message[i]) {
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
            copy_sprite_1bit(small_charmap[(int) message[i]], x + x_offset, y + y_offset + (line * 9), w, h, charmap_palette, color);
            x_offset += (message[i] == ' ') ? 3 : (w + 1 + (message[i] == '(' || message[i] == ')' ? 1 : 0));
        }
        if (x + x_offset >= 384) {
            x_offset = 0;
            ++line;
        }
        if (y + y_offset + (line * h) >= 216)
            break;
    }
}

int small_text_width(const char *msg) {
    int total = 0, max_total = 0;
	for (int i = 0; i < strlen(msg); i++) {
        if (msg[i] == '\n') {
            max_total = max(total, max_total);
            total = 0;
        } else {
            int w = small_char_width[(int) msg[i]];
            switch (msg[i]) {
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