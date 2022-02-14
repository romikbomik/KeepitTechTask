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
		const void* data() const;
		size_t size() const;
		static MappedFile* openFile(const char* path);
		MappedFile(MappedFile& other) = delete;
		void operator=(const MappedFile&) = delete;
		~MappedFile();
};
