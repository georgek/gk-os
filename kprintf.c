/* gk-os
 *
 * polled IO
 *
 * */

extern void kputc(char);

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
