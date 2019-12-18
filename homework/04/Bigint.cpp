#include "Bigint.h"
#include<algorithm>

using namespace std;

size_t BigInt::reserve_size = 10;
BigInt::BigInt(int a)
	: size(0), is_positive(a >= 0), maxsize(0)
{
	if (a < 0) a = -a;
	int tmp = a;

	while (tmp != 0) {
		maxsize++;
		tmp /= 10;
	}

	memory = new char[maxsize];
	while (a != 0) {
		memory[size++] = (a % 10);
		a /= 10;
	}
}

BigInt::BigInt(const BigInt& a)
	: memory(new char[a.maxsize]), is_positive(a.is_positive), maxsize(a.maxsize), size(a.size) 
{
	copy(a.memory, a.memory + a.size, memory);
}

BigInt::BigInt(BigInt&& a)
	: memory(a.memory), size(a.size), is_positive(a.is_positive), maxsize(a.maxsize)
{
	a.memory = nullptr;
	a.maxsize = 0;
	a.size = 0;
}

BigInt& BigInt::operator=(const BigInt& a) {
	if (this == &a) 
		return *this;
	char* tmp = new char[a.maxsize];
	delete[] memory;

	size = a.size;
	memory = tmp;
	copy(a.memory, a.memory + a.size, memory);
	is_positive = a.is_positive;
	maxsize = a.maxsize;

	return *this;
}

BigInt& BigInt::operator=(BigInt&& a){
	if (this == &a) 
		return *this;
	delete[] memory;

	size = a.size;
	maxsize = a.maxsize;
	is_positive = a.is_positive;
	memory = a.memory;
	a.memory = nullptr;
	a.size = 0;
	a.maxsize = 0;

	return *this;
}

BigInt::~BigInt(){
	delete[] memory;
}

BigInt BigInt::operator-() const {
	BigInt a(*this);
	a.is_positive = !is_positive;
	return a;
}

bool BigInt::operator>(const BigInt& a) const{

	if (is_positive != a.is_positive) 
		return is_positive > a.is_positive;

	bool bigger_module = false; // сравниваю по модулю
	if (size != a.size)
		bigger_module = (size > a.size);
	else {
		for (int i = size - 1; i >= 0; i--) {
			if (memory[i] != a.memory[i]) {
				bigger_module = (memory[i] > a.memory[i]);
				break;
			}
		}
	}
	if (is_positive)
		return bigger_module;
	else
		return !bigger_module;
}

bool BigInt::operator<(const BigInt& a) const{
	return a > *this;
}

bool BigInt::operator>=(const BigInt& a) const{
	return !(*this < a);
}

bool BigInt::operator<=(const BigInt& a) const{
	return !(*this > a);
}

bool BigInt::operator==(const BigInt& a) const{
	if (size == 0 and size == a.size)
		return true;
	if (is_positive != a.is_positive or size != a.size)
		return false;
	for (size_t i = 0; i < size; i++) 
		if (memory[i] != a.memory[i]) 
			return false;
	return true;
}

bool BigInt::operator!=(const BigInt& a) const{
	return !(*this == a);
}

BigInt operator+(const BigInt &b, const BigInt& a)
{
	bool add = false;
	BigInt ans;
	delete[] ans.memory;
	ans.memory = new char[max(b.maxsize, a.maxsize)];

	if ((b.is_positive and a.is_positive) or (!b.is_positive and !a.is_positive)) {
		ans.is_positive = b.is_positive;

		for (size_t i = 0; i < min(b.size, a.size); i++) {
			ans.memory[i] = (b.memory[i] + a.memory[i] + add) % 10;
			add = (b.memory[i] + a.memory[i] + add) > 9;
		}

		char* greater_int = (b.size > a.size) ? b.memory : a.memory;
		for (size_t i = min(b.size, a.size); i < max(b.size, a.size); i++) {
			ans.memory[i] = (greater_int[i] + add) % 10;
			add = (greater_int[i] + add) > 9;
		}

		if (add and max(b.size, a.size) == max(b.maxsize, a.maxsize)) {// выделяю больше памяти
			int biggestsize = max(b.maxsize,a.maxsize);
			auto tmp = new char[biggestsize + BigInt::reserve_size];

			copy(ans.memory, ans.memory + biggestsize, tmp);
			tmp[biggestsize] = add;

			delete[]ans.memory;
			ans.memory = tmp;
			ans.size = biggestsize + 1;
			ans.maxsize = biggestsize + BigInt::reserve_size;
		}
		else {
			if (add) 
				ans.memory[max(b.size, a.size)] = 1;
			ans.size = (add) ? max(b.size, a.size) + 1 : max(b.size, a.size);
			ans.maxsize = max(b.maxsize, a.maxsize);
		}
	}
	else {
		bool b_bigger = false; // сравниваю по модулю
		if (b.size != a.size)
			b_bigger = (b.size > a.size);
		else {
			for (int i = b.size - 1; i >= 0; i--) {
				if (b.memory[i] != a.memory[i]) {
					b_bigger = (b.memory[i] > a.memory[i]);
					break;
				}
			}
		}

		const BigInt* greater, * less;

		if (b_bigger) {
			greater = &b, less = &a;
			ans.is_positive = b.is_positive;
		}
		else {
			greater = &a, less = &b;
			ans.is_positive = a.is_positive;
		}

		for (size_t i = 0; i < less->size; i++) {
			char tmp = greater->memory[i] - less->memory[i] - add;
			add = tmp < 0;

			ans.memory[i] = (tmp >= 0) ? tmp : 10 + tmp;
		}
		for (size_t i = less->size; i < greater->size; i++) {
			char tmp = greater->memory[i] - add;
			add = tmp < 0;

			ans.memory[i] = (tmp >= 0) ? tmp : 10 + tmp;
		}

		ans.size = greater->size;
		ans.maxsize = greater->maxsize;

		while (ans.size > 0 and ans.memory[ans.size - 1] == 0) ans.size--;
		if (ans.size == 0) ans.is_positive = true;
	}
	return ans;
}

BigInt operator-(const BigInt& b, const BigInt& a){
	if (&b == &a) 
		return BigInt();

	BigInt nega;
	delete[]nega.memory;
	nega.memory = a.memory; // поверхностное копирование и newa = -a
	nega.is_positive = !a.is_positive;
	nega.size = a.size;
	nega.maxsize = a.maxsize;

	BigInt tmp = b + nega;
	nega.memory = nullptr;

	return tmp;
}

ostream& operator<<(ostream& out, const BigInt& a) {
	if (a.size==0) 
		return out << '0';
	if (!a.is_positive) 
		out << '-';
	for (int i = a.size - 1; i >= 0; i--) 
		out << char(a.memory[i]+'0');
	return out;
}