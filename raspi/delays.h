/* gk-os */

#ifndef DELAYS_H
#define DELAYS_H

void wait_cycles(unsigned int n);
void wait_msec(unsigned int n);

#define WAIT_WHILE(COND) do {asm volatile("nop");} while(COND)
#define WAIT_UNTIL(COND) do {asm volatile("nop");} while(!(COND))

#endif /* DELAYS_H */
