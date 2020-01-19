#include<iostream>
#include<fstream>
#include<thread>
#include<exception>
#include<vector>
#include<mutex>
#include<string>
#include<functional>
#include<algorithm>
#include<queue>
#include"sort.h"

void sort_func(std::mutex& read, std::mutex& write, std::ifstream& input_file, std::ofstream& tmp_file, size_t memory_size) {
		std::unique_ptr<uint64_t[]> a(new uint64_t[memory_size / sizeof(uint64_t)]);
		while (true) {
			size_t read_count;
			{
				std::unique_lock<std::mutex> lock_read(read);
				input_file.read((char*)a.get(), memory_size);
				read_count = input_file.gcount();
			}

			if (read_count == 0) 
				break;
			std::sort(a.get(), a.get() + read_count / sizeof(uint64_t));

			{
				std::unique_lock<std::mutex> lock_write(write);
				tmp_file.write((char*)&read_count, sizeof(size_t));
				tmp_file.write((char*)a.get(), read_count);
			}
		}
};

void sort_file(const std::string input_path, const std::string output_path, const std::string tmp_path, size_t num_threads){
	const size_t memory_size = 3145728;//3 mb

	std::ifstream input_file(input_path, std::ios::binary);

	if (!input_file) 
		throw(std::runtime_error("Can't open input file\n"));
	
	std::ofstream out_file(output_path, std::ios::binary);

	if (!out_file) 
		throw(std::runtime_error("Can't open output file\n"));
	
	std::ofstream tmp_file(tmp_path, std::ios::binary);

	if (!tmp_file)
		throw(std::runtime_error("Can't open tmp file\n"));
	

	std::mutex read, write;

	std::vector<std::thread> threads(num_threads);
	auto thread_sort = std::bind(sort_func, std::ref(read), std::ref(write), std::ref(input_file), std::ref(tmp_file), memory_size);
	for (int i = 0; i < num_threads; ++i) {
	 	threads[i] = std::thread(thread_sort);
	}

	for (int i = 0; i < num_threads; ++i) 
		threads[i].join();

	tmp_file.close();
	input_file.close();

	input_file.open(tmp_path, std::ios::binary);
	if (!input_file) 
		throw(std::runtime_error("Can't open tmp file\n"));
	
	struct Small { //Содержит минимальный элемент сортированного массива, указатель на остальные и размер
	uint64_t val, pos, max;

	Small(uint64_t val_, uint64_t pos_, uint64_t max_)  //Содержит минимальный элемент сортированного массива, указатель на остальные и размер
	: val(val_), pos(pos_), max(max_) 
	{
	}

	bool operator>(const Small& A) const {
		return val > A.val;
	}

	};

	std::priority_queue<Small, std::vector<Small>, std::greater<Small>> que;

	size_t i = 0;

	while (true) {
		uint64_t tmp;
		size_t count;

		if (!input_file.read((char*)&count, sizeof(size_t))) 
			break;
		input_file.read((char*)&tmp, sizeof(uint64_t));

		que.emplace(Small( tmp, input_file.tellg(), (uint64_t)input_file.tellg() + count - sizeof(uint64_t) ));
		input_file.seekg(count - sizeof(uint64_t), std::ios::cur);
	}
	input_file.clear();

	while (!que.empty()) {

		auto smallest = que.top();
		auto smallest_val = smallest.val;
		auto smallest_pos = smallest.pos;
		auto smallest_max = smallest.max;
		que.pop();

		out_file.write((char*)&smallest_val, sizeof(uint64_t));
		if (smallest_pos >= smallest_max) continue;

		input_file.seekg(smallest_pos);
		uint64_t tmp;

		input_file.read((char*)&tmp, sizeof(uint64_t));
		que.emplace(Small( tmp,smallest_pos + sizeof(uint64_t),smallest_max ));
	}
}
