#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gemm_ref.cpp"
#include "gemm_compiler_32_32_32_32_32_32.cpp"
#include <vector>

TEST_CASE("Test 32 GEMM", "[gemm][fixed32]"){
    unsigned int lambda = 32;
    std::vector<float> l_A(lambda * lambda),
        l_B(lambda * lambda),
        l_C(lambda * lambda),
        l_excepted_C(lambda * lambda);
    
    // populate l_A and l_B
    for (int i = 0; i<lambda * lambda; i++){
        l_A[i] = l_B[i] = i;
    }

    // calculate reference solution
    gemm_ref(l_A.data(), l_B.data(), l_excepted_C.data(), 
        lambda, lambda, lambda, lambda, lambda, lambda);

    // test mnk variant
    gemm_compiler_32_32_32_32_32_32_mnk(
        l_A.data(), l_B.data(), l_C.data());
    REQUIRE_THAT(l_excepted_C, Catch::Approx(l_C).epsilon(1e-5));

    // test nkm variant
    l_C = std::vector<float>(lambda * lambda);
    gemm_compiler_32_32_32_32_32_32_nkm(
        l_A.data(), l_B.data(), l_C.data());
    REQUIRE_THAT(l_excepted_C, Catch::Approx(l_C).epsilon(1e-5));
}