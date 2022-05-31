#include <cstdint>
#include <chrono>
#include <omp.h>
#include <iostream>
#include "kernels/gemm_ref.cpp"
#include "AlignedAllocator.cpp"
#include <algorithm>
#include <vector>
#include <numeric>

extern "C" {   
    void gemm_asm_sve_128_6_48( float const * i_a,
                                float const * i_b,
                                float       * io_c );
    void gemm_asm_sve_128_48_48( float const * i_a,
                                 float const * i_b,
                                 float       * io_c );
}

template<typename T, std::size_t ALIGNMENT_IN_BYTES = 256>
using AlignedVector = std::vector<T, AlignedAllocator<T, ALIGNMENT_IN_BYTES> >;

template<class It>
float maxDifference(It first, It last, It d_first) {
  float diff = 0;
  for (; first != last; (void)++first, (void)++d_first) {
    diff = std::max(diff, std::abs(*d_first - *first));
  }
  return diff;
}

int main(){
  AlignedVector<float> l_A(128*48),
    l_B(48*6),
    l_C(128*6),
    l_expected_C;
  const float epsilon = 0.00001;
  uint64_t l_reps_128_6_48  = 2000000;
  //uint64_t l_reps_128_48_48 = 10;
  std::chrono::steady_clock::time_point l_tp0, l_tp1;
  std::chrono::duration< double > l_dur;
  uint64_t l_fl_ops;
  float gflops;
  bool test_passed;
  float max_diff;

  // test gemm_asm_sve_128_6_48
  std::iota(l_A.begin(), l_A.end(), 0);
  std::iota(l_B.begin(), l_B.end(), 0);
  std::iota(l_C.begin(), l_C.end(), 0);
  l_expected_C = AlignedVector<float>(l_C);
  gemm_ref(l_A.data(), l_B.data(), l_expected_C.data(), 128, 6, 48, 128, 48, 128);
  gemm_asm_sve_128_6_48(l_A.data(), l_B.data(), l_C.data());
  max_diff = maxDifference(l_C.begin(), l_C.end(), l_expected_C.begin());
  test_passed = max_diff < epsilon;
  std::cout << "Max error of gemm_asm_sve_128_6_48: " << max_diff << ". Test " << (test_passed ? "passed." : "failed.") << std::endl;

  // test gemm_asm_sve_128_48_48
  l_A = AlignedVector<float>(128 * 48);
  l_B = AlignedVector<float>(48 *  48);
  l_C = AlignedVector<float>(128 *  48);
  std::iota(l_A.begin(), l_A.end(), 0);
  std::iota(l_B.begin(), l_B.end(), 0);
  
  l_expected_C = AlignedVector<float>(l_C);
  // check for correctness using reference driver
  gemm_ref(l_A.data(), l_B.data(), l_expected_C.data(), 128, 48, 48, 128, 48, 128);
  gemm_asm_sve_128_48_48(l_A.data(), l_B.data(), l_C.data());
  max_diff = maxDifference(l_C.begin(), l_C.end(), l_expected_C.begin());
  test_passed = max_diff < epsilon;
  std::cout << "Max error of gemm_asm_sve_128_48_48: " << max_diff << ". Test " << (test_passed ? "passed." : "failed.") << std::endl;
  

  // benchmark gemm_asm_sve_128_6_48
  l_A = AlignedVector<float>(128*48);
  l_B = AlignedVector<float>(48*6);
  l_C = AlignedVector<float>(128*6);
  // dry-run
  gemm_asm_sve_128_6_48(l_A.data(), l_B.data(), l_C.data());

  l_tp0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < l_reps_128_6_48; i++){
    gemm_asm_sve_128_6_48(l_A.data(), l_B.data(), l_C.data());
  }
  l_tp1 = std::chrono::steady_clock::now();
  l_dur = std::chrono::duration_cast< std::chrono::duration< double > >( l_tp1 - l_tp0 );
  std::cout << "gemm_asm_sve_128_6_48" << std::endl;
  std::cout << "  #executions: " << l_reps_128_6_48 << std::endl;
  std::cout << "  Time (s): " << l_dur.count() << std::endl;
  l_fl_ops = l_reps_128_6_48 * 2 * 128 * 6 * 48;
  gflops = l_fl_ops / l_dur.count() * 1.0E-9;
  std::cout << "  GFLOPS:" << gflops << std::endl;
  std::cout << "  %peak:" << gflops / 115.2 * 100 << std::endl;
}