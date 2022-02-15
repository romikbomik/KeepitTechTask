#include "dictionary.h"

Dictionary::Dictionary() {}

size_t Dictionary::size() {
	std::lock_guard<std::mutex> lock(m_mtx);
	auto size = m_set.size();
	return size;
}

bool Dictionary::insert(const std::string& str) {
	std::lock_guard<std::mutex> lock(m_mtx);
	auto result = m_set.insert(str);
	return result.second;
}

