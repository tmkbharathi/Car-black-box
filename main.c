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
    init_animation();
    init_adc();
    init_timer0();
}
unsigned int controlflag=1;
unsigned int logout=0;

void main(void) {
    init_config();
    unsigned char ucKey,uc1Key;
    unsigned short usAdc;
    while(1){
        usAdc = (unsigned short)(read_adc(4)/10.33);
        ucKey = read_switches(EDGE);
        uc1Key = read_switches(0);
        if(uc1Key == 12)
        {
            if(logout++ == 1000)
            {
                logout=0;
                controlflag=1;
            }
        }
        if(ucKey == 10)
        {
            controlflag=0;
            CLEAR_DISP_SCREEN;
        }
        switch(controlflag)
        {
            case 0:
                logscreen(ucKey);
                break;
            case 1:
                display_dashboard(ucKey, usAdc);  
                break;
            case 4:
                scrolllog();
            case 3: //defualt screnn
                break;
        }
    }
    
    return;
}