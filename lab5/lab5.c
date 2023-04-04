// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "graphic.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (map_vram(mode) != 0) {
    printf("couldnt map vram!\n");
    return 1;
  }
  if (set_mode_graphic(mode) != 0) {
    printf("couldnt set mode!\n");
    return 1;
  }
  sleep(delay);
  vg_exit();
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  if (map_vram(mode) != 0) {
    printf("couldnt map vram!\n");
    return 1;
  }
  if (set_mode_graphic(mode) != 0) {
    printf("couldnt set mode!\n");
    return 1;
  }
  for (uint16_t i = y; i < y + height; i++) {
    if (vg_draw_hline(x, i, width, color) != 0) {
      printf("draw_hline failed!\n");
      return 1;
    }
  }
  sleep(3);
  vg_exit();
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if (map_vram(0x105) != 0) {
    printf("couldnt map vram!\n");
    return 1;
  }
  if (set_mode_graphic(0x105) != 0) {
    printf("couldnt set mode!\n");
    return 1;
  }
  if (print_xpm(xpm, x, y) != 0) {
    printf("print failed!\n");
    return 1;
  }
  sleep(3);
  vg_exit();
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
