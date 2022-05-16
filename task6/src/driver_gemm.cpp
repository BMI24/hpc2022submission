#include <iostream>
#include <cassert>

extern "C" {
  void gemm_asm_gp( uint32_t const * i_a,
                    uint32_t const * i_b,
                    uint32_t * i_c );
}

int main() {

    uint32_t* a = new uint32_t[4] {1, 2, 3, 4};
    uint32_t* b = new uint32_t[8] {1, 2, 3, 4, 5, 6, 7, 8};
    uint32_t* c = new uint32_t[8] {1, 2, 3, 4, 5, 6, 7, 8};

    gemm_asm_gp(a, b, c);

    assert(c[0] == 12);
    assert(c[1] == 16);
    assert(c[2] == 20);
    assert(c[3] == 24);
    assert(c[4] == 28);
    assert(c[5] == 36);
    assert(c[6] == 44);
    assert(c[7] == 52);

    std::cout << "Kernel test passed." << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}