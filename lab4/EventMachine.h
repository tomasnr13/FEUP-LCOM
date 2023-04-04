#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>


uint8_t handle_draw(uint8_t xlen ,  uint8_t tolerance ,  struct packet *pp);

typedef enum{INIT , DRAWING_UP , VERTEX ,  DRAWING_DOWN} STATES;


struct mouse_ev * 	mouse_detect_event_v2 (struct packet *pp);



