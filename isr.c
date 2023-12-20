#include "main.h"
extern short int sec;
void __interrupt() isr(void)
{
    static unsigned int count = 0;
    if (TMR0IF == 1)
    {
        TMR0 = TMR0 + 8;
        if (++count == 20000)
        {
            count=0;
            sec--;
        }
 
        TMR0IF = 0;
    }
}