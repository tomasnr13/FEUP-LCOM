#include "Sprite.h"

void changepos(Sprite *sp, int16_t x, int16_t y) {
  sp->x = x;
  sp->y = y;
}

void changespeed(Sprite *sp, int16_t xspeed, int16_t yspeed) {
  sp->xspeed = xspeed;
  sp->yspeed = yspeed;
}

void print_sprite(Sprite *sp) {
  uint8_t *base2 = (sp->base);
  for (int16_t j = (sp->y); j < ((sp->y) + (sp->height)); j++) {
    for (int16_t i = (sp->x); i < ((sp->x) + (sp->width)); i++) {
      uint32_t r = *(base2 + 2);
      uint32_t g = *(base2 + 1);
      uint32_t b = *(base2);

      uint32_t color = ((r << 16) & 0xFF0000) | ((g << 8) & 0xFF00) | (b & 0xFF);
      base2 += 4;
      if (xpm_transparency_color(XPM_8_8_8) == color) {
        continue;
      }
      color_pixel(i, j, color);
    }
  }
}

Sprite *create_sprite(xpm_map_t xpm, int16_t x, int16_t y, int16_t xspeed, int16_t yspeed) {

    //allocate space for the "object"
    Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
    if( sp == NULL )
        return NULL;

    xpm_image_t img;

    // read the sprite pixmap
    sp->base = xpm_load(xpm, XPM_8_8_8_8, &img);
    if( sp->base == NULL ) {
        free(sp);
        return NULL;
    }
    sp->width = img.width; sp->height=img.height;

    sp->x = x ; sp->y = y; sp->xspeed =xspeed ; sp->yspeed=yspeed;

    return sp;
}

void destroy_sprite(Sprite *sp)
{
    if( sp == NULL )
        return;
    if( sp ->base )
        free(sp->base);
        free(sp);
    sp = NULL;
}

int getnextsppos(Sprite *sp, uint16_t counter) {
  if (sp->xspeed >= 0) {
    changepos(sp, sp->x + (sp->xspeed), sp->y);
  }
  else {
    if (counter % (-(sp->xspeed)) == 0) {
      changepos(sp, (sp->x)++, sp->y);
    }
  }
  return 0;
}

int getnextspneg(Sprite *sp, uint16_t counter) {
  if (sp->xspeed >= 0) {
    changepos(sp, sp->x - (sp->xspeed), sp->y);
  }
  else {
    if (counter % (-(sp->xspeed)) == 0) {
      changepos(sp, (sp->x)--, sp->y);
    }
  }
  return 0;
}

void move_cursor(Sprite *cursor, int xstep, int ystep) {

  int vres = getvres();
  int hres = gethres();

  if (xstep > 0) {
    if (cursor->x + xstep > (int) hres - cursor->width)
      cursor->x = (int) hres - cursor->width;
    else
      cursor->x += xstep;
  }
  else if (xstep < 0) {
    if (cursor->x + xstep < 0)
      cursor->x = 0;
    else
      cursor->x += xstep;
  }
  if (ystep < 0) {
    if (cursor->y + cursor->height - ystep > (int) vres)
      cursor->y = (int) vres - cursor->height;
    else
      cursor->y -= ystep;
  }
  else if (ystep > 0) {
    if (cursor->y - ystep < 0)
      cursor->y = 0;
    else
      cursor->y -= ystep;
  }
}

