#include <stdlib.h>
#include <lcom/lcf.h>

#include "graphic.h"
#include "Sprite.h"
//#include "Laser.h"


typedef struct {
  Sprite *shot;
  int damage;
  int16_t x, y;
  int16_t speed;
} SpShot;

typedef struct {
  Sprite *sp;
  int life;
  int points;
  int16_t x;
  bool powerup;
  int16_t speed;
  SpShot *spshot;
  //Laser *ls;
} Spaceship;

typedef struct {
  Sprite *sp1;
  Sprite *sp2;
  Sprite *sp3;
  Sprite *sp4;
  int life;
  int16_t x;
} Defense;

typedef struct {
  Defense *def[4];
} Defenses;



Spaceship *create_spaceship(int16_t x, int16_t xspeed);

void destroy_sp(Spaceship *sp);

void print_sp(Spaceship *sp);

void changepos_sp(Spaceship *sp, int16_t x);

void changespeed_sp(Spaceship *sp, int16_t xspeed);

void changepos_kbp(Spaceship *sp, uint16_t counter);

void changepos_kbn(Spaceship *sp, uint16_t counter);

void sp_shoot(Spaceship *sp);



Defense *create_defense(int16_t x);

void print_defense(Defense *d);

Defenses *create_defenses(int16_t x);

void print_defenses(Defenses * d);





void destroy_spshot(SpShot *ls);

void print_spshot(SpShot *ls);

void changepos_spshot(SpShot *ls, int16_t x, int16_t y);

bool move_spshot(SpShot *ls);
