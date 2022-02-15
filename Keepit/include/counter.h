#pragma once
#include "dictionary.h"
#include "mapped_file.h"
#include "thread_pool.h"
#include <memory>


/*
* Class that count number of word in file
* workerFunction can do work in parall
*/
class FileWordCounter {
	private:
		Dictionary m_dic;
		ThreadPool m_tp;
		std::unique_ptr<MappedFile> m_mf;
		size_t m_pageSize;

		FileWordCounter(const char* path);
		void workerFunction(const int offset);
		void addWord(const int start, const int end);
		inline
		bool isSeparator(const char c) {
			return c == ' ' || c == '\n' || c == '\t' || c == '\r';
		}
	public:
		FileWordCounter(FileWordCounter& other) = delete;
		void operator=(const FileWordCounter&) = delete;

		/*method to create FileWordCounter 
		* @param path - cahr* file path
		* @return  unique_ptr<FileWordCounter> or nullptr
		*/
		static std::unique_ptr<FileWordCounter> createFileWordCounter(
			const char* path
		);

		/*method to count words in file
		* @return  size_t number of words
		*/
		size_t count();
		

};