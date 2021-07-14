//
// Created by mbaratella on 14/07/2021.
//

#ifndef PAGERANK_DAAT_H
#define PAGERANK_DAAT_H

#include "../Utilities//Utilities.h"

class DAAT {
protected:
    vector<double> values;

public:
    explicit DAAT(const vector<double> &values);

    const vector<double> &getValues() const;

    void setValues(const vector<double> &values);

    vector<double> topK(int k);
};


#endif //PAGERANK_DAAT_H
