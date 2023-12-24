#include "timer.h"
#include "tm4c123.h"

#define ST_COUNT_MASK (unsigned long) 0x00010000   // bits PF3-1
#define ST_ENABLE_MASK (unsigned long) 0x000000001   // bits PF3-1
#define ST_SOURCE_MASK (unsigned long) 0x00000004   // bits PF3-1

#define sw_delay 1530           //define delay for switch press

void timer_start(void)
{
    ST_CTRL_R &= ~ST_SOURCE_MASK;
    ST_CTRL_R |= ST_ENABLE_MASK;
}

/*void timer_stop(void)
{
    ST_CTRL_R &= ~ST_ENABLE_MASK;
}*/

int timer_poll(void)
{
    if((ST_CTRL_R & ST_COUNT_MASK) == 0x0)
        return (0);
    else
        return (1);

}

void delay(int ms)
{
    volatile int i;
    while (ms > 0)
    {
        // delay for 1 millisecond
       for(i=0;i<sw_delay;i++)
            ;

        ms--;
    }
    /*int a, b;
    ST_RELOAD_R = TICKS_1MS*ms;
    //timer_start();
    while(a = timer_poll())
        b = ST_CURRENT_R;
    */
    //timer_stop();
}

