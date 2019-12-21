#pragma once
#include<iostream>
#include<thread>
#include<future>
#include<vector>
#include<queue>
#include <functional>

class ThreadPool {
	std::queue<std::function<void()>> tasks;
	std::mutex work_mutex;
	std::condition_variable condition;
	std::vector<std::thread> threads;

	size_t _poolSize;
	
	bool stop = false;

	void ThreadWork() {
		while ((!stop) or tasks.size()!=1) {
			std::unique_lock<std::mutex> lock(work_mutex);

			condition.wait(lock, [this]() {return !(tasks.empty() and (!stop)); });
			if (stop) 
				break;

			auto task = std::move(tasks.front());
			tasks.pop();

			lock.unlock();
			task();

		}
	}
public:
	explicit ThreadPool(size_t poolSize):_poolSize(poolSize) {
		for (size_t i = 0; i < poolSize; i++) {
			threads.emplace_back([this]() {ThreadWork(); });
		}
	}

	~ThreadPool() {
		std::unique_lock<std::mutex> lock(work_mutex);

		stop = true;

		condition.notify_all();
		lock.unlock();
		
		for (int i = 0; i < _poolSize; i++) 
			threads[i].join();
	}

	template <class Func, class... Args>
	auto exec(Func&& func, Args... args)->std::future<decltype(func(args...))> {
		using T = decltype(func(args...));
		auto f = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

		auto task = std::make_shared< std::promise<T> >();

		std::function<void()> ff = [f, task]() {task->set_value(f()); };

		{
			std::unique_lock<std::mutex> lock(work_mutex);

			if (stop)
				throw std::runtime_error("exec on stopped threadpool");

			tasks.emplace(ff);
		}

		condition.notify_one();

		return task->get_future();
	}
};