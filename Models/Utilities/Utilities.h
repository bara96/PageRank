//
// Created by mbaratella on 13/07/2021.
//

#ifndef PAGERANK_UTILITIES_H
#define PAGERANK_UTILITIES_H

#include <iostream>
#include <cerrno>
#include <cstdio>
#include <vector>

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
