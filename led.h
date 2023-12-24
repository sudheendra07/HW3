#ifndef LED_H
#define LED_H

#define LED_RED     (1 << 1)
#define LED_BLUE    (1 << 2)
#define LED_GREEN   (1 << 3)

extern void led_init(void);
extern void led_on(unsigned long led_mask);
extern void led_off(unsigned long led_mask);
extern void led_toggle(unsigned long led_mask);

#endif /* LED_H */
