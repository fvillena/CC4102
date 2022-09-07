#!/bin/bash
algorithm=$1
for n in {3..15}
do
    for i in {1..50}
    do
        string_length=$((2**$n))
        X=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        Y=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        ti=$(date +%s%N)
        distance=$(./measure $algorithm $X $Y)
        tf=$(date +%s%N)
        elapsed_time=$((($tf - $ti)/1000000))
        echo $string_length $distance $elapsed_time
    done
done