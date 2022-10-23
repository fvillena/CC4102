test: measure
	./test.sh 1

measure: measure.cpp *.h
	g++ -O3 measure.cpp -o measure

clean:
	rm -f measure *.csv