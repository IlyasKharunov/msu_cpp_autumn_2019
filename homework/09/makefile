all: test

test.out: test.cpp
	g++ -c -o test.out test.cpp

sort.out: sort.cpp
	g++ -c -o sort.out sort.cpp

test: test.out sort.out
	g++ -pthread -o test test.out sort.out

run: test
	./test