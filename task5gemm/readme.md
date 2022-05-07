# Übung 5 Small GEMMs

# Task 5.1

## Task 5.1.1

Done.

## Task 5.1.2

Done.

## Task 5.1.3

Done, see `src/test_ref.cpp`.

# Task 5.2

## Task 5.2.1

For each of the $m\cdot n$ entries there needs to be $k$ times one addition and one multiplication, which results in $2\cdot m\cdot n\cdot k$ FP operations.

## Task 5.2.2

Done. (used 1000000 repititions)

## Task 5.2.3

Done. (but I use steady_clock instead of high_resolution_clock)

## Task 5.2.4

Done.

## Task 5.2.5

To counteract the increase in runtime with growing lambda, I chose to set repititions to $\frac{10000000}{\lambda^2}$.
Results without optimization:
```
g++ driver.cpp -o driver && ./driver
lambda: 4
  duration: 0.904896 seconds
  repititions: 625000
  average duration: 1.44783e-06 seconds
  GFLOPS: 0.0884079
lambda: 8
  duration: 1.66465 seconds
  repititions: 156250
  average duration: 1.06538e-05 seconds
  GFLOPS: 0.096116
lambda: 12
  duration: 2.3257 seconds
  repititions: 69444
  average duration: 3.34903e-05 seconds
  GFLOPS: 0.103194
lambda: 16
  duration: 3.38638 seconds
  repititions: 39062
  average duration: 8.66925e-05 seconds
  GFLOPS: 0.0944949
lambda: 24
  duration: 4.91807 seconds
  repititions: 17361
  average duration: 0.000283282 seconds
  GFLOPS: 0.0975987
lambda: 32
  duration: 6.21353 seconds
  repititions: 9765
  average duration: 0.000636306 seconds
  GFLOPS: 0.102995
lambda: 48
  duration: 9.3631 seconds
  repititions: 4340
  average duration: 0.0021574 seconds
  GFLOPS: 0.102524
lambda: 64
  duration: 12.3936 seconds
  repititions: 2441
  average duration: 0.00507728 seconds
  GFLOPS: 0.103262
```
GFLOPS are a little higher with bigger lambdas (maybe due to reduced overhead when calling the kernel), but average duration grows faster than $\lambda^2$.
```
g++ driver.cpp -o2 -o driver && ./driver
lambda: 4
  duration: 0.906594 seconds
  repititions: 625000
  average duration: 1.45055e-06 seconds
  GFLOPS: 0.0882424
lambda: 8
  duration: 1.70862 seconds
  repititions: 156250
  average duration: 1.09351e-05 seconds
  GFLOPS: 0.093643
lambda: 12
  duration: 2.32516 seconds
  repititions: 69444
  average duration: 3.34825e-05 seconds
  GFLOPS: 0.103218
lambda: 16
  duration: 3.38703 seconds
  repititions: 39062
  average duration: 8.67091e-05 seconds
  GFLOPS: 0.0944769
lambda: 24
  duration: 4.90614 seconds
  repititions: 17361
  average duration: 0.000282595 seconds
  GFLOPS: 0.097836
lambda: 32
  duration: 6.27001 seconds
  repititions: 9765
  average duration: 0.000642091 seconds
  GFLOPS: 0.102067
lambda: 48
  duration: 9.31521 seconds
  repititions: 4340
  average duration: 0.00214636 seconds
  GFLOPS: 0.103051
lambda: 64
  duration: 12.3394 seconds
  repititions: 2441
  average duration: 0.00505504 seconds
  GFLOPS: 0.103716
```
`-o2` does not increase performance (in a significant way) in this case.
```
g++ driver.cpp -o3 -o driver && ./driver
lambda: 4
  duration: 0.905156 seconds
  repititions: 625000
  average duration: 1.44825e-06 seconds
  GFLOPS: 0.0883825
lambda: 8
  duration: 1.70179 seconds
  repititions: 156250
  average duration: 1.08914e-05 seconds
  GFLOPS: 0.0940188
lambda: 12
  duration: 2.33139 seconds
  repititions: 69444
  average duration: 3.35722e-05 seconds
  GFLOPS: 0.102942
lambda: 16
  duration: 3.45423 seconds
  repititions: 39062
  average duration: 8.84295e-05 seconds
  GFLOPS: 0.0926388
lambda: 24
  duration: 4.91492 seconds
  repititions: 17361
  average duration: 0.000283101 seconds
  GFLOPS: 0.0976611
lambda: 32
  duration: 6.19782 seconds
  repititions: 9765
  average duration: 0.000634698 seconds
  GFLOPS: 0.103255
lambda: 48
  duration: 9.26025 seconds
  repititions: 4340
  average duration: 0.0021337 seconds
  GFLOPS: 0.103662
lambda: 64
  duration: 12.3594 seconds
  repititions: 2441
  average duration: 0.00506323 seconds
  GFLOPS: 0.103548
```
`-o3` does not help either.
```
g++ driver.cpp -ofast -march=native -ffast-math -o driver && ./driver
lambda: 4
  duration: 0.869144 seconds
  repititions: 625000
  average duration: 1.39063e-06 seconds
  GFLOPS: 0.0920446
lambda: 8
  duration: 1.56591 seconds
  repititions: 156250
  average duration: 1.00218e-05 seconds
  GFLOPS: 0.102177
lambda: 12
  duration: 2.29713 seconds
  repititions: 69444
  average duration: 3.30789e-05 seconds
  GFLOPS: 0.104478
lambda: 16
  duration: 3.20184 seconds
  repititions: 39062
  average duration: 8.1968e-05 seconds
  GFLOPS: 0.0999414
lambda: 24
  duration: 4.62752 seconds
  repititions: 17361
  average duration: 0.000266547 seconds
  GFLOPS: 0.103727
lambda: 32
  duration: 6.10801 seconds
  repititions: 9765
  average duration: 0.0006255 seconds
  GFLOPS: 0.104774
lambda: 48
  duration: 9.04016 seconds
  repititions: 4340
  average duration: 0.00208299 seconds
  GFLOPS: 0.106186
lambda: 64
  duration: 12.1776 seconds
  repititions: 2441
  average duration: 0.00498876 seconds
  GFLOPS: 0.105094
```
Even activating all usual math optimization flags using `-ofast -march=native -ffast-math`, we get no noticable performance increase.

