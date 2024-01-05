#include "main.h"
short int sec=10, min=0;
char uckey[5]={0};
unsigned long int wait=0;
unsigned char i=0;
unsigned int blink=0;
unsigned int blinkflag=0, tryflag=3, enterflag=0, compareflag=0;
extern char pass[5];
extern unsigned int controlflag;
unsigned long int notpressed=10000;
void logscreen(unsigned char key)
{
        uckey[4]='\0';
        if(enterflag==0)
            clcd_print( TC " Enter Password ", LINE1(0));
        if(tryflag>0)
        {
             if(i<4)
             {
                 if(!(notpressed--))
                 {
                     notpressed=10000;
                     i=0, tryflag=0;
                     controlflag=1;
                     return;
                 }
                compareflag=0;   
                if ((key != 0xFF) && key != 10)
                {
                    notpressed=10000;
                    uckey[i]=key-11+48;
                    clcd_putch('*', LINE2(i+5));
                    i++;
                }
                else
                {
                    if(blinkflag == 0)
                    {
                        blink++;
                        if(blink == 1600)
                            blink=0;
                        else if(blink < 800)
                        {
                            clcd_putch('_', LINE2(i+5));
                        }
                        else if(blink >= 800)
                        {
                            clcd_putch(' ', LINE2(i+5));
                        }
                    }
                }
              }
              else 
              {
                compareflag=1;
                i=0;
              }
              if(compareflag == 1)
              {
                if(!mystrcmp(uckey, pass))                 
                {
                    enterflag=1;
                    blinkflag=1;
                    for(unsigned int wait=50000; wait--;);
                    clcd_print( TC "  Code Passed   ", LINE1(0));
                    clcd_print( TC " Car Black Box  ", LINE2(0));
                    for(wait=500000; wait--;);
                    CLEAR_DISP_SCREEN;
                    controlflag=3;
                    blink=0, tryflag=3, enterflag=0, compareflag=0,blinkflag=0;
                    return;
                }
                else
                {
                    notpressed=10000;
                    enterflag=1;
                     clcd_print( TC " Wrong Password ", LINE1(0));                
                     clcd_print( TC " attempt Remains", LINE2(1));
                     tryflag--;
                     clcd_putch((unsigned char)tryflag+48, LINE2(0));
                     for(wait=1000000; wait--;);
                     CLEAR_DISP_SCREEN;
                     enterflag=0;
                }               
              }
       }
       else
       {
              enterflag=1;
              CLEAR_DISP_SCREEN;
              timeleft();
              blink=0, tryflag=3, enterflag=0, compareflag=0,blinkflag=0;
       } 
}
void timeleft()
{  
    CLEAR_DISP_SCREEN;
    min=0;
    TMR0ON=1;
    while(sec!=0)
    {
        clcd_print( TC "Try Again left" , LINE1(0));
        clcd_print( TC "Wait for", LINE2(0));
        clcd_print( TC " s  ", LINE2(11));
       // clcd_putch(0x98, LINE2(14));
        clcd_putch(sec%10+48, LINE2(10));
        clcd_putch(((sec/10)%10)+48, LINE2(9));
    }
    TMR0ON=0;
    sec=10;
    CLEAR_DISP_SCREEN;
}
int mystrcmp(char*s1, char *s2)
{
    int i=0;
    while(s1[i]!= '\0')
    {
        if(s1[i]!=s2[i])
        {
            return 1;
        }
        i++;
    }
    return 0;
    
}
void change_pass(unsigned  char ucKey)
{
    static char count=0,flag=0;
    static char passcheck[5];
    static char passcheck1[5];
    passcheck1[4]='\0';
    passcheck[4]='\0';
    clcd_print(TC "changing password", LINE1(0));
    for(unsigned long int wait=10000; wait--;);
    if(flag==0)
    {
            clcd_print(TC "\n current Pass", LINE1(0));
            if(count<4)
            {
                if(ucKey!=0xFF)
                {
                    passcheck[count]=ucKey+48-11;
                    count++;
                }
            }
            else
            {
                CLEAR_DISP_SCREEN;
                count=0;
                if(!mystrcmp(pass, passcheck))
                {
                    clcd_print(TC "Password Correct", LINE1(0));
                    for(unsigned long int wait=10000; wait--;);
                    CLEAR_DISP_SCREEN;
                    flag=1;
                }
            }
    }
    if(flag==1)
    {
        clcd_print(TC "\n New Password", LINE1(0));
        if(count<4)
            {
                if(ucKey!=0xFF)
                {
                    passcheck1[count]=ucKey+48-11;
                    count++;
                }
            }
            else
            {
                CLEAR_DISP_SCREEN;
                count=0;
                flag=2;
            }
    }
    if(flag==2)
    {
            clcd_print(TC "RE-Enter  Pass", LINE1(0));
            if(count<4)
            {
                if(ucKey!=0xFF)
                {
                    passcheck1[count]=ucKey+48-11;
                    count++;
                }
            }
            else
            {
                CLEAR_DISP_SCREEN;
                count=0;
                if(!mystrcmp(passcheck1, passcheck))
                {
                    clcd_print(TC"  Pass Changed  ", LINE1(0));
                    clcd_print(TC"  Successfully  ", LINE2(0));
                    for(unsigned long int wait=10000; wait--;);
                    CLEAR_DISP_SCREEN;
                    controlflag=1;
                }
            }
    }
    
    
}
