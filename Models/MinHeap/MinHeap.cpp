#include "MinHeap.h"


// Data structure to store a min-heap node

//contructor
MinHeap::MinHeap(int capacity){
    size=0;
    this->capacity= capacity;
    heap.resize(capacity);
}

void MinHeap::insert (pair<int, double> val){
    //check if thre is space in the heap
    if(size == capacity){
        cout<<"MIN HEAP FULL"<<endl;
        return;
    }
    //increase amount of elements in heap
    size++;
    
    //insert new key at the end
    int i = size - 1;
    heap[i]=val;

    //fix the min heap property
    //moves the elements up until i >= parent or root

    while (i != 0 && heap[parent(i)].second > heap[i].second)
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
    

}

void MinHeap::heapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;

    //find smallest element of the three

    if((l < size) && (heap[l].second < heap[smallest].second)){
        smallest=l;
    }
    if((l < size) && (heap[r].second < heap[smallest].second)){
        smallest=r;
    }

    if (smallest != i){
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

pair<int, double> MinHeap::extractMin(){
    //check if the heap is empty
    if(size == 0){
        cerr << "Heap empty" << endl;
        exit(1);
    }
    else if (size==1)
    {
        size --;
        return heap[0];
    }
    else {
        pair<int, double> root = heap[0];

        heap[0] = heap[size-1];
        size--;
        heapify(0);

        return root;
    }
}

pair<int, double> MinHeap::getMin(){
    //check if the heap is empty
    if(size == 0){
        cerr << "Heap empty" << endl;
        exit(1);
    }
    else
    {
        return heap[0];
    }
}

bool sortPairs (pair<int, double> i,pair<int, double> j) { return (i.second>j.second); }
vector<pair<int, double>> MinHeap::getVector() {
    vector<pair<int, double>> minHeap;
    minHeap.reserve(size);
    for (int i = 0; i < size; i++)
    {
       minHeap.push_back(heap[i]);
    }
    sort(minHeap.begin(), minHeap.end(), sortPairs);
    return minHeap;
}

