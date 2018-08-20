#ifndef _SPACE_H
#define _SPACE_H

#include "screen.h"
#include "system.h"
#include "keypad.h"

uint8_t aliens[4][10];
uint8_t aliensr[4][10];
uint8_t aliensc[4][10];
uint8_t alienh;
uint8_t alienw;
uint8_t deathcount;

uint8_t fortress[4];
uint8_t fortressr[4];
uint8_t fortressc[4];
uint8_t fortressw;
uint8_t fortressHP;

uint8_t rowspaceship;
uint8_t columnspaceship;
uint8_t spaceshiplives[3];
uint8_t spaceshiplivescount;

uint8_t rowplayerbullet;
uint8_t columnplayerbullet;
bool playerbullet;

uint8_t rowalienbullet;
uint8_t columnalienbullet;
bool alienbullet;
uint8_t alienLines[4];
uint8_t alienLineCount[4];

int totaScore = 0;

bool play;
bool clearbg;

void setAliens();
void paintAliens();
void paintAliens2();
void paintMovedAliens();

void setFortress();
void paintFortress();

void paintSpaceship();

void paintPlayerBullet();
void playerBulletHitBox();

void paintDeathcount();
void paintLives();

void paintAlienBullet();
void alienBulletHitBox();
void alienBulletSetter();

void gameOn();
void defaultSettings();
void paintLOSEScreen();
void paintWINScreen();

int divi(int num, int den);
void put_decimal(uint32_t n);

#endif /* _SPACE_H */
