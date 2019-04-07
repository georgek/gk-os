/* gk-os */

#ifndef DELAYS_H
#define DELAYS_H

void wait_cycles(unsigned int n);
unsigned long get_system_time();

#define WAIT_WHILE(COND) do {asm volatile("nop");} while(COND)
#define WAIT_UNTIL(COND) do {asm volatile("nop");} while(!(COND))

#endif /* DELAYS_H */
