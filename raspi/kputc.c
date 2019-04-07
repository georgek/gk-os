/* gk-os
 *
 * mini-uart
 *
 * */

#include "aux.h"
#include "pl011.h"
#include "delays.h"

void uart0_putc(char c)
{
     /* wait to send */
     WAIT_WHILE(*UART0_FR & 0x20);
     *UART0_DR = (unsigned int) c;
}

void uart1_putc(char c)
{
     /* wait to send */
     WAIT_UNTIL(*AUX_MU_LSR & 0x20);
     *AUX_MU_IO = (unsigned int) c;
}

void kputc(char c)
{
     uart0_putc(c);
}
