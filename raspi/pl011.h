/* gk-os
 *
 * PL011 UART stuff
 *
 */

#ifndef PL011_H
#define PL011_H

#include "gpio.h"

/* registers */
#define UART0_DR    ((unsigned int volatile *)(MMIO_BASE+0x00201000))
#define UART0_FR    ((unsigned int volatile *)(MMIO_BASE+0x00201018))
#define UART0_IBRD  ((unsigned int volatile *)(MMIO_BASE+0x00201024))
#define UART0_FBRD  ((unsigned int volatile *)(MMIO_BASE+0x00201028))
#define UART0_LCRH  ((unsigned int volatile *)(MMIO_BASE+0x0020102C))
#define UART0_CR    ((unsigned int volatile *)(MMIO_BASE+0x00201030))
#define UART0_IMSC  ((unsigned int volatile *)(MMIO_BASE+0x00201038))
#define UART0_ICR   ((unsigned int volatile *)(MMIO_BASE+0x00201044))

#endif /* PL011_H */
