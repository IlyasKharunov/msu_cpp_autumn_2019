#include<limits>
#include<memory>
#include<stdexcept>

#pragma once

template <class T>
class Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using rvalue_reference = T&&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	Allocator()  = default;
	~Allocator()  = default;

	pointer address(reference x) const {
		return &x;
	}
	const_pointer address(const_reference x) const {
		return &x;
	}

	pointer allocate(size_type n) {
		pointer p= (pointer)malloc(n * sizeof(value_type));
		if (p == nullptr) throw std::bad_alloc();
		return p;
	}

	void deallocate(pointer p, size_type n = 0) {
		free(p);
	}

	size_type max_size() const noexcept {
		return std::numeric_limits<size_type>::max();
	}

	void construct(pointer p, const_reference val) {
		new(p) T(val);
	}

	void construct(pointer p, rvalue_reference val) {
		new(p) T(std::move(val));
	}

	void destroy(pointer p) {
		p->~T();
	}
};