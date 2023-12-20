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

#include <xc.h>
#include "conf.h"
#include "clcd.h"
#include "string.h"
void init_config(void);
void init_animation(void);
/*  Matrix keypad MKP1 MKP2 MKP3*/
#define EDGE 1
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
void scrolllog(void);
void timeleft(void);
void init_timer0(void);
#endif	/* MAIN_H */
