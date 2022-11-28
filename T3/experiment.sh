#!/bin/bash
algorithm=$1
echo "n,c,elapsed_time"
for n_i in {16..26}
do
    n=$((2**$n_i))
    if [[ $(($algorithm)) == 3 ]]
    then
        for c_i in {1..6}
        do
            c=$((10**$c_i))
            if [[ $(($c)) -lt $(($n)) ]]
            then
                for i in {0..10}
                do
                    result=$(./measure $algorithm $n $c random)
                    IFS=$' ' read median elapsed_time <<< $result
                    echo "$n","$c","$elapsed_time"
                done
            fi
        done
    else
        for c_i in {1..20}
        do
            c=$((1+2*$c_i))
            for i in {0..10}
            do
                result=$(./measure $algorithm $n $c random)
                IFS=$' ' read median elapsed_time <<< $result
                echo "$n","$c","$elapsed_time"
            done
        done
    fi
done