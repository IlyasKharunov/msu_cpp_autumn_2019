#include "Matrix.h"
#include<iostream>
#include <cassert>
using namespace std;

int main() 
{
	size_t rows = 2, cols = 3;

	Matrix a(rows, cols);

	assert(a.getRows() == 2);
	assert(a.getColumns() == 3);

	try 
	{
		for(int i = 0;i<a.getRows();i++) {
			for(int j = 0;j<a.getColumns();j++)
				a[i][j] = 10;
		}
		
		cout << a[1][2] << endl;

		int x = a[0][2];
		double y = a[1][1];

		cout << x << endl;
		cout << y << endl;
	}
	catch (out_of_range) {
		cout << "out of range" << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}

	try 
	{
		int x = a[2][3];
		cout << x << endl;		
	}
	catch (out_of_range) {
		cout << "out of range" << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}

	try 
	{
		cout << "lol" << endl;
		const Matrix a(2,3) , b(1,3), c(2,3);
		if (a == b)
			cout << "a == b" << endl;
		if (a != b)
			cout << "a != b" << endl;

		if (a == c)
			cout << "a == b" << endl;
		if (a != c)
			cout << "a != b" << endl;
	}
	catch (out_of_range) {
		cout << "out of range" << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}

	try 
	{
		for(int i = 0;i<a.getRows();i++) {
			for(int j = 0;j<a.getColumns();j++)
				a[i][j] = 10;
		}

		Matrix b(rows,cols);

		for(int i = 0;i<b.getRows();i++) {
			for(int j = 0;j<b.getColumns();j++)
				b[i][j] = 30;
		}

		a *= 3;

		if (a == b)
			cout << "a == b" << endl;

		a[0][0] = 2;

		if (a != b)
			cout << "a != b" << endl;
	}
	catch (out_of_range) {
		cout << "out of range" << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}
	return 0;
}