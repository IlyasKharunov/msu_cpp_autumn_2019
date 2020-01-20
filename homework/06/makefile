all: test

test.o: test.cpp
	g++ -c -o test.o test.cpp

canstr.o: canstr.cpp
	g++ -c -o canstr.o canstr.cpp

test: test.o canstr.o
	g++ -o test test.o canstr.o

run: test
	./test