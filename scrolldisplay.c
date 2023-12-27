#include "main.h"
char *scrolling[5]={"View log     ", "Download log ", "Clear log    ", "Set time     ", "Change Pass  "};
char logg=0;
char star=1;
int k=0, p=0;
char mpos=0;
//char log[11];
int press=0;
extern unsigned int controlflag;
#define LONG_PRESS_THRESHOLD 2000 // Define the threshold for a long press (adjust as needed)

void scrolllog(unsigned char key, unsigned char keys) {
    static unsigned int out = 0;
    static unsigned int longPressTimer = 0;
    static char longPressActive = 0;

    if (keys == 12) {
        if (out++ == 4000) {
            out = 0;
            controlflag = 1;
            CLEAR_DISP_SCREEN;
            return;
        }
        longPressTimer++;
        if (longPressTimer >= LONG_PRESS_THRESHOLD) {
            longPressActive = 1;
            longPressTimer = 0; // Reset the timer after detecting long press
        }
    } else {
        longPressActive = 0; // Reset long press flag if the button is released
        longPressTimer = 0; // Reset the timer
    }

    if (press == 0) {
        clcd_putch('*', LINE1(1));
        clcd_print(TC scrolling[logg], LINE1(3));
        clcd_print(TC scrolling[logg + 1], LINE2(3));
    }

    if ((key == 12) && (logg < 3)) {
        CLEAR_DISP_SCREEN;
        logg++; 
        press = 1;
        clcd_putch('*', LINE2(1));
        clcd_print(TC scrolling[logg - 1], LINE1(3));
        clcd_print(TC scrolling[logg], LINE2(3));
    } else if ((key == 11) && (logg >= 1)) {
        CLEAR_DISP_SCREEN;
        logg--;
        press = 1;
        clcd_putch('*', LINE1(1));
        clcd_print(TC scrolling[logg], LINE1(3));
        clcd_print(TC scrolling[logg + 1], LINE2(3));
    } else if (longPressActive && (key == 11) && (logg == 1)) {
        CLEAR_DISP_SCREEN;
        logg = 0;
        press = 1;
        clcd_putch('*', LINE1(1));
        clcd_print(TC scrolling[logg], LINE1(3));
        clcd_print(TC scrolling[logg + 1], LINE2(3));
    }
}
 /*void view_log(unsigned char key,unsigned char reset_flag)
{
    char rlog[11];
    unsigned char add;
    static unsigned char rpos;
    if(event_count ==-1)
    {
        clcd_print(" No logs",LINE2(0));
    }
    else
    {
        if (reset_flag==VIEW_LOG_RESET)
        {
            rpos=0;
        }
        if(key==SW5 && rpos< (event_count-1))
        {
            rpos++;
        }
        else if(key==SW4 && rpos > 0)
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
}     *//*
void log_event()
{
    unsigned char add;
    pos++;
    if(pos==10)
    {
        pos=0;
    }
    add=pos*10+5;
    for(int i=0;log[i]!='\0';i++)
    {
        eeprom_write(add,log[i]);
        add++;
    }
    if(event_count<9)
        event_count++;
}

void log_car_event(char event[], unsigned char speed)
{
    get_time();
    strncpy(log, time, 6);
    strncpy(&log[6], event, 2);
    log[8] = (speed/10)+'0';
    log[9] = (speed%10)+'0';
    log[10] = '\0';
    log_event();
}*/