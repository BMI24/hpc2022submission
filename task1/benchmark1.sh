#!/bin/bash

for i in {1..160}
do 
    (export OMP_NUM_THREADS=$i; build/micro_asimd)
done