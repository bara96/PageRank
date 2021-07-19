//
// Created by mbaratella on 14/07/2021.
//

#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include <cmath>
#include <utility>
#include "../Utilities/Utilities.h"
#include "../CSR/CSR.h"

class PageRank {
protected:
    CSR csr;
    float dampingFactor = 0.85;
    vector<double> p;

public:
    explicit PageRank(CSR csr);

    const CSR &getCsr() const;

    void setCsr(const CSR &csr);

    float getDampingFactor() const;

    void setDampingFactor(float dampingFactor);

    const vector<double> &getScores() const;

    void setScores(const vector<double> &rankings);

    void compute(bool showRanking);

protected:
    /**
     * Initialize the stochastization of the matrix
     *
     * @param row_pointer
     */
    void stochastization(const int *row_pointer);

    /**
     * Compute main PageRank algorithm
     *
     * @param row_pointer
     * @param col_index
     */
    void pageRank(const int *row_pointer, const int *col_index);

};


#endif //PAGERANK_PAGERANK_H
