all: test

Matrix.out: Matrix.cpp
	g++ -c -o Matrix.out Matrix.cpp

test.out: test.cpp
	g++ -c -o test.out test.cpp

test: Matrix.out test.out
	g++ -o test Matrix.out test.out

run: test
	./test