#include"main.h"

void init_animation(void)
{
    char firsthalfcar[8] = { 0x00, 0x07, 0x04, 0x0E, 0x1F, 0x04, 0x00,0x00};
    char secondhalfcar[8] = { 0x00, 0x1C, 0x04, 0x0E, 0x1F, 0x04, 0x00,0x00};
    char m[8]={0x00, 0x03, 0x07, 0x1F, 0x1F, 0x1F, 0x0C, 0x00};
    char n[8]={0x00, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x0C, 0x00};
    
    clcd_write(0x40,0);
    for (int i=0; i<8; i++) 
        clcd_write(firsthalfcar[i],1);
    clcd_write(0x48,0);
    for (int i=0; i<8; i++) 
        clcd_write(secondhalfcar[i],1);
        clcd_write(0x50,0);
    for (int i=0; i<8; i++) 
        clcd_write(m[i],1);
    clcd_write(0x58,0);
    for (int i=0; i<8; i++) 
        clcd_write(n[i],1);
}

void car_animation(void)
{
        clcd_putch( 0x03, LINE1(1));
        clcd_putch( 0x02, LINE1(0));
        clcd_putch( 0x01, LINE2(1));
        clcd_putch( 0x00, LINE2(0));
    
}
