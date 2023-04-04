#include <lcom/lcf.h>

#include <stdlib.h>

#include "Sprite.h"
#include "graphic.h"

typedef struct {
  Sprite *shot;
  int damage;
  int16_t x, y;
  int16_t speed;
} Laser;

Laser *create_ls(int16_t x, int16_t y, int16_t speed, int damage, bool rebel);

void destroy_ls(Laser *ls);

void print_ls(Laser *ls);

void changepos_ls(Laser *ls, int16_t x, int16_t y);

bool move_ls(Laser *ls);
