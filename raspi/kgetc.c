/* gk-os
 *
 * mini-uart
 *
 * */

#include "aux.h"

char kgetc()
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
