#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>


#define     BIT(n)  (1 << (n))



#define     OBF     BIT(0)   //Output buffer full - data available for reading
#define     IBF     BIT(1)   //Input buffer full , don’t write commands or arguments
#define     INH     BIT(4)   //Inhibit flag: 0 if keyboard is inhibited
#define     TIMEOUT BIT(6)   //Timeout error - invalid data
#define     PARITY  BIT(7)   //Parity error - invalid data


#define     KBD_CMD_REG 0x64
#define     KBD_OUT_BUF 0x60     //OUTPUT BUFFER THAT RECEIVES THE SCAN CODE
#define     KBD_IN_BUFF 0x64    //INPUT BUFFER  OU COMANDO BUFF
#define     ST_REGISTER 0x64 //STATUS REGISTER PARA CHECKAR POSSIVEIS ERROS
#define     READ_CMD_BYTE   0x20 //READ COMMAND BYTE
#define     WRITE_CMD_BYTE  0x60 //WRITE COMMAND BYTE
#define		DELAY_US 20000



#define     ESC_KEY     0x81    //ESC_KEY
#define     A			0x1E
#define     D			0x20
#define     SPACEDOWN	0x39
#define     SPACEUP		0xB9

#define     CHECK_2BYTE 0xF    
#define     SPC_KEY     0xE0
#define     MAKE_CODE_CHECK BIT(7)



#define     IRQ1    1       //linha de interrupção do keyboard 
#define     IRQ0    0




#endif
