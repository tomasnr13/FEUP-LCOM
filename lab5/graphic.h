#ifndef __GRAPHIC_H
#  define __GRAPHIC_H

#include <lcom/lcf.h>



int set_mode_graphic(uint16_t mode);

int map_vram(uint16_t mode);

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int color_pixel(uint16_t x, uint16_t y, uint32_t color);

//int(changePixelColor)(uint16_t x, uint16_t y, uint32_t color);

//int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

//void get_next_byte(uint32_t *var);

//void get_rect_dimensions(uint8_t nr, uint16_t *width, uint16_t *height);

//uint32_t index_mode(uint8_t row, uint8_t col, uint8_t no_rectangles, uint8_t step, uint32_t first);

//uint32_t get_color_direct(uint8_t row, uint8_t col, uint8_t step, uint32_t first);

int print_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

//uint16_t getpixwidth();

//uint16_t getpixheight();

//int getnext(uint16_t *xi, uint16_t *yi, uint16_t xf, uint16_t yf, int16_t speed, uint16_t counter);

int gethres();

int getvres();

#endif
