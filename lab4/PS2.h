#include <lcom/lcf.h>

#define   BIT(n)    (1 << (n))


#define     ST_REG      0x64
#define     CTRL_REG    0x64
#define     IN_BUFF     0x60
#define     OUT_BUFF    0x60


#define     LB  BIT(0)
#define     RB  BIT(1)
#define     MB  BIT(2)

#define     X_SIGN BIT(4)
#define     Y_SIGN BIT(5)

#define     x_ovfl BIT(6)
#define     y_ovfl  BIT(7)


#define     DISABLE_DATA_ARG    0xF5
#define     ENABLE_DATA_ARG     0xF4
#define     SET_REMOTE_MODE     0xF0
#define     SET_STREAM_MODE     0XEA
#define     SEND_DATA_REQUEST   0XEB


#define     OBF     BIT(0)   //Output buffer full - data available for reading
#define     IBF     BIT(1)   //Input buffer full , don’t write commands or arguments
#define     MOUSE_DATA  BIT(5) //Mouse Data
#define     TIMEOUT BIT(6)   //Timeout error - invalid data
#define     PARITY  BIT(7)   //Parity error - invalid data

#define     READ_CMD_BYTE   0x20 //READ COMMAND BYTE
#define     WRITE_CMD_BYTE  0x60 //WRITE COMMAND BYTE

#define     WRITE_BYTE_M    0xD4 //Write byte to mouse

#define     ACK     0xFA        //if everything is ok
#define     NACK    0xFE        //if invalid byte
#define     ERROR   0xFC        //if second consecutive invalid byte


#define     IRQ12   12          //LINHA DE INTERRUPÇÃO DO MOUSE , LINHA 12
#define     IRQ0    0           //LIHA DE INTERRUPÇÃO DO TIMER , LINHA 0


#define     DELAY_US    2000

