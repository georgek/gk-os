/* gk-os
 *
 * AUX peripherals registers
 *
 * BCM2835 S2.1
 *
 * */

#ifndef AUX_H
#define AUX_H

#include "gpio.h"

#define AUX_IRQ         ((unsigned int volatile *)(MMIO_BASE+0x00215000))
#define AUX_ENABLE      ((unsigned int volatile *)(MMIO_BASE+0x00215004))

#define AUX_MU_IO       ((unsigned int volatile *)(MMIO_BASE+0x00215040))
#define AUX_MU_IER      ((unsigned int volatile *)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR      ((unsigned int volatile *)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR      ((unsigned int volatile *)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR      ((unsigned int volatile *)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR      ((unsigned int volatile *)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR      ((unsigned int volatile *)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((unsigned int volatile *)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL     ((unsigned int volatile *)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT     ((unsigned int volatile *)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD     ((unsigned int volatile *)(MMIO_BASE+0x00215068))

#define AUX_SPI1_CNTL0  ((unsigned int volatile *)(MMIO_BASE+0x00215080))
#define AUX_SPI1_CNTL1  ((unsigned int volatile *)(MMIO_BASE+0x00215084))
#define AUX_SPI1_STAT   ((unsigned int volatile *)(MMIO_BASE+0x00215088))
#define AUX_SPI1_IO     ((unsigned int volatile *)(MMIO_BASE+0x00215090))
#define AUX_SPI1_PEEK   ((unsigned int volatile *)(MMIO_BASE+0x00215094))

#define AUX_SPI2_CNTL0  ((unsigned int volatile *)(MMIO_BASE+0x002150C0))
#define AUX_SPI2_CNTL1  ((unsigned int volatile *)(MMIO_BASE+0x002150C4))
#define AUX_SPI2_STAT   ((unsigned int volatile *)(MMIO_BASE+0x002150C8))
#define AUX_SPI2_IO     ((unsigned int volatile *)(MMIO_BASE+0x002150D0))
#define AUX_SPI2_PEEK   ((unsigned int volatile *)(MMIO_BASE+0x002150D4))

#endif /* AUX_H */
