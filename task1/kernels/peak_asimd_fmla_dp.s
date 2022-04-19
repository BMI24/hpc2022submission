        .text
        .type peak_asimd_fmla_dp, %function
        .global peak_asimd_fmla_dp
        /*
         * Microbenchmark measuring achievable performance using fmla instructions.
         * Repeats 30 independent DP ASIMD-FMAs.
         * @param x0 number of repetitions.
         * @return number of flops per iteration.
         */ 
peak_asimd_fmla_dp:
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
        fmla v0.2d, v30.2d, v31.2d
        fmla v1.2d, v30.2d, v31.2d
        fmla v2.2d, v30.2d, v31.2d
        fmla v3.2d, v30.2d, v31.2d
        
        fmla v4.2d, v30.2d, v31.2d
        fmla v5.2d, v30.2d, v31.2d
        fmla v6.2d, v30.2d, v31.2d
        fmla v7.2d, v30.2d, v31.2d
        
        fmla v8.2d, v30.2d, v31.2d
        fmla v9.2d, v30.2d, v31.2d
        fmla v10.2d, v30.2d, v31.2d
        fmla v11.2d, v30.2d, v31.2d
        
        fmla v12.2d, v30.2d, v31.2d
        fmla v13.2d, v30.2d, v31.2d
        fmla v14.2d, v30.2d, v31.2d
        fmla v15.2d, v30.2d, v31.2d
        
        fmla v16.2d, v30.2d, v31.2d
        fmla v17.2d, v30.2d, v31.2d
        fmla v18.2d, v30.2d, v31.2d
        fmla v19.2d, v30.2d, v31.2d
        
        fmla v20.2d, v30.2d, v31.2d
        fmla v21.2d, v30.2d, v31.2d
        fmla v22.2d, v30.2d, v31.2d
        fmla v23.2d, v30.2d, v31.2d
        
        fmla v24.2d, v30.2d, v31.2d
        fmla v25.2d, v30.2d, v31.2d
        fmla v26.2d, v30.2d, v31.2d
        fmla v27.2d, v30.2d, v31.2d
        
        fmla v28.2d, v30.2d, v31.2d
        fmla v29.2d, v30.2d, v31.2d
        cbnz x0, loop_repeat

        // PCS: restore SIMD registers
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16


        // write number of flops to return register
        mov x0, 30*4

        ret
        .size peak_asimd_fmla_dp, (. - peak_asimd_fmla_dp)
