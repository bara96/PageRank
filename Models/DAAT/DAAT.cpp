//
// Created by mbaratella on 14/07/2021.
//

#include "DAAT.h"
#include "../MinHeap/MinHeap.h"

DAAT::DAAT() = default;

DAAT::DAAT(const vector<double> &values) : values(values) {}

const vector<double> &DAAT::getValues() const {
    return values;
}

void DAAT::setValues(const vector<double> &valuesVal) {
    DAAT::values = valuesVal;
}

vector<pair<int, double>> DAAT::topK(int k) {
    MinHeap heap(k);
    double min, score;

    // init an heap of K elements
    for(int i=0; i<k; i++) {
        heap.insert(pair<int, double>(i, values.at(i)));
    }

    // DAAT algorithm
    for (int i=k+1; i<values.size(); i++) {
        min = heap.getMin().second;     // get current heap minimum
        score = values.at(i);   //current score
        if(score > min) {
            heap.extractMin();  //heap root delete
            heap.insert(pair<int, double>(i, score));   //insert the new score
        }
    }

    return  heap.getVector();
}
