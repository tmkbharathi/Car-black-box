#include "main.h"
#include<string.h>
char *scrolling[5]={"View log     ", "Download log ", "Clear log    ", "Set time     ", "Change Pass  "};
char logg=0;
char log[17];
int press=0;
extern unsigned char time[9];
char logpos=(-1);
unsigned eventcount=0;
extern unsigned int controlflag;
unsigned int out=0;
extern char*signature;
extern char signindex;

void get_speed()
{
    unsigned short adc = (unsigned short)(read_adc(4)/10.33);
    log[14] = ((adc/10)%10)+'0';
    log[15] = (adc%10)+'0';
}
void getforstoreevent()
{
    for(int i=0; i<16; i++)
        log[i]=' ';
    log[16] = '\0';
    get_time();
    for(int i=0; i<8; i++)
        log[i+2]=time[i];   
    get_speed();

    log_event();
}
void log_event()
{
    unsigned char address;
    logpos++;
    if(logpos==10)
        logpos=0;
    address=logpos*16;
    for(int i=0; i<16 ;i++)
    {
        write_external_eeprom(address,log[i]);
        address++;
    }
    /*if(eventcount<9)
        eventcount++;*/
}

void print(unsigned char key)
{    
    if((key==12)&&(logg < 4)) 
    {
        CLEAR_DISP_SCREEN;
        logg++; 
        press=1;
        clcd_putch('*', LINE2(1));
        clcd_print(TC scrolling[logg-1], LINE1(3));
        clcd_print(TC scrolling[logg], LINE2(3));
    } 
    else if((key== 11)&&(logg>=1)) 
    {
        CLEAR_DISP_SCREEN;
        logg--;
        press = 1;
        clcd_putch('*', LINE1(1));
        clcd_print(TC scrolling[logg], LINE1(3));
        clcd_print(TC scrolling[logg+1], LINE2(3));
    }
}
void scrolllog(unsigned char key) {
    static unsigned char prevkey=0xFF;
    if(press==0) 
        {
        clcd_putch('*', LINE1(1));
        clcd_print(TC scrolling[logg], LINE1(3));
        clcd_print(TC scrolling[logg + 1], LINE2(3));
        }
    if(key==12 || key==11)             
    {
        out++;
        prevkey=key;
        if(out > 4000 && key==12)
        {
            out=0;
            CLEAR_DISP_SCREEN;
            controlflag=1;
            press=0;
            return;
        }
        else if(out>4000 && key==11)
        {
            if(logg==0)
            {
                CLEAR_DISP_SCREEN;
                controlflag=4;
            }
        }
    }
    else if(out!=0 && out<=4000)
        {
            out=0;
            print(prevkey);
            prevkey=0xFF;
        }

}
    
/*
 void view_log(unsigned char key)
{
    char rlog[11];
    unsigned char add;
    static unsigned char rpos=0;
    if(eventcount ==-1)
    {
        clcd_print(" No logs",LINE2(0));
    }
    else
    {
        if(key==12 && rpos< (eventcount-1))
        {
            rpos++;
        }
        else if(key==11 && rpos > 0)
        {
            rpos--;
        }
        for(int i=0;i<10;i++)
        {
            add=rpos*10+5;
            rlog[i]=eeprom_read(add + i);
        }

        clcd_putch(rpos%10 + '0',LINE2(0));

        clcd_putch(rlog[0],LINE2(2));
        clcd_putch(rlog[1],LINE2(3));
        clcd_putch(':',LINE2(4));

        clcd_putch(rlog[2],LINE2(5));
        clcd_putch(rlog[3],LINE2(6));
        clcd_putch(':',LINE2(7));

        clcd_putch(rlog[4],LINE2(8));
        clcd_putch(rlog[5],LINE2(9));
        
        clcd_putch(rlog[6],LINE2(11));
        clcd_putch(rlog[7],LINE2(12));

        clcd_putch(rlog[8],LINE2(14));
        clcd_putch(rlog[9],LINE2(15));   
    }
}     
*/