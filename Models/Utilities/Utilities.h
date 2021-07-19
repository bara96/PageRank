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
#include <cmath>

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

    /**
     * Check the error between two vectors, return true if is less than the threshold
     * @param vector
     * @param vectorNew
     * @return
     */
    static bool checkTermination(const vector<double> &vector, const std::vector<double> &vectorNew, int nNodes, double errorThreshold);

    /**
     * Compute Jaccard coefficient
     *
     * @param scores1
     * @param scores2
     * @param nNodes
     * @return
     */
    static double jaccard(const vector<pair<int, double>> &scores1, const vector<pair<int, double>> &scores2);
};


#endif //PAGERANK_UTILITIES_H
