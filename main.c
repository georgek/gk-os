/* gk-os */

#include "kio.h"

/* this function does any hardware initialisation */
extern void init();

void main()
{
     init();

     kprintf("Hello, world... I did things\n");

     while(1) {
          kputc(kgetc());
     }
}
