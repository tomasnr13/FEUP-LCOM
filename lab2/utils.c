#include <lcom/lcf.h>

#include <stdint.h>



int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  val = (unsigned char) val; //colocar val em 8 bits , um unsigned char tem 8 bits

  *lsb = val;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  val = val >> 8; //shift rigth 8 bits

  *msb = val;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t lst; 
  //Reading timer status
	//Temporary variable because sys_inb requires an unsigned long pointer as its second argument, despite the output desired only being an unsigned char)
  if(sys_inb(port , &lst) != OK)
  {
    printf("System call failed");
    return 1;
  }
  else
  {
    *value = lst;
  }

  return 0;
}
