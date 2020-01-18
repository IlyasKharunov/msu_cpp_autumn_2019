#include"Allocator.h"
#include"Iterator.h"
#include<algorithm>

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type capacity)
	: data_(alloc_.allocate(capacity)),size_(0),capacity_(capacity) 
	{
	}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type capacity, value_type value) 
	: data_(alloc_.allocate(capacity)), size_(0), capacity_(capacity) 
	{
		for (; size_ < capacity_; size_++) alloc_.construct(data_ + size_, value);
	}

template <class T, class Alloc>
Vector<T, Alloc>::~Vector() {
	for (; size_ > 0; size_--) alloc_.destroy(data_ + size_ - 1);
	alloc_.deallocate(data_);
}


template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::operator[](Vector<T, Alloc>::size_type pos) {
	return data_[pos];
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::operator[](Vector<T, Alloc>::size_type pos) const {
	return data_[pos];
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(Vector<T, Alloc>::value_type&& value) {
	if (size_ == capacity_) {
		capacity_ = std::max(capacity_*2, size_type(1));
		auto newData = alloc_.allocate(capacity_);
		for (size_type s = 0; s < size_; s++) {
			alloc_.construct(newData + s, data_[s]);
			alloc_.destroy(data_ + s);
		}
		std::swap(data_, newData);
		alloc_.deallocate(newData);
	}
	alloc_.construct(data_ + size_, value);
	size_++;
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const Vector<T, Alloc>::value_type& value) {
	if (size_ == capacity_) {
		capacity_ = std::max(capacity_*2, size_type(1));
		auto newData = alloc_.allocate(capacity_);
		for (size_type s = 0; s < size_; s++) {
			alloc_.construct(newData + s, data_[s]);
			alloc_.destroy(data_ + s);
		}
		std::swap(data_, newData);
		alloc_.deallocate(newData);

	}
	alloc_.construct(data_ + size_, value);
	size_++;
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back() {
	if (size_ == 0) throw std::runtime_error("No elements to pop");
	size_--;
	alloc_.destroy(data_ + size_);
}

template <class T, class Alloc>
bool Vector<T, Alloc>::empty() const {
	return size_ == 0;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const {
	return size_;
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear() {
	while (size_ != 0) alloc_.destroy(data_ + --size_);
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(Vector<T, Alloc>::size_type count, Vector<T, Alloc>::value_type value) {
	if (count > capacity_) {
		capacity_ = std::max(capacity_*2, count);
		auto newData = alloc_.allocate(capacity_);
		for (size_type s=0; s < size_; s++) {
			alloc_.construct(newData + s, data_[s]);
			alloc_.destroy(data_ + s);
		}
		std::swap(data_, newData);
		alloc_.deallocate(newData);
		for (; size_ < count; size_++) alloc_.construct(data_ + size_, value);
	}
	else if (count > size_) {
		for (; size_ < count; size_++) alloc_.construct(data_ + size_, value);
	}
	else {
		for (; size_ > count; size_--) alloc_.destroy(data_ + size_ - 1);
	}
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(Vector<T, Alloc>::size_type count) {
	if (count <= capacity_) return;
	capacity_ = count;
	auto newData = alloc_.allocate(capacity_);
	for (size_type s=0; s < size_; s++) {
		alloc_.construct(newData + s, data_[s]);
		alloc_.destroy(data_ + s);
	}
	std::swap(data_, newData);
	alloc_.deallocate(newData);
}

template <class T, class Alloc>
Iterator<T> Vector<T, Alloc>::begin() {
	return Iterator<T>(data_);
}

template <class T, class Alloc>
Iterator<T> Vector<T, Alloc>::end() {
	return Iterator<T>(data_+size_);
}

template <class T, class Alloc>
rIterator<T> Vector<T, Alloc>::rbegin() {
	return rIterator<T>(data_ + size_ - 1);
}

template <class T, class Alloc>
rIterator<T> Vector<T, Alloc>::rend() {
	return rIterator<T>(data_ - 1);
}

template <class T, class Alloc>
const Iterator<const T> Vector<T, Alloc>::begin() const {
	return Iterator<const T>(data_);
}

template <class T, class Alloc>
const Iterator<const T> Vector<T, Alloc>::end() const {
	return Iterator<const T>(data_ + size_);
}

template <class T, class Alloc>
const rIterator<const T> Vector<T, Alloc>::rbegin() const {
	return rIterator<const T>(data_ + size_ - 1);
}

template <class T, class Alloc>
const rIterator<const T> Vector<T, Alloc>::rend() const {
	return rIterator<const T>(data_ - 1);
}