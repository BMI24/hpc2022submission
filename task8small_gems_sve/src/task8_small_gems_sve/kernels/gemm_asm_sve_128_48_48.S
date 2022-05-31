.text
        .type gemm_asm_sve_128_48_48, %function
        .global gemm_asm_sve_128_48_48
#define dim_m 128
#define dim_n 48
#define dim_k 48
#define dim_lda 128
#define dim_lda_bytes dim_lda*4
#define dim_ldb 48
#define dim_ldb_bytes dim_ldb*4
#define dim_ldc 128
#define dim_ldc_bytes dim_ldc*4
#define b_batchsize 4
#define a_batchsize 6
#define sve_len_bytes 16*4
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (128x48) += (128x48) * (48x48).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 
gemm_asm_sve_128_48_48:
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


        // initialize loop counter (over n)
        mov x6, #dim_n/a_batchsize
loop_n:
        sub x6, x6, #1


        // initialize loop counter (over m)
        mov x4, #dim_m/(b_batchsize*16)
loop_m:
        sub x4, x4, #1

        // load part of accumulator block (matrix C)
        ldr z0, [x2]
        add x2, x2, #sve_len_bytes
        ldr z1, [x2]
        add x2, x2, #sve_len_bytes
        ldr z2, [x2]
        add x2, x2, #sve_len_bytes
        ldr z3, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes

        ldr z4, [x2]
        add x2, x2, #sve_len_bytes
        ldr z5, [x2]
        add x2, x2, #sve_len_bytes
        ldr z6, [x2]
        add x2, x2, #sve_len_bytes
        ldr z7, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        ldr z8, [x2]
        add x2, x2, #sve_len_bytes
        ldr z9, [x2]
        add x2, x2, #sve_len_bytes
        ldr z10, [x2]
        add x2, x2, #sve_len_bytes
        ldr z11, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        ldr z12, [x2]
        add x2, x2, #sve_len_bytes
        ldr z13, [x2]
        add x2, x2, #sve_len_bytes
        ldr z14, [x2]
        add x2, x2, #sve_len_bytes
        ldr z15, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        ldr z16, [x2]
        add x2, x2, #sve_len_bytes
        ldr z17, [x2]
        add x2, x2, #sve_len_bytes
        ldr z18, [x2]
        add x2, x2, #sve_len_bytes
        ldr z19, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        ldr z20, [x2]
        add x2, x2, #sve_len_bytes
        ldr z21, [x2]
        add x2, x2, #sve_len_bytes
        ldr z22, [x2]
        add x2, x2, #sve_len_bytes
        ldr z23, [x2]
        sub x2, x2, #(a_batchsize-1)*dim_ldc_bytes+(b_batchsize-1)*sve_len_bytes


        // initialize loop counter (over k)
        mov x3, #dim_k
loop_k:
        sub x3, x3, #1
        

        // load row of matrix B  (broadcast to sve register)
        ld1rw {z24.s}, p0/z, [x1]
        add x1, x1, #dim_ldb_bytes
        ld1rw {z25.s}, p0/z, [x1]
        add x1, x1, #dim_ldb_bytes
        ld1rw {z26.s}, p0/z, [x1]
        add x1, x1, #dim_ldb_bytes
        ld1rw {z27.s}, p0/z, [x1]
        add x1, x1, #dim_ldb_bytes
        ld1rw {z28.s}, p0/z, [x1]
        add x1, x1, #dim_ldb_bytes
        ld1rw {z29.s}, p0/z, [x1]
        sub x1, x1, #(a_batchsize-1)*dim_ldb_bytes-4


        // load first half column of matrix A (into two vectors)
        ldr z30, [x0]
        add x0, x0, #sve_len_bytes
        ldr z31, [x0]
        add x0, x0, #sve_len_bytes


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
        add x0, x0, #sve_len_bytes
        ldr z31, [x0]
        add x0, x0, #dim_lda_bytes-(b_batchsize-1)*sve_len_bytes


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


        // jump back if iteration over k not finished
        cbnz x3, loop_k
        

        // store part of accumulator block (matrix C)
        str z0, [x2]
        add x2, x2, #sve_len_bytes
        str z1, [x2]
        add x2, x2, #sve_len_bytes
        str z2, [x2]
        add x2, x2, #sve_len_bytes
        str z3, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes

        str z4, [x2]
        add x2, x2, #sve_len_bytes
        str z5, [x2]
        add x2, x2, #sve_len_bytes
        str z6, [x2]
        add x2, x2, #sve_len_bytes
        str z7, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        str z8, [x2]
        add x2, x2, #sve_len_bytes
        str z9, [x2]
        add x2, x2, #sve_len_bytes
        str z10, [x2]
        add x2, x2, #sve_len_bytes
        str z11, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        str z12, [x2]
        add x2, x2, #sve_len_bytes
        str z13, [x2]
        add x2, x2, #sve_len_bytes
        str z14, [x2]
        add x2, x2, #sve_len_bytes
        str z15, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        str z16, [x2]
        add x2, x2, #sve_len_bytes
        str z17, [x2]
        add x2, x2, #sve_len_bytes
        str z18, [x2]
        add x2, x2, #sve_len_bytes
        str z19, [x2]
        add x2, x2, #dim_ldc_bytes-(b_batchsize-1)*sve_len_bytes
        
        str z20, [x2]
        add x2, x2, #sve_len_bytes
        str z21, [x2]
        add x2, x2, #sve_len_bytes
        str z22, [x2]
        add x2, x2, #sve_len_bytes
        str z23, [x2]

        // adjust pointers for next iteration over m
        
        mov x5, #dim_k*dim_lda_bytes-sve_len_bytes*4
        sub x0, x0, x5

        sub x1, x1, #dim_ldb_bytes

        mov x5, #(a_batchsize-1)*dim_ldc_bytes-sve_len_bytes
        sub x2, x2, x5


        // jump back if iteration over m not finished
        cbnz x4, loop_m

        
        // adjust pointers for next iteration over k
eofa:
        add x0, x0, #b_batchsize*dim_lda_bytes-sve_len_bytes*2
        add x1, x1, #b_batchsize*dim_ldb_bytes
        add x2, x2, #b_batchsize*dim_ldc_bytes-dim_n*4



        //jump back if iteration over n not finished
        cbnz x6, loop_n

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
        .size gemm_asm_sve_128_48_48, (. - gemm_asm_sve_128_48_48)
