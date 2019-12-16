#pragma once
#include<cstddef>

class LinearAllocator 
{
	size_t base = 0;
	size_t maxSize;
	char* memory;

public:
	LinearAllocator(size_t max = 200);
	char* alloc(size_t size);
	void reset();
	~LinearAllocator();
};