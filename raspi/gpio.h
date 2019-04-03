/* gk-os
 *
 * GPIO registers
 *
 * BCM2835 S6.1
 *
 */

#ifndef GPIO_H
#define GPIO_H

#define MMIO_BASE    0x3F000000

#define GPFSEL0      ((unsigned int volatile *)(MMIO_BASE+0x00200000))
#define GPFSEL1      ((unsigned int volatile *)(MMIO_BASE+0x00200004))
#define GPFSEL2      ((unsigned int volatile *)(MMIO_BASE+0x00200008))
#define GPFSEL3      ((unsigned int volatile *)(MMIO_BASE+0x0020000C))
#define GPFSEL4      ((unsigned int volatile *)(MMIO_BASE+0x00200010))
#define GPFSEL5      ((unsigned int volatile *)(MMIO_BASE+0x00200014))

#define GPSET0       ((unsigned int volatile *)(MMIO_BASE+0x0020001C))
#define GPSET1       ((unsigned int volatile *)(MMIO_BASE+0x00200020))

#define GPCLR0       ((unsigned int volatile *)(MMIO_BASE+0x00200028))
#define GPCLR1       ((unsigned int volatile *)(MMIO_BASE+0x0020002C))

#define GPLEV0       ((unsigned int volatile *)(MMIO_BASE+0x00200034))
#define GPLEV1       ((unsigned int volatile *)(MMIO_BASE+0x00200038))

#define GPEDS0       ((unsigned int volatile *)(MMIO_BASE+0x00200040))
#define GPEDS1       ((unsigned int volatile *)(MMIO_BASE+0x00200044))

#define GPREN0       ((unsigned int volatile *)(MMIO_BASE+0x0020004C))
#define GPREN1       ((unsigned int volatile *)(MMIO_BASE+0x00200050))

#define GPFEN0       ((unsigned int volatile *)(MMIO_BASE+0x00200058))
#define GPFEN1       ((unsigned int volatile *)(MMIO_BASE+0x0020005C))

#define GPHEN0       ((unsigned int volatile *)(MMIO_BASE+0x00200064))
#define GPHEN1       ((unsigned int volatile *)(MMIO_BASE+0x00200068))

#define GPLEN0       ((unsigned int volatile *)(MMIO_BASE+0x00200070))
#define GPLEN1       ((unsigned int volatile *)(MMIO_BASE+0x00200074))

#define GPAREN0      ((unsigned int volatile *)(MMIO_BASE+0x0020007C))
#define GPAREN1      ((unsigned int volatile *)(MMIO_BASE+0x00200080))

#define GPAFEN0      ((unsigned int volatile *)(MMIO_BASE+0x00200088))
#define GPAFEN1      ((unsigned int volatile *)(MMIO_BASE+0x0020008C))

#define GPPUD        ((unsigned int volatile *)(MMIO_BASE+0x00200094))
#define GPPUDCLK0    ((unsigned int volatile *)(MMIO_BASE+0x00200098))
#define GPPUDCLK1    ((unsigned int volatile *)(MMIO_BASE+0x0020009C))

#endif /* GPIO_H */
