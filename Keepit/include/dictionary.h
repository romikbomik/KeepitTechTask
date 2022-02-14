#pragma once
#include<unordered_set>
#include<mutex>


/*
* Class that stores unique strings
* all methods are thread safe
*/
class Dictionary {
	private:
		std::unordered_set<std::string> m_set;
		std::mutex m_mtx;

	public:
		size_t size();
		bool insert(const std::string& str);
		Dictionary();
};