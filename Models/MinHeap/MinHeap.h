//
// Created by acarraro on 13/07/2021.
//

#ifndef PAGERANK_MINHEAP_H
#define PAGERANK_MINHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>

using namespace std;

class MinHeap {
protected:
    int size;
    int capacity;

    vector<pair<int, double>> heap;
    int parent (int i) {return (i-1) /2;};

    int left (int i){return 2 * i +1;}

    int right (int i){return 2 * i + 2;};

public:
   explicit MinHeap(int capacity);

   void insert(pair<int, double>);

    pair<int, double> extractMin();

    pair<int, double> getMin();

   void heapify(int i);

   vector<pair<int, double>> getVector();

private:
    void postorder(vector<double> &arr, int size, int i);

};


#endif //PAGERANK_MINHEAP_H
