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
    int *row_pointer = nullptr; //stores the column indexes of the elements in the val vector
    int *col_index = nullptr;  //stores the position of the starting rows
    float dampingFactor = 0.85;
    vector<double> p;

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
    /**
     * Initialize the stochastization of the matrix
     */
    void stochastization();

    /**
     * Do PageRank
     */
    void pageRank();

};


#endif //PAGERANK_PAGERANK_H
