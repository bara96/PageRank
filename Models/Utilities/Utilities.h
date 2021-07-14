//
// Created by mbaratella on 13/07/2021.
//

#ifndef PAGERANK_UTILITIES_H
#define PAGERANK_UTILITIES_H

#include <iostream>
#include <vector>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class Utilities {
public:

    /**
     * Open a file pointer
     */
    static FILE* openFile(const string& filename, const string &mode);

    /**
     * Open a mmap file pointer
     * @param filename
     * @param mapPointerSize
     * @return
     */
    static int* openMMap(const string& filename, const int& mapPointerSize);

    /**
     * Close a mmap file pointer
     * @param pointer
     * @param pointerSize
     */
    static void closeMMap(int* pointer, int pointerSize);

    /***
     * Print an array of elements
     * @param vector
     */
    template<typename T>
    static void printVector(const vector<T> &vector){
        for (auto &value : vector)
            cout << value << " ";
        cout << "\n";
    }

};


#endif //PAGERANK_UTILITIES_H
