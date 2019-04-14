/* gk-os
 *
 * the scheduler
 *
 */

#include "kio.h"

/* these must remain 16-byte aligned whenever they are changed */
unsigned long *this_stack;
unsigned long *stack1 = (unsigned long *)0x3A400000;
unsigned long *stack2 = (unsigned long *)0x39400000;

int current_proc = 0;
int proc1_active = 0, proc2_active = 0;

/* some high memory address */
#define STACK_BASE (unsigned long *)0x39400000;
#define STACK_SIZE 0x200000;    /* 2MB stacks */

extern void ctxsw(unsigned long **old_stack, unsigned long **new_stack);

void func1()
{
     int i;

     for (i = 0; i < 30; i++) {
          kprintf("func1: ");
          kprintdec(i);
          kprintf("\n");
          ctxsw(&stack1, &stack2);
     }
     kprintf("func1 done.\n");
}

void func2()
{
     int i;

     for (i = 30; i > 0; i--) {
          kprintf("func2: ");
          kprintdec(i);
          kprintf("\n");
          ctxsw(&stack2, &stack1);
     }
     kprintf("func2 done.\n");
}

void exit()
{
     kprintf("Process ");
     kprintdec(current_proc);
     kprintf(" exited.\n");

     if (current_proc == 1) {
          proc1_active = 0;
          ctxsw(&stack1, &this_stack);
     }
     else if (current_proc == 2) {
          proc2_active = 0;
          ctxsw(&stack2, &this_stack);
     }
}

void create(void *funcaddr, unsigned long **stack)
{
     int i;
     /* push stuff to new stack; just zero everything out */
     *stack -= 32;              /* 256 bytes */
     for (i = 0; i < 32; i++) {
          *(*stack + i) = 0;
     }
     /* set the return value (x30) to the exit routine */
     *(*stack + 30) = (unsigned long)&exit;
     /* set new process to the funcaddr */
     *(*stack + 31) = (unsigned long)funcaddr;
}

void concurrent()
{
     asm volatile("mov %0, sp" : "=r" (this_stack));
     create(&func1, &stack1);
     proc1_active = 1;
     create(&func2, &stack2);
     proc2_active = 1;

     current_proc = 1;

     while (proc1_active || proc2_active) {
          if (current_proc == 1 && proc2_active) {
               current_proc = 2;
               ctxsw(&this_stack, &stack2);
               continue;
          }
          if (current_proc == 2 && proc1_active) {
               current_proc = 1;
               ctxsw(&this_stack, &stack1);
               continue;
          }
     }
     kprintf("All done.\n");
}
