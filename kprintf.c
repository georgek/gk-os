/* gk-os
 *
 * polled IO
 *
 * */

extern void kputc(char);

void kprinthex(unsigned int d)
{
     unsigned char c;
     int i;

     kputc('0');
     kputc('x');
     for (i = 28; i >= 0; i -= 4) {
          c = (d >> i) & 0xF;
          c += c > 9 ? 0x37 : 0x30;
          kputc(c);
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
