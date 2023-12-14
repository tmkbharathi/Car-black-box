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
void init_config(void);

/*  Matrix keypad MKP1 MKP2 MKP3*/
#define EDGE 1
void init_matrixkeypad(void);
unsigned char read_switches(unsigned char ucdetection);
unsigned char scan_key(void);

/*car black box*/
void display_dashboard(unsigned char uckey);
void display_time(void);
void gear_monitor(unsigned char uckey);
void display_speed(void);


#endif	/* MAIN_H */

