#include<string>
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<limits>
#include<vector>

bool can_stream(...) {
	return false;
}

template<class T>
bool can_stream(std::string& s, T&& t, typename decltype(std::cout << t)* = nullptr) {
	std::stringstream tmp_stream;
	tmp_stream << t;
	while (tmp_stream.rdbuf()->in_avail() != 0) tmp_stream >> s;
	return true;
}

void parse_args(std::vector<std::string>& args) {
	return;
}

template<class T,class... ArgsT>
void parse_args(std::vector<std::string>& args, T &&a, ArgsT&& ...arg) {
	args.emplace_back();
	if (can_stream(args.back(),a)) {
		parse_args(args, std::forward<ArgsT>(arg)...);
	}
	else throw (std::runtime_error("Cant output to stream"));
}

template<class... ArgsT>
std::string format(const std::string& s, ArgsT&&... arg) {
	std::vector<std::string> args;
	parse_args(args, std::forward<ArgsT>(arg)...);
	std::string ans = "";
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '{') {
			if (i == s.size() - 1) throw(std::runtime_error("too much {"));
			int num = stoll(s.substr(++i),&i);
			if (s[i] != '}') num = -1;
			if (num == -1) throw(std::runtime_error("Wrong input in brackets"));
			if (num >= args.size()) throw(std::runtime_error("Not enough arguments"));
			ans += args[num];
		}
		else if (s[i] == '}') throw(std::runtime_error("too much }"));
		else ans += s[i];
	}
	return ans;
}