
#include <lcom/lcf.h>

#include "PS2.h"
#include "mouse.h"

#include <stdint.h>

static int hook_id;

//static int hook_id_timer;

int(mouse_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  if (sys_irqsetpolicy(IRQ12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK) {
    return 1;
  }
  return 0;
}

int(mouse_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != OK) {
    return 1;
  }
  return 0;
}

void(mouse_ih)() {
  uint8_t status;
  if (util_sys_inb(ST_REG, &status) != 0) {
    return;
  }
  if (status & OBF) {
    if (util_sys_inb(OUT_BUFF, &scancode) != OK) {
      valid_byte = true;
      return;
    }
  }
  if ((status & TIMEOUT) || (status & PARITY)) {
    printf("[ERROR] PARITY or TIMEOUT error\n");
    valid_byte = false;
    return;
  }
  return;
}

void PacketParsing() {
  pp.bytes[0] = byte_packet[0];
  pp.bytes[1] = byte_packet[1];
  pp.bytes[2] = byte_packet[2];

  if ((byte_packet[0] & X_SIGN) == X_SIGN) {
    pp.delta_x = byte_packet[1] - 256;
  }

  else
    pp.delta_x = byte_packet[1];

  if ((byte_packet[0] & Y_SIGN) == Y_SIGN) {
    pp.delta_y = byte_packet[2] - 256;
  }

  else
    pp.delta_y = byte_packet[2];

  pp.lb = (byte_packet[0] & LB);
  pp.rb = (byte_packet[0] & RB);
  pp.mb = (byte_packet[0] & MB);
  pp.x_ov = (byte_packet[0] & x_ovfl);
  pp.y_ov = (byte_packet[0] & y_ovfl);
}

