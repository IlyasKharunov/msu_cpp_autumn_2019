#include"Allocator.h"
#include"Iterator.h"
#include<algorithm>

#pragma once
template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using iterator = Iterator<T>;
	using pointer = T*;
	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;

	Vector(size_type capacity = 0);

	Vector(size_type capacity, value_type value);

	~Vector();

	reference operator[](size_type pos);

	const_reference operator[](size_type pos) const;

	void push_back(value_type&& value);

	void push_back(const value_type& value);

	void pop_back();

	bool empty() const;

	size_type size() const;

	void clear();

	void resize(size_type count, value_type value=value_type());

	void reserve(size_type count);

	Iterator<T> begin();

	Iterator<T> end();

	rIterator<T> rbegin();

	rIterator<T> rend();

	const Iterator<const T> begin() const;

	const Iterator<const T> end() const;

	const rIterator<const T> rbegin() const;

	const rIterator<const T> rend() const;
	
private:
	Alloc alloc_;
	pointer data_;
	size_type size_, capacity_;
};

#include "Vector.tpp"
