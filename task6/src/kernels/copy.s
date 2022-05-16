        .text
        .align 4
        .type   copy_asm, %function
        .global copy_asm
copy_asm:
        ldp w2, w3, [x0]
        ldp w4, w5, [x0, #8]
        ldp w6, w7, [x0, #16]
        ldr w8, [x0, #24]

        stp x2, x3, [x1]
        stp x4, x5, [x1, #16]
        stp x6, x7, [x1, #32]
        str x8, [x1, #48]

        ret
        .size copy_asm, (. - copy_asm)
