#include "main.h"
#include<string.h>
char *scrolling[5]={"View log     ", "Download log ", "Clear log    ", "Set time     ", "Change Pass  "};
char logg=0;
char log[17];
int press=0;
extern unsigned char time[9];
char logpos=(char)(-1);
unsigned int eventcount=0;
extern unsigned int controlflag;
unsigned int out=0;
extern char*signature[];
extern char signindex;
char eventdata[10][17];

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
    log[11]=signature[signindex][0];  
    log[12]=signature[signindex][1];     
    log[0]= eventcount+48;
    log_event();
}
void log_event()
{
    unsigned char address;
    logpos++;
    if(logpos==10)
        logpos=0;
    address=(logpos*16)+5;
    if(logpos > 9)
        logpos=0;
    int i;
    for(eventcount++, i=0; i<16 ;i++)
    {
        
        write_external_eeprom(address,log[i]);
        address++;
    }
    if(eventcount>10)
        logpos=0;
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
            if(logg==0 || logg==(char)-1)
            {
                CLEAR_DISP_SCREEN;
                controlflag=4;
                return;
            }
            else if(logg==1)
            {
                CLEAR_DISP_SCREEN;          //downloading logs
                controlflag=5;
                return;
            }
            else if(logg==2)
            {
                CLEAR_DISP_SCREEN;
                clcd_print(TC "Clearing logs", LINE1(0));
                unsigned char k=0;
                for(int i=0; eventcount!=0 ; eventcount--)
                {
                    k++;
                    if(k>3)
                        clcd_putch('.',LINE2(k-3));
                    else
                        clcd_putch('.', LINE1(k));
                }
                return;
            }
            else if(log==3)
            {
                CLEAR_DISP_SCREEN;
                controlflag=6;
                return;
            }
            else if(logg==4)
            {
                CLEAR_DISP_SCREEN;
                controlflag=2;
                return;
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
    
 void view_log(unsigned char key)
{
 
    static unsigned char vpos=0;
    unsigned char address;
    for(int j=0; j<10; j++)
    {
        address=(vpos*16)+5;
        for(int i=0;i<16;i++)
        {
            eventdata[j][i]= read_external_eeprom(address + (unsigned char)i);
        }
    }
    if(key==12 &&  vpos<10)
            vpos++;
    else if(key==11 && vpos > 0)
            vpos--;
    
      clcd_print( TC eventdata[vpos], LINE1(0)); 
      clcd_print( TC eventdata[vpos+1], LINE2(0));
        
}     
void set_time(unsigned char ucKey)
{
    static char draft[9];
    draft[8]='\0';
    
}
void download_log(unsigned char ucKey)
{
    static char k=0x05;
     clcd_print(TC "Downloading logs ..", LINE1(0));
      for(int j=0; j<10; j++)
    {
        for(int i=0;i<16;i++)
        {
            eventdata[j][i]= read_external_eeprom( k + (unsigned char)i);                    
        }
        puts(eventdata[j]);
        putch('\n');
        k+=16;
    }
}