#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <functional>

#ifndef  THREAD_COUNT
	#define THREAD_COUNT 3
#endif



/*
* Class that manages threads, as alternaty boost lib can be used
*/
class ThreadPool {
	private:
		unsigned int m_workersMaxCount;
		unsigned int m_workersCurrentCount;
		std::vector<std::unique_ptr<std::thread>> m_threads;
		//std::vector<std::shared_ptr<std::atomic<bool>>> m_flags;

	public:
		ThreadPool();
		size_t maxThreadNumber();
		void execute(std::function< void() > lambda);
		void waitAll();
		void stopAll();
		~ThreadPool();
};
