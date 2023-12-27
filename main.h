/* 
 * File:   main.h
 * Author: Manikanda Bharathi T
 *
 * Created on 13 December, 2023, 9:55 PM
 */

#ifndef MAIN_H
#define	MAIN_H
#include "stdlib.h"
/*Macros for ports*/
#define B PORTBbits 
#define C PORTCbits
#define D PORTBbits
#define TC (unsigned char*)

#include <xc.h>
#include "conf.h"
#include "clcd.h"
#include "i2c.h"
#include "ds1307.h"
void init_config(void);
void init_animation(void);
int mystrcmp(char*s1, char *s2);
/*  Matrix keypad MKP1 MKP2 MKP3*/
#define EDGE 1
#define LEVEL 0
void init_matrixkeypad(void);
unsigned char read_switches(unsigned char ucdetection);
unsigned char scan_key(void);

/*car black box*/
void display_dashboard(unsigned char uckey, unsigned short usAdc);
void display_time(void);
void gear_monitor(unsigned char uckey);
void display_speed(unsigned short usads);
void car_animation(void);

/*adc*/
void init_adc(void);
unsigned short read_adc(unsigned char channel);

/*logscreen*/
void logscreen(unsigned char uckey);
void scrolllog(unsigned char key, unsigned char key1);
void timeleft(void);
void init_timer0(void);

void display_times(void);
static void get_time(void);
void init_ds1307(void);
#endif	/* MAIN_H */