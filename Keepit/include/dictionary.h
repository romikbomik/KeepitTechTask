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
		/*method to get size of Dictionary thread safe
		* @return  size_t number of unique strings 
		*/
		size_t size();

		/*method that insert string into Dictionary thread safe
		* @return  bool true inserted/false already present
		*/
		bool insert(const std::string& str);
		Dictionary();
};