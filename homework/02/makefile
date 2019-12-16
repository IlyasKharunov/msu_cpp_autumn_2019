all: test

LinearAllocator.out: LinearAllocator.cpp
	g++ -c -o LinearAllocator.out LinearAllocator.cpp

test.out: test.cpp
	g++ -c -o test.out test.cpp

test: LinearAllocator.out test.out
	g++ -o test LinearAllocator.out test.out

run: test
	./test