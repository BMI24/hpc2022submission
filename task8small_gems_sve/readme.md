# Übung 8 Small GEMMs: SVE

## Task 8.1 Loop over M

Done. Performance:
```
gemm_asm_sve_128_6_48
  #executions: 2000000
  Time (s): 1.823
  GFLOPS:80.8865
  %peak:70.2139
```
## Task 8.2 Loop over N

I tried, but failed (see `gemm_asm_sve_128_48_48.S`)