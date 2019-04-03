/* gk-os
 *
 * mini-uart
 *
 * */

#include "aux.h"

void kputc(char c)
{
     /* wait to send */
     do {
          asm volatile("nop");
     } while(!(*AUX_MU_LSR & 0x20));
     *AUX_MU_IO = (unsigned int) c;
}
