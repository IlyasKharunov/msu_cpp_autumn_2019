#pragma once
#include<stdexcept>

class Matrix {
	int* matrix;
	std::size_t rows, cols;
	class column {
		Matrix* e;
		const Matrix* ce;
		int base, width;
		public:
		column(const Matrix* ptr, int rownum, int rowidth);
		column(Matrix* ptr, int rownum, int rowidth);
		const int& operator[](int columnum) const;
		int& operator[](int columnum);
	};
	public:
	Matrix(int rownum, int colnum);
	std::size_t getRows() const;
	std::size_t getColumns() const;
	const column operator[](int row) const;
	column operator[](int row);
	Matrix& operator*=(int a);
	bool operator==(const Matrix& b) const;
	bool operator!=(const Matrix& b) const;
	~Matrix();
};