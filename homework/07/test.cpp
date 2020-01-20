#include<iostream>
#include<cassert>
#include"Vector.h"

using namespace std;


int main() {
	Vector<int> v;
	assert(v.size() == 0);
	assert(v.empty() == 1);
	v.push_back(0);
	assert(v.empty() == 0);
	assert(v.size() == 1);

	for (int i = 0; i < 10; i++) v.push_back(12);
	for (int i = 0; i < 100; i++) v.push_back(13);

	assert(v.size() == 111);
	assert(v[0] == 0);
	for (int i = 1; i < 11; i++) assert(v[i] == 12);
	for (int i = 11; i < 111; i++) assert(v[i] == 13);

	for (int i = 0; i < 5; i++) v.pop_back();
	for (int i = 0; i < 5; i++) v.push_back(14);
	assert(v.size() == 111);
	for (auto i = v.begin(); i != v.end(); ++i) cout << *i << ' ';
	cout << "\n--------------------------------------\n";

	Vector<int> a(3,666);
	for (int i = 0; i < 10; i++) a.push_back(i);
	for (auto i : a) cout << i << ' ';
	cout << a.size() << endl;
	cout << "\n--------------------------------------\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 13);
	
	for (int i = 0; i < a.size(); i++) cout << a[i] << ' ';
	cout << "\n\n";
	auto it = a.begin();
	*it = 888;
	a[1] = 777;
	for (int i = 0; i < a.size(); i++) cout << a[i] << ' ';
	cout << "\n\n";


	for (int i = 0; i < 5; i++) a.pop_back();
	for (auto i : a) cout << i << ' ';
	cout << "\n--------------------------------------\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 8);

	a.resize(10,8);
	for (auto i : a) cout << i << ' ';
	cout << "\n--------------------------------------\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 10);

	a.resize(2, 3);
	for (auto i : a) cout << i << ' ';
	cout << "\n--------------------------------------\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 2);

	a.clear();
	for (auto i : a) cout << i << ' ';
	cout << "\n--------------------------------------\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 0);

	Vector<string> b;
	assert(b.size() == 0);
	assert(b.empty() == 1);
	b.push_back("string");
	assert(b.empty() == 0);
	assert(b.size() == 1);
	b.reserve(100);
	assert(b.size() == 1);
	b.reserve(0);
	assert(b.size() == 1);

	const Vector<double> c(10, 42.0);
	auto t = c.begin();
	double tmp = *t;
	//*t = tmp;
	for (auto i : c) cout << i << ' ';
	cout << "\n--------------------------------------\n";
	for (auto i = c.rbegin(); i != c.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	
	for (int i = 0; i < c.size(); i++) cout << c[i] << ' ';
	cout << "\n\n";
	
	assert(c.size() == 10);
	assert(c.empty() == 0);
}