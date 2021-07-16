//
// Created by mbaratella on 14/07/2021.
//

#include <cmath>
#include "PageRank.h"

PageRank::PageRank(const CSR &csr) : csr(csr) {
    row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    col_index = Utilities::openMMap(csr.getMapColIndFilename(), csr.getColIndexSize());
}

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

const vector<double> &PageRank::getRankings() const {
    return p;
}

void PageRank::setRankings(const vector<double> &rankingsVal) {
    PageRank::p = rankingsVal;
}

void PageRank::compute(bool showRanking) {
    cout << "COMPUTING PAGERANK START" << endl;

    cout << "- Stochastization Start" << endl;
    stochastization();
    cout << "- Stochastization End" << endl;

    cout << "- PageRank Start" << endl;
    pageRank();
    cout << "- PageRank End" << endl;

    if(showRanking) {
        cout << "FINAL RANKINGS" << endl;
        Utilities::printVector(p);
    }

    cout << "COMPUTING PAGERANK END" << endl;
}

void PageRank::stochastization() {
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

void PageRank::pageRank() {
    int n_iterations = 0;
    bool loop=true;

    p = vector<double>();

    // Initial probability distribution
    for(int i=0; i < csr.getNNodes(); i++){
        p.push_back(1.0 / csr.getNNodes());
    }

    while (loop){
        // Initialize p_new as a vector of n 0.0 cells
        vector<double> p_new(csr.getNNodes() + 1, 0.0);

        int row_element = 0;
        int current_col = 0;

        // PageRank modified algorithm
        // Initialize the teleportation matrix
        for(int i=0; i<csr.getNNodes(); i++){
            row_element = row_pointer[i+1] - row_pointer[i];
            for (int j=0; j<row_element; j++) {
                p_new.at(col_index[current_col]) = p_new[col_index[current_col]] + csr.getValues().at(current_col) * p.at(i);
                current_col++;
            }
        }

        // Final Matrix after removing dangling nodes and adding teleportation
        // Add a link from each page to every page and give each link a small transition probability controlled by the dampingFactor
        for(int i=0; i<csr.getNNodes(); i++){
            p_new.at(i) = dampingFactor * p_new.at(i) + (1.0 - dampingFactor) / csr.getNNodes();
        }

        // termination condition is defined by the case in which two consecutive iterations of the algorithm produce two almost identical p-vectors.
        // Compute the Euclidean distance between the vectors p and p_new
        float error = 0.0;
        for(int i=0; i<csr.getNNodes(); i++) {
            error =  error + (float) fabs(p_new.at(i) - p.at(i));
        }
        //if two consecutive instances of pagerank vector are almost identical, stop
        if (error < 0.000005){
            loop= false;
        }

        // Update p[]
        for (int i=0; i<csr.getNNodes();i++){
            p.at(i) = p_new.at(i);
        }

        // Increase the number of iterations
        n_iterations = n_iterations + 1;
    }

    cout << "N° of iteration to converge: " << n_iterations << endl;

    Utilities::closeMMap(col_index, csr.getColIndexSize());
    Utilities::closeMMap(row_pointer, csr.getRowPointerSize());

}
