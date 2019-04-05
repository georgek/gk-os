/* gk-os
 *
 * mailbox functions
 */

#ifndef MAILBOX_H
#define MAILBOX_H

extern unsigned int volatile __attribute__((aligned(16))) mailbox_buffer[36];

unsigned long mbox_get_serial_number();
int mailbox_property_call();
void mailbox_write(unsigned char channel, unsigned int data);
unsigned int mailbox_read(unsigned char channel);

#endif /* MAILBOX_H */
