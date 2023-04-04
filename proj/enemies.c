#include "enemies.h"



Tiefighter *create_tief(int16_t xi, int16_t yi, int16_t speed) {
  Tiefighter *tf = (Tiefighter *) malloc(sizeof(Tiefighter));
  if (tf == NULL)
    return NULL;
  tf->life = true;
  tf->x = xi;
  tf->y = yi;
  tf->speed = speed;
  tf->sp = create_sprite(tiefighter, xi, yi, speed, 0);
  return tf;
}

void print_tief(Tiefighter *tf) {
  print_sprite(tf->sp);
}

void changepos_tf(Tiefighter *tf, int16_t x, int16_t y) {
  tf->x = x;
  tf->y = y;
  changepos(tf->sp, x, y);
}

void changespeed_tf(Tiefighter *tf, int16_t xspeed) {
  tf->speed = xspeed;
  changespeed(tf->sp, xspeed, 0);
}

Deathstar *create_ds(int16_t xi, int16_t speed) {
  Deathstar *ds = (Deathstar *) malloc(sizeof(Deathstar));
  if (ds == NULL)
    return NULL;
  ds->life = 200;
  ds->x = xi;
  ds->speed = speed;
  ds->sp = create_sprite(deathstar, xi, 0, speed, 0);
  return ds;
}

void print_ds(Deathstar *ds) {
  print_sprite(ds->sp);
}

void changepos_ds(Deathstar *ds) {
  if(ds->speed > 0 && ds->x + ds->sp->width + ds->speed>gethres()) ds->speed *=-1;
  if(ds->speed < 0 && ds->x + ds->speed<0) ds->speed *=-1;
  if(ds->x <= 0) ds->x = 0;
  if(ds->x >= gethres()) ds->x = gethres();
  ds->x += ds->speed;
  changepos(ds->sp, ds->x, 0);
}

void changespeed_ds(Deathstar *ds, int16_t xspeed) {
  ds->speed = xspeed;
  changespeed(ds->sp, xspeed, 0);
}

Enemies *create_enemies(int16_t speed) {
  Enemies *en = (Enemies *) malloc(sizeof(Enemies));

  move_side = true;

  en->final = false;
  en->nr_enemies = 50;
  en->speed = speed;
  en->hdiff = 40;
  en->vdiff = 60;
  en->yjump = 10;
  en->curr_y = 5 * (38 + en->vdiff) - en->vdiff;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      Tiefighter *t = create_tief(j * (46 + en->hdiff), i * (38 + en->vdiff), 10);
      en->tief[i][j] = t;
    }
  }

  create_ds(300 ,  10);
  en->ens = NULL;
  return en;
}

void print_enemies(Enemies *en) {
  if (en->final) {
    print_ds(en->ds);
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (en->tief[i][j]->life) {
        print_tief(en->tief[i][j]);
      }
    }
  }
}

void movedown_en(Enemies *en) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      changepos_tf(en->tief[i][j], en->tief[i][j]->x, en->tief[i][j]->y + en->yjump);
    }
  }
}

void new_curr_y(Enemies *en) {
  for (int i = 4; i > 0; i--) {
    for (int j = 0; j < 10; j++) {
      if (en->tief[i][j]->life) {
        return;
      }
    }
    en->curr_y -= en->yjump;
  }
}

bool changepos_en(Enemies *en, int16_t diff) {
  bool md = false;
  ;
  new_curr_y(en);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      //if ((move_side & (en->tief[i][9 - j]->x + diff + 46 > gethres()) & (en->tief[i][9-j]->life)) || (!move_side & (en->tief[i][j]->x - diff < 0)) & (en->tief[i][j]->life)) {
      if ((move_side & (en->tief[i][9 - j]->x + diff + 46 > gethres())) || (!move_side & (en->tief[i][j]->x - diff < 0))) {
        md = true;
      }
      else {
        break;
      }
    }
    if (md) {
      if (en->curr_y + 38 >= 690) {
        //CHANGE!!
        return false;
      }
      else {
        movedown_en(en);
        en->curr_y += en->yjump;
        move_side = !move_side;
        break;
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (move_side) {
        changepos_tf(en->tief[i][j], en->tief[i][j]->x + diff, en->tief[i][j]->y);
      }
      else {
        changepos_tf(en->tief[i][j], en->tief[i][j]->x - diff, en->tief[i][j]->y);
      }
    }
  }

  return true;
}

bool changepos_kb(Enemies *en, uint16_t counter) {
  if (en->speed >= 0) {
    return changepos_en(en, en->speed);
  }
  else {
    if (counter % (-(en->speed)) == 0) {
      return changepos_en(en, 1);
    }
  }

  return true;

}



void changespeed_en(Enemies *en, int16_t xspeed) {
  en->speed = xspeed;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      changespeed_tf(en->tief[i][j], xspeed);
    }
  }
}




void en_shoot(Enemies *en) {
  bool shot_line = true;
  int tshot_index=0;
  Tiefighter *tshot[10];
  for (int col = 0; col < 10; col++) {
    for (int line1 = 0; line1 < 5; line1++) {
      if (!en->tief[line1][col]->life) {
        continue;
      }
      else {
        

        for (int line2 = line1 + 1; line2 < 5; line2++) {
          if (en->tief[line2][col]->life) {
            shot_line = false;
            break;
          }
        }
        if (shot_line) {
          tshot[tshot_index] = en->tief[line1][col];
          tshot_index++;
          break; //sair do ciclo de linhas (a menor linhe possivel ja foi encontrada) e ir para nova coluna
        }
        shot_line = true;

      }
    }
  }

  if (tshot_index > 0) {
    tshot_index--;
  }

  time_t t;
  srand((unsigned) time(&t));
  tf_shoot(en, tshot[tshot_index ==0 ? 0:rand() % tshot_index]);
}

void tf_shoot(Enemies *en, Tiefighter *t) {
  EnShot *enshot = (EnShot *) malloc(sizeof(EnShot));
  enshot->damage = 1;
  enshot->x = t->x + 19;
  enshot->y = t->y + 40;
  enshot->speed = 30;
  enshot->shot = create_sprite(en_shot, enshot->x, enshot->y, 0, enshot->speed);
  en->ens = enshot;
}

void destroy_enshot(EnShot *enshot) {
  destroy_sprite(enshot->shot);
  free(enshot);
}

void print_enshot(EnShot *enshot) {
  print_sprite(enshot->shot);
}

void changepos_enshot(EnShot *enshot, int16_t x, int16_t y) {
  enshot->y = y;
  enshot->x = x;
  changepos(enshot->shot, x, y);
}

bool move_enshot(EnShot *enshot) {
  if (enshot->y + enshot->speed +40> getvres()) {
    destroy_enshot(enshot);
    return false;
  }
  changepos_enshot(enshot, enshot->x, enshot->y + enshot->speed);
  return true;
}
