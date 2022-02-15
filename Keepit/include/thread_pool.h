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
		/*method to get max number of threads supported
		* @return  size_t max thread number
		*/
		size_t maxThreadNumber();

		/*method to execute user function async
		* @param lambda - std::function<void()> user function
		*/
		void execute(std::function< void() > lambda);

		/*method waits for execution of all threads
		*/
		void waitAll();

		/*method kills all threads
		*/
		void stopAll();
		~ThreadPool();
};
