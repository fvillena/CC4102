#!/bin/bash
algorithm=$1
vertices=$((2**14))
echo "edges,elapsed_time"
for n in {16..24}
do
    for i in {0..50}
    do
        edges=$((2**$n))
        result=$(./measure $algorithm random $vertices $edges)
        IFS=$'\t' read elapsed_time distances <<< $result
        echo "$edges","$elapsed_time"
    done
done