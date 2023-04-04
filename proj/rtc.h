#include <lcom/lcf.h>
#include "rtc_const.h"



extern uint8_t day_time[3];

uint8_t Convert_bcd_to_decimal(uint8_t bcd);

int rtc_unsubscribe_int();

int rtc_subscribe_int(uint8_t* bit_no);

void enable();

void disable();

void wait_valid_rtc(void);

void  rtc_read_reg(uint8_t reg);

void rtc_ih();

int enable_update_interrupts();

int disable_update_interrupts();


