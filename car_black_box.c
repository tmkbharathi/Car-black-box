#include "main.h"

char* signature[8]={"ON","GN","G1","G2","G3","G4","GR", "C "};
unsigned char time[9]={0};
unsigned char clock_reg[3]={0};
unsigned int controlflag;
char signindex=0;
void display_dashboard(unsigned char uckey, unsigned short usads)
{
    clcd_print( (unsigned char*) "   Time    E  S" , LINE1(0));     //time, event, speed
    clcd_putch(0x70,LINE1(15));                                     //Character p in CGRAM
    if(uckey == 10)
        {
            controlflag=0;
            CLEAR_DISP_SCREEN;
            return;
        }
    display_time();
    display_speed(usads);
}
void display_time(){
     get_time();
	 display_times();
     clcd_putch(signature[signindex][0], LINE2(11));
     clcd_putch(signature[signindex][1], LINE2(12));
}
void display_times(void)
{
	clcd_print(time, LINE2(2));
}

void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}
void gear_monitor(unsigned char uckey){
    static unsigned char crashflag=0, prekey=0xFF;
    static long int delay=0;
    if(uckey==1 || uckey==2 || uckey==3)
    {
        delay++;
        prekey=uckey;
        if(delay>4000)
            delay=0;
    }
    else if(delay!=0)
    {
        if(prekey == 1)
        {
            crashflag=1;                         //crashed
            signindex=7;                     
        }        
        else if(prekey == 2)                      //increment
        {
            if(signindex < 6)
                signindex++;
            else if(signindex ==7)
            {
                signindex=1;
                crashflag=0;
            }
        } 
        else if(prekey == 3)                       //decrement
        {
              if(crashflag ==0 && signindex > 1)
                  signindex--; 
        }
        prekey=0xFF;
    }
}
void display_speed(unsigned short usadc){
        clcd_putch((unsigned char)(usadc/10)%10+48, LINE2(14));
        clcd_putch((unsigned char)usadc%10+48, LINE2(15));

}
