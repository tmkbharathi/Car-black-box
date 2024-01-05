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
   // init_uart();
}
unsigned int controlflag=1;
unsigned int logout=0;
char pass[5];
unsigned char firstrunflag;
void main(void) {
    init_config();
    
    write_external_eeprom(0x00,'0');
    write_external_eeprom(0x01,'0');
    write_external_eeprom(0x02,'0');
    write_external_eeprom(0x03,'0');
    pass[4]='\0';
    
    
    pass[0]=read_external_eeprom(0x00);
    pass[1]=read_external_eeprom(0x01);
    pass[2]=read_external_eeprom(0x02);
    pass[3]=read_external_eeprom(0x03);
    unsigned char ucKey;
    unsigned short usAdc;
    getforstoreevent();
    while(1){
        usAdc = (unsigned short)(read_adc(4)/10.33);
        if(controlflag==0 || controlflag==2)
            ucKey = read_switches(EDGE);
        else
        {
            ucKey = read_switches(LEVEL);
            gear_monitor(ucKey);
        }
       
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
                view_log(ucKey);
                break;
            case 2:
                change_pass(ucKey);
                break;
            case 5:
                download_log(ucKey);
                break;
            case 6:
                set_time(ucKey);
                break;
            default:
                clcd_print( TC "Control flag miss", LINE1(0));
                break;
        }
    }
    
    
    return;
}