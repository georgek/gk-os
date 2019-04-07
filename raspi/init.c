/* gk-os

 does basic initialisation for raspberry pi

*/

#include "gpio.h"
#include "aux.h"
#include "mailbox.h"
#include "pl011.h"
#include "delays.h"

/* initialise the PL011 uart and set GPIO pins 14 and 15 to use it */
void uart0_init()
{
     register unsigned int r;

     *UART0_CR = 0;             /* disable uart */

     mbox_set_clock_rate(MBOX_CLK_UART, 4000000, 0);

     /* enable pl011 on GPIO pins 14 and 15 */
     r = *GPFSEL1;
     r &= ~((7<<12) | (7<<15)); /* reset gpio 14, 15 modes */
     r |=   (4<<12) | (4<<15);  /* set gpio 14, 15 to alt0 */
     *GPFSEL1 = r;
     *GPPUD = 0;                /* disable pull up/down... */
     wait_cycles(150);
     *GPPUDCLK0 = (1<<14)|(1<<15); /* ...for pins 14, 15 */
     wait_cycles(150);
     *GPPUDCLK0 = 0;            /* flush GPIO setup */

     *UART0_ICR = 0x7E0;        /* clear interrupts */
     *UART0_IBRD = 2;           /* 115200 baud */
     *UART0_FBRD = 0xB;
     *UART0_LCRH = 0x70;        /* 8 bit, fifos */
     *UART0_CR = 0x301;         /* enable Tx, Rx, UART */
}

/* initialise the mini-uart and set GPIO pins 14 and 15 to use it */
void uart1_init()
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
     wait_cycles(150);
     *GPPUDCLK0 = (1<<14)|(1<<15); /* ...for pins 14, 15 */
     wait_cycles(150);
     *GPPUDCLK0 = 0;            /* flush GPIO setup */
     *AUX_MU_CNTL = 3;          /* enable Tx, Rx */
}

void init()
{
     uart0_init();
}
