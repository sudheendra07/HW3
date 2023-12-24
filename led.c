#include "tm4C123.h"
#include "led.h"

#define LED_MASK (unsigned long) 0x0E   // bits PF3-1
#define LED_MASK_PCTL 0x0000FFF0UL      // 4 bits for PF3-1

void led_init(void)
{
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x00000020;       // F clock
    delay = SYSCTL_RCGC2_R;             // reading register adds a delay

    GPIO_PORTF_AFSEL_R &= ~LED_MASK;          // no alternate function
    GPIO_PORTF_PCTL_R &= ~LED_MASK_PCTL;      // clear bits to specify GPIO
    GPIO_PORTF_AMSEL_R &= ~LED_MASK;          // disable analog function
    GPIO_PORTF_DIR_R |= LED_MASK;             // set bits to specify output
    GPIO_PORTF_DEN_R |= LED_MASK;             // enable digital pins
}

void led_on(unsigned long led_mask)
{
    GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~LED_MASK) + led_mask;
}

void led_off(unsigned long led_mask)
{
    GPIO_PORTF_DATA_R &= ~led_mask;
}

void led_toggle(unsigned long led_mask)
{

    if (GPIO_PORTF_DATA_R & LED_MASK != led_mask)
        GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~LED_MASK) + led_mask;
    else
        GPIO_PORTF_DATA_R &= ~led_mask;

}

