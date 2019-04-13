/* get ready for running C code by clearing the bss and setting stack
 * before the code
 */

        .section ".text.boot"

        .global _start

_start:
        mrs     x1, mpidr_el1
        and     x1, x1, #3
        cbz     x1, 2f
1:      wfe
        b       1b

2:      ldr     x1, =_start

        // get into EL1
        mrs     x0, CurrentEL
        and     x0, x0, #12     // clear reserved bits

        // check if running at EL3
        cmp     x0, #12
        bne     el2
        // in EL3
        mov     x2, #0x5b1
        msr     scr_el3, x2
        mov     x2, #0x3c9
        msr     spsr_el3, x2
        adr     x2, el2
        msr     elr_el3, x2
        eret

        // check if running at EL2
el2:    cmp     x0, #4
        beq     set_stack
        msr     sp_el1, x1
        // enable cntp for EL1
        mrs     x0, cnthctl_el2
        orr     x0, x0, #3
        msr     cnthctl_el2, x0
        msr     cntvoff_el2, xzr
        // enable aarch64 in EL1
        mov     x0, #(1 << 31)  // aarch64
        orr     x0, x0, #(1 << 1) // SWIO hardwired on Pi3
        msr     hcr_el2, x0
        // change to EL1
        mov     x2, #0x3c4
        msr     spsr_el2, x2
        adr     x2, set_stack
        msr     elr_el2, x2
        eret

set_stack:
        mov     sp, x1

        ldr     x1, =__bss_start
        ldr     w2, =__bss_size
        cbz     w2, 4f
3:      str     xzr, [x1], #8
        sub     w2, w2, #1
        cbnz    w2, 3b

4:      bl      main
        b       1b
