#!/bin/bash
while IFS=" " read -r X Y true_distance
do
    algorithm=$1
    if (( $algorithm == 3 ))
    then
        l=${#X}
        x=$(($l+1))
        result=$(./measure $algorithm $x $X $Y)
    else
        result=$(./measure $algorithm $X $Y)
    fi
    result_splitted=(${result// / })
    distance=${result_splitted[0]}
    if [ $((distance)) = $((true_distance)) ]; then
        echo -n "."
    else
        echo -n "F"
    fi
done < test_cases.txt
echo ""