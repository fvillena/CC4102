experiment: measure
	./experiment.sh 1 > algorithm_1_results.csv
	./experiment.sh 2 > algorithm_2_results.csv

test: measure
	./test.sh 1
	./test.sh 2

measure: measure.cpp *.h
	g++ -O3 measure.cpp -o measure

clean:
	rm -f measure *.csv