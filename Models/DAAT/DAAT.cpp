//
// Created by mbaratella on 14/07/2021.
//

#include "DAAT.h"

DAAT::DAAT(const vector<double> &values) : values(values) {}

const vector<double> &DAAT::getValues() const {
    return values;
}

void DAAT::setValues(const vector<double> &valuesVal) {
    DAAT::values = valuesVal;
}

vector<double> DAAT::topK(int k) {
    return vector<double>(); //TODO min heap DAAT
}
