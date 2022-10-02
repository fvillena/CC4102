#!/bin/bash
algorithm=$1
if (( $algorithm == 3 ))
    then
        echo "string_length,distance,sub_matrix_size,elapsed_time,X,Y"
    else
        echo "string_length,distance,elapsed_time,X,Y"
fi
for n in {3..15}
do
    for i in {1..50}
    do
        string_length=$((2**$n))
        X=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        Y=$(cat /dev/urandom | tr -dc '[:alpha:]' | fold -w $string_length | head -n 1)
        if (( $algorithm == 3 ))
        then
            for s in 0 1 2 3 4 5 9 10 12 13
            do
                size=$((2**$s))
                if (($string_length % $size == 0))
                then
                    result=$(./measure $algorithm $(($size+1)) $X $Y)
                    result_splitted=(${result// / })
                    distance=${result_splitted[0]}
                    elapsed_time=${result_splitted[1]} # microseconds
                    echo $string_length","$distance","$size","$elapsed_time","$X","$Y
                fi
            done
        else
            result=$(./measure $algorithm $X $Y)
            result_splitted=(${result// / })
            distance=${result_splitted[0]}
            elapsed_time=${result_splitted[1]} # microseconds
            echo $string_length","$distance","$elapsed_time","$X","$Y
        fi
    done
done