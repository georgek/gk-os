/* gk-os
 *
 * mailbox functions
 */

#ifndef MAILBOX_H
#define MAILBOX_H

unsigned long mbox_req_single_tag();
int mailbox_property_call();
void mailbox_write(unsigned char channel, unsigned int data);
unsigned int mailbox_read(unsigned char channel);

#endif /* MAILBOX_H */
