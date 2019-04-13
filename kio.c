/* gk-os
 *
 * polled IO
 *
 * */

#include "kio.h"

extern void kputc(char);

/* a 64 bit word can be 19 decimal digits */
static char dec_buf[19];

void kprintdec(unsigned long d)
{
     int i;
     if (d == 0) {
          kputc('0');
          return;
     }
     /* fill buffer right to left */
     for (i = 18; i >= 0; --i) {
          dec_buf[i] = d % 10;
          d = d/10;
     }
     /* skip leading zeros */
     for (i = 0; i < 19 && dec_buf[i] == 0; ++i);
     /* print left to right */
     for ( ; i < 19; ++i) {
          kputc('0' + dec_buf[i]);
     }
}

void kprinthex(unsigned long d)
{
     unsigned char c;
     int i;

     kprintf("0x");
     if (d == 0) {
          kputc('0');
          return;
     }
     /* skip leading zeros */
     for (i = 60; i >= 0 && ((d >> i) & 0xF) == 0; i -= 4);
     /* print left to right */
     for ( ; i >= 0; i -= 4) {
          c = (d >> i) & 0xF;
          c += c > 9 ? 0x37 : 0x30;
          kputc(c);
     }
}

void kprintbits(unsigned long d)
{
     int i;
     unsigned long m;

     for (i = 63; i >= 0; i--) {
          kputc('0' + i/10);
     }
     kputc('\n');
     kputc('\r');
     for (i = 63; i >= 0; i--) {
          kputc('0' + i%10);
     }
     kputc('\n');
     kputc('\r');
     for (m = 1l << 63; m != 0; m >>= 1) {
          kputc(d & m ? '1' : '0');
     }
}

/* very basic printf that uses polled IO */
void kprintf(char *s)
{
     /* TODO disable interrupts? */
     while (*s) {
          /* convert lf to crlf */
          if (*s == '\n') {
               kputc('\r');
          }
          kputc(*s++);
     }
}
