#include "screen.h"
#include "system.h"

int main (int argc, char *argv[])
{
    set_color(0xf,0xc);
    //putss("Quiet Sun were an English progressive rock/jazz fusion band from the Canterbury scene consisting of Phil Manzanera, Bill MacCormick, Dave Jarrett and Charles Hayward");
    clear_screen();
    set_cursor(0,0);
    put_char('O');
    set_cursor(0,79);
    put_char('O');
    set_cursor(29,0);
    put_char('O');
    set_cursor(29,79);
    put_char('O');
    set_color(0xc,0xf);
    set_cursor(9,10);
    putss("here's a number:");
    set_cursor(10,10);
    put_decimal(32);
    return 0;
}