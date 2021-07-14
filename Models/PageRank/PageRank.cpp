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
    return rankings;
}

void PageRank::setRankings(const vector<double> &rankingsVal) {
    PageRank::rankings = rankingsVal;
}

void PageRank::compute() {
    cout << "COMPUTING PAGERANK START" << endl;

    cout << "- Stochastization Start" << endl;
    stochastization();
    cout << "- Stochastization End" << endl;

    cout << "- PageRank Start" << endl;
    pageRank();
    cout << "- PageRank End" << endl;

    cout<< "FINAL RANKINGS" << endl;
    Utilities::printVector(rankings);

    cout << "COMPUTING PAGERANK END" << endl;
}

void PageRank::stochastization() {
    int row_elem = 0;
    int current_col = 0;

    //initialize out_links with n 0 cells
    vector<int> out_link(csr.getNNodes() + 1, 0);

    //get out_links from mmap file
    for(int i=0; i < csr.getNNodes(); i++) {
        if (row_pointer[i+1] != 0) {
            row_elem = row_pointer[i+1] - row_pointer[i];
            out_link[i] = row_elem;
        }
    }

    //get values from mmap file
    for(int i=0; i < csr.getNNodes(); i++) {
        row_elem = row_pointer[i+1] - row_pointer[i];
        for (int j=0; j<row_elem; j++) {
            csr.getValues().at(current_col) = csr.getValues().at(current_col) / out_link[i];
            current_col++;
        }
    }
}

void PageRank::pageRank() {
    int n_iterations = 0;
    bool loop=true;

    rankings = vector<double>();

    // Initialize p[] vector
    for(int i=0; i < csr.getNNodes(); i++){
        rankings.push_back(1.0/csr.getNNodes());
    }

    while (loop){
        // Initialize rankings_new as a vector of n 0.0 cells
        vector<double> rankings_new(csr.getNNodes() + 1, 0.0);

        int row_element = 0;
        int current_col = 0;

        // Page rank modified algorithm
        for(int i=0; i<csr.getNNodes(); i++){
            row_element = row_pointer[i+1] - row_pointer[i];
            for (int j=0; j<row_element; j++) {
                rankings_new.at(col_index[current_col]) = rankings_new[col_index[current_col]] + csr.getValues().at(current_col) * rankings.at(i);
                current_col++;
            }
        }

        // Adjustment to manage dangling elements
        for(int i=0; i<csr.getNNodes(); i++){
            rankings_new.at(i) = dampingFactor * rankings_new[i] + (1.0 - dampingFactor) / csr.getNNodes();
        }

        // TERMINATION: check if we have to stop
        float error = 0.0;
        for(int i=0; i<csr.getNNodes(); i++) {
            error =  error + (float) fabs(rankings_new.at(i) - rankings.at(i));
        }
        //if two consecutive instances of pagerank vector are almost identical, stop
        if (error < 0.000005){
            loop= false;
        }

        // Update p[]
        for (int i=0; i<csr.getNNodes();i++){
            rankings.at(i) = rankings_new.at(i);
        }

        // Increase the number of iterations
        n_iterations = n_iterations + 1;
    }

    cout << "N° of iteration to converge: " << n_iterations << endl;

    Utilities::closeMMap(col_index, csr.getColIndexSize());
    Utilities::closeMMap(row_pointer, csr.getRowPointerSize());

}
