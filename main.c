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
    
}

void main(void) {
    init_config();
    unsigned char ucKey;
    while(1){
        
        ucKey = read_switches(EDGE);
        display_dashboard(ucKey);
    }
    return;
}

