#!/bin/bash
while IFS="#" read -r A true_median
do
    algorithm=$1
    n=$(($(($(tr -dc ' ' <<<"$A" | awk '{ print length; }')))+1))
    result=$(./measure $algorithm $n 5 $A)
    result_splitted=(${result// / })
    median=${result_splitted[0]}
    if [ $((median)) = $((true_median)) ]; then
        echo -n "."
    else
        echo -n $median
    fi
done < test_cases.txt
echo ""