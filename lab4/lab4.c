// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"
#include "PS2.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

struct packet pp;
uint8_t byte_packet[3];
//uint8_t byte_counter=0;
uint8_t scancode=0;
uint8_t counter_bytes=0;
bool valid_byte;

int(mouse_test_packet)(uint32_t cnt) {
  //1) how to read, using an interrupt handler (IH), the packets the PS/2 mouse sends when operating in stream mode
  //2) how to parse the mouse packets
  //3) We expect that, in your final version data reporting in stream mode will be enabled by your own code,
  //rather than by calling the function we are providing you. In the final project, you will score points for that.

  if (mouse_enable_data_reporting_v2() != 0) {
    printf("Could not enable the data report \n");
    return 1;
  }

  int ipc_status;
  message msg;
  uint8_t bit_no = IRQ12;
  unsigned long res;

  if (mouse_subscribe_int(&bit_no)) {
    printf("[ERROR] Did not subscribed the interrupts\n");
    return 1;
  }

  while (cnt > 0) {
    //subscribe interruption

    if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", res);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(bit_no)) {

            valid_byte = true;

            mouse_ih();

            if (valid_byte) {

              if (counter_bytes == 0 && (scancode & BIT(3))) {
                byte_packet[0] = scancode;
                counter_bytes++;
                continue;
              }

              if (counter_bytes == 1) {
                byte_packet[1] = scancode;
                counter_bytes++;
                continue;
              }

              if (counter_bytes == 2) {

                byte_packet[2] = scancode;

                PacketParsing();
                mouse_print_packet(&pp);
                cnt--;
                counter_bytes = 0;
                continue;
              }
            }
          }
          break;
        default:
          break;
      }
    }
    else {
    }
  }

  if (mouse_unsubscribe_int() != 0) {
    printf("[ERROR] Did not unsubscribed the interrupts\n");
    return 1;
  }

  if (mouse_disable_data_reporting() != 0) {
    printf("[ERROR] Did not return the mouse to the initial state\n");
    return 1;
  }
  //before returning, it should reset the mouse to its state before the execution of your program, i.e. it must disable data reporting and unsubscribe mouse interrupts
  return 0;
}

/*int (mouse_test_packet)(uint32_t cnt) {
    int ipc_status;
    message msg;
    uint8_t mib = 12;
    unsigned long r;

    mouse_enable_data_reporting_v2();

    mouse_subscribe_int(&mib);

    byte_counter = 0;
    while (cnt>0) { 
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE :                                            
                    if (msg.m_notify.interrupts & BIT(mib)) {

                        mouse_ih();

                        if (valid_byte) {
                          
                            if ((byte_counter == 0) && (scancode & BIT(3))){
                                byte_packet[0] = scancode;
                                byte_counter++;
                                continue;
                            }
                            else if (byte_counter == 1) {
                                byte_packet[1] = scancode;
                                byte_counter++;
                                continue;
                            }
                            else if (byte_counter == 2) {
                                byte_packet[2] = scancode;
                                PacketParsing();
                                mouse_print_packet(&pp);
                                byte_counter = 0;
                                cnt--;
                                continue;
                            }
                            else {
                                continue;
                            }
                        }
                    }
                    break;
                default: 
                    break; 
            }

        }
        else { 
        }
    }

    mouse_disable_data_reporting();
    mouse_unsubscribe_int();

    return 0;
} */

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

