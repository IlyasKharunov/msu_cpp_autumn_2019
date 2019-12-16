all: calc

run: calc
	./calc 2 + 2

test: calc
	python3 ./test.py

calc: calc.cpp
	g++ -o calc calc.cpp
