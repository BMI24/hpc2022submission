# Übung 3 A64FX

## Task 2.4.1

Done, see src.

## Task 2.4.2

Done, see src.

## Task 2.4.3

Done, see src/plots. Replacing ASIMD by SVE resulted in (mostly) 4 times the GFLOP/s (see plots/fmla_dp_speedup.png and plots/fmla_sp_speedup.png). A single SVE FMLA instruction seems to take the same time as a single ASIMD FMLA instruction, but does 4 times the FP ops.