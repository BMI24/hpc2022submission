	.text
        .type gemm_asm_gp, %function
        .global gemm_asm_gp
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (4x2) = (4x2) * (2x2).
         * The input-data is of type uint32_t.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */
gemm_asm_gp:
        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        // your matrix-kernel goes here!

        // load matrix C into registers w3-w10
        ldp w3, w4, [x2], #8
        ldp w5, w6, [x2], #8
        ldp w7, w8, [x2], #8
        ldp w9, w10, [x2], #8

        // load matrix B into registers w11-w18
        ldp w11, w12, [x1], #8
        ldp w13, w14, [x1], #8
        ldp w15, w16, [x1], #8
        ldp w17, w18, [x1], #8

        // load matrix A into registers w19-w22
        ldp w19, w20, [x0], #8
        ldp w21, w22, [x0], #8

        // perform gemm

        madd w3, w11, w19, w3
        madd w3, w15, w20, w3

        madd w4, w12, w19, w4
        madd w4, w16, w20, w4

        madd w5, w13, w19, w5
        madd w5, w17, w20, w5

        madd w6, w14, w19, w6
        madd w6, w18, w20, w6
        
        
        madd w7, w11, w21, w7
        madd w7, w15, w22, w7

        madd w8, w12, w21, w8
        madd w8, w16, w22, w8

        madd w9, w13, w21, w9
        madd w9, w17, w22, w9

        madd w10, w14, w21, w10
        madd w10, w18, w22, w10

        
        // store matrix A back into memory
        stp w9, w10, [x2, #-8]!
        stp w7, w8, [x2, #-8]!
        stp w5, w6, [x2, #-8]!
        stp w3, w4, [x2, #-8]!
        

        // restore
        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_gp, (. - gemm_asm_gp)
