all: test
test.out: test.cpp
	g++ -c -o test.out test.cpp
BigInt.out: BigInt.cpp
	g++ -c -o BigInt.out BigInt.cpp
test: BigInt.out test.out
	g++ -o test BigInt.out test.out
run: test
	./test