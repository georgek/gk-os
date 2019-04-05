/* gk-os

 mailboxes are used to communicate with the videocore

 there are two mailbox, 0 and 1. 0 is for the VC to write and ARM to read, and
 1 is for the ARM to write the VC to read. Each mailbox is a queue of 8 32-bit
 words.

 Mailbox messages consist of a 4-bit channel (in the lower 4 bits) and a
 28-bit message (in the upper 28 bits).

 When an address of a buffer is sent via a mailbox the buffer must be 16-byte
 aligned because only the top 28-bits of the address are sent. Other messages
 can be 28 bits and shifted into the top bits.

*/

#include "gpio.h"
#include "mailbox.h"

/* mailbox registers */
#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
/* mailbox 0 is to RECIEVE from the videocore */
#define MBOX_0_RW       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x0))
#define MBOX_0_PEEK     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x10))
#define MBOX_0_SENDER   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x14))
#define MBOX_0_STATUS   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x18))
#define MBOX_0_CONFIG   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x1C))
/* mailbox 1 is to SEND to the videocore */
#define MBOX_1_RW       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x20))
#define MBOX_1_PEEK     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x30))
#define MBOX_1_SENDER   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x34))
#define MBOX_1_STATUS   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x38))
#define MBOX_1_CONFIG   ((volatile unsigned int*)(VIDEOCORE_MBOX+0x3C))

#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

#define MBOX_PROP_SUCC  0x80000000
#define MBOX_PROP_FAIL  0x80000001

#define MBOX_REQUEST    0

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_GETSERIAL      0x10004
#define MBOX_TAG_LAST           0



/* static message buffer for mailbox communication */
struct {
     unsigned int buf_size;
     unsigned int req_code;
     unsigned int tags[34];
} volatile __attribute__((aligned(16))) mbox_buf;


unsigned long mbox_req_single_tag(unsigned int tag)
{
     unsigned long ret;

     mbox_buf.buf_size = 8*4;
     mbox_buf.req_code = MBOX_REQUEST;
     /* sequence of tags */
     mbox_buf.tags[0] = MBOX_TAG_GETSERIAL; /* tag identifier */
     mbox_buf.tags[1] = 8;                  /* value buffer size (bytes) */
     mbox_buf.tags[2] = 0;                  /* request code */
     mbox_buf.tags[3] = 0;                  /* value buffer */
     mbox_buf.tags[4] = 0;
     mbox_buf.tags[5] = MBOX_TAG_LAST;

     mailbox_property_call();

     ret = (((unsigned long) mbox_buf.tags[4]) << 32) | mbox_buf.tags[3];
     return ret;
}

/* mailbox property call
 *
 * assumes that mailbox_buffer already contains a valid property request
 */
int mailbox_property_call()
{
     unsigned int message;
     mailbox_write(MBOX_CH_PROP, (unsigned long) &mbox_buf);
     while (1) {
          message = mailbox_read(MBOX_CH_PROP);
          /* if this is our response the returned value will be the same */
          if ((message & ~0xF) == (((unsigned long) &mbox_buf) & ~0xF)) {
               /* check if the request was successful */
               return mbox_buf.req_code == MBOX_PROP_SUCC;
          }
     }
}

/* write a message into the mailbox
 *
 * the data must already be shifted into position; the lower 4 bits will be
 * lost
 */
void mailbox_write(unsigned char channel, unsigned int data)
{
     unsigned int message = channel & 0xF;
     message |= data & ~0xF;

     /* wait until mailbox is not full */
     while (*MBOX_1_STATUS & MBOX_FULL) {
          asm volatile("nop");
     }
     *MBOX_1_RW = message;
}

/* read a message from the mailbox
 *
 * a message of the desired channel will be returned. The whole message is
 * returned, not just the data
 */
unsigned int mailbox_read(unsigned char channel)
{
     unsigned int message;
     /* keep reading until we get a message on the desired channel */
     while (1) {
          while (*MBOX_0_STATUS & MBOX_EMPTY) {
               asm volatile("nop");
          }
          message = *MBOX_0_RW;
          if ((message & 0xF) == channel) {
               return message;
          }
     }
}
