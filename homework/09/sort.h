#pragma once

struct Small { //Содержит минимальный элемент сортированного массива, указатель на остальные и размер
	uint64_t val, pos, max;
	Small(uint64_t val_, uint64_t pos_, uint64_t max_);
	bool operator>(const Small& A) const;
};
void sort_file(const char* in_path, const char* output_path, const char* tmp_path = "tmp.dat", size_t num_threads = 2);
