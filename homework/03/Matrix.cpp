#include "Matrix.h"

Matrix::Matrix(int rownum, int colnum) {
	rows = rownum;
	cols = colnum;
	matrix = new int[rows*cols];
}

Matrix::column::column(const Matrix* ptr, int rownum, int rowidth) 
	: base(rownum), width(rowidth), e(0), ce(ptr) 
{
}

Matrix::column::column(Matrix* ptr, int rownum, int rowidth) 
	: base(rownum), width(rowidth), e(ptr), ce(0)
{
}

const int& Matrix::column::operator[](int columnum) const {
	if (columnum >= width)
		throw std::out_of_range("");
	return ce->matrix[base*width + columnum];
}

int& Matrix::column::operator[](int columnum) {
	if (columnum >= width)
		throw std::out_of_range("");
	return e->matrix[base*width + columnum];
}

std::size_t Matrix::getRows() const {
	return rows;
}

std::size_t Matrix::getColumns() const {
	return cols;
}

const Matrix::column Matrix::operator[](int row) const {
	if (row >= rows)
		throw std::out_of_range("");
	return Matrix::column(this, row,cols);
}

Matrix::column Matrix::operator[](int row) {
	if (row >= rows)
		throw std::out_of_range("");
	return Matrix::column(this, row,cols);
}

Matrix& Matrix::operator*=(int a) {
	for (int i = 0;i < rows*cols;i++)
		matrix[i] *= a;
	return *this;
}

bool Matrix::operator==(const Matrix& b) const {
	if (cols != b.cols or rows != b.rows)
		return false;
	for (int i = 0; i<rows*cols;i++) {
		if (matrix[i] != b.matrix[i])
			return false;
	}
	return true;
}

bool Matrix::operator!=(const Matrix& b) const {
	if (cols != b.cols or rows != b.rows)
		return true;
	for (int i = 0; i<rows*cols;i++) {
		if (matrix[i] != b.matrix[i])
			return true;
	}
	return false;
}

Matrix::~Matrix() {
	delete[] matrix;
}