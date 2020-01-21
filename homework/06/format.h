#include<string>
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<limits>
#include<vector>
#pragma once

bool can_stream(...);

template<class T>
bool can_stream(std::string& s, T&& t, typename decltype(std::cout << t)* = nullptr);

void parse_args(std::vector<std::string>& args);

template<class T,class... ArgsT>
void parse_args(std::vector<std::string>& args, T &&a, ArgsT&& ...arg);

template<class... ArgsT>
std::string format(const std::string& s, ArgsT&&... arg);
