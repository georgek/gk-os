/* gk-os */

#include "kio.h"
#include "raspi/mailbox.h"
#include "raspi/delays.h"
#include "scheduler.h"

/* this function does any hardware initialisation */
extern void init();

void vanity()
{
     kprintf(
"       _\n"
"  __ _| | __      ___  ___\n"
" / _` | |/ /____ / _ \\/ __|\n"
"| (_| |   <_____| (_) \\__ \\\n"
" \\__, |_|\\_\\     \\___/|___/\n"
" |___/\n\n");
}

void main()
{
     sysinfo_t *sysinfo;
     char *cmdline;
     unsigned long el, time1, time2;
     unsigned int arm_clock_rate;

     init();

     vanity();

     kprintf("System information:\n");

     sysinfo = mbox_sysinfo();

     kprintf("Videocore firmware revision:\n");
     kprinthex(sysinfo->vc_fw_rev);
     kprintf("\n");

     kprintf("Board model:\n");
     kprinthex(sysinfo->brd_model);
     kprintf("\n");

     kprintf("Board revision:\n");
     kprinthex(sysinfo->brd_rev);
     kprintf("\n");

     kprintf("MAC address (wrong endian):\n");
     kprinthex(sysinfo->mac_addr);
     kprintf("\n");

     kprintf("Board serial number:\n");
     kprinthex(sysinfo->brd_serial);
     kprintf("\n");

     kprintf("ARM memory base address:\n");
     kprinthex(sysinfo->arm_mem_base_addr);
     kprintf("\n");

     kprintf("ARM memory size:\n");
     kprinthex(sysinfo->arm_mem_size);
     kprintf("\n");

     kprintf("VideoCore memory base address:\n");
     kprinthex(sysinfo->vc_mem_base_addr);
     kprintf("\n");

     kprintf("VideoCore memory size:\n");
     kprinthex(sysinfo->vc_mem_size);
     kprintf("\n");

     kprintf("unsigned short:\n");
     kprintdec(sizeof(unsigned short));
     kprintf("\n");

     kprintf("unsigned int:\n");
     kprintdec(sizeof(unsigned int));
     kprintf("\n");

     kprintf("unsigned long:\n");
     kprintdec(sizeof(unsigned long));
     kprintf("\n");

     cmdline = mbox_cmdline();
     kprintf("Command line:\n");
     kprintf(cmdline);
     kprintf("\n");

     arm_clock_rate = mbox_get_clock_rate(MBOX_CLK_ARM)/1000000;
     kprintf("ARM clock rate (MHz):\n");
     kprintdec(arm_clock_rate);
     kprintf("\n");

     asm volatile("mrs %0, CurrentEL"
                  : "=r" (el)
          );
     kprintf("Current Exception Level:\n");
     kprinthex((el >> 2) & 3);
     kprintf("\n");

     time1 = get_system_time();
     kprintf("Current system time:\n");
     kprintdec(time1);
     kprintf("\n");

     kprintf("Waiting 1200000 instructions...\n");
     time1 = get_system_time();
     wait_cycles(1200000);
     time2 = get_system_time();
     kprintf("Done.\n");

     kprintf("Time taken to wait:\n");
     kprintdec(time2 - time1);
     kprintf("\n");

     kprintf("Cycles per instruction:\n");
     kprintdec((arm_clock_rate*(time2-time1))/1200000);
     kprintf("\n");

     asm volatile("mrs %0, sctlr_el1"
                  : "=r" (el)
          );
     kprintf("sctlr_el1:\n");
     kprintbits(el);
     kprintf("\n");

     concurrent();

     while(1) {
          kputc(kgetc());
     }
}
