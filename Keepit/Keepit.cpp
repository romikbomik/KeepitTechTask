// Keepit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "dictionary.h"
#include "counter.h"
#include <iostream>
#include <thread>
#include <string>
#include <memory>

int main(int argc, char* argv[])
{
    if (argc != 1) /* argc should be 2 for correct execution */
    {
        std::cout << "Please input file name as command line argument" << std::endl;
    }
    else {
        std::cout << "Processing " << argv[0] << std::endl;
        //"E:\poem.txt"
        std::unique_ptr<FileWordCounter>fc = FileWordCounter::createFileWordCounter("E:\poem.txt");
        if (!fc) {
            std::cout << "Invalid file"<< std::endl;
        }
        else {
            std::cout << "number: " << fc->count();
        }
    }
}
