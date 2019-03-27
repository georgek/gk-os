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
        mov     sp, x1

        ldr     x1, =__bss_start
        ldr     w2, =__bss_size
        cbz     w2, 4f
3:      str     xzr, [x1], #8
        sub     w2, w2, #1
        cbnz    w2, 3b

4:      bl      main
        b       1b
