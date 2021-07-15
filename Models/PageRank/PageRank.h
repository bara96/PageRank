//
// Created by mbaratella on 14/07/2021.
//

#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include "../Utilities//Utilities.h"
#include "../CSR//CSR.h"

class PageRank {
protected:
    CSR csr;
    int *row_pointer = nullptr;
    int *col_index = nullptr;
    float dampingFactor = 0.85;
    vector<double> rankings;

public:
    explicit PageRank(const CSR &csr);

    const CSR &getCsr() const;

    void setCsr(const CSR &csr);

    float getDampingFactor() const;

    void setDampingFactor(float dampingFactor);

    const vector<double> &getRankings() const;

    void setRankings(const vector<double> &rankings);

    void compute(bool showRanking);

protected:
    void stochastization();

    void pageRank();

};


#endif //PAGERANK_PAGERANK_H
