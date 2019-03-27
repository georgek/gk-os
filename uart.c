/* gk-os
 *
 * mini-uart
 *
 * */

#include "gpio.h"
#include "aux.h"

void uart_init()
{
     register unsigned int r;

     /* initialise mini-uart */
     *AUX_ENABLE |= 1;
     *AUX_MU_CNTL = 0;          /* disable Tx, Rx */
     *AUX_MU_LCR = 3;           /* 8 bits */
     *AUX_MU_MCR = 0;
     *AUX_MU_IER = 0;           /* disable interrupts */
     *AUX_MU_IIR = 0xC6;        /* clear Tx, Rx FIFOs */
     *AUX_MU_BAUD = 270;        /* 115200 baud */
     /* enable mini-uart on GPIO pins 14 and 15 */
     r = *GPFSEL1;
     r &= ~((7<<12) | (7<<15)); /* reset gpio 14, 15 modes */
     r |=   (2<<12) | (2<<15);  /* set gpio 14, 15 to alt5 */
     *GPFSEL1 = r;
     *GPPUD = 0;                /* disable pull up/down... */
     for (r = 150; r > 0; r--) {
          asm volatile("nop");
     }
     *GPPUDCLK0 = (1<<14)|(1<<15); /* ...for pins 14, 15 */
     for (r = 150; r > 0; r--) {
          asm volatile("nop");
     }
     *GPPUDCLK0 = 0;            /* flush GPIO setup */
     *AUX_MU_CNTL = 3;          /* enable Tx, Rx */
}

void uart_send(char c)
{
     /* wait to send */
     do {
          asm volatile("nop");
     } while(!(*AUX_MU_LSR & 0x20));
     *AUX_MU_IO = (unsigned int) c;
}

char uart_getc()
{
     char c;
     /* wait until something is in buffer */
     do {
          asm volatile("nop");
     } while(!(*AUX_MU_LSR & 0x01));
     c = (char)(*AUX_MU_IO);
     /* convert carriage return to newline */
     return c == '\r' ? '\n' : c;
}

void uart_puts(char *s)
{
     while (*s) {
          /* convert lf to crlf */
          if (*s == '\n') {
               uart_send('\r');
          }
          uart_send(*s++);
     }
}
