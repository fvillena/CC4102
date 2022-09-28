#!/bin/bash
test () {
    algorithm=$1
    X=$2
    Y=$3
    true_distance=$4
    result=$(./measure $algorithm $X $Y)
    result_splitted=(${result// / })
    distance=${result_splitted[0]}
    if [ $((distance)) = $((true_distance)) ]; then
        echo -n "OK"
    else
        echo -n "FAIL"
    fi
}
while IFS=" " read -r X Y true_distance
do
   echo "$(test $1 $X $Y $true_distance)"
done < test_cases.txt