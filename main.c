/*
 * File:   car_black_box.c
 * Author: Manikanda Bharathi
 *
 * Created on 13 December, 2023, 9:24 PM
 */
#include "main.h"

void init_config(){
    init_matrixkeypad();
    init_clcd();
    //init_animation();
    init_adc();
    init_timer0();
    init_i2c();
	init_ds1307();
}
unsigned int controlflag=1;
unsigned int logout=0;
extern char mpos;
void main(void) {
    init_config();
    unsigned char ucKey,uc1Key;
    unsigned short usAdc;
    while(1){
        usAdc = (unsigned short)(read_adc(4)/10.33);
        ucKey = read_switches(EDGE);
        uc1Key = read_switches(LEVEL);
        if(ucKey == 10)
        {
            controlflag=0;
            CLEAR_DISP_SCREEN;
        }
        switch(controlflag)
        {
            case 0:
                logscreen(ucKey);
                mpos=0;
                break;
            case 1:
                display_dashboard(ucKey, usAdc);
                mpos=0;
                break;
            case 3:
                scrolllog(ucKey, uc1Key);
                break;
            case 4: //default screen
                break;
        }
    }
    
    
    return;
}