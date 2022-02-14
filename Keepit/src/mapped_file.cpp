#include "mapped_file.h"


MappedFile::MappedFile(HANDLE h, size_t s, void* d) :m_handle(h), m_size(s), m_data(d) {
}

MappedFile* MappedFile::openFile(const char* path) {
    HANDLE f = CreateFile(
        path,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr);
    if (f == INVALID_HANDLE_VALUE) {
        return nullptr;
    }
        


    size_t size = 0;
    LARGE_INTEGER i;
    if (GetFileSizeEx(f, &i)) {
        size = (size_t)i.QuadPart;
    }
    if(!size) {
        CloseHandle(f);
        return nullptr;
    }

    // Create a file mapping, needed for a map view
    HANDLE hmap = CreateFileMapping(f, nullptr, PAGE_READONLY, 0, 0, nullptr);

    if (!hmap)
        return nullptr;

    // Actually memory map the file
    void* data = MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, size);

    // Close the regular file handle, keep hmap around
    CloseHandle(f);

    if (!data) {
        CloseHandle(hmap);
        return nullptr;
    }

    return new MappedFile(hmap, size, data);
}

const void* MappedFile::data() const {
    return m_data;
}

size_t MappedFile::size() const{
    return m_size;
}

MappedFile::~MappedFile() {
    UnmapViewOfFile(m_data);
    CloseHandle(m_handle);
}