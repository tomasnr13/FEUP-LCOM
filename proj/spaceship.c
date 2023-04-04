#include "spaceship.h"

Spaceship *create_spaceship(int16_t x, int16_t xspeed) {
  Spaceship *sps = (Spaceship *) malloc(sizeof(Spaceship));
  if (sps == NULL)
    return NULL;
  sps->life = 100;
  sps->points = 0;
  sps->x = x;
  sps->speed = xspeed;
  sps->powerup = false;
  sps->sp = create_sprite(xwing, x, 750, xspeed, 0);
  SpShot *spshot = (SpShot *) malloc(sizeof(SpShot));
  sps->spshot = spshot;
  return sps;
}

void destroy_sp(Spaceship *sp) {
  destroy_sprite(sp->sp);
  free(sp);
  sp = NULL;
}

void print_sp(Spaceship *sp) {
  print_sprite(sp->sp);
}

void changepos_sp(Spaceship *sp, int16_t x) {
  if (x + sp->sp->width > gethres()) {
    sp->x = 0;
  }
  else if (x < 0) {
    sp->x = gethres() - sp->sp->width;
  }
  else {
    sp->x = x;
  }
  changepos(sp->sp, sp->x, 750);
}

void changespeed_sp(Spaceship *sp, int16_t xspeed) {
  sp->speed = xspeed;
  changespeed(sp->sp, xspeed, 0);
}

void changepos_kbp(Spaceship *sp, uint16_t counter) {
  if (sp->speed >= 0) {
    changepos_sp(sp, sp->x + (sp->speed));
  }
  else {
    if (counter % (-(sp->speed)) == 0) {
      changepos_sp(sp, (sp->x)++);
    }
  }
}

void changepos_kbn(Spaceship *sp, uint16_t counter) {
  if (sp->speed >= 0) {
    changepos_sp(sp, sp->x - (sp->speed));
  }
  else {
    if (counter % (-(sp->speed)) == 0) {
      changepos_sp(sp, (sp->x)--);
    }
  }
}




Defense *create_defense(int16_t x) {
  Defense *df = (Defense *) malloc(sizeof(Defense));
  if (df == NULL)
    return NULL;
  df->life = 4;
  df->x = x;
  df->sp1 = create_sprite(def1, x, 670, 0, 0);
  df->sp2 = create_sprite(def2, x, 670, 0, 0);
  df->sp3 = create_sprite(def3, x, 670, 0, 0);
  df->sp4 = create_sprite(def4, x, 670, 0, 0);
  return df;
}

void print_defense(Defense *d) {
  if (d->life == 4) {
    print_sprite(d->sp1);
  }
  else if (d->life == 3) {
    print_sprite(d->sp2);
  }
  else if (d->life == 2) {
    print_sprite(d->sp3);
  }
  else if (d->life == 1) {
    print_sprite(d->sp4);
  }
}

Defenses *create_defenses(int16_t x) {
  Defenses *dfs = (Defenses *) malloc(sizeof(Defenses));
  for (int i = 0; i < 4; i++) {
    dfs->def[i] = create_defense(i * 300 + x);
  }
  return dfs;
}

void print_defenses(Defenses *d) {
  for (int i = 0; i < 4; i++) {
    print_defense(d->def[i]);
  }
}



/*void sp_shoot(Spaceship *sp) {
  sp->ls = create_ls(sp->x + 59, 730, 50, 10, true);
}*/

void sp_shoot(Spaceship* sp) {
  SpShot *spshot = (SpShot *) malloc(sizeof(SpShot));
  spshot->damage = 10;
  spshot->x = sp->x + 59;
  spshot->y = 730;
  spshot->speed = 50;
  spshot->shot = create_sprite(sp_shot, spshot->x,spshot->y,0,spshot->speed);
  sp->spshot = spshot;
}


void destroy_spshot(SpShot* spshot) {
  destroy_sprite(spshot->shot);
  free(spshot);
}

void print_spshot(SpShot* spshot) {
  print_sprite(spshot->shot);
}

void changepos_spshot(SpShot *spshot, int16_t x, int16_t y) {
  spshot->y = y;
  spshot->x = x;
  changepos(spshot->shot, x, y);
}

bool move_spshot(SpShot *spshot) {
  if (spshot->y - spshot->speed < 0) {
    destroy_spshot(spshot);
    return false;
  }
  changepos_spshot(spshot, spshot->x, spshot->y - spshot->speed);
  return true;
}
