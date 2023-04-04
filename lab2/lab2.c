#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


extern uint32_t counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  
  uint8_t status;

  if(timer_get_conf(timer ,  &status) != 0)
  {
    printf("[ERROR] Could not get the timer config\n");
    return 1;
  }

  if(timer_display_conf(timer , status , field) != 0)
  {
    printf("[ERROR] Could not display the status of the timer\n");
    return 1;
  }
  

  //if everything went as expected
  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
    if (timer_set_frequency(timer, freq) != 0) {
        printf("[ERROR] Could not set the desired frequency\n");
        return 1;
    }
    //if everything went as expected
    return 0;
}

int(timer_test_int)(uint8_t time) {

    int ipc_status;

    message msg;

    uint8_t bit_no = 0;

    
  

    unsigned long res;

    timer_subscribe_int(&bit_no);


    while(time > 0) { 
        //subscribe interruption
        
         
        if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
        printf("driver_receive failed with: %d", res);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE :                              
                    if (msg.m_notify.interrupts & BIT(bit_no)) {

                      timer_int_handler();
                      
                       
                      if(counter % 60  == 0) //FREQUENCIA DEFINIDA A 60 HZ , 60 VEZES POR SEGUNDO
                      {
                        timer_print_elapsed_time();
                        time--;
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

    timer_unsubscribe_int();
    
    return 0; //if success
  
}

