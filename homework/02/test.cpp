#include<iostream>
#include "LinearAllocator.h"
using namespace std;

int main()
{
	LinearAllocator mem(200);
	char* ptr;

	cout << (void*)(ptr = mem.alloc(60)) << endl;
	cout << (void*)(ptr = mem.alloc(60)) << endl;
	cout << (void*)(ptr = mem.alloc(0)) << endl;
	cout << (void*)(ptr = mem.alloc(80)) << endl;
	cout << (void*)(ptr = mem.alloc(60)) << '\n' << endl;

	mem.reset();

	cout << (void*)(ptr = mem.alloc(220)) << endl;
	cout << (void*)(ptr = mem.alloc(60)) << endl;
	cout << (void*)mem.alloc(60) << '\n' << endl;

	mem.reset();

	LinearAllocator mem1(0);

	cout << (void*)(ptr = mem1.alloc(60)) << endl;
	cout << (void*)(ptr = mem1.alloc(0)) << '\n' << endl;

	LinearAllocator mem2(2);

	cout << (void*)(ptr = mem2.alloc(60)) << endl;
	cout << (void*)(ptr = mem2.alloc(2)) << endl;

	return 0;
}