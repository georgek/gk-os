/* gk-os
 *
 * context switch
 *
 * ctxsw(unsigned long *old_sp, unsigned long *new_sp)
 *
 */

        .arch armv8-a
        .text
        .global ctxsw
        .type ctxsw, %function

ctxsw:
        // push x0-x30 to old stack in reverse order
        sub     sp,  sp,  #256
        stp     x0,  x1,  [sp]
        stp     x2,  x3,  [sp, #16]
        stp     x4,  x5,  [sp, #32]
        stp     x6,  x7,  [sp, #48]
        stp     x8,  x9,  [sp, #64]
        stp     x10, x11, [sp, #80]
        stp     x12, x13, [sp, #96]
        stp     x14, x15, [sp, #112]
        stp     x16, x17, [sp, #128]
        stp     x18, x19, [sp, #144]
        stp     x20, x21, [sp, #160]
        stp     x22, x23, [sp, #176]
        stp     x24, x25, [sp, #192]
        stp     x26, x27, [sp, #208]
        stp     x28, x29, [sp, #224]
        str     x30,      [sp, #240]

        // switch stacks
        mov     x9, sp
        str     x9, [x0]
        ldr     x9, [x1]
        mov     sp, x9

        // pop from new stack
        ldp     x0,  x1,  [sp]
        ldp     x2,  x3,  [sp, #16]
        ldp     x4,  x5,  [sp, #32]
        ldp     x6,  x7,  [sp, #48]
        ldp     x8,  x9,  [sp, #64]
        ldp     x10, x11, [sp, #80]
        ldp     x12, x13, [sp, #96]
        ldp     x14, x15, [sp, #112]
        ldp     x16, x17, [sp, #128]
        ldp     x18, x19, [sp, #144]
        ldp     x20, x21, [sp, #160]
        ldp     x22, x23, [sp, #176]
        ldp     x24, x25, [sp, #192]
        ldp     x26, x27, [sp, #208]
        ldp     x28, x29, [sp, #224]
        ldr     x30,      [sp, #240]
        add     sp,  sp,  #256

        // return to new process
        ret
