#include "tm4C123.h"
#include "sw.h"

#define SW_MASK (unsigned long) 0x11    // bits PF4,0
#define SW_MASK_PCTL 0x000F000FUL       // 4 bits for PF4,0

void sw_init(void)
{
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x00000020;    // F clock
    delay = SYSCTL_RCGC2_R;          // reading register adds a delay

    GPIO_PORTF_LOCK_R = 0x4C4F434B;       // unlock PortF
    GPIO_PORTF_CR_R |= 0x11;                 // allow changes to PF0 and PF4 (table 10.7 TRM)
    //GPIO_PORTF_LOCK_R = 0;                // lock PortF

    GPIO_PORTF_AFSEL_R &= ~SW_MASK;       // no alternate function
    GPIO_PORTF_PCTL_R &= ~SW_MASK_PCTL;   // clear bits to specify GPIO
    GPIO_PORTF_AMSEL_R &= ~SW_MASK;       // disable analog function
    GPIO_PORTF_DIR_R |= ~SW_MASK;         // clear bits to specify input
    GPIO_PORTF_PUR_R |= SW_MASK;          // enable internal pull-up resister
    GPIO_PORTF_DEN_R |= SW_MASK;          // enable digital pins


    return;
}

unsigned long sw_get(void)
{
    // return 1's complement (on = 1, off = 0)
    return ~(GPIO_PORTF_DATA_R & SW_MASK);
}
