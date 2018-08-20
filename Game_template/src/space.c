#ifndef _SPACE_C
#define _SPACE_C

#include "space.h"

void setAliens(){
    for(int32_t i = 0; i<4; i++){
        for(int32_t j = 0; j<10;j++){
            aliens[i][j] = 1;
            aliensr[i][j] = 0;
            aliensc[i][j] = 0;
        }
    }
}

void setFortress(){
    for(int32_t i = 0; i<4; i++){
        fortress[i] = 0;
        fortressr[i]= 0;
        fortressc[i]= 0;
    }
}

void paintFortress(){
    uint8_t wid = fortressw;
    set_color(0x6,0x0);
    for(int32_t i = 0; i<4; i++){
        set_cursor(19, wid);
        if(fortress[i] == 0){
            fortressr[i]= 20;
            fortressc[i]= wid;
            putchar(5);
        }
        else if(fortress[i] == 1){
            fortressr[i]= 20;
            fortressc[i]= wid;
            putchar(6);
        }
        else if(fortress[i] == 2){
            fortressr[i]= 20;
            fortressc[i]= wid;
            putchar(7);
        }
        else{
            fortressr[i]= 0;
            fortressc[i]= 0;
            putchar(' ');
        }
        wid += 16;
    }
}

void paintAliens(){
    uint8_t hei = alienh;
    uint8_t wid = alienw;
    uint8_t counter = 0;
    set_color(0x5,0x0);
    for(uint8_t i = 0; i<4; i++){
        for(uint8_t j = 0; j<10;j++){
        	set_cursor(hei, wid);

            alienLines[i]=hei;
            counter+=aliens[i][j];

            if(aliens[i][j] == 1){
                aliensr[i][j] = hei;
                aliensc[i][j] = wid;
                if(i>=2){
                    set_color(0x2,0x0);
                    putchar(8);
                }
                else
                {
                    putchar(1);
                }
            }
            wid += 4;
        }
        alienLineCount[i] = counter;
        counter = 0;
        hei += alienh + 2;
        wid = alienw;
    }
}

void paintAliens2(){
    uint8_t hei = alienh;
    uint8_t wid = alienw;
    set_color(0x5,0x0);
    for(uint8_t i = 0; i<4; i++){
        for(uint8_t j = 0; j<10;j++){
        	set_cursor(hei, wid);
            putchar(' ');
            wid += 4;
        }
        hei += alienh + 2;
        wid = alienw;
    }
}

void paintMovedAliens(){
    if(alienbullet){
        paintAliens();
    }
    else{
        paintAliens2();
        if(alienw > 36){
            alienw = 0;
        }
        else{
            alienw += 4;
        }
    }
}

void paintSpaceship(){
    uint8_t input = keypad_getkey();
    set_color(0x1,0x0);
    set_cursor(rowspaceship,columnspaceship);
    putchar(' ');

    switch(input){
        case 1:
            if(columnspaceship-2>=0){
                columnspaceship-=2;
            }
            delay_ms(50);
            break;
        case 2:
            if(columnspaceship+2<80){
                columnspaceship+=2;
            }
            delay_ms(50);
            break;
        case 3:
            if(!playerbullet){
                playerbullet = true;
                rowplayerbullet = rowspaceship-1;
                columnplayerbullet = columnspaceship;
            }
            delay_ms(50);
            break;
        default:
            break;
    }

    set_color(0x1,0x0);
    set_cursor(rowspaceship,columnspaceship);
    putchar(4);
}

void paintPlayerBullet(){
    set_color(0x7,0x0);
    set_cursor(rowplayerbullet,columnplayerbullet);
    putchar(' ');

    rowplayerbullet-=1;

    set_color(0x7,0x0);
    set_cursor(rowplayerbullet,columnplayerbullet);
    putchar(2);

    delay_ms(15);
}

void playerBulletHitBox(){
    if(rowplayerbullet == 0){
        set_cursor(rowplayerbullet,columnplayerbullet);
        putchar(' ');
        playerbullet = false;
    }

    for(int32_t i = 0; i<4; i++){
        for(int32_t j = 0; j<10;j++){
            if(rowplayerbullet == aliensr[i][j] && columnplayerbullet == aliensc[i][j]){
                aliens[i][j] = 0;
                aliensr[i][j] = 0;
                aliensc[i][j] = 0;
                deathcount++;
                set_cursor(rowplayerbullet,columnplayerbullet);
                putchar(' ');
                playerbullet = false;
            }
        }
    }

}

