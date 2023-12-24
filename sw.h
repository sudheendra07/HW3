#ifndef SW_H
#define SW_H

#define SW1 (1 << 4)
#define SW2 (1 << 0)

/* initialize ports for switches */
void sw_init(void);

/* get the status of switches
 *
 * returns a bitfield with one bit for each switch.
 *      bit set = switch is on
 *      bit clear = switch is off
 *
 * example usage:
 *
 *  sw = sw_get();
 *  if (sw & SW1)
 *      ; SW1 is on
 *  if (sw & SW2)
 *      ; SW2 is on
 */
unsigned long sw_get(void);

#endif /* SW_H */
