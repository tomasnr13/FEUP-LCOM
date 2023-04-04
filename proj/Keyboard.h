#include <stdbool.h>
#include <stdint.h>


extern uint32_t scancode;

extern bool make, ValidScanCode;

extern uint8_t size;

extern uint8_t bytes[2];

int (kbd_subscribe_int)(uint8_t *bit_no);
//int (timer_subscribe_int_kb)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();
//int (timer_unsubscribe_int_kb)();

void two_byte_parsing(uint32_t code);

void ScanCodeParsing(uint32_t scancode);

void kbd_ih();

void kbd_read_poll();

int write_data_kb(uint32_t data);

uint32_t read_data_kb();

int issue_command_kb(uint8_t cmd);

