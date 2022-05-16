#include <cstdint>

void copy_c( uint32_t const * i_a,
             uint64_t       * o_b ) {
    
    o_b[0] = i_a[0];
    o_b[1] = i_a[1];
    o_b[2] = i_a[2];
    o_b[3] = i_a[3];
    o_b[4] = i_a[4];
    o_b[5] = i_a[5];
    o_b[6] = i_a[6];
}
