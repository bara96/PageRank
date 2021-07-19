#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank/PageRank.h"
#include "Models/HITS/HITS.h"
#include "Models/InDegree/InDegree.h"
#include "Models/DAAT/DAAT.h"
#include <chrono>

using namespace std;

vector<pair<int,double>> doPageRank(int topK, bool showTop) {
    //CSR csr = CSR("../src/test.txt");
    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute(false);

    DAAT daat = DAAT(pr.getScores());
    vector<pair<int,double>> top = daat.topK(topK);

    if(showTop) {
        cout << "PageRank Top k:" << endl;
        for (pair<int, double> &pair : top)
            cout << pair.first << ": " << pair.second << endl;
    }
    return top;
}

vector<pair<int, double>> doHITS(HITS::COMPUTE_MODE mode, int topK, bool showTop) {
    CSR csrHub = CSR();
    if(mode == HITS::all || mode == HITS::hub) {
        csrHub = CSR("../src/web-NotreDame.txt");
        csrHub.setMapColIndFilename(csrHub.getMapColIndFilename() + "_hub");
        csrHub.setMapRowPtrFilename(csrHub.getMapRowPtrFilename() + "_hub");
        csrHub.compute();
    }

    CSR csrAut = CSR();
    if(mode == HITS::all || mode == HITS::authority) {
        csrAut = CSR("../src/web-NotreDame-transpose.txt");
        csrAut.setMapColIndFilename(csrAut.getMapColIndFilename() + "_aut");
        csrAut.setMapRowPtrFilename(csrAut.getMapRowPtrFilename() + "_aut");
        csrAut.compute();
    }

    HITS hits = HITS(csrHub, csrAut);
    hits.compute(mode, false);

    vector<pair<int, double>> topHub;
    if(mode == HITS::all || mode == HITS::hub) {
        DAAT daatHub = DAAT(hits.getHubScores());
        topHub = daatHub.topK(topK);
        if(showTop) {
            cout << "HITS Hub Top k:" << endl;
            for (pair<int, double> &pair : topHub)
                cout << pair.first << ": " << pair.second << endl;
        }
    }

    if(showTop && mode == HITS::all)
        cout << endl;

    vector<pair<int, double>> topAut;
    if(mode == HITS::all || mode == HITS::authority) {
        DAAT daatAut = DAAT(hits.getAutScores());
        topAut = daatAut.topK(topK);
        if(showTop) {
            cout << "HITS Authority Top k:" << endl;
            for (pair<int, double> &pair : topAut)
                cout << pair.first << ": " << pair.second << endl;
        }
    }

    if(mode == HITS::hub)
        return topAut;
    else
        return topHub;
}

vector<pair<int, double>> doInDegree(int topK, bool showTop) {
    CSR csr = CSR("../src/web-NotreDame-transpose.txt");
    csr.compute();
    InDegree inDegree = InDegree(csr);
    inDegree.compute(false);

    DAAT daat = DAAT(inDegree.getScores());
    
    vector<pair<int,double>> top = daat.topK(topK);

    if(showTop) {
        cout << "InDegree Top k:" << endl;
        for (pair<int,double> &pair : top)
            cout << pair.first << ": " << pair.second << endl;
    }
    return top;
}

void doAll() {
    vector<pair<int, double>> topPageRank = doPageRank(30, false);
    vector<pair<int, double>> topHITSAut = doHITS(HITS::authority, 30, false);
    vector<pair<int, double>> topInDegree = doInDegree(30, false);

    double jaccard_pr_hits = Utilities::jaccard(topPageRank, topHITSAut);
    double jaccard_pr_degree = Utilities::jaccard(topPageRank, topInDegree);
    double jaccard_hits_degree = Utilities::jaccard(topHITSAut, topInDegree);

    cout << "Jaccard PageRank - HITS Authority: " << jaccard_pr_hits << endl;
    cout << "Jaccard PageRank - InDegree: " << jaccard_pr_degree << endl;
    cout << "Jaccard HITS Authority - InDegree: " << jaccard_hits_degree << endl;

}

int main() {
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    doAll();

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("\nTime measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}