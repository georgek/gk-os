/* gk-os
 *
 * mini-uart
 *
 * */

#ifndef UART_H
#define UART_H

void uart_init();
void uart_send(char c);
char uart_getc();
void uart_puts(char *s);

#endif /* UART_H */
