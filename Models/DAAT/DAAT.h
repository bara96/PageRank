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
    DAAT();

    explicit DAAT(const vector<double> &values);

    const vector<double> &getValues() const;

    void setValues(const vector<double> &values);

    /**
     * Compute the topK with DAAT
     * @param k
     * @return pair<int, double> as follows:
     *      int: the first is the position of the rank
     *      double: the second is the score of the rank
     */
    vector<pair<int, double>> topK(int k);
};


#endif //PAGERANK_DAAT_H
