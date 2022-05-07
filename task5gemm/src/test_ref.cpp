#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gemm_ref.cpp"
#include <vector>

TEST_CASE("some general test cases", "[gemm][ref]"){
  std::vector<float> l_A = { 2, 1, 5, 0 };
  std::vector<float> l_B = { 3, 1, 4, 1 };
  std::vector<float> l_C = { 0, 0, 0, 0 };
  unsigned int l_m, l_n, l_k, l_lda, l_ldb, l_ldc;
  l_m = l_n = l_k = l_lda = l_ldb = l_ldc = 2;

  std::vector<float> l_excepted_C = { 11, 3, 13, 4 };

  gemm_ref(l_A.data(), l_B.data(), l_C.data(), l_m, l_n, l_k, l_lda, l_ldb, l_ldc);
  REQUIRE(l_C == l_excepted_C);

  l_A = {-3, 1, -1, 10, 4, 5, 2, 0, 3, 19, 4, 3, 2, 10, 99};
  l_B = {2, 5, 0, 0, 1, 1, -1, 4};
  l_C = {0, 0, 0, 0, 0, 0};
  l_excepted_C = {19, 12, -2, -2, 0, -3};
  l_m = l_k = 3;
  l_n = 2;
  l_lda = 5;
  l_ldb = 4;
  l_ldc = 3;

  gemm_ref(l_A.data(), l_B.data(), l_C.data(), l_m, l_n, l_k, l_lda, l_ldb, l_ldc);
  REQUIRE(l_C == l_excepted_C);

  l_C = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  l_excepted_C = { 19, 12, -2, 35, -2, 0, -3, 3, 0, 0 };
  l_ldc = 4;
  l_m = 4;
  gemm_ref(l_A.data(), l_B.data(), l_C.data(), l_m, l_n, l_k, l_lda, l_ldb, l_ldc);
  REQUIRE(l_C == l_excepted_C);

  l_C = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  l_excepted_C = { 19, 12, -2, 35, 103, -2, 0, -3, 3, -76 };
  l_ldc = 5;
  l_m = 5;
  gemm_ref(l_A.data(), l_B.data(), l_C.data(), l_m, l_n, l_k, l_lda, l_ldb, l_ldc);
  REQUIRE(l_C == l_excepted_C);

  
  l_C = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  l_excepted_C = { 20, 13, -1, 36, 104, -1, 1, -2, 4, -75 };
  gemm_ref(l_A.data(), l_B.data(), l_C.data(), l_m, l_n, l_k, l_lda, l_ldb, l_ldc);
  REQUIRE(l_C == l_excepted_C);
}