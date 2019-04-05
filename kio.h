/* gk-os

 polled IO

*/

#ifndef KPRINTF_H
#define KPRINTF_H

char kgetc();
void kputc(char);
void kprintf(char *);
void kprinthex(unsigned long);

#endif /* KPRINTF_H */
