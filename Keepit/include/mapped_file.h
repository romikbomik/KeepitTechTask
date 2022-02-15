#pragma once
#include <windows.h>


/*
* Class that loads file into virtual memmory
*/
class MappedFile {
	private:
		 const void const * m_data;
		 const size_t m_size;
		 const HANDLE m_handle;

		 MappedFile();
		 MappedFile(HANDLE h, size_t s, void* d);

	public:
		/*method to get pointer for data
		* @return  const void*  
		*/
		const void* data() const;

		/*method to get size of data
		* @return  size_t data size
		*/
		size_t size() const;

		/*method to create MappedFile
		* @param path - cahr* file path
		* @return  MappedFile* or nullptr
		*/
		static MappedFile* openFile(const char* path);
		MappedFile(MappedFile& other) = delete;
		void operator=(const MappedFile&) = delete;
		~MappedFile();
};
