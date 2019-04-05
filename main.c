/* gk-os */

#include "kio.h"
#include "raspi/mailbox.h"

/* this function does any hardware initialisation */
extern void init();

void vanity()
{
     kprintf("\n"
"       _\n"
"  __ _| | __      ___  ___\n"
" / _` | |/ /____ / _ \\/ __|\n"
"| (_| |   <_____| (_) \\__ \\\n"
" \\__, |_|\\_\\     \\___/|___/\n"
" |___/\n\n");
}

void main()
{
     unsigned long serial;
     init();

     vanity();

     serial = mbox_req_single_tag();

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
