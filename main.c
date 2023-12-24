#include "tm4c123.h"
#include "sw.h"
#include "led.h"
#include "timer.h"


int n=1, led=0, m=0, i=1, led_status=1;

int main(void)
{

    sw_init();
    led_init();

    timer_start();

    ST_RELOAD_R = TICKS_1MS*250;

    while(1)
    {

        if(sw_get()&0x10)                       // if SW1 is pressed
        {
            delay(150);                         // account for button de-press delay
            n=n%4+1;                            // change speed multiplier
            ST_RELOAD_R = TICKS_1MS*250*n;      // set systick reload value accordingly
            ST_CURRENT_R = 0x1;                 // simulate an interrupt by making timer_poll() = true
        }

        if(sw_get()&0x01)                       // if SW2 is pressed
        {
            delay(150);                         // account for button de-press delay
            m=(m+1)%5;                          // change switch case for blink pattern
            ST_CURRENT_R = 0x1;                 // simulate an interrupt by making timer_poll() = true
        }

        //delay(250*n);                   // wait

        if (timer_poll())                       // if systick counter reaches down to 0
        {

            switch (m)
            {
            case 0:                                     // all colours cycle (0,2,4,...)

                led_on(led);
                led=(led+2)%16;                         // update 'led'
                break;

            case 1:                                     // colours blink (2, off, 4, off ...)

                if (led == 0)
                    led = 2;
                if (led_status)
                    led_on(led);
                else
                    {
                        led_off(0x0E);
                        led=(led+2)%16;                         // update 'led'
                    }
                led_status = (led_status+1)%2;
                break;

            case 2:                                      // RGBRGBRGB...

                led_on(1 << i);
                i=(i+1)%3+1;                            // update 'i'
                break;

            case 3:                                      // R off G off B off ...

                if (led_status)
                    led_on(1 << i);
                else
                    led_off(0x0E);
                led_status = (led_status+1)%2;
                i=(i)%3+1;                              // update 'i'
                break;

            case 4:                                      // R off R off G off G off B off B off ...

                if ((led_status%2) != 0)
                    led_on(1 << i);
                else
                    led_off(0x0E);
                led_status = (led_status+1)%4;
                if (led_status == 0)
                    i=(i+1)%3+1;                            // update 'i'
                break;

            }


            //led=(led+2)%16;                         // update 'led'

        }


    }
}

