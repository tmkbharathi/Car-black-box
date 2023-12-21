#include "main.h"

void init_matrixkeypad()
{
    PORTB =0x00;
    TRISB = TRISB & 0x1E;
    RBPU=0;
}

unsigned char read_switches(unsigned char ucdetection)
{
    static unsigned char uconce=1, uckey;
    if(ucdetection ==0 )
        return scan_key();
    else if(ucdetection == 1)
    {
        uckey = scan_key();
        if((uckey != 0xFF) && uconce)
        {
            uconce=0;
            return uckey;
        }
        else if(uckey == 0xFF)
            uconce = 1;
    }
    return 0xFF;
}

unsigned char scan_key()
{       
    B.RB5 = 0, B.RB6 = 1, B.RB7 = 1;
    if( B.RB1 == 0)
        return 1;
    /*else if( RB2 == 0)
        return 4;
    else if( RB3 == 0)
        return 7;*/
    else if( B.RB4 == 0)
        return 10;
    
    B.RB5 = 1, B.RB6 = 0, B.RB7 = 1;
    if( B.RB1 == 0)
        return 2;
    /*else if( RB2 == 0)
        return 5;
    else if( RB3 == 0)
        return 8;*/
    else if( B.RB4 == 0)
        return 11;
    
    B.RB5 = 1, B.RB6 = 1, B.RB7 = 0, B.RB7 = 0;
    if( B.RB1 == 0)
        return 3;
    /*else if( RB2 == 0)
        return 6;
    else if( RB3 == 0)
        return 9;*/
    else if( B.RB4 == 0)
        return 12;
   
        return 0xFF;
}


