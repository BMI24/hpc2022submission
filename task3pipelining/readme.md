# Übung 3 - Pipelining

## Task 4.1

| instruction | used pipeline | latency | throughput |
| --- | --- | --- | --- |
| `fmul` | FP/ASIMD 0/1 | 3 | 2 |
| `fmla` | FP/ASIMD 0/1 | 4 (oder 2 wenn ähnliche Operationen vorher in die Quellregister geschrieben hätte) | 2 |

## Task 4.2

Assuming clock speed of 3GHz.

Using `fmul`:
- if we can parallelize the `fmul`s we can achieve 2 (throughput) instructions which do 1 FP operations every 3 (latency) cycles: 3GHz * (2 instructions / 3) * (1 FLOP/ instruction) = 2 GFLOPs
- if there are read-after-write data dependencies preventing using 2 `fmuls` parallel in same pipeline: 3GHz * (1 instructions / 3) * (1 FLOP/ instruction) = 1 GFLOPs

Using `fmla` (assuming we can achieve the latency of 2, otherwise the following FLOPs need to be devided by 2)
- if we can parallelize the `fmla`s we can achieve 2 (throughput) instructions which do 2 FP operations every 3 (latency) cycles: 3GHz * (2 instructions / 2) * (2 FLOP/ instruction) = 6 GFLOPs
- if there are read-after-write data dependencies: 3GHz * (1 instructions / 2) * (2 FLOP/ instruction) = 3GFLOPs

Using `fmla` when possible seems apropriate.

## Task 4.3

The `latency_src_asimd_fmla_sp` kernel achieves 639.424 GFLOPS (which equals 3 GFLOPs * 2 Lanes * 106.5 single-core equivalents).

## Task 4.4

The `latency_src_asimd_fmul_sp.s` kernel achieves 598.413 GFLOPS (which probably means that I have made an error in Task 4.2).

## Task 4.5

If we increase the distance of read-after-write dependencies, the FLOPS should be higher if we actually do FP operations (instead of just adding `NOOP`s)

## Task 4.6

Doing this we can achieve more GFLOPs. `latency_dst_asimd_fmla_sp`: 1782.49 GFLOPS and `latency_dst_asimd_fmul_sp`: 3555.08. `fmul` does not even need to respect what the content of the target register was so all it has to do is respect the write-order now and can still have multiple `fmul`s running in the pipeline. `fmla` is dependent on the destination register (because it needs to add the product of the both source registers to it), so it needs to wait for the last `fmal` to finish its computation on the destination register and then add the calculated product to it.