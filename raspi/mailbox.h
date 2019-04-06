/* gk-os
 *
 * mailbox functions
 */

#ifndef MAILBOX_H
#define MAILBOX_H

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

/* property tags */
#define MBOX_TAG_VC_FW_REV      0x00001
#define MBOX_TAG_BRD_MODEL      0x10001
#define MBOX_TAG_BRD_REVSN      0x10002
#define MBOX_TAG_MAC_ADDRS      0x10003
#define MBOX_TAG_BRD_SRIAL      0x10004
#define MBOX_TAG_ARM_MEMRY      0x10005
#define MBOX_TAG_VC_MEMORY      0x10006
#define MBOX_TAG_CMDLINE        0x50001
#define MBOX_TAG_LAST           0

typedef struct {
     unsigned int vc_fw_rev;
     unsigned int brd_model;
     unsigned int brd_rev;
     unsigned long mac_addr;
     unsigned long brd_serial;
     unsigned int arm_mem_base_addr;
     unsigned int arm_mem_size;
     unsigned int vc_mem_base_addr;
     unsigned int vc_mem_size;
} sysinfo_t;

char *mbox_cmdline();
sysinfo_t *mbox_sysinfo();
int mailbox_property_call();
void mailbox_write(unsigned char channel, unsigned int data);
unsigned int mailbox_read(unsigned char channel);



#endif /* MAILBOX_H */
