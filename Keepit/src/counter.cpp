#include "counter.h"

FileWordCounter::FileWordCounter(const char* path) {
	m_mf = std::unique_ptr<MappedFile>(MappedFile::openFile(path));
    if (m_mf) {
        m_pageSize = m_mf->size()/m_tp.maxThreadNumber();
        std::cout << "m_pageSize: "<< m_pageSize << std::endl;
    }
}

std::unique_ptr<FileWordCounter> FileWordCounter::createFileWordCounter(
	const char* path
) {
	FileWordCounter* counter = new FileWordCounter(path);
	return counter->m_mf ? std::unique_ptr<FileWordCounter>(counter) : nullptr;
}

void FileWordCounter::addWord(const int start, const int end) {
    const char const* data = (const char*)m_mf->data();
    const char* pointer = data + start;
    m_dic.insert(std::string(pointer, end - start + 1));
}

void FileWordCounter::workerFunction(const int offset) {
    std::cout << "workerFunction called with: " << offset << std::endl;
    const char const*  data = (const char* )m_mf->data();
    if (data == NULL) { return; }
    const char* pointer = data + offset;

    //0 outside the word 1 inside
    int state = 0;
    int startPos, endPos;


    // we may split in the middle of word so skip it
    if (offset) { 
        while (*pointer && !isSeparator(*pointer)) {
            pointer++;
        }
    }

    if (pointer - (data + offset) > m_pageSize || !pointer) { return; }//page proccessed we done

    while (*pointer) {
        if (isSeparator(*pointer)) {
            if (state == 1) {
                this->addWord(startPos, endPos);
                state = 0;
                if (pointer - (data + offset) >= m_pageSize) {
                    break;
                }
            }
            //else skipp just 2 separators in a row
        }
        else if (state == 0) {
            state = 1;
            startPos = pointer - data;
        }
        endPos = pointer - data;
        ++pointer;
    }
    //last word finished with eof
    if (state == 1 && !pointer) {
        this->addWord(startPos, endPos);
    }
}

size_t FileWordCounter::count() {
    /*auto thr = std::thread([this]() {
        this->workerFunction(0);
       });
    auto thr2 = std::thread([this]() {
        this->workerFunction(m_pageSize);
        });
        */
    for (auto i = 0; i < m_tp.maxThreadNumber(); i++) {
        m_tp.execute([this, i]() {
            this->workerFunction(i*this->m_pageSize);
         });
    }
    m_tp.waitAll();
    return m_dic.size();
}