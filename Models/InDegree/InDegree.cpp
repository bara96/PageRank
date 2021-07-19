//
// Created by mbaratella on 19/07/2021.
//

#include "InDegree.h"

InDegree::InDegree(CSR csr) : csr(std::move(csr)) {}

const CSR &InDegree::getCsr() const {
    return csr;
}

void InDegree::setCsr(const CSR &csrVal) {
    InDegree::csr = csrVal;
}

const vector<double> &InDegree::getScores() const {
    return scores;
}

void InDegree::setScores(const vector<double> &scoresVal) {
    InDegree::scores = scoresVal;
}

void InDegree::compute(bool showRanking) {
    cout << "COPUTING IN-DEGREE START" << endl;

    inDegree();

    if(showRanking) {
        cout << "FINAL RANKINGS" << endl;
        Utilities::printVector(scores);
    }

    cout << "COMPUTING IN-DEGREE END" << endl;
}

void InDegree::inDegree() {
    int *row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    double rowel = 0.0;

    scores = vector<double>(csr.getNNodes() + 1, 0.0);

    for(int i=0; i<csr.getNNodes(); i++){
        rowel = row_pointer[i+1] - row_pointer[i];
        scores.at(i) = rowel/csr.getNNodes();
    }

    Utilities::closeMMap(row_pointer, csr.getRowPointerSize());
}

