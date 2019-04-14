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
     ctxsw(&stack1, &this_stack);
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
     ctxsw(&stack2, &this_stack);
}

void exit()
{
     kprintf("Process ");
     /* kprintdec(i); */
     kprintf("exited.");
}

void create(void *funcaddr, unsigned long **stack)
{
     int i;
     /* push stuff to new stack; just zero everything out */
     *stack -= 32;              /* 256 bytes */
     for (i = 0; i < 32; i++) {
          *(*stack + i) = 0;
     }
     /* set the return value (x30) to process function */
     *(*stack + 30) = (unsigned long)funcaddr;
}

void concurrent()
{
     asm volatile("mov %0, sp" : "=r" (this_stack));
     create(&func1, &stack1);
     create(&func2, &stack2);
     ctxsw(&this_stack, &stack1);
     kprintf("All done.\n");
}
