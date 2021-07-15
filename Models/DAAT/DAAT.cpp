//
// Created by mbaratella on 14/07/2021.
//

#include "DAAT.h"
#include "../MinHeap/MinHeap.h"

DAAT::DAAT(const vector<double> &values) : values(values) {}

const vector<double> &DAAT::getValues() const {
    return values;
}

void DAAT::setValues(const vector<double> &valuesVal) {
    DAAT::values = valuesVal;
}

vector<pair<int, double>> DAAT::topK(int k) {
    MinHeap heap(k);

    for(int i=0; i<k; i++) {
        heap.insert(pair<int, double>(i, values.at(i)));
    }
    double min, score;

    for (int i=k+1; i<values.size(); i++) {
        min = heap.getMin().second;
        score = values.at(i);
        if(score > min) {
            heap.extractMin();
            heap.insert(pair<int, double>(i, score));
        }
    }

    return  heap.getVector();
}
