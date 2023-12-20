#include "main.h"

void init_timer0(void)
{
    GIE=1;
    PEIE=1;
    TMR0IE=1;
    TMR0ON=0;
    TMR0IF=0;
            
    T08BIT=1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 6;
}
void init_timer2(void)
{

    T2CKPS0 = 1;
    T2CKPS1 = 1;
    PR2 = 250;
    TMR2IE = 1;
    TMR2ON = 1;
}