#include "main.h"

char* signature[8]={"ON","GN","G1","G2","G3","G4","GR", "C "};
unsigned char time[9]={0};
unsigned char clock_reg[3]={0};
void display_dashboard(unsigned char uckey, unsigned short usads)
{
    clcd_print( (unsigned char*) "   Time    E  S" , LINE1(0));     //time, event, speed
    //car_animation(); 
    clcd_putch(0x70,LINE1(15));
    display_time();
    gear_monitor(uckey);
    display_speed(usads);
}
void display_time(){
    //clcd_print( TC " 10:00:00", LINE2(0));
     get_time();
	 display_times();
}
void display_times(void)
{
	clcd_print(time, LINE2(2));
}

static void get_time(void)
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
    static char signindex=0, crashflag=0;
    if(uckey == 1)
    {
        crashflag=1;                         //crashed
        signindex=7;                     
    }        
    else if(uckey == 2)                      //increment
    {
        if(signindex < 6)
            signindex++;
        else if(signindex ==7)
        {
            signindex=1;
            crashflag=0;
        }
    } 
    else if(uckey == 3)                       //decrement
    {
          if(crashflag ==0 && signindex > 1)
              signindex--; 
    }
    clcd_putch(signature[signindex][0], LINE2(11));
    clcd_putch(signature[signindex][1], LINE2(12));
}
void display_speed(unsigned short usadc){
        clcd_putch((unsigned char)(usadc/10)%10+48, LINE2(14));
        clcd_putch((unsigned char)usadc%10+48, LINE2(15));

}
