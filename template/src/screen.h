#include "system.h"
#ifndef SCREEN_H_
#define SCREEN_H_

void clear_screen();
void set_cursor(uint8_t row, uint8_t column);
void get_cursor(uint8_t *row, uint8_t *column);
void set_color(uint8_t fgcolor, uint8_t bgcolor);
void get_color(uint8_t *fgcolor, uint8_t *bgcolor);
void put_char(uint8_t ch);
void putss(char *str);
int divi(int num, int den);
void put_decimal(uint32_t n);
void testVGA();
void testVGA2();

#endif /* SCREEN_H_ */