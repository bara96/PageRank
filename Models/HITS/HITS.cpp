//
// Created by mbaratella on 17/07/2021.
//

#include "HITS.h"

HITS::HITS() = default;

HITS::HITS(CSR csrHub, CSR csrAut) : csrHub(std::move(csrHub)), csrAut(std::move(csrAut)) {}

const CSR &HITS::getCsrHub() const {
    return csrHub;
}

void HITS::setCsrHub(const CSR &csrHubVal) {
    csrHub = csrHubVal;
}

const CSR &HITS::getCsrAut() const {
    return csrAut;
}

void HITS::setCsrAut(const CSR &csrAutVal) {
    csrAut = csrAutVal;
}

const vector<double> &HITS::getHubScores() const {
    return hubScores;
}

void HITS::setHubScores(const vector<double> &hubScoresVal) {
    HITS::hubScores = hubScoresVal;
}

const vector<double> &HITS::getAutScores() const {
    return autScores;
}

void HITS::setAutScores(const vector<double> &autScoresVal) {
    HITS::autScores = autScoresVal;
}

void HITS::compute(COMPUTE_MODE mode, bool showRanking) {
    cout << "COMPUTING HITS START" << endl;

    if(mode == all || mode == hub) {
        cout << "- Hub Ranking Start" << endl;
        hits(true);
        cout << "- Hub Ranking End" << endl;
    }

    if(mode == all || mode == authority) {
        cout << "- Authority Ranking Start" << endl;
        hits(false);
        cout << "- Authority Ranking End" << endl;
    }

    if(showRanking) {
        cout << "FINAL RANKINGS" << endl;
        if(mode == all || mode == hub) {
            cout << "- Hub Rankings:" << endl;
            Utilities::printVector(hubScores);
        }
        if(mode == all || mode == authority) {
            cout << "- Authority Rankings:" << endl;
            Utilities::printVector(autScores);
        }
    }

    cout << "COMPUTING HITS END" << endl;
}

int HITS::hits(bool isHubScore){
    bool loop = true;
    int nIterations = 0;
    //counters
    double temp = 0.0;
    double vSum = 0.0;  //cumulative sum of elements in the matrix, used to normalize
    int rowElement = 0; //number of elemtens in a row
    int currentCol = 0; //current column

    CSR csr;
    if(isHubScore) {
        csr = csrHub;
    }
    else {
        csr = csrAut;
    }
    int *row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    int *col_index = Utilities::openMMap(csr.getMapColIndFilename(), csr.getColIndexSize());

    //initial vector to calculate authority and hub values
    vector<double> v(csr.getNNodes(), 1.0);
    vector<double> v_new;

    while (loop){
        //reset variables
        temp = 0.0;
        vSum = 0.0;
        rowElement = 0;
        currentCol = 0;

        // Initialize v_new as a vector of n 0.0 cells
        v_new = vector<double>(csr.getNNodes() + 1, 0.0);

        for(int i=0; i<csr.getNNodes(); i++){
            rowElement = row_pointer[i + 1] - row_pointer[i];
            for (int j=0; j < rowElement; j++) {//per tutti i nodi entranti o uscenti (entranti (authority) o uscenti (hub))
                temp = temp + (csr.getValues()[currentCol] * v[col_index[currentCol]]); //product between matrix and vector, è una sommatoria
                //     sommatoria 
                currentCol++;
            }
            v_new[i] = temp;// salvo l'hub o authority delle pagine vicine 
            temp = 0.0;
        }

        // v_new normalization
        for(int i=0; i<csr.getNNodes(); i++){
            vSum = vSum + v_new[i];//somma di tutti gli score delle pagine
        }
        for(int i=0; i<csr.getNNodes(); i++){
            v_new[i] = v_new[i] / vSum;//normalizzazione
        }

        // termination condition is defined by the case in which two consecutive iterations of the algorithm produce two almost identical p-vectors.
        loop = Utilities::checkTermination(v, v_new, csr.getNNodes(), 0.000005);

        // Update vector[]
        for (int i=0; i < csr.getNNodes();i++){
            v[i] = v_new[i];
        }

        // Increase the number of iterations and set everything to 0
        nIterations = nIterations + 1;
    }

    cout << "N° of iteration to converge: " << nIterations << endl;

    if(isHubScore) {
        csrHub = csr;
        hubScores = v;
    }
    else {
        csrAut = csr;
        autScores = v;
    }

    Utilities::closeMMap(col_index, csr.getColIndexSize());
    Utilities::closeMMap(row_pointer, csr.getRowPointerSize());

    return nIterations;
}
