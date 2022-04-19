#!/bin/bash

for i in {1..160}
do 
    (export OMP_PLACES='{51}' export OMP_NUM_THREADS=$i; build/micro_asimd)
done