/* gk-os
 *
 * delay cpu by n cycles
 *
 */

        .arch armv8-a
        .text
        .global wait_cycles
        .type wait_cycles, %function

wait_cycles:
        cmp     x0, 0
        ble     end
        sub     x0, x0, #4      // we'll spend 4 cycles in the loop
        b       wait_cycles
end:
        ret
