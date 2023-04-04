#include <lcom/lcf.h>
#include <stdint.h>

#include "Keyboard.h"
#include "i8042.h"

#include "i8042.h"

#include "mouse.h"

static int hook_id_kbd;

extern int hook_id_timer;

uint32_t scancode;

int counter_sys;



//dado que estamos no lab3 procuramos countar o número de system calls

#ifdef LAB3

int sys_inb_counter(int port , uint32_t *var)
{
    if(sys_inb(port , var) != OK)
    {
        printf("[ERROR] Could not get the value from the port \n");
        return 1;
    }

    else counter_sys++;

    //if everything went as expected

    return 0;
}

#else

int sys_inb_counter(int port , uint32_t *var)
{
    if(sys_inb(port , var) != OK)
    {
        printf("[ERROR] Could not get the value from the port \n");
        return 1;
    }
    //if everything went as expected

    return 0;
    
}

#endif

int (kbd_subscribe_int)(uint8_t *bit_no)
{
    hook_id_kbd = *bit_no;

    if(sys_irqsetpolicy(IRQ1 ,  IRQ_REENABLE|IRQ_EXCLUSIVE ,&hook_id_kbd) != OK)
    {
        printf("[ERROR] Could not subscribe the keyboard interrupts\n");
        return 1;
    }

    //if everything went as expected

    return 0;
}

int (kbd_unsubscribe_int)()
{
    if(sys_irqrmpolicy(&hook_id_kbd) != OK)
    {
        printf("[ERROR] Could not unsubscribe the keyboard interrupts \n");
        return 1;
    }

    //if everything went as expected

    return 0;
}



void two_byte_parsing(uint32_t code)
{
    size = 2;

    bytes[0] = SPC_KEY;

    code = code >> 8; //2ª byte do scancode

    bytes[1] = code;

    if(code & MAKE_CODE_CHECK)  make = false;

    else    make = true;


    return;
}


void ScanCodeParsing(uint32_t scancode)
{
    //Ver se o scancode é break ou make code
    //Checkar o size , 1 ou 2 bytes
    // colocar os bytes/byte no array



    if((scancode & CHECK_2BYTE) == SPC_KEY)
    {
        two_byte_parsing(scancode);
    }

    else{
        size = 1;

        bytes[0] = scancode;

        if(scancode & MAKE_CODE_CHECK)  make = false;

        else    make = true;
    }

    //if everything went as expected
    return ;
}


void kbd_ih()
{

    //1 ler o status  a partir do status register
    //2 verificar se o output buffer está cheio , se sim , proceder para ler o scancode
    //3 verificar se há erro de paridade ou timeout se sim , descartar o scancode

    uint32_t status;


    if(sys_inb_counter(ST_REGISTER,  &status) != 0)
    {
        printf("[ERROR] could not get the status from the status register\n");
        return ;
    }


    if(status & OBF)
    {
        if(sys_inb_counter(KBD_OUT_BUF , &scancode) != 0)
        {
            printf("[ERROR] Could not get the scancode from the output buffer\n");
            return ;
        }
    }

    if((status & TIMEOUT) || (status & PARITY))
    {
        printf("[ERROR] PARITY or TIMEOUT error\n");
        ValidScanCode = false;
        return ;
    }
    
    else{
        ValidScanCode = true;
        ScanCodeParsing(scancode);
    }

    //if everything went as expected 
    return ;

}

void kbd_read_poll()
{
    //1 ler o status  a partir do status register
    //2 verificar se o output buffer está cheio , se sim , proceder para ler o scancode
    //3 verificar se há erro de paridade ou timeout se sim , descartar o scancode

    uint32_t status;

    if(sys_inb_counter(ST_REGISTER,  &status) != 0)
    {
        printf("[ERROR] could not get the status from the status register\n");
        return ;
    }


    if((status & OBF) == OBF)
    {
        if(sys_inb_counter(KBD_OUT_BUF , &scancode) != 0)
        {
            printf("[ERROR] Could not get the scancode from the output buffer\n");
            return ;
        }
    }

    else
    {
        return;
    }

    if((status & TIMEOUT) || (status & PARITY))
    {
        printf("[ERROR] PARITY or TIMEOUT error\n");
        ValidScanCode = false;
        return ;
    }
    
    else{
        ValidScanCode = true;
        ScanCodeParsing(scancode);
    }

    //if everything went as expected 
    return ;
}


int issue_command_kb(uint8_t cmd)
{
    //1 ver se o input buffer está cheio se , sim , não podemos escrever no command register
    //2 se o input buffer não estiver cheio podemos escrever o comando no command register

  uint32_t stat;
  while (1){
    if(sys_inb_counter(ST_REGISTER, &stat) != OK)
    {
        printf("[ERROR] status\n");

        return 1;  
    }
    if ((stat & IBF) == 0) {
        if(sys_outb(KBD_CMD_REG, cmd) == OK) return 0;  

        else return 1;  
    }   
    tickdelay(micros_to_ticks(DELAY_US));
  }

}

uint32_t read_data_kb()
{
  uint32_t stat , data;
  while (1) {
    if(sys_inb_counter(ST_REGISTER, &stat) != OK)
    {
        printf("[ERROR] status\n");

        return 1;  
    } 
    
    if (stat & OBF) {

        if(sys_inb_counter(KBD_OUT_BUF, &data) != OK)
        {
            printf("[ERROR] status\n");

            return 1;  
        } 
        else return data;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int write_data_kb(uint32_t data)
{

  uint32_t stat;
  while (1) {
    if(sys_inb_counter(ST_REGISTER, &stat) != OK)
    {
        printf("[ERROR] status\n");

        return 1;  
    } 
    if ((stat & OBF) == 0) {
      if(sys_outb(KBD_OUT_BUF, data) == OK) return 0;  

      else return 1;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }

}

