#include "MinHeap.h"


// Data structure to store a min-heap node

//contructor
MinHeap::MinHeap(int capacity){
    size=0;
    this->capacity= capacity;
    heap.resize(capacity);
}

void MinHeap::insert (double val){
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

    while (i != 0 && heap[parent(i)] > heap[i])
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

    if((l < size) && (heap[l] < heap[smallest])){
        smallest=l;
    }
    if((l < size) && (heap[r] < heap[smallest])){
        smallest=r;
    }

    if (smallest != i){
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

double MinHeap::extractMin(){
    //check if the heap is empty
    if(size == 0){
        return NULL;
    }
    else if (size==1)
    {
        size --;
        return heap[0];
    }
    else {
        double root = heap[0];

        heap[0]= heap[size-1];
        size--;
        heapify(0);

        return root;
    }
}

double MinHeap::getMin(){
    //check if the heap is empty
    if(size == 0){
        return NULL;
    }
    else
    {
        return heap[0];
    }
}

vector<double> MinHeap::getVector() {
    vector<double> minheap;
    int power=0;
    int value =1;
    for (int i = 0; i < size; i++)
    {
       if (i==value){
           power += 1;
           value += (1 << power);
       }
       minheap.push_back(heap[i]);
    }
    return minheap;
}

