#include "main.h"

char *scrolling[5]={"   view    log   ", "   download  log  ", "  clear   log  ", "  set   time  ", "  change password  "};
void scrolllog(void)
{
    clcd_print( TC " Scroll display ", LINE1(0));
    clcd_print( TC " Scroll display ", LINE2(0));
}