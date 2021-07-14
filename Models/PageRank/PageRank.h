//
// Created by mbaratella on 14/07/2021.
//

#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include "../Utilities//Utilities.h"
#include "../CSR//CSR.h"

class PageRank {
private:
    CSR csr;
    int *row_pointer = nullptr;
    int *col_index = nullptr;

public:

    PageRank(const CSR &csr);

    void compute();

private:
    void stochastization();


};


#endif //PAGERANK_PAGERANK_H
