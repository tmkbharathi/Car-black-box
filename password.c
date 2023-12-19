#include "main.h"
//char *scrolling[5]={"   view    log   ", "   download  log  ", "  clear   log  ", "  set   time  ", "  change password  "};
char uckey[5];
unsigned long int wait=0;
unsigned char i=0;
unsigned char blink=0, tryflag=5, enterflag=0, compareflag=0;
unsigned int blinkflag=0;
char pass[5]="1100";
void scrolllog(void)
{
    clcd_print((unsigned char)" Scroll display ", LINE1(0));
    clcd_print((unsigned char)" Scroll display ", LINE2(0));
}
void logscreen(unsigned char key)
{
        uckey[4]='\0';
        if(enterflag==0)
        {
            clcd_print(" Enter Password ", LINE1(0));
        }
        if(tryflag!=0)
        {
             if(i<4)
             {
                compareflag=0;   
                if ((key != 0xFF) && key != 10)
                {
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
                    clcd_print(" Excellent  you ", LINE1(0));
                    clcd_print("cracked the code", LINE2(0));
                }
                else
                {
                     enterflag=1;
                     clcd_print(" Wrong Password ", LINE1(0));                
                     clcd_print(" attempt Remains", LINE2(1));
                     tryflag--;
                     clcd_putch(tryflag+48, LINE2(0));
                     for(wait=1000000; wait--;);
                     CLEAR_DISP_SCREEN;
                     enterflag=0;
                }               
              }
       }
       else
       {
              CLEAR_DISP_SCREEN;
              enterflag=1;
              clcd_print("Chances Exausted", LINE1(0));
              clcd_print("Reset the Board", LINE2(0));
       } 
}
