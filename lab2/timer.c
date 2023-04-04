#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"


uint32_t counter = 0;

static int hook_id;



int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

    //Funcao que permite mudar  a frequência com que o timer 0 gera interrupcoes , apesar que deve ser uma funçao geral
    // to test your code to configure the specified timer (one of 0, 1 and 2) to generate a time base with a given frequency in Hz.

    //1 - >Escrever a control word do timer para o control reg ->
    //-> Lendo se primeiro a configuração do timer através de timer_get_conf()
    //-> nao mudar os primeiros 4 bits ou seja , o operating mode e o BCDxBin

    if(timer < 0 || timer > 2) 
    {
        printf("[ERRO] timer index out of range\n");
        return 1;
    }



    uint8_t configuration , final_conf = 0;

    if(timer_get_conf(timer, &configuration) != 0)
    {
        printf("[ERROR] could not get the configuration of the timer from the timer_get_conf()\n");
        return 1;
    }

    uint8_t Init_4_bit  = configuration & 0xF;

    switch(timer)
    {
        case 0:

            final_conf = TIMER_SEL0 | TIMER_LSB_MSB | Init_4_bit;
            break;

        case 1:
            final_conf = TIMER_SEL1 | TIMER_LSB_MSB | Init_4_bit;
            break;

        case 2:
            final_conf = TIMER_SEL2 | TIMER_LSB_MSB | Init_4_bit;
            break;

        default:
            break;
    }


    if(sys_outb(TIMER_CTRL , final_conf) != OK)
    {
        printf("[ERROR] Sys_outb failed , could not write the control word\n");
        return 1;
    }

    //Econtrar uma time base para a frequência que desejamos , por exemplo que se quissemos 1 hz , time base = TIMER_FREQ / 1 , assim teriamos 1 interrupcao por segundo;

    uint16_t time_base = TIMER_FREQ / freq;

    uint8_t LSB , MSB;

    util_get_LSB(time_base , &LSB);
    util_get_MSB(time_base , &MSB);


    switch(timer)  //DAR LOAD DO VALOR PARA O TIMER REQUESITADO SEGUNDO LSB_followed_MSB
    {
        case 0:
            if((sys_outb(TIMER_0 , LSB) != OK )  || (sys_outb(TIMER_0 , MSB) != OK))
            {
                printf("[ERROR] Could not load the time base to the timer\n");
                return 1;
            } 

            break;
        
        case 1:
            if((sys_outb(TIMER_1 , LSB) != OK )  || (sys_outb(TIMER_1 , MSB) != OK))
            {
                printf("[ERROR] Could not load the time base to the timer\n");
                return 1;
            } 

            break;

        case 2:
            if((sys_outb(TIMER_2 , LSB) != OK )  || (sys_outb(TIMER_2 , MSB) != OK))
            {
                printf("[ERROR] Could not load the time base to the timer\n");
                return 1;
            } 

            break;

        default:
            break;
        
    }


    //if everything went as expected

    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {

    hook_id = *bit_no;

    if(sys_irqsetpolicy(TIMER0_IRQ ,  IRQ_REENABLE , &hook_id) != OK)
    {
        printf("[ERROR] Could not subscribe the timer interrupts\n");
        return 1;
    }

    return 0;
 
}

int (timer_unsubscribe_int)() {

    if(sys_irqrmpolicy(&hook_id) != OK)
    {
        printf("[ERROR] error in unsubscribe_int()\n");
        return 1;
    }

    return 0;

}

void (timer_int_handler)() {

    counter += 1;
    return;
  
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {


    if(timer  < 0 || timer  > 2)
    {
        printf("[ERROR] Timer index out of range\n");
        return 1;
    }

    //1 - > escrever o read back command
    //2 - > coloca lo no control register
    //3 - > tirar a conf dos ports dos timers

    uint8_t read_cmd = 0;

    switch(timer)
    {
        case 0:
            read_cmd |= TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0);
            break;
        case 1:
            read_cmd |= TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1);
            break;

        case 2:

            read_cmd |= TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(2);
            break;
        default:
            break;
    }


    //Escrever o read-back command no control register

    if(sys_outb(TIMER_CTRL , read_cmd) != OK)
    {
        printf("[ERROR] Could not write the read back command to the control register\n");
        return 1;
    }

    switch(timer)
    {
        case 0:
            if(util_sys_inb(TIMER_0 , st) != OK)
            {
                printf("[ERROR] Could not get the configuration of the timer\n");
                return 1;
            };
            break;
        case 1:
            if(util_sys_inb(TIMER_1 , st) != OK)
            {
                printf("[ERROR] Could not get the configuration of the timer\n");
                return 1;
            };
            break;
        case 2:
            if(util_sys_inb(TIMER_2 , st) != OK)
            {
                printf("[ERROR] Could not get the configuration of the timer\n");
                return 1;
            };
            break;
    }

    //if everything went as expected 

    return 0;

  
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {


    union timer_status_field_val val;

    switch(field)
    {
        case tsf_all:
            val.byte = st;
            break;

        case tsf_initial:
            
            if((st & TIMER_LSB_MSB) == TIMER_LSB_MSB) val.in_mode = MSB_after_LSB;
            
            else if((st & TIMER_LSB_MSB) == TIMER_LSB) val.in_mode = LSB_only;

            else if((st & TIMER_LSB_MSB) == TIMER_MSB) val.in_mode = MSB_only;

            else val.in_mode = INVAL_val;

            break;

        case tsf_mode:

            if((st & CHECK_MODE) == TIMER_MODE_0) val.count_mode = 0;

            else if((st & CHECK_MODE) == TIMER_MODE_1) val.count_mode = 1;

            else if((st & CHECK_MODE) == TIMER_RATE_GEN) val.count_mode = 2;

            else if((st & CHECK_MODE) == TIMER_SQR_WAVE) val.count_mode = 3;

            else if((st & CHECK_MODE) == TIMER_MODE_4) val.count_mode = 4;

            else if((st & CHECK_MODE) == TIMER_MODE_5) val.count_mode = 5;

            break;

        case tsf_base:
            if((st & 1) == TIMER_BIN) val.bcd = false;

            else val.bcd = true;

            break;

        default:
            return 1;

    }


    //if everything went as expected 

    timer_print_config(timer , field , val);

    return 0;

}


