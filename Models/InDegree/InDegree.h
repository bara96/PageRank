//
// Created by mbaratella on 19/07/2021.
//

#ifndef PAGERANK_INDEGREE_H
#define PAGERANK_INDEGREE_H

#include <cmath>
#include <utility>
#include "../Utilities/Utilities.h"
#include "../CSR/CSR.h"

class InDegree {
protected:
    CSR csr;
    vector<double> scores;

public:
    explicit InDegree(CSR csr);

    const CSR &getCsr() const;

    void setCsr(const CSR &csr);

    const vector<double> &getScores() const;

    void setScores(const vector<double> &scores);

    /**
     * Compute in-degree
     *
     * @param showRanking
     */
    void compute(bool showRanking);

protected:
     /**
      * Compute in-degree algorithm
      */
    void inDegree();
};


#endif //PAGERANK_INDEGREE_H