void paintDeathcount(){
    set_cursor(28,1);
    set_color(0xf,0x0);
    puts("ALIENS:");
	put_decimal(deathcount);
}

void paintLives(){
    set_cursor(28,16);
    set_color(0xf,0x0);
    puts("LIVES:");
    set_color(0x4,0x0);
    puts("      ");
    for(int32_t i = 0; i<spaceshiplivescount; i++){
        set_cursor(28,(22+i+1));
        putchar(9);
    }
}

void paintAlienBullet(){

    set_color(0xe,0x0);
    set_cursor(rowalienbullet,columnalienbullet);
    putchar(' ');

    rowalienbullet+=1;

    set_color(0xe,0x0);
    set_cursor(rowalienbullet,columnalienbullet);
    putchar(3);

    delay_ms(60);

}

void alienBulletHitBox(){
    if(rowalienbullet == 27){
        set_cursor(rowalienbullet,columnalienbullet);
        putchar(' ');
        alienbullet = false;
    }
    else if(rowalienbullet == rowspaceship && columnalienbullet == columnspaceship){
        spaceshiplivescount-=1;
        set_cursor(rowalienbullet,columnalienbullet);
        putchar(' ');
        alienbullet = false;
    }

    for(int32_t i = 0; i<4; i++){
        if(rowalienbullet == fortressr[i] && columnalienbullet == fortressc[i]){
            fortress[i] += 1;
            fortressHP -=1;
            set_cursor(rowalienbullet,columnalienbullet);
            putchar(' ');
            alienbullet = false;
        }
    }

}

void alienBulletSetter(){
    if(alienbullet){
        paintAlienBullet();
        alienBulletHitBox();
    }
    else{

        for(int32_t i = 3; i>=0; i--){
            if(alienLineCount[i]!=0){
            rowalienbullet = alienLines[i]+1;
            break;
            }
        }

        if(columnalienbullet > 76){
            columnalienbullet = 0;
        }
        else{
            columnalienbullet += 4;
        }

        alienbullet = true;

    }
}

void gameOn(){
    if(play){
        paintMovedAliens();
        paintFortress();
        paintSpaceship();
        paintDeathcount();
        alienBulletSetter();
        paintLives();
        if(playerbullet){
            paintPlayerBullet();
            playerBulletHitBox();
        }
        else if(spaceshiplivescount == 0 || deathcount == 40){
            play = false;
            clearbg = true;
        }
    }
    else{
        if(clearbg){
            if(spaceshiplivescount == 0){
                paintLOSEScreen();
            }
            else if(deathcount == 40){
                paintWINScreen();
            }
            clearbg = false;
        }

        uint8_t input = keypad_getkey();

        if(input == 3){
            defaultSettings();
            set_color(0x0, 0x0);
	        clear_screen();
            play = true;
        }
    }
}

void defaultSettings(){
    alienh=1;
    alienw=0;
    fortressw=12;
    rowspaceship=25;
    columnspaceship=4;
    deathcount = 0;
    fortressHP=12;
    spaceshiplivescount=3;
    columnalienbullet=0;
    playerbullet = false;
    alienbullet = false;
    play = true;
    clearbg = false;
    totaScore = 0;

    setAliens();
    setFortress();
}

void paintLOSEScreen(){
    set_color(0x0, 0x4);
	clear_screen();
    set_cursor(10, 28);
    puts("GAME OVER!");
    set_cursor(14, 28);
    puts("Your SCORE: ");
    totaScore += (deathcount*5);
    totaScore += (fortressHP*15);
    totaScore += (spaceshiplivescount*10);
    put_decimal(totaScore);
    set_cursor(16, 28);
	puts("Continue? Press Down");
}

void paintWINScreen(){
    set_color(0x7,0x9);
	clear_screen();
    set_cursor(10, 28);
    puts("YOU WON");
    set_cursor(14, 28);
    puts("Your SCORE: ");
    totaScore += (deathcount*5);
    totaScore += (fortressHP*15);
    totaScore += (spaceshiplivescount*10);
    put_decimal(totaScore);
    set_cursor(16, 28);
	puts("Continue? Press Down");
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

    puts(res);
}

#endif /* _SPACE_C */
