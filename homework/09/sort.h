#pragma once

void sort_file(const std::string & in_path, const std::string & output_path, const std::string & tmp_path = "tmp.dat", size_t num_threads = 2);
void sort_file(const char* in_path, const char* output_path, const char* tmp_path = "tmp.dat", size_t num_threads = 2);