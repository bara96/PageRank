//
// Created by mbaratella on 14/07/2021.
//

#include "PageRank.h"

PageRank::PageRank(CSR csr) : csr(std::move(csr)) {}

const CSR &PageRank::getCsr() const {
    return csr;
}

void PageRank::setCsr(const CSR &csrVal) {
    PageRank::csr = csrVal;
}

float PageRank::getDampingFactor() const {
    return dampingFactor;
}

void PageRank::setDampingFactor(float dampingFactorVal) {
    PageRank::dampingFactor = dampingFactorVal;
}

const vector<double> &PageRank::getScores() const {
    return p;
}

void PageRank::setScores(const vector<double> &rankings) {
    PageRank::p = rankings;
}

void PageRank::compute(bool showRanking) {
    cout << "COMPUTING PAGERANK START" << endl;

    //stores the column indexes of the elements in the val vector
    int *row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    //stores the position of the starting rows
    int *col_index = Utilities::openMMap(csr.getMapColIndFilename(), csr.getColIndexSize());

    cout << "- Stochastization Start" << endl;
    stochastization(row_pointer);
    cout << "- Stochastization End" << endl;

    cout << "- PageRank Start" << endl;
    pageRank(row_pointer, col_index);
    cout << "- PageRank End" << endl;

    if(showRanking) {
        cout << "FINAL RANKINGS" << endl;
        Utilities::printVector(p);
    }

    Utilities::closeMMap(row_pointer, csr.getRowPointerSize());
    Utilities::closeMMap(col_index, csr.getColIndexSize());

    cout << "COMPUTING PAGERANK END" << endl;
}

void PageRank::stochastization(const int *row_pointer) {
    int row_elem = 0;
    int current_col = 0;

    // initialize out_links with n 0 cells
    vector<int> out_link(csr.getNNodes() + 1, 0);

    // init out_links from mmap file
    // only store the values different from zero without adding "artificial" outgoing links.
    for(int i=0; i < csr.getNNodes(); i++) {
        if (row_pointer[i+1] != 0) {
            row_elem = row_pointer[i+1] - row_pointer[i];
            out_link.at(i) = row_elem;
        }
    }

    // Normalize, making the matrix stochastic
    // divide each csr value for its out_link
    for(int i=0; i < csr.getNNodes(); i++) {
        row_elem = row_pointer[i+1] - row_pointer[i];
        for (int j=0; j<row_elem; j++) {
            csr.getValues().at(current_col) = csr.getValues().at(current_col) / out_link.at(i);
            current_col++;
        }
    }
}

void PageRank::pageRank(const int *row_pointer, const int *col_index) {
    int nIterations = 0;
    bool loop = true;
    //counters
    int rowElement = 0;
    int currentCol = 0;

    // Initial probability distribution
    p = vector<double>(csr.getNNodes(), 1.0 / csr.getNNodes());

    vector<double> p_new;
    while (loop){
        //reset variables
        rowElement = 0;
        currentCol = 0;
        // Initialize p_new as a vector of n 0.0 cells
        p_new = vector<double>(csr.getNNodes() + 1, 0.0);

        // PageRank modified algorithm
        // Initialize the teleportation matrix
        for(int i=0; i<csr.getNNodes(); i++){
            rowElement = row_pointer[i + 1] - row_pointer[i];
            for (int j=0; j < rowElement; j++) {
                p_new.at(col_index[currentCol]) = p_new[col_index[currentCol]] + csr.getValues().at(currentCol) * p.at(i);
                currentCol++;
            }
        }

        // Final Matrix after removing dangling nodes and adding teleportation
        // Add a link from each page to every page and give each link a small transition probability controlled by the dampingFactor
        for(int i=0; i<csr.getNNodes(); i++){
            p_new.at(i) = dampingFactor * p_new.at(i) + (1.0 - dampingFactor) / csr.getNNodes();
        }

        // termination condition is defined by the case in which two consecutive iterations of the algorithm produce two almost identical p-vectors.
        loop = Utilities::checkTermination(p, p_new, csr.getNNodes(), 0.000005);

        // Update p[]
        for (int i=0; i<csr.getNNodes();i++){
            p.at(i) = p_new.at(i);
        }

        // Increase the number of iterations
        nIterations = nIterations + 1;
    }

    cout << "N° of iteration to converge: " << nIterations << endl;
}
