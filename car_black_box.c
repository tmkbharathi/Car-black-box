#include "main.h"

char* signature[8]={"ON","GN","G1","G2","G3","G4","GR", "C "};

void display_dashboard(unsigned char uckey, unsigned short usads)
{
    clcd_print( (unsigned char*) "   Time    E  SP" , LINE1(0));     //time, event, speed
    //car_animation(); 
    display_time();
    gear_monitor(uckey);
    display_speed(usads);
}
void display_time(){
    clcd_print(" 10:00:00", LINE2(0));
}

void gear_monitor(unsigned char uckey){
    static char signindex=0, crashflag=0;
    if(uckey == 1)
    {
        crashflag=1;                         //crashed
        signindex=7;                     
    }        
    else if(uckey == 2)                      //increment
    {
        if(signindex < 6)
            signindex++;
        else if(signindex ==7)
        {
            signindex=1;
            crashflag=0;
        }
    } 
    else if(uckey == 3)                       //decrement
    {
          if(crashflag ==0 && signindex > 1)
              signindex--; 
    }
    clcd_putch(signature[signindex][0], LINE2(11));
    clcd_putch(signature[signindex][1], LINE2(12));
}

void display_speed(unsigned short usadc){
        clcd_putch((unsigned char)(usadc/10)%10+48, LINE2(14));
        clcd_putch((unsigned char)usadc%10+48, LINE2(15));
}