#include "EventMachine.h"


#include <stdint.h>


static STATES curr_state = INIT;

struct mouse_ev   mouse_event;



uint8_t x_percorrido , y_percorrido;


static bool lb_pressed = false , rb_pressed  = false , mb_pressed = false;


struct mouse_ev * 	mouse_detect_event_v2 (struct packet *pp)
{

    mouse_event.delta_x = pp->delta_x;

    mouse_event.delta_y = pp->delta_y;


    /*
    TEMOS 5 POSSÍVEIS EVENTOS DO MOUSE:


        1.LB_pressed - quando lb_pressed é falso e pp->lb = true;
        2.LB_RELEASED - quando lb_pressed é true e pp->lb = false;
        3.RB_pressed - quando rb_pressed é false e pp->rb = true;
        4.RB_RELEASED - quando rb_pressed é true e pp->rb = false;
        5Quando mb é pressed ou released mouse_event = BUTTON_EV
        6.QUALQUER OUTRO TIPO DE AÇÃO SIGNIFICA MOUSE_EVENT = MOUSE_MOV

    */

    if(!rb_pressed && !pp->rb && !mb_pressed && !pp->mb &&  lb_pressed && !pp->lb)
    {
        mouse_event.type = LB_RELEASED;
        lb_pressed = false;
    }

    else if(!rb_pressed && !pp->rb && !mb_pressed && !pp->mb &&  !lb_pressed && pp->lb)
    {
        mouse_event.type = LB_PRESSED;
        lb_pressed = true;
    }


    else if(rb_pressed && !pp->rb && !mb_pressed && !pp->mb &&  !lb_pressed && !pp->lb)
    {
        mouse_event.type = RB_RELEASED;
        rb_pressed = false;
    }

    else if(!rb_pressed && pp->rb && !mb_pressed && !pp->mb &&  !lb_pressed && !pp->lb)
    {
        mouse_event.type = RB_PRESSED;
        rb_pressed = true;
    }

    else if((!mb_pressed && pp->mb) || (mb_pressed && !pp->mb))
    {
        mouse_event.type = BUTTON_EV;

        if(!mb_pressed) mb_pressed = true;

        else if(mb_pressed) mb_pressed = false;
    }


    else mouse_event.type = MOUSE_MOV;

    return &mouse_event;

}

int handle_menu(struct packet *pp)
{

    struct mouse_ev * mouse_event = mouser_detect_event_v2(pp);

    //mouse event pode ser
    //LB_PRESSED
    //LB_RELEASED
    //RB_PRESSED
    //RB_RELEASED
    //BUTTON_EV
    //MOUSE_MOV

    //Retorna 1 se o user clicou na opção new game
    //Retorn 2 se o user clicou na opção help
    //Retorn 3 se o user clicou na opção quit



}


uint8_t handle_draw(uint8_t xlen ,  uint8_t tolerance ,  struct packet *pp)
{

    struct mouse_ev * mouse_event = mouse_detect_event_v2(pp);

    //DE ACORDO COM O FACTO SE O USER JÁ DESENHOU OU NÃO O V INVERTIDO A FUNÇÃO PODE RETURNAR 1 OU 0;


    



    switch(curr_state)
    {
        case INIT:

            if(mouse_event->type == LB_PRESSED)
            {
                curr_state = DRAWING_UP;
            }

            x_percorrido = 0;
            y_percorrido = 0;


            break;

        case DRAWING_UP:

            if(mouse_event->type == LB_RELEASED)
            {
                if(x_percorrido>= xlen &&  ((mouse_event->delta_x ==0) || (mouse_event->delta_x != 0 && abs(mouse_event->delta_y/mouse_event->delta_x) > 1)))
                {  
                    curr_state = VERTEX;
                }

                else curr_state = INIT;
            }

            else if(mouse_event->type == MOUSE_MOV)
            {
                if((mouse_event->delta_x < 0) && (abs(mouse_event->delta_x) >= tolerance))
                {
                    curr_state = INIT;

                }

                else if((mouse_event->delta_y < 0) && (abs(mouse_event->delta_y) >= tolerance))
                {
                    curr_state = INIT;
                }



                else{
                    x_percorrido += mouse_event->delta_x;

                    y_percorrido += mouse_event->delta_y;

                }
                    




            }

            else    curr_state = INIT;
        
            break;
        case DRAWING_DOWN:


            if(mouse_event->type == RB_RELEASED)
            {
                if((x_percorrido >= xlen) && ((mouse_event->delta_x == 0) || (abs(mouse_event->delta_y / mouse_event->delta_x)) > 1))
                {
                    return 0;
                }

                else curr_state = INIT;
            }

            else if(mouse_event->type == MOUSE_MOV)
            {
                if((mouse_event->delta_x < 0) && (abs(mouse_event->delta_x) >= tolerance ))
                {

                    curr_state = INIT;

                }

                
                else if((mouse_event->delta_y < 0 ) && (abs(mouse_event->delta_y) >= tolerance ))
                {
                    curr_state = INIT;
                }

                else{

                    x_percorrido += mouse_event->delta_x;

                    y_percorrido += mouse_event->delta_y;

                }



            }

            else if(mouse_event->type == LB_PRESSED)
                curr_state = DRAWING_UP;

            
            
            else

                curr_state = INIT;

            break;

        case VERTEX:

            x_percorrido = 0;
            y_percorrido = 0;

            if(mouse_event->type == RB_PRESSED)
            {
                curr_state = DRAWING_DOWN;
            }

            else if(mouse_event->type == LB_PRESSED)
            {
                curr_state = DRAWING_UP;
            }

            else if((mouse_event->type == MOUSE_MOV) && (abs(mouse_event->delta_x) <= tolerance) && (abs(mouse_event->delta_y) <= tolerance))
                curr_state = VERTEX;

            else
                curr_state = INIT;




            break;

        default:


            break;
    }

    //SE O OBJETO AINDA NÃO FOI DESENHADO 

    return -1;


}


