#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>
#include <fstream>

extern "C" {
  uint64_t peak_sve_fmla_sp( uint64_t i_n_repetitions );
  uint64_t peak_sve_fmla_dp( uint64_t i_n_repetitions );
}

void benchmark(std::string i_name, uint64_t(*i_f)(uint64_t), int i_n_repetitions, int i_n_threads) {
  std::chrono::steady_clock::time_point l_tp0, l_tp1;
  double l_g_flops = 0;
  
  std::cout << i_name << std::endl;
  // dry-run
  (*i_f)( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::steady_clock::now();
    }
    l_g_flops = (*i_f)( i_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::steady_clock::now();
    }
  }

  std::chrono::duration< double > l_dur = std::chrono::duration_cast< std::chrono::duration< double > >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= i_n_threads;
  l_g_flops *= i_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;
  std::ofstream logfile;
  logfile.open("plots/data/"+i_name, std::ios::out | std::ios::app);
  logfile << l_g_flops << ",";
  logfile.close();
}



int main() {
  std::cout << "running SVE microbenchmarks" << std::endl;
  int l_n_threads = 1;
  uint64_t l_n_repetitions = 50000000;

#pragma omp parallel
  {
   #pragma omp master
   {
     l_n_threads = omp_get_num_threads();
   } 
  }
  std::cout << "  threads: " << l_n_threads << std::endl;

  benchmark("peak_sve_fmla_sp", peak_sve_fmla_sp, l_n_repetitions, l_n_threads);
  benchmark("peak_sve_fmla_dp", peak_sve_fmla_dp, l_n_repetitions, l_n_threads);
  
  std::cout << "finished ASIMD microbenchmarks" << std::endl;
  return EXIT_SUCCESS;
}
