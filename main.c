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
}

void main(void) {
    init_config();
    unsigned char ucKey;
    unsigned short usAdc;
    unsigned int controlflag=1;
    while(1){
        usAdc = (unsigned short)(read_adc(4)/10.33);
        ucKey = read_switches(EDGE);
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
            case 3: //defualt screnn
                break;
        }
    }
    
    return;
}

