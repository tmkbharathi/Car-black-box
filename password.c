#include "main.h"
short int sec=10, min=0;
//char *scrolling[5]={"   view    log   ", "   download  log  ", "  clear   log  ", "  set   time  ", "  change password  "};
char uckey[5]={0};
unsigned long int wait=0;
unsigned char i=0;
unsigned int blink=0;
unsigned int blinkflag=0, tryflag=2, enterflag=0, compareflag=0;
char pass[5]="1100";
extern unsigned int controlflag;
void scrolllog(void)
{
    clcd_print((unsigned char)" Scroll display ", LINE1(0));
    clcd_print((unsigned char)" Scroll display ", LINE2(0));
}
unsigned long int notpressed=10000;
void logscreen(unsigned char key)
{
        uckey[4]='\0';
        if(enterflag==0)
            clcd_print(" Enter Password ", LINE1(0));
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
                    clcd_putch(key-11+48, LINE2(i+4));
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
                            clcd_putch('_', LINE2(i+4));
                        }
                        else if(blink >= 800)
                        {
                            clcd_putch(' ', LINE2(i+4));
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
                if(!strcmp(uckey, pass))                 
                {
                    enterflag=1;
                    blinkflag=1;
                    clcd_print("                ", LINE1(0));
                    clcd_print("Code Passed  -->", LINE2(0));
                    for(wait=100000; wait--;);
                    controlflag=4;
                }
                else
                {
                    notpressed=10000;
                    enterflag=1;
                     clcd_print(" Wrong Password ", LINE1(0));                
                     clcd_print(" attempt Remains", LINE2(1));
                     tryflag--;
                     clcd_putch(tryflag+48, LINE2(0));
                     for(wait=100000; wait--;);
                     CLEAR_DISP_SCREEN;
                     enterflag=0;
                }               
              }
       }
       else
       {
              enterflag=1;
              clcd_print("Try Again left" , LINE1(0));
              clcd_print("               ", LINE2(0));
              timeleft();
              blink=0, tryflag=4, enterflag=0, compareflag=0,blinkflag=0;
       } 
}
void timeleft()
{  
    CLEAR_DISP_SCREEN;
    min=0;
    TMR0ON=1;
    //sec=60;
    while(sec!=0)
    {
        clcd_print("Try Again left" , LINE1(0));
        clcd_print("Wait for", LINE2(0));
        clcd_print(" s  ", LINE2(11));
        clcd_putch(sec%10+48, LINE2(10));
        clcd_putch(((sec/10)%10)+48, LINE2(9));
       //if(sec==0)
         //  min--;
        
    }
    TMR0ON=0;
    sec=10;
    CLEAR_DISP_SCREEN;
}