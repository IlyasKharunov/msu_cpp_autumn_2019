#pragma once
#include<iostream>
#include<thread>
#include<future>
#include<vector>
#include<queue>
#include <functional>

template<typename F, typename T>
void setv(const std::shared_ptr<std::promise<T>> & p, F && f);

template<typename F>
void setv(const std::shared_ptr<std::promise<void>> & p, F && f);

class ThreadPool {
	std::queue<std::function<void()>> tasks;
	std::mutex work_mutex;
	std::condition_variable condition;
	std::vector<std::thread> threads;

	size_t _poolSize;
	
	bool stop = false;

	void ThreadWork();
public:
	explicit ThreadPool(size_t poolSize);

	~ThreadPool();

	template <class Func, class... Args>
	auto exec(Func&& func, Args... args)->std::future<decltype(func(args...))>;
};

#include "ThreadPool.tpp"