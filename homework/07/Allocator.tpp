#include<limits>
#include<memory>
#include<stdexcept>

template <class T>
typename Allocator<T>::pointer Allocator<T>::address(Allocator<T>::reference x) const {
	return &x;
}
template <class T>
typename Allocator<T>::const_pointer Allocator<T>::address(Allocator<T>::const_reference x) const {
	return &x;
}

template <class T>
typename Allocator<T>::pointer Allocator<T>::allocate(Allocator<T>::size_type n) {
	Allocator<T>::pointer p= (Allocator<T>::pointer)malloc(n * sizeof(Allocator<T>::value_type));
	if (p == nullptr) throw std::bad_alloc();
	return p;
}

template <class T>
void Allocator<T>::deallocate(Allocator<T>::pointer p, Allocator<T>::size_type n) {
	free(p);
}

template <class T>
typename Allocator<T>::size_type Allocator<T>::max_size() const noexcept {
	return std::numeric_limits<Allocator<T>::size_type>::max();
}

template <class T>
void Allocator<T>::construct(Allocator<T>::pointer p, Allocator<T>::const_reference val) {
	new(p) T(val);
}

template <class T>
void Allocator<T>::destroy(Allocator<T>::pointer p) {
	p->~T();
}