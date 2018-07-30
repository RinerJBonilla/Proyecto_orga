#include "screen.h"
#include "system.h"

uint8_t cursor_row;
uint8_t cursor_column;
uint8_t fore_color;
uint8_t back_color;

void clear_screen(){
    set_cursor(0x0,0x0);
    for(uint16_t g = 0xb800; g<0xcabf;g+=0x2){
        put_char(' ');
    }
    set_cursor(0x0,0x0);
}

void set_cursor(uint8_t row, uint8_t column){
    cursor_column = column;
    cursor_row = row;
}

void get_cursor(uint8_t *row, uint8_t *column){
    row = &cursor_row;
    column = &cursor_column;
}

void set_color(uint8_t fgcolor, uint8_t bgcolor){
    fore_color = fgcolor;
    back_color = bgcolor;
}

void get_color(uint8_t *fgcolor, uint8_t *bgcolor){
    fgcolor = &fore_color;
    bgcolor = &back_color;
}

void put_char(uint8_t ch){
    if(ch == '\n'){
        cursor_row = cursor_row + 0x1;
        cursor_column = 0x0;
    }
    else{
        uint8_t new_color = (back_color << 4) | fore_color;
        uint16_t data = (new_color << 8 ) | ch;

        uint16_t *vgaptr = (uint16_t*)((((cursor_row*0x50)+cursor_column)*0x2)+0xb800);
        //uint16_t *vgaptr = (uint16_t*)0xb800;
        
        *vgaptr = data;

        if(cursor_column == 0x4f){
            cursor_row = cursor_row + 0x1;
            cursor_column = 0x0;
        }
        else{
            cursor_column = cursor_column + 0x1;
        }
    }
}

void putss(char *str){
    for(int i=0; str[i] != 0; i++){
        put_char(str[i]);
    }
}
int divi(int num, int den)
{
    int res;
    for (res = 0; num >= den; num -= den, res++);
    return res;
}

void put_decimal(uint32_t n){
    char res[7];
    int tmpi;
    char* ptr = res, *ptr1 = res, tmp_char;
    
    do {
        tmpi = n;
        n= divi(n,10);
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz" [(tmpi - n * 10)];
    } while ( n );

    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    putss(res);
}

void testVGA(){
    uint16_t data = 0xcf00 | 'a';
    uint16_t *vgaptr = (uint16_t *)0xb800;
    *vgaptr = data;
}
void testVGA2(){
    uint16_t data = 0xcf00 | 'b';
    uint16_t *vgaptr = (uint16_t *)0xb802;
    *vgaptr = data;
}