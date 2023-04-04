#ifndef __MOUSE_H
#define __MOUSE_H

#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>



extern struct mouse_ev mouse_event;

extern bool lb_pressed , rb_pressed  , mb_pressed;

extern struct packet pp;

extern uint8_t counter_bytes;

extern bool valid_byte;

extern uint8_t byte_packet[3];

extern uint32_t counter;

extern uint8_t scancode_mouse;

int (util_sys_inb)(int port, uint8_t *value);

int (mouse_disable_data_reporting)();

int mouse_enable_data_reporting_v2();

int (mouse_subscribe_int)(uint8_t *bit_no);

int(timer_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int(timer_unsubscribe_int)();

void PacketParsing();

void (mouse_ih)();

int getResponse(uint8_t *res);

int write_data(uint32_t data);

uint32_t read_data();

int issue_command(uint8_t cmd);

int disable_interrupts();

int setRemoteMode();

int setStreamMode();

int send_data_request();

void mouse_remote_packet();

struct mouse_ev * 	mouse_detect_event_v2();

void (timer_int_handler)();

#endif

