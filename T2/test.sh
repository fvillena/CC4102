#!/bin/bash
while IFS=';' read -r G true_distances
do
    algorithm=$1
    result=$(./measure $algorithm $G)
    IFS=$'\t' read elapsed_time distances <<< $result
    if [ "$(echo $distances | xargs)" == "$true_distances" ]; then
        echo -n "."
    else
        echo -n "F"
    fi
done < test_cases.txt
echo ""