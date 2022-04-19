        .text
        .type peak_asimd_fmadd_sp, %function
        .global peak_asimd_fmadd_sp
        /*
         * Microbenchmark measuring achievable performance using fmla instructions.
         * Repeats 30 independent DP ASIMD-FMAs.
         * @param x0 number of repetitions.
         * @return number of flops per iteration.
         */ 
peak_asimd_fmadd_sp:
        // PCS: save required data in SIMD registers to stack
        stp  d8,  d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!

        // set SIMD registers to zero
        eor v0.16b, v0.16b, v0.16b
        eor v1.16b, v1.16b, v1.16b
        eor v2.16b, v2.16b, v2.16b
        eor v3.16b, v3.16b, v3.16b

        eor v4.16b, v4.16b, v4.16b
        eor v5.16b, v5.16b, v5.16b
        eor v6.16b, v6.16b, v6.16b
        eor v7.16b, v7.16b, v7.16b

        eor v8.16b, v8.16b, v8.16b
        eor v9.16b, v9.16b, v9.16b
        eor v10.16b, v10.16b, v10.16b
        eor v11.16b, v11.16b, v11.16b

        eor v12.16b, v12.16b, v12.16b
        eor v13.16b, v13.16b, v13.16b
        eor v14.16b, v14.16b, v14.16b
        eor v15.16b, v15.16b, v15.16b

        eor v16.16b, v16.16b, v16.16b
        eor v17.16b, v17.16b, v17.16b
        eor v18.16b, v18.16b, v18.16b
        eor v19.16b, v19.16b, v19.16b

        eor v20.16b, v20.16b, v20.16b
        eor v21.16b, v21.16b, v21.16b
        eor v22.16b, v22.16b, v22.16b
        eor v23.16b, v23.16b, v23.16b

        eor v24.16b, v24.16b, v24.16b
        eor v25.16b, v25.16b, v25.16b
        eor v26.16b, v26.16b, v26.16b
        eor v27.16b, v27.16b, v27.16b

        eor v28.16b, v28.16b, v28.16b
        eor v29.16b, v29.16b, v29.16b
        eor v30.16b, v30.16b, v30.16b
        eor v31.16b, v31.16b, v31.16b

loop_repeat:
        sub x0, x0, #1
        fmadd s0, s30, s31, s0
        fmadd s1, s30, s31, s1
        fmadd s2, s30, s31, s2
        fmadd s3, s30, s31, s3
        
        fmadd s4, s30, s31, s4
        fmadd s5, s30, s31, s5
        fmadd s6, s30, s31, s6
        fmadd s7, s30, s31, s7
        
        fmadd s8, s30, s31, s8
        fmadd s9, s30, s31, s9
        fmadd s10, s30, s31, s10
        fmadd s11, s30, s31, s11
        
        fmadd s12, s30, s31, s12
        fmadd s13, s30, s31, s13
        fmadd s14, s30, s31, s14
        fmadd s15, s30, s31, s15
        
        fmadd s16, s30, s31, s16
        fmadd s17, s30, s31, s17
        fmadd s18, s30, s31, s18
        fmadd s19, s30, s31, s19
        
        fmadd s20, s30, s31, s20
        fmadd s21, s30, s31, s21
        fmadd s22, s30, s31, s22
        fmadd s23, s30, s31, s23
        
        fmadd s24, s30, s31, s24
        fmadd s25, s30, s31, s25
        fmadd s26, s30, s31, s26
        fmadd s27, s30, s31, s27
        
        fmadd s28, s30, s31, s28
        fmadd s29, s30, s31, s29
        cbnz x0, loop_repeat

        // PCS: restore SIMD registers
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16


        // write number of flops to return register
        mov x0, 30*2

        ret
        .size peak_asimd_fmadd_sp, (. - peak_asimd_fmadd_sp)
