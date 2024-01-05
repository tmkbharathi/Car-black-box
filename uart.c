#include "main.h"

void init_uart()
{
    
    TRISC6=0;
    TRISC7=1;
    
    TX9=0;
    TXEN=1;
    SYNC=0;
    BRGH=1;
    
    SPEN=1;
    RX9=0;
    CREN=1;
    
    BRG16=0;
    SPBRG=129;
    SENDB=1;
   // GIE=1;
   // PEIE=1;
    TXIE=1;
    RCIE=1;
    TXIF=0;
    RCIF=0;
}

unsigned char getch()
{
    while(!RCIF);
    RCIF=0;
    return RCREG;
}
unsigned char getche()
{
    char ch;
    while(!RCIF);
    RCIF=0;
    putch(ch=RCREG);
    return ch;
}
void putch(unsigned char data)
{
    TXREG=data;
    while(!TXIF)
        TXIF=0;
}
void puts(char*data)
{
    while(*data)
    {
        putch(*data);
        data++;
    }
}


