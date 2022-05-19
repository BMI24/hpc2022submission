.text
        .type gemm_asm_sve_64_6_1, %function
        .global gemm_asm_sve_64_6_1
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (64x6) = (64x1) * (1x6).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 
gemm_asm_sve_64_6_1:
        // set predicate register to true
        ptrue p0.b

        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        stp  d8,  d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!

        // load accumulator block (matrix C)
        ldr z0, [x2]
        add x2, x2, #16*4
        ldr z1, [x2]
        add x2, x2, #16*4
        ldr z2, [x2]
        add x2, x2, #16*4
        ldr z3, [x2]
        add x2, x2, #16*4

        ldr z4, [x2]
        add x2, x2, #16*4
        ldr z5, [x2]
        add x2, x2, #16*4
        ldr z6, [x2]
        add x2, x2, #16*4
        ldr z7, [x2]
        add x2, x2, #16*4
        
        ldr z8, [x2]
        add x2, x2, #16*4
        ldr z9, [x2]
        add x2, x2, #16*4
        ldr z10, [x2]
        add x2, x2, #16*4
        ldr z11, [x2]
        add x2, x2, #16*4
        
        ldr z12, [x2]
        add x2, x2, #16*4
        ldr z13, [x2]
        add x2, x2, #16*4
        ldr z14, [x2]
        add x2, x2, #16*4
        ldr z15, [x2]
        add x2, x2, #16*4
        
        ldr z16, [x2]
        add x2, x2, #16*4
        ldr z17, [x2]
        add x2, x2, #16*4
        ldr z18, [x2]
        add x2, x2, #16*4
        ldr z19, [x2]
        add x2, x2, #16*4
        
        ldr z20, [x2]
        add x2, x2, #16*4
        ldr z21, [x2]
        add x2, x2, #16*4
        ldr z22, [x2]
        add x2, x2, #16*4
        ldr z23, [x2]
        sub x2, x2, #23*16*4


        // load row of matrix B (broadcast to sve register)
        ld1rw {z24.s}, p0/z, [x1]
        add x1, x1, #4
        ld1rw {z25.s}, p0/z, [x1]
        add x1, x1, #4
        ld1rw {z26.s}, p0/z, [x1]
        add x1, x1, #4
        ld1rw {z27.s}, p0/z, [x1]
        add x1, x1, #4
        ld1rw {z28.s}, p0/z, [x1]
        add x1, x1, #4
        ld1rw {z29.s}, p0/z, [x1]
        add x1, x1, #4

        // load first half column of matrix A (into two vectors)
        ldr z30, [x0]
        add x0, x0, #16*4
        ldr z31, [x0]
        add x0, x0, #16*4

        // use full row of B and first half column of A to do first calculations on accumulator block
        fmla z0.s, p0/m, z24.s, z30.s
        fmla z4.s, p0/m, z25.s, z30.s
        fmla z8.s, p0/m, z26.s, z30.s
        fmla z12.s, p0/m, z27.s, z30.s
        fmla z16.s, p0/m, z28.s, z30.s
        fmla z20.s, p0/m, z29.s, z30.s
        
        fmla z1.s, p0/m, z24.s, z31.s
        fmla z5.s, p0/m, z25.s, z31.s
        fmla z9.s, p0/m, z26.s, z31.s
        fmla z13.s, p0/m, z27.s, z31.s
        fmla z17.s, p0/m, z28.s, z31.s
        fmla z21.s, p0/m, z29.s, z31.s

        // load second half column of matrix A (into two vectors)
        ldr z30, [x0]
        add x0, x0, #16*4
        ldr z31, [x0]

        // use full row of B and second half column of A to do first calculations on accumulator block
        fmla z2.s, p0/m, z24.s, z30.s
        fmla z6.s, p0/m, z25.s, z30.s
        fmla z10.s, p0/m, z26.s, z30.s
        fmla z14.s, p0/m, z27.s, z30.s
        fmla z18.s, p0/m, z28.s, z30.s
        fmla z22.s, p0/m, z29.s, z30.s
        
        fmla z3.s, p0/m, z24.s, z31.s
        fmla z7.s, p0/m, z25.s, z31.s
        fmla z11.s, p0/m, z26.s, z31.s
        fmla z15.s, p0/m, z27.s, z31.s
        fmla z19.s, p0/m, z28.s, z31.s
        fmla z23.s, p0/m, z29.s, z31.s
        

        // store accumulator block (matrix C)
        str z0, [x2]
        add x2, x2, #16*4
        str z1, [x2]
        add x2, x2, #16*4
        str z2, [x2]
        add x2, x2, #16*4
        str z3, [x2]
        add x2, x2, #16*4

        str z4, [x2]
        add x2, x2, #16*4
        str z5, [x2]
        add x2, x2, #16*4
        str z6, [x2]
        add x2, x2, #16*4
        str z7, [x2]
        add x2, x2, #16*4
        
        str z8, [x2]
        add x2, x2, #16*4
        str z9, [x2]
        add x2, x2, #16*4
        str z10, [x2]
        add x2, x2, #16*4
        str z11, [x2]
        add x2, x2, #16*4
        
        str z12, [x2]
        add x2, x2, #16*4
        str z13, [x2]
        add x2, x2, #16*4
        str z14, [x2]
        add x2, x2, #16*4
        str z15, [x2]
        add x2, x2, #16*4
        
        str z16, [x2]
        add x2, x2, #16*4
        str z17, [x2]
        add x2, x2, #16*4
        str z18, [x2]
        add x2, x2, #16*4
        str z19, [x2]
        add x2, x2, #16*4
        
        str z20, [x2]
        add x2, x2, #16*4
        str z21, [x2]
        add x2, x2, #16*4
        str z22, [x2]
        add x2, x2, #16*4
        str z23, [x2]


        // restore
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16

        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_sve_64_6_1, (. - gemm_asm_sve_64_6_1)
