/* gk-os
 *
 * mini-uart
 *
 * */

#include "aux.h"
#include "pl011.h"

void uart0_putc(char c)
{
     /* wait to send */
     do {
          asm volatile("nop");
     } while(*UART0_FR & 0x20);
     *UART0_DR = (unsigned int) c;
}

void uart1_putc(char c)
{
     /* wait to send */
     do {
          asm volatile("nop");
     } while(!(*AUX_MU_LSR & 0x20));
     *AUX_MU_IO = (unsigned int) c;
}

void kputc(char c)
{
     uart0_putc(c);
}
