/* gk-os

 polled IO

*/

#ifndef KPRINTF_H
#define KPRINTF_H

char kgetc();
void kputc(char);
void kprintf(char *);
void kprintdec(unsigned long);
void kprinthex(unsigned long);
void kprintbits(unsigned long);

#endif /* KPRINTF_H */
