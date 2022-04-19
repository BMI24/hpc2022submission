#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>
#include <fstream>

extern "C" {
  uint64_t peak_asimd_fmla_sp( uint64_t i_n_repetitions );
  uint64_t peak_asimd_fmla_dp( uint64_t i_n_repetitions );
  uint64_t peak_asimd_fmadd_sp( uint64_t i_n_repetitions );
  uint64_t peak_asimd_fmadd_dp( uint64_t i_n_repetitions );
}

int main(int argc, char** argv) {
  std::cout << "running ASIMD microbenchmarks" << std::endl;
  std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
  std::chrono::duration< double > l_dur;
  std::ofstream logfile;
  double l_g_flops = 0;
  int l_n_threads = 1;
  uint64_t l_n_repetitions = 5000000;

#pragma omp parallel
  {
   #pragma omp master
   {
     l_n_threads = omp_get_num_threads();
   } 
  }
  std::cout << "  threads: " << l_n_threads << std::endl;


  /*
   * Peak ASIMD FMLA SP
   */
  std::cout << "peak_asimd_fmla_sp" << std::endl;
  // dry-run
  peak_asimd_fmla_sp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::high_resolution_clock::now();
    }
    l_g_flops = peak_asimd_fmla_sp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::high_resolution_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;
  logfile.open("peak_asimd_fmla_sp", std::ios::out | std::ios::app);
  logfile << l_g_flops << ",";
  logfile.close();


  /*
   * Peak ASIMD FMLA DP
   */
  std::cout << "peak_asimd_fmla_dp" << std::endl;
  // dry-run
  peak_asimd_fmla_dp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::high_resolution_clock::now();
    }
    l_g_flops = peak_asimd_fmla_dp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::high_resolution_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;
  logfile.open("peak_asimd_fmla_dp", std::ios::out | std::ios::app);
  logfile << l_g_flops << ",";
  logfile.close();

  /*
   * Peak ASIMD FMADD SP
   */
  std::cout << "peak_asimd_fmadd_sp" << std::endl;
  // dry-run
  peak_asimd_fmadd_sp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::high_resolution_clock::now();
    }
    l_g_flops = peak_asimd_fmadd_sp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::high_resolution_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;
  logfile.open("peak_asimd_fmadd_sp", std::ios::out | std::ios::app);
  logfile << l_g_flops << ",";
  logfile.close();

  /*
   * Peak ASIMD FMADD DP
   */
  std::cout << "peak_asimd_fmadd_dp" << std::endl;
  // dry-run
  peak_asimd_fmadd_dp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::high_resolution_clock::now();
    }
    l_g_flops = peak_asimd_fmadd_dp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::high_resolution_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;
  logfile.open("peak_asimd_fmadd_dp", std::ios::out | std::ios::app);
  logfile << l_g_flops << ",";
  logfile.close();

  std::cout << "finished ASIMD microbenchmarks" << std::endl;
  return EXIT_SUCCESS;
}
