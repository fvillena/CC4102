#!/bin/bash
algorithm=$1
echo "string_length,distance,elapsed_time,X,Y"
for n in {3..15}
do
    for i in {1..50}
    do
        string_length=$((2**$n))
        X=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        Y=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        result=$(./measure $algorithm $X $Y)
        result_splitted=(${result// / })
        distance=${result_splitted[0]}
        elapsed_time=${result_splitted[1]}
        echo $string_length","$distance","$elapsed_time","$X","$Y
    done
done