int issue_command(uint8_t cmd) {
  //1 ver se o input buffer está cheio se , sim , não podemos escrever no command register
  //2 se o input buffer não estiver cheio podemos escrever o comando no command register

  uint8_t stat;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }
    if ((stat & IBF) == 0) {
      if (sys_outb(CTRL_REG, cmd) != OK) {
        printf("[ERROR] SYS OUTB FAILED \n");
        return 1;
      }

      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

uint8_t read_data() {
  uint8_t stat, data;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }

    if (stat & OBF) {

      if (util_sys_inb(OUT_BUFF, &data) != OK) {
        printf("[ERROR] status\n");

        return 1;
      }
      else
        return data;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int write_data(uint32_t data) {

  uint8_t stat;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }
    if ((stat & OBF) == 0) {
      if (sys_outb(OUT_BUFF, data) != OK) {
        printf("[ERROR] SYS OUTB FAILED \n");
        return 1;
      }
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int getResponse(uint8_t *res) {
  uint8_t stat;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }
    if ((stat & OBF) != 0) {
      if (util_sys_inb(OUT_BUFF, res) != OK) {
        printf("[ERROR] SYS OUTB FAILED \n");
        return 1;
      }
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int(mouse_disable_data_reporting)() {
  int end = 2;
  uint8_t res;
  while (end > 0) {
    if (issue_command(WRITE_BYTE_M) != 0) {
      return 1;
    }

    if (write_data(DISABLE_DATA_ARG) != 0) {
      return 1;
    }

    res = read_data();

    if (res == ACK) {
      return 0;
    }
    if (res == NACK) {
      end--;
    }
    else {
      return 1;
    }
  }
  return 0;
}

int mouse_enable_data_reporting_v2() {
  int end = 2;
  uint8_t res;
  while (end > 0) {
    if (issue_command(WRITE_BYTE_M) != 0) {
      return 1;
    }

    if (write_data(ENABLE_DATA_ARG) != 0) {
      return 1;
    }

    res = read_data();

    if (res == ACK) {
      return 0;
    }
    if (res == NACK) {
      end--;
    }
    else {
      return 1;
    }
  }
  return 0;
}

int(util_sys_inb)(int port, uint8_t *value) {
  uint32_t val;
  if (sys_inb(port, &val) != 0) {
    return 1;
  }
  *value = val;
  return 0;
}

/*
int (timer_subscribe_int)(uint8_t *bit_no)
{
    hook_id_timer = *bit_no;

    if(sys_irqsetpolicy(IRQ0 , IRQ_REENABLE , &hook_id_timer) != OK)
    {
        printf("[ERROR] Could not subscribe the timer interrupts\n");
        return 1;
    }

    //if everything went as expected

    return 0;
}

int(timer_unsubscribe_int)()
{
    if(sys_irqrmpolicy(&hook_id_timer) != OK)
    {
        printf("[ERROR] Could not unsubscribe the timer interruts\n");
        return 1;
    }

    //if everyhting went as expected 

    return 0;
}


int (mouse_subscribe_int)(uint8_t *bit_no) {

  hook_id = *bit_no;

  if (sys_irqsetpolicy(IRQ12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK) {

    printf("kernel call failed!\n");
    return 1;
  }

  return 0;
}

int(mouse_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != OK) {
    printf("kernel call failed!\n");
    return 1;
  }
  return 0;
}*/

/*void PacketParsing() {

  pp.bytes[0] = byte_packet[0];

  pp.bytes[1] = byte_packet[1];

  pp.bytes[2] = byte_packet[2];

  pp.lb = byte_packet[0] & LB;

  pp.mb = byte_packet[0] & MB;

  pp.rb = byte_packet[0] & RB;

  if ((byte_packet[0] & X_SIGN) == X_SIGN) {
    pp.delta_x = byte_packet[1] - 256;
  }

  else
    pp.delta_x = byte_packet[1];

  if ((byte_packet[0] & Y_SIGN) == Y_SIGN) {
    pp.delta_y = byte_packet[2] - 256;
  }

  else
    pp.delta_y = byte_packet[2];

  if (byte_packet[0] & x_ovfl) {
    pp.x_ov = true;
  }

  else
    pp.x_ov = false;

  if (byte_packet[0] & y_ovfl) {
    pp.y_ov = true;
  }

  else
    pp.y_ov = false;

  return;
}

void(mouse_ih)() {
  //1 ler o status  a partir do status register
  //2 verificar se o output buffer está cheio , se sim , proceder para ler o scancode
  //3 verificar se há erro de paridade ou timeout se sim , descartar o scancode

  uint8_t status;

  if (util_sys_inb(ST_REG, &status) != 0) {
    printf("[ERROR] could not get the status from the status register\n");
    return;
  }

  if (status & OBF) {
    if (util_sys_inb(OUT_BUFF, &scancode) != 0) {
      printf("[ERROR] Could not get the scancode from the output buffer\n");
      return;
    }
  }

  if ((status & TIMEOUT) || (status & PARITY)) {
    printf("[ERROR] PARITY or TIMEOUT error\n");
    valid_byte = false;
    return;
  }

  //if everything went as expected
  return;
}




void mouse_remote_packet()
{

  //1 ler o status  a partir do status register
  //2 verificar se o output buffer está cheio , se sim , proceder para ler o scancode
  //3 verificar se há erro de paridade ou timeout se sim , descartar o scancode

    uint8_t status;


    if(util_sys_inb(ST_REG,  &status) != 0)
    {
        printf("[ERROR] could not get the status from the status register\n");
        return ;
    }


    if(status & OBF)
    {
        if(util_sys_inb(OUT_BUFF , &scancode) != 0)
        {
          printf("[ERROR] Could not get the scancode from the output buffer\n");
          return ;
        }
    }

    

    if((status & TIMEOUT) || (status & PARITY))
    {
        printf("[ERROR] PARITY or TIMEOUT error\n");
        valid_byte = false;
        return ;
    }

    valid_byte = true;

    //if everything went as expected 
    return;
}

void (timer_int_handler)()
{
  counter++;
}

int issue_command(uint8_t cmd)
{
    //1 ver se o input buffer está cheio se , sim , não podemos escrever no command register
    //2 se o input buffer não estiver cheio podemos escrever o comando no command register

  uint8_t stat;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }
    if ((stat & IBF) == 0) {
        if(sys_outb(CTRL_REG, cmd) != OK)
        {
          printf("[ERROR] SYS OUTB FAILED \n");
          return 1;
        }

        return 0;    
    }   
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

uint32_t read_data() {
  uint8_t stat, data;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }

    if (stat & OBF) {

      if (util_sys_inb(OUT_BUFF, &data) != OK) {
        printf("[ERROR] status\n");

        return 1;
      }
      else
        return data;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int write_data(uint32_t data) {

  uint8_t stat;
  while (1) {
    if (util_sys_inb(ST_REG, &stat) != OK) {
      printf("[ERROR] status\n");

      return 1;
    }
    if ((stat & OBF) == 0) {
        if(sys_outb(OUT_BUFF, data) != OK)
        {
          printf("[ERROR] SYS OUTB FAILED \n");
          return 1;
        }

        return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}


int getResponse(uint8_t *res)
{
  if(util_sys_inb(OUT_BUFF,res) != 0)
  {
    printf("Could not get the response from the output buffer \n");

    return 1;
  }

  return 0;
}



int mouse_enable_data_reporting_v2()
{
      //1ªLER O status register e verificar o bit do IBF , se estiver a 1 , não posso escrever 
    //o 0xD4 no CTRL_REGISTER

    uint8_t status , resposta = 0;

    int number_of_tries = 2;


    while(number_of_tries > 0)
    {

       if(util_sys_inb(ST_REG , &status) != OK)
      {
        printf("[ERROR] Could not get the status \n");
        return 1;
      }


      if((status & IBF) == 0)
      {
        if(issue_command(WRITE_BYTE_M) != 0)
        {
          printf("[ERROR] Could not issue the command\n");
          return 1;
        }
      }


      if(write_data(ENABLE_DATA_ARG) != 0)
      {
        printf("[ERROR] Could not write the argument\n");
        return 1;
      }


      if(getResponse(&resposta) != 0)
      {
        printf("[ERROR]\n");
        return 1;
      }

      if(resposta == ACK)  return 0;

      else if(resposta == ERROR) return 1;

      else if(resposta == NACK) number_of_tries--;
         

  }

  return 1;
}


int (mouse_disable_data_reporting)()
{
    //1ªLER O status register e verificar o bit do IBF , se estiver a 1 , não posso escrever 
    //o 0xD4 no CTRL_REGISTER

    int number_of_tries = 2;
    uint8_t status, resposta = 0;


    while(number_of_tries > 0)
    {

       if(util_sys_inb(ST_REG , &status) != OK)
      {
        printf("[ERROR] Could not get the status \n");
        return 1;
      }


      if((status & IBF) == 0)
      {
        if(issue_command(WRITE_BYTE_M) != 0)
        {
          printf("[ERROR] Could not issue the command\n");
          return 1;
        }
      }


      if(write_data(DISABLE_DATA_ARG) != 0)
      {
        printf("[ERROR] Could not write the argument\n");
        return 1;
      }


      if(getResponse(&resposta) != 0)
      {
        printf("[ERROR]\n");
        return 1;
      }

      if(resposta == ACK)  return 0;

      else if(resposta == ERROR) return 1;

      else if(resposta == NACK) number_of_tries--;
         

    }

  return 1;
}



int disable_interrupts()
{

  uint8_t cmd_byte = 0;
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

  cmd_byte = cmd_byte & ~(BIT(1)); //DESATIVAR AS INTERRUPTS;

  if(write_data(cmd_byte) != 0)
  {
    printf("[ERROR] Could not write data into th*e Output buffer\n");
    return 1;
  }

  return 0;
}


int setRemoteMode()
{
      //1ªLER O status register e verificar o bit do IBF , se estiver a 1 , não posso escrever 
    //o 0xD4 no CTRL_REGISTER

    uint8_t status , resposta = 0;

    int number_of_tries = 2;


    while(number_of_tries > 0)
    {

      if (util_sys_inb(ST_REG, &status) != OK) {
        printf("[ERROR] Could not get the status \n");
        return 1;
      }

      if ((status & IBF) == 0) {
        if (issue_command(WRITE_BYTE_M) != 0) {
          printf("[ERROR] Could not issue the command\n");
          return 1;
        }
      }

      
      if (write_data(SET_REMOTE_MODE) != 0) {
        printf("[ERROR] Could not write the argument\n");
        return 1;
      }

      if (resposta == ACK) {
        break;
      }

      else if (resposta == NACK) {
        number_of_tries--;
        continue;
      }

      else if (resposta == ERROR) {
        printf("ERROR!\n");
        return 1;
      }
    }

  return 0;

}


int setStreamMode()
{

  //1ªLER O status register e verificar o bit do IBF , se estiver a 1 , não posso escrever 
  //o 0xD4 no CTRL_REGISTER

    uint8_t status , resposta = 0;

    int number_of_tries = 2;


    while(number_of_tries > 0)
    {

       if(util_sys_inb(ST_REG , &status) != OK)
      {
        printf("[ERROR] Could not get the status \n");
        return 1;
      }


      if((status & IBF) == 0)
      {
        if(issue_command(WRITE_BYTE_M) != 0)
        {
          printf("[ERROR] Could not issue the command\n");
          return 1;
        }
      }


      if(write_data(SET_STREAM_MODE) != 0)
      {
        printf("[ERROR] Could not write the argument\n");
        return 1;
      }

      if (getResponse(&resposta) != 0) {
        printf("[ERROR]\n");
        return 1;
      }

      if (resposta == ACK) {
        return 0;
      }

      else if (resposta == NACK) {
        number_of_tries--;
        continue;
      }
  
      else if (resposta == ERROR) {
        printf("ERROR!\n");
        return 1;
      }


    }

  return 0;
}



int send_data_request()
{

  uint8_t status , resposta = 0;

  int number_of_tries = 2;

  while(number_of_tries > 0)
  {


    if(util_sys_inb(ST_REG , &status) != OK)
    {
        printf("[ERROR] Could not get the status \n");
        return 1;
    }


      if((status & IBF) == 0)
      {
        if(issue_command(WRITE_BYTE_M) != 0)
        {
          printf("[ERROR] Could not issue the command\n");
          return 1;
        }
      }


      if(write_data(SEND_DATA_REQUEST) != 0)
      {
        printf("[ERROR] Could not write the argument\n");
        return 1;
      }


      if(getResponse(&resposta) != 0)
      {
        printf("[ERROR]\n");
        return 1;
      }

      if(resposta == ACK)  return 0;

      else if(resposta == ERROR) return 1;

      else if(resposta == NACK) number_of_tries--;
         

  }

  return 1;

} */
