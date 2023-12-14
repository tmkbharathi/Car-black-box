#include "main.h"

char* signature[8]={"ON","GN","G1", "G2","G3","G4","GR", "C "};

void display_dashboard(unsigned char uckey)
{
    clcd_print( (unsigned char*) "  TIME     E  SP" , LINE1(0));     //time, event, speed
    display_time();
    gear_monitor(uckey);
    display_speed();
}
void display_time(){
    clcd_putch('1', LINE2(2));
    clcd_putch('5', LINE2(3));
    clcd_putch(':', LINE2(4));
    clcd_putch('0', LINE2(5));
    clcd_putch('0', LINE2(6));
    clcd_putch(':', LINE2(7));
    clcd_putch('0', LINE2(8));
    clcd_putch('0', LINE2(9));
}

void gear_monitor(unsigned char uckey){
    static char signindex=0;
    if(uckey == 1)
    {
        signindex=7;                     //crashed
    }    
    else if(uckey == 2)                  //increment
    {
        if(signindex != 6)
            signindex++;
    }
    else if(uckey == 3)                  //decrement
    {
       if(signindex != 0)
            signindex--;   
    }
    clcd_putch(signature[signindex][0], LINE2(11));
    clcd_putch(signature[signindex][1], LINE2(12));
}

void display_speed(){
        clcd_putch('9', LINE2(14));
        clcd_putch('9', LINE2(15));
    }