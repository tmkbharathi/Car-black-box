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
    init_adc();
    init_timer0();
    init_i2c();
	init_ds1307();
}
unsigned int controlflag=1;
unsigned int logout=0;
void main(void) {
    init_config();
    unsigned char ucKey;
    unsigned short usAdc;
    getforstoreevent();
    while(1){
        usAdc = (unsigned short)(read_adc(4)/10.33);
        if(controlflag == 0 || controlflag == 1)
            ucKey = read_switches(EDGE);
        else
            ucKey = read_switches(LEVEL);
        
        switch(controlflag)
        {
            case 0:
                logscreen(ucKey);
                break;
            case 1:
                display_dashboard(ucKey, usAdc);
                break;
            case 3:
                scrolllog(ucKey);
                break;
            case 4: //default screen
                clcd_print("View log",LINE2(0));
                break;
        }
    }
    
    
    return;
}