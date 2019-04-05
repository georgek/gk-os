/* gk-os */

#include "kio.h"
#include "raspi/mailbox.h"

/* this function does any hardware initialisation */
extern void init();

void main()
{
     unsigned long serial;
     init();

     serial = mbox_get_serial_number();

     kprintf("Hello, world\n");

     kprintf("My serial number:\n");
     kprinthex(serial);
     kprintf("\n");

     kprintf("unsigned short:\n");
     kprinthex(sizeof(unsigned short));
     kprintf("\n");

     kprintf("unsigned int:\n");
     kprinthex(sizeof(unsigned int));
     kprintf("\n");

     kprintf("unsigned long:\n");
     kprinthex(sizeof(unsigned long));
     kprintf("\n");

     while(1) {
          kputc(kgetc());
     }
}
