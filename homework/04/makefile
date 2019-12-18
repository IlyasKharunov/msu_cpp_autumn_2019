all: test
test.out: test.cpp
	g++ -c -o test.out test.cpp
Bigint.out: Bigint.cpp
	g++ -c -o Bigint.out Bigint.cpp
test: Bigint.out test.out
	g++ -o test Bigint.out test.out
run: test
	./test