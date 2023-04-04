// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you

#include "Menu.h"


//Game_State GameState = MENU;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/*static int print_usage() {
  printf("Usage: <mode - hex>\n");

  return 0;
}*/

int(proj_main_loop)(int argc, char *argv[]) {
  /* 
   * Substitute the code below by your own
   */
  if (map_vram(0x14c) != 0) {
    vg_exit();
    printf("[ERROR] Could not map the video RAM \n");

    return 1;
  }

  if (set_mode_graphic(0x14c) != 0) {
    vg_exit();
    printf("[ERROR] Could not set the video card to graphic mode \n");

    return 1;
  }



  //Spaceship *sp = create_spaceship(0, 20);
  //Tiefighter *t = create_tief(0, 0, 20);
  /*Enemies *en = create_enemies(20);
  en_shoot(en);
  print_enshot(en->ens);
  double_buff();
  sleep(1);*/
  /*tf_shoot(en,t);
  print_tief(t);
  print_enshot(en->ens);
  double_buff();
  sleep(1);

  int num = 0;
  for (int i= 0; i < 40; i++) {
    if (!move_enshot(en->ens)) {
      num++;
      changepos_tf(t, num*100,t->y);
      tf_shoot(en,t);
    }
    print_tief(t);
    print_enshot(en->ens);
    double_buff();
    sleep(1);
  }*/

  
  load_Menu(30);

  vg_exit();
  
  /*while (GameState != END) {

    switch (GameState) {
      case INIT:
        load_game();
        break;

      case MENU:
        break;

      case PAUSE_MENU:
        break;

      case POWERUP:

        break;

      case END:

        break;
    }
  }*/

  return 0;
}
