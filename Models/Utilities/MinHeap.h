//
// Created by acarraro on 13/07/2021.
//

#ifndef PAGERANK_MINHEAP_H
#define PAGERANK_MINHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class MinHeap {
private:

    int size;
    int capacity;
    vector<int> heap;
    int parent (int i) {return (i-1) /2;};

    int left (int i){return 2 * i +1;}

    int right (int i){return 2 * i + 2;};

public:

   MinHeap(int capacity);

   void insert(int val);

   int extractMin();

   void heapify(int i);

   vector<double> getVector();
};


#endif //PAGERANK_MINHEAP_H
