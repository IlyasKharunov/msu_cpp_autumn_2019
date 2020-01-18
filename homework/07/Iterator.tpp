#pragma once
template <class T>
Iterator<T>::Iterator(T* ptr) : ptr_(ptr) {}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
	return ptr_ == other.ptr_;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
	return !(*this == other);
}

template<class T>
T& Iterator<T>::operator*() const {
	return *ptr_;
}

template<class T>
Iterator<T>& Iterator<T>::operator++() {
	++ptr_;
	return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator--() {
	--ptr_;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator+(int offset) const {
	return Iterator(ptr_ + offset);
}

template<class T>
Iterator<T> Iterator<T>::operator-(int offset) const {
	return Iterator(ptr_ - offset);
}

template<class T>
int Iterator<T>::operator-(const Iterator<T>& it) const {
	return ptr_ - it.ptr_;
}

template<class T>
Iterator<T> operator+(int offset, const Iterator<T>& it) {
	return it + offset;
}

template <class T>
rIterator<T>::rIterator(T* ptr) : ptr_(ptr) {}

template<class T>
bool rIterator<T>::operator==(const rIterator<T>& other) const {
	return ptr_ == other.ptr_;
}

template<class T>
bool rIterator<T>::operator!=(const rIterator<T>& other) const {
	return !(*this == other);
}

template<class T>
T& rIterator<T>::operator*() const {
	return *ptr_;
}

template<class T>
rIterator<T>& rIterator<T>::operator++() {
	--ptr_;
	return *this;
}

template<class T>
rIterator<T>& rIterator<T>::operator--() {
	++ptr_;
	return *this;
}

template<class T>
rIterator<T> rIterator<T>::operator+(int offset) const {
	return rIterator(ptr_ - offset);
}

template<class T>
rIterator<T> rIterator<T>::operator-(int offset) const {
	return rIterator(ptr_ + offset);
}

template<class T>
int rIterator<T>::operator-(const rIterator<T>& it) const {
	return ptr_ + it.ptr_;
}

template<class T>
rIterator<T> operator+(int offset, const rIterator<T>& it) {
	return it - offset;
}

template<class T>
bool operator==(const Iterator<T>& it, const rIterator<T>& rit) {
	return it.ptr_ == rit.ptr_;
}

template<class T>
bool operator==(const rIterator<T>& rit, const Iterator<T>& it) {
	return it.ptr_ == rit.ptr_;
}

template<class T>
bool operator!=(const Iterator<T>& it, const rIterator<T>& rit) {
	return it.ptr_ != rit.ptr_;
}

template<class T>
bool operator!=(const rIterator<T>& rit, const Iterator<T>& it) {
	return it.ptr_ != rit.ptr_;
}