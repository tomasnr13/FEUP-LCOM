#include <lcom/lcf.h>
#include <stdlib.h>

#include "graphic.h"
#include "Sprite.h"

static bool move_side;

typedef struct {
  Sprite *sp;
  int16_t speed;
  int16_t x;
  int life;
  bool openfinal;
} Deathstar;

typedef struct {
  Sprite *sp;
  int16_t speed;
  int16_t x, y;
  bool life;
} Tiefighter;

typedef struct {
  Sprite *shot;
  int damage;
  int16_t x, y;
  int16_t speed;
} EnShot;

/*typedef struct {
  Tiefighter  ***tief;
  Tiefighter *tief[5][10];
  Deathstar *ds;
  bool final;
  int nr_enemies;
  int nr_lines, en_per_line;
  int xi, yi;
  int16_t diff;
  int16_t tf_width, tf_height;
  int16_t ds_width, ds_height;
  int16_t speed;
} Enemies;*/

typedef struct {
  Tiefighter *tief[5][10];
  Deathstar *ds;
  bool final;
  int nr_enemies;
  int curr_y;
  uint16_t hdiff,vdiff;
  uint16_t yjump;
  int16_t speed;
  EnShot *ens;
} Enemies;

//Enemies *create_enemies(int16_t xi, int16_t yi, int16_t speed, int nen, int16_t diff);
//void changepos_en(Enemies *en, int16_t x, int16_t y);
//void changepos_kb(Enemies *en, uint16_t counter);

Tiefighter *create_tief(int16_t xi, int16_t yi, int16_t speed);

void print_tief(Tiefighter *tf);

void changepos_tf(Tiefighter *tf, int16_t x, int16_t y);

void changespeed_tf(Tiefighter *tf, int16_t xspeed);



Deathstar *create_ds(int16_t xi, int16_t speed);

void print_ds(Deathstar *ds);

void changepos_ds(Deathstar *ds);

void changespeed_ds(Deathstar *ds, int16_t xspeed);



Enemies *create_enemies(int16_t speed);

void print_enemies(Enemies *en);

void movedown_en(Enemies *en);

bool changepos_en(Enemies *en, int16_t diff);

bool changepos_kb(Enemies *en, uint16_t counter);

void changespeed_en(Enemies *en, int16_t xspeed);

void new_curr_y(Enemies *en);





void en_shoot(Enemies *en);

void tf_shoot(Enemies *en, Tiefighter *t);

void destroy_enshot(EnShot *enshot);

void print_enshot(EnShot *enshot);

void changepos_enshot(EnShot *enshot, int16_t x, int16_t y);

bool move_enshot(EnShot *enshot);




