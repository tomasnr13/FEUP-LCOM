#ifndef __GAME_H
# define __GAME_H

//INCLUDE DEVICES
#include "Keyboard.h"
#include "graphic.h"
#include "Sprite.h"
#include "mouse.h"
#include "rtc.h"

//include xpm's
//#include "xwing.h"
//#include "tiefighter.h"
//#include "deathstar.h"
#include "background.h"
#include "numbers.h"


//INCLUDE CONSTS
#include "graphic_consts.h"
#include "i8254.h"
#include "i8042.h"
#include "PS2.h"

//INCLUDE MEMBERS
#include "spaceship.h"
#include "enemies.h"




//hook id's
extern int hook_id_kbd;

extern int hook_id_timer;

extern int hook_id_rtc;

//Variaveis timer
uint32_t timercounter;

//variaveis keyboard
extern uint32_t scancode;

extern bool make, ValidScanCode;

//variaveis mouse
extern uint8_t bytes[2];

extern int counter_sys;

extern uint8_t size;

//variaveis grafica
extern int bytes_per_pixel;

extern int h_res, v_res;

extern void *video_mem; //FRAME BUFFER VIDEO MEM ENDERE�O

static void *video_mem2;

extern vbe_mode_info_t vmi_p;


extern Sprite* zero;
extern Sprite* um;
extern Sprite* dois;
extern Sprite* tres;
extern Sprite* quatro;
extern Sprite* cinco;
extern Sprite* seis;
extern Sprite* sete;
extern Sprite* oito;
extern Sprite* nove;


extern int arr[5];

extern int score;



enum Game_State { INIT, MENU, POWERUP, PAUSE_MENU, END };

int video_rectangle(uint16_t mode, uint16_t x, uint16_t y,
                    uint16_t width, uint16_t height, uint32_t color);

int video_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

int video_move_sprite(Sprite *sp, uint8_t fr_rate);

void game(Spaceship *sp, Enemies *en, Defenses *def, uint8_t fr_rate);

void print_score(int x , int y , int score);

int getScore();

void create_score_sprites(int x , int y);


void button_pressed();

void collision_shot(Spaceship *sp , Enemies *en);

void collision_en_shot(Spaceship *sp  , Defenses *def, Enemies *en);

bool check(Sprite* sp , uint32_t color);

#endif
