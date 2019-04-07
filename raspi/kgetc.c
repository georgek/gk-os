/* gk-os
 *
 * mini-uart
 *
 * */

#include "aux.h"
#include "pl011.h"
#include "delays.h"

char uart0_getc()
{
     char c;
     WAIT_WHILE(*UART0_FR & 0x10);
     c = (char)(*UART0_DR);
     /* convert carriage return to newline */
     return c == '\r' ? '\n' : c;
}

char uart1_getc()
{
     char c;
     WAIT_UNTIL(*AUX_MU_LSR & 0x01);
     c = (char)(*AUX_MU_IO);
     /* convert carriage return to newline */
     return c == '\r' ? '\n' : c;
}

char kgetc()
{
     return uart0_getc();
}
