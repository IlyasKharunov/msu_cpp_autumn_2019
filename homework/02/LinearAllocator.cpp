#include "LinearAllocator.h"


LinearAllocator::LinearAllocator(size_t max)
	: maxSize(max)
	{
		if(maxSize != 0)
			memory = new char(maxSize);
		else
			memory = nullptr;
	}

char* LinearAllocator::alloc(size_t size){
	if (base + size > maxSize)
		return nullptr;
	else {
		char * ptr = &memory[base];
		base += size;
		return ptr;
	}
}

void LinearAllocator::reset() {
	base = 0;
}
LinearAllocator::~LinearAllocator(){
	delete [] memory;
}