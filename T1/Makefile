experiment: measure
	./experiment.sh 1 > algorithm_1_results.csv
	./experiment.sh 2 > algorithm_2_results.csv

test: measure
	./test.sh

measure: measure.c
	gcc -O3 measure.c -o measure

clean:
	rm -f measure *.csv