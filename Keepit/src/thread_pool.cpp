#include "thread_pool.h"

ThreadPool::ThreadPool() {
	// THREAD_COUNT threads per CPU
	m_workersCurrentCount = 0;
	m_workersMaxCount = std::thread::hardware_concurrency() * THREAD_COUNT;
	m_workersMaxCount = m_workersMaxCount ? m_workersMaxCount : 1; // in case hardware_concurrency 0
	m_threads.resize(m_workersMaxCount);
}

size_t ThreadPool::maxThreadNumber() {
	return m_workersMaxCount;
}

void ThreadPool::execute(std::function<void()> lambda) {
	if (m_workersCurrentCount + 1 > m_workersMaxCount) { return; }
	m_threads[m_workersCurrentCount] = std::make_unique<std::thread>(std::thread(lambda));
	m_workersCurrentCount++;
}

void ThreadPool::stopAll() {
	m_threads.clear();
}

void ThreadPool::waitAll() {
	for (int i = 0; i < (int)(this->m_threads.size()); ++i) {
		if (m_threads[i]->joinable())
			m_threads[i]->join();
	}
}


ThreadPool::~ThreadPool() {
	m_threads.clear();
}