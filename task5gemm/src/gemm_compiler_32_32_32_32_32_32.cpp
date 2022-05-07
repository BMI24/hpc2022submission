void gemm_compiler_32_32_32_32_32_32_mnk( float const * i_a,
                                          float const * i_b,
                                          float       * io_c ) {
    
    for (unsigned int l_m = 0; l_m < 32; l_m++) {
        for (unsigned int l_n = 0; l_n < 32; l_n++) {
            for (unsigned int l_k = 0; l_k < 32; l_k++) {
                io_c[ l_n * 32 + l_m ] += i_a[ l_k * 32 + l_m ] * i_b[ l_n * 32 + l_k ];
            }
        }
    }
}

void gemm_compiler_32_32_32_32_32_32_nkm( float const * i_a,
                                          float const * i_b,
                                          float       * io_c ) {
    
    for (unsigned int l_n = 0; l_n < 32; l_n++) {
        for (unsigned int l_k = 0; l_k < 32; l_k++) {
            for (unsigned int l_m = 0; l_m < 32; l_m++) {
                io_c[ l_n * 32 + l_m ] += i_a[ l_k * 32 + l_m ] * i_b[ l_n * 32 + l_k ];
            }
        }
    }
}