#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>

#include "Keyboard.h"
#include "i8042.h"





uint32_t scancode = 0;

int counter_sys;

bool make ,ValidScanCode = false;

uint8_t size;

uint8_t bytes[2];

extern uint32_t counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
int(kbd_test_scan)() {
  int ipc_status;
  message msg;
  uint8_t kbd_int_bit = IRQ1;

  


  unsigned long res;

  

  kbd_subscribe_int(&kbd_int_bit);

    while(scancode != ESC_KEY) { 
        //subscribe interruption
        
        /* Get a request message. */
        if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
        printf("driver_receive failed with: %d", res);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE :                              /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & BIT(kbd_int_bit)) {

                      kbd_ih();
                      if(ValidScanCode)
                      {
                        kbd_print_scancode( make, size, bytes);
                        ValidScanCode = false;
                        
                      }                  

                    }
                    break;
                default:  
                    break; /* no other notifications expected: do nothing */

            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }

    kbd_unsubscribe_int();

    kbd_print_no_sysinb(counter_sys);

    counter_sys = 0; //resetar o counter

    return 0; //if success

}

int(kbd_test_poll)() {
  
  uint32_t cmd_byte = 0;

  while(scancode != ESC_KEY){

    kbd_read_poll();

    if(ValidScanCode)
    {
      kbd_print_scancode( make, size, bytes);
      ValidScanCode = false;
                        
    }

    tickdelay(micros_to_ticks(DELAY_US));

  }

  if(issue_command(READ_CMD_BYTE) != 0)
  {
    printf("[ERROR] Could not issue the command to the Cmd register\n");
    return 1;
  }

  cmd_byte = read_data();

  if(cmd_byte == 1)
  {
    printf("[ERROR] Invalid cmd_byte \n");
    return 1;
  }

  cmd_byte = cmd_byte | BIT(0); //ativar de novo o teclado

  if(issue_command(WRITE_CMD_BYTE) != 0)
  {
    printf("[ERROR] Could not issue the command to the Cmd register\n");
    return 1;
  }

  if(write_data(cmd_byte) != 0)
  {
    printf("[ERROR] Could not write data into the Output buffer\n");
    return 1;
  }

  kbd_print_no_sysinb(counter_sys);

  counter_sys = 0; //resetar o counter

  return 0;

}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  message msg;
  uint8_t kbd_int_bit = IRQ1;
  uint8_t timer_int_bit = IRQ0;

  unsigned long res;

  

  kbd_subscribe_int(&kbd_int_bit);

  timer_subscribe_int(&timer_int_bit);



  while((scancode != ESC_KEY) && (n > 0)) { 
        if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
          printf("driver_receive failed with: %d", res);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE :
                if (msg.m_notify.interrupts & BIT(timer_int_bit)) {
                  timer_int_handler();

                  if(counter % 60 == 0) n--;

                }

                if (msg.m_notify.interrupts & BIT(kbd_int_bit)) {

                  kbd_ih();
                  if(ValidScanCode)
                  {
                    kbd_print_scancode( make, size, bytes);
                    ValidScanCode = false;
                  }
                  counter = 0; //resetar o counter quando uma tecla for pressionada
                }
                break;   

              default:  
                break; 

            }
      } 
      
  }

  kbd_unsubscribe_int();
  timer_unsubscribe_int();

  return 0;
}






