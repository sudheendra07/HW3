#ifndef TIMER_H
#define TIMER_H

#define TICKS_1MS 3999  // tweak this number to get 1ms delay

/* provide a delay of 1 ms */
extern void delay(int ms);

void sw_init(void);

void timer_start(void);

void timer_stop(void);

int timer_poll(void);

#endif  /* TIMER_H */
