/* gk-os */

#include "gpio.h"
#include "delays.h"

#define SYSTMR_LO ((unsigned int volatile *)(MMIO_BASE+0x00003004))
#define SYSTMR_HI ((unsigned int volatile *)(MMIO_BASE+0x00003008))

unsigned long get_system_time()
{
     unsigned int hi, lo;
     hi = *SYSTMR_HI;
     lo = *SYSTMR_LO;
     /* most significant half could have ticked over between reads */
     if (hi != *SYSTMR_HI) {
          hi = *SYSTMR_HI;
          lo = *SYSTMR_LO;
     }
     return ((unsigned long) hi << 32) | lo;
}
