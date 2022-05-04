#!/bin/bash

for i in {1..48}
do 
    (export OMP_PLACES={0}:$i:1; export OMP_NUM_THREADS=$i; build/micro_asimd)
    (export OMP_PLACES={0}:$i:1; export OMP_NUM_THREADS=$i; build/micro_sve)
done