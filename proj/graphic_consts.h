#include <lcom/lcf.h>

#define BIT(n) (1 << (n))

//VBE graphics mode 105h, 1024x768@256, linear mode:

#define SET_VBE_MODE 0x4F02 //VBE call, function 02 -- set VBE mode

#define INDEXED_COLOR_MODE 0x105

#define VIDEO_CARD_BIOS 0x10

#define AUX_COLOR 0xFF
