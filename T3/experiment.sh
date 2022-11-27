#!/bin/bash
algorithm=$1
echo "n,c,elapsed_time"
for n_i in {16..26}
do
    n=$((2**$n_i))
    for c_i in {1..10}
    do
        c=$((1+2*$c_i))
        for i in {0..10}
            do
                result=$(./measure $algorithm $n $c random)
                IFS=$' ' read median elapsed_time <<< $result
                echo "$n","$c","$elapsed_time"
            done
    done
done