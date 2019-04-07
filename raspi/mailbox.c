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
#include "delays.h"

/* mailbox registers */
#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
/* mailbox 0 is to RECIEVE from the videocore */
#define MBOX_0_RW       ((unsigned int volatile *)(VIDEOCORE_MBOX+0x0))
#define MBOX_0_PEEK     ((unsigned int volatile *)(VIDEOCORE_MBOX+0x10))
#define MBOX_0_SENDER   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x14))
#define MBOX_0_STATUS   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x18))
#define MBOX_0_CONFIG   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x1C))
/* mailbox 1 is to SEND to the videocore */
#define MBOX_1_RW       ((unsigned int volatile *)(VIDEOCORE_MBOX+0x20))
#define MBOX_1_PEEK     ((unsigned int volatile *)(VIDEOCORE_MBOX+0x30))
#define MBOX_1_SENDER   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x34))
#define MBOX_1_STATUS   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x38))
#define MBOX_1_CONFIG   ((unsigned int volatile *)(VIDEOCORE_MBOX+0x3C))

#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

#define MBOX_PROP_SUCC  0x80000000
#define MBOX_PROP_FAIL  0x80000001

#define MBOX_REQUEST    0


/* static message buffer for mailbox communication */
struct {
     unsigned int buf_size;
     unsigned int req_code;
     unsigned int tags[34];
} volatile __attribute__((aligned(16))) mbox_buf;

sysinfo_t sysinfo;

/* get clock rate of clock */
unsigned int mbox_get_clock_rate(
     unsigned int clock_id
)
{
     mbox_buf.buf_size = 9*4;
     mbox_buf.req_code = MBOX_REQUEST;

     mbox_buf.tags[0] = MBOX_TAG_GETCLKRTE;
     mbox_buf.tags[1] = 2*4;
     mbox_buf.tags[2] = MBOX_REQUEST;
     mbox_buf.tags[3] = clock_id;
     mbox_buf.tags[4] = 0;

     mbox_buf.tags[5] = MBOX_TAG_LAST;

     mailbox_property_call();

     return mbox_buf.tags[4];
}

/* set clock rate of clock */
void mbox_set_clock_rate(
     unsigned int clock_id,
     unsigned int rate,
     int turbo)
{
     mbox_buf.buf_size = 9*4;
     mbox_buf.req_code = MBOX_REQUEST;

     mbox_buf.tags[0] = MBOX_TAG_SETCLKRTE;
     mbox_buf.tags[1] = 3*4;
     mbox_buf.tags[2] = MBOX_REQUEST;
     mbox_buf.tags[3] = clock_id;
     mbox_buf.tags[4] = rate;
     mbox_buf.tags[5] = turbo;

     mbox_buf.tags[6] = MBOX_TAG_LAST;

     mailbox_property_call();
}

/* this returns a variable length string */
char *mbox_cmdline()
{
     int i;
     char *ret;

     mbox_buf.buf_size = 36*4;
     mbox_buf.req_code = MBOX_REQUEST;

     mbox_buf.tags[0] = MBOX_TAG_CMDLINE;
     mbox_buf.tags[1] = 30*4;
     mbox_buf.tags[2] = MBOX_REQUEST;
     /* clear output buffer */
     for (i = 0; i < 30; i++) {
          mbox_buf.tags[3+i] = 0;
     }
     mbox_buf.tags[33] = MBOX_TAG_LAST;

     mailbox_property_call();

     ret = (char *) &mbox_buf.tags[3];
     /* make it's null terminated */
     ret[30*4-1] = '\0';

     return ret;
}

/* get all of the system information in one request */
sysinfo_t *mbox_sysinfo(unsigned int tag)
{
     mbox_buf.buf_size = 35*4;
     mbox_buf.req_code = MBOX_REQUEST;
     /* sequence of tags */
     mbox_buf.tags[0] = MBOX_TAG_VC_FW_REV; /* tag identifier */
     mbox_buf.tags[1] = 4;                  /* value buffer size (bytes) */
     mbox_buf.tags[2] = MBOX_REQUEST;       /* request code */
     mbox_buf.tags[3] = 0;                  /* value buffer */

     mbox_buf.tags[4] = MBOX_TAG_BRD_MODEL;
     mbox_buf.tags[5] = 4;
     mbox_buf.tags[6] = MBOX_REQUEST;
     mbox_buf.tags[7] = 0;

     mbox_buf.tags[8] = MBOX_TAG_BRD_REVSN;
     mbox_buf.tags[9] = 4;
     mbox_buf.tags[10] = MBOX_REQUEST;
     mbox_buf.tags[11] = 0;

     mbox_buf.tags[12] = MBOX_TAG_MAC_ADDRS;
     mbox_buf.tags[13] = 8;
     mbox_buf.tags[14] = MBOX_REQUEST;
     mbox_buf.tags[15] = 0;
     mbox_buf.tags[16] = 0;

     mbox_buf.tags[17] = MBOX_TAG_BRD_SRIAL;
     mbox_buf.tags[18] = 8;
     mbox_buf.tags[19] = MBOX_REQUEST;
     mbox_buf.tags[20] = 0;
     mbox_buf.tags[21] = 0;

     mbox_buf.tags[22] = MBOX_TAG_ARM_MEMRY;
     mbox_buf.tags[23] = 8;
     mbox_buf.tags[24] = MBOX_REQUEST;
     mbox_buf.tags[25] = 0;
     mbox_buf.tags[26] = 0;

     mbox_buf.tags[27] = MBOX_TAG_VC_MEMORY;
     mbox_buf.tags[28] = 8;
     mbox_buf.tags[29] = MBOX_REQUEST;
     mbox_buf.tags[30] = 0;
     mbox_buf.tags[31] = 0;

     mbox_buf.tags[32] = MBOX_TAG_LAST;

     mailbox_property_call();

     sysinfo.vc_fw_rev = mbox_buf.tags[3];
     sysinfo.brd_model = mbox_buf.tags[7];
     sysinfo.brd_rev = mbox_buf.tags[11];
     /* FIXME reverse endian here */
     sysinfo.mac_addr = (((unsigned long) mbox_buf.tags[16]) << 32) | mbox_buf.tags[15];
     sysinfo.brd_serial = (((unsigned long) mbox_buf.tags[21]) << 32) | mbox_buf.tags[20];
     sysinfo.arm_mem_base_addr = mbox_buf.tags[25];
     sysinfo.arm_mem_size = mbox_buf.tags[26];
     sysinfo.vc_mem_base_addr = mbox_buf.tags[30];
     sysinfo.vc_mem_size = mbox_buf.tags[31];
     return &sysinfo;
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
     WAIT_WHILE(*MBOX_1_STATUS & MBOX_FULL);
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
          WAIT_WHILE(*MBOX_0_STATUS & MBOX_EMPTY);
          message = *MBOX_0_RW;
          if ((message & 0xF) == channel) {
               return message;
          }
     }
}
