#include "gemm_ref.cpp"
#include "gemm_compiler_32_32_32_32_32_32.cpp"
#include <vector>
#include <chrono>
#include <iostream>

int main(){
  std::vector<unsigned int> lambdas = {4, 8, 12, 16, 24, 32, 48, 64};
  for (unsigned int lambda : lambdas) {
    std::vector<float> l_A(lambda*lambda), 
      l_B(lambda*lambda), 
      l_C(lambda*lambda);

    unsigned int l_reps = 10000000 / (lambda * lambda);
    std::chrono::steady_clock::time_point l_tp0, l_tp1;
    std::chrono::duration< double > l_dur;
    unsigned int l_fl_ops;

    l_tp0 = std::chrono::steady_clock::now();
    for (unsigned int i = 0; i < l_reps; i++){
      gemm_ref(l_A.data(), l_B.data(), l_C.data(), lambda, lambda, lambda, lambda, lambda, lambda);
    }
    l_tp1 = std::chrono::steady_clock::now();

    l_dur = std::chrono::duration_cast< std::chrono::duration< double > >( l_tp1 - l_tp0 );
    std::cout << "lambda: " << lambda << std::endl;
    std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
    std::cout << "  repititions: " << l_reps << std::endl;
    std::cout << "  average duration: " << l_dur.count() / l_reps << " seconds" << std::endl;
    l_fl_ops = l_reps * 2 * lambda * lambda * lambda;
    std::cout << "  GFLOPS: " << l_fl_ops / l_dur.count() * 1.0E-9 << std::endl;

    if (lambda == 32){
      l_tp0 = std::chrono::steady_clock::now();
      for (unsigned int i = 0; i < l_reps; i++){
        gemm_compiler_32_32_32_32_32_32_mnk(l_A.data(), l_B.data(), l_C.data());
      }
      l_tp1 = std::chrono::steady_clock::now();
      l_dur = std::chrono::duration_cast< std::chrono::duration< double > >( l_tp1 - l_tp0 );
    
      std::cout << "lambda: " << lambda << " (compiler aware) mnk order" << std::endl;
      std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
      std::cout << "  repititions: " << l_reps << std::endl;
      std::cout << "  average duration: " << l_dur.count() / l_reps << " seconds" << std::endl;
      l_fl_ops = l_reps * 2 * lambda * lambda * lambda;
      std::cout << "  GFLOPS: " << l_fl_ops / l_dur.count() * 1.0E-9 << std::endl;

      
      l_tp0 = std::chrono::steady_clock::now();
      for (unsigned int i = 0; i < l_reps; i++){
        gemm_compiler_32_32_32_32_32_32_nkm(l_A.data(), l_B.data(), l_C.data());
      }
      l_tp1 = std::chrono::steady_clock::now();
      l_dur = std::chrono::duration_cast< std::chrono::duration< double > >( l_tp1 - l_tp0 );
    
      std::cout << "lambda: " << lambda << " (compiler aware) nkm order" << std::endl;
      std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
      std::cout << "  repititions: " << l_reps << std::endl;
      std::cout << "  average duration: " << l_dur.count() / l_reps << " seconds" << std::endl;
      l_fl_ops = l_reps * 2 * lambda * lambda * lambda;
      std::cout << "  GFLOPS: " << l_fl_ops / l_dur.count() * 1.0E-9 << std::endl;
    }
  }
  return 0;
}