# Task 5.3

## Task 5.3.1

Done.

## Task 5.3.2

Done.

## Task 5.3.3

Done. (in test_gemm_32.cpp)

## Task 5.3.4

Added code into driver.cpp. Without optimization (look for "lambda: 32 (compiler aware)"):
```
g++ driver.cpp -o driver && ./driver
[...]
lambda: 32
  duration: 6.18958 seconds
  repititions: 9765
  average duration: 0.000633853 seconds
  GFLOPS: 0.103393
lambda: 32 (compiler aware) mnk order
  duration: 5.5827 seconds
  repititions: 9765
  average duration: 0.000571705 seconds
  GFLOPS: 0.114632
lambda: 32 (compiler aware) nkm order
  duration: 4.72022 seconds
  repititions: 9765
  average duration: 0.000483382 seconds
  GFLOPS: 0.135578
[...]
```
The specialized lambda=32 kernels are faster. The nkm kernel outperforms the mnk kernel.
```
g++ driver.cpp -o2 -o driver && ./driver
[...]
lambda: 32
  duration: 6.2054 seconds
  repititions: 9765
  average duration: 0.000635474 seconds
  GFLOPS: 0.103129
lambda: 32 (compiler aware) mnk order
  duration: 5.58261 seconds
  repititions: 9765
  average duration: 0.000571695 seconds
  GFLOPS: 0.114634
lambda: 32 (compiler aware) nkm order
  duration: 4.72124 seconds
  repititions: 9765
  average duration: 0.000483486 seconds
  GFLOPS: 0.135549
[...]
```
Using `-o2` does not increase performance futher.
```
g++ driver.cpp -o3 -o driver && ./driver
[...]
lambda: 32
  duration: 6.27977 seconds
  repititions: 9765
  average duration: 0.00064309 seconds
  GFLOPS: 0.101908
lambda: 32 (compiler aware) mnk order
  duration: 5.59332 seconds
  repititions: 9765
  average duration: 0.000572792 seconds
  GFLOPS: 0.114415
lambda: 32 (compiler aware) nkm order
  duration: 4.74013 seconds
  repititions: 9765
  average duration: 0.000485421 seconds
  GFLOPS: 0.135009
[...]
```
Using `-o3` does not help either.
```
g++ driver.cpp -ofast -march=native -ffast-math -o driver && ./driver
[...]
lambda: 32
  duration: 6.11559 seconds
  repititions: 9765
  average duration: 0.000626276 seconds
  GFLOPS: 0.104644
lambda: 32 (compiler aware) mnk order
  duration: 6.09895 seconds
  repititions: 9765
  average duration: 0.000624572 seconds
  GFLOPS: 0.104929
lambda: 32 (compiler aware) nkm order
  duration: 4.69963 seconds
  repititions: 9765
  average duration: 0.000481273 seconds
  GFLOPS: 0.136172
[...]
```
Using `-ofast -march=native -ffast-math` the mnk kernel somehow gets slower (reproduced in repeated tests). nkm performance doesn't change/changes very little.

# Task 5.4

## Task 5.4.1

Basic steps:
```
git clone https://github.com/libxsmm/libxsmm
cd libxsmm
make -j 48
```
The libxsmm folder cant be added to a commit. Maybe some git submodule stuff? Cant figure out right now.

## Task 5.4.2

`libxsmm_dmmdispatch` requires multiple parameters:
1. int m (see matrix dim)
2. int n (see matrix dim)
3. int k (see matrix dim)
4. int lda (see matrix dim); when NULL the value is set to m
5. int ldb (see matrix dim); when NULL the value is set to k
6. int ldc (see matrix dim); when NULL the value is set to m
7. double alpha (passed as reference, set at runtime by function)
8. double beta (passed as reference, set at runtime by function)
9. int flags (passed as reference, set at runtime by function)
10. int prefatch strategy (passed by reference)

... and returns a kernel (function) which can be called to compute the GEMM on any matrices if their shapes correspond to the given m, n, k, lda, ldb and ldc.


The returned kernel (function) requires 3 parameters: one pointer for matrix A, one pointer for matrix B, one pointer for matrix C. `hello.c` contains one call to such a kernel function. Because it defines multiple matrices A and B it needs a loop to accumulate all matrix products in a single C matrix.

To build, first navigate to `libxsmm/samples/hello`, then `make BLAS=0 -j 48` to run without dependencies on external BLAS libraries. Then run `LIBXSMM_TARGET=a64fx ./helloc` as instructed to make it generate kernels that target the a64fx architecture.

## Task 5.4.3

Didnt to yet (didnt have time to figure out how to build my driver with libxsmm)