#pragma once
template <class T>
class Iterator {
	T* ptr_;
public:
	explicit Iterator(T* ptr);

	bool operator==(const Iterator<T>& other) const;

	bool operator!=(const Iterator<T>& other) const;

	T& operator*() const;

	Iterator& operator++();

	Iterator& operator--();

	Iterator operator+(int offset) const;

	Iterator operator-(int offset) const;

	int operator-(const Iterator<T>& it) const;

};

template<class T>
Iterator<T> operator+(int offset, const Iterator<T>& it);

template <class T>
class rIterator {
	T* ptr_;
public:
	explicit rIterator(T* ptr);

	bool operator==(const rIterator<T>& other) const;

	bool operator!=(const rIterator<T>& other) const;

	T& operator*() const;

	rIterator& operator++();

	rIterator& operator--();

	rIterator operator+(int offset) const;

	rIterator operator-(int offset) const;

	int operator-(const rIterator<T>& it) const;

};

template<class T>
rIterator<T> operator+(int offset, const rIterator<T>& it);

template<class T>
bool operator==(const Iterator<T>& it, const rIterator<T>& rit);

template<class T>
bool operator==(const rIterator<T>& rit, const Iterator<T>& it);

template<class T>
bool operator!=(const Iterator<T>& it, const rIterator<T>& rit);

template<class T>
bool operator!=(const rIterator<T>& rit, const Iterator<T>& it);

#include "Iterator.tpp"