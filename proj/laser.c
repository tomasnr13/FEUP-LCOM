#include "laser.h"

Laser *create_ls(int16_t x, int16_t y, int16_t speed, int damage, bool rebel) {
  Laser *lsr = (Laser *) malloc(sizeof(Laser));
  if (lsr == NULL)
    return NULL;
  lsr->damage = damage;
  lsr->x = x;
  lsr->y = y;
  lsr->speed = speed;
  if (rebel) {
    lsr->shot = create_sprite(sp_shot, x, y, 0, speed);
  }
  else {
    lsr->shot = create_sprite(en_shot, x, y, 0, speed);
  }

  return lsr;
}

void destroy_ls(Laser *ls) {
  destroy_sprite(ls->shot);
  free(ls);
}

void print_ls(Laser *ls) {
  print_sprite(ls->shot);
}

void changepos_ls(Laser *ls, int16_t x, int16_t y) {
  ls->y = y;
  ls->x = x;
  changepos(ls->shot, x, y);
}

bool move_ls(Laser *ls) {
  if (ls->y - ls->speed < 0) {
    destroy_ls(ls);
    return false;
  }
  changepos_ls(ls, ls->x, ls->y - ls->speed);
  return true;
}
