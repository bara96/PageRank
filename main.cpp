#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank/PageRank.h"
#include "Models/HITS/HITS.h"
#include "Models/DAAT/DAAT.h"

using namespace std;

void doHITS() {
    CSR csrHub = CSR("../src/web-NotreDame.txt");
    csrHub.setMapColIndFilename(csrHub.getMapColIndFilename() + "_hub");
    csrHub.setMapRowPtrFilename(csrHub.getMapRowPtrFilename() + "_hub");
    csrHub.compute();

    CSR csrAut = CSR("../src/web-NotreDame-transpose.txt");
    csrAut.setMapColIndFilename(csrAut.getMapColIndFilename() + "_aut");
    csrAut.setMapRowPtrFilename(csrAut.getMapRowPtrFilename() + "_aut");
    csrAut.compute();

    HITS hits = HITS(csrHub, csrAut);
    hits.compute(false);

    DAAT daatHub = DAAT(hits.getHubScores());
    vector<pair<int,double>> topHub = daatHub.topK(10);
    cout << "HITS Hub Top k:" << endl;
    for (pair<int,double> &pair : topHub)
        cout << pair.first << ": " << pair.second << endl;

    cout << endl;
    DAAT daatAut = DAAT(hits.getAutScores());
    vector<pair<int,double>> topAut = daatAut.topK(10);
    cout << "HITS Hub Top k:" << endl;
    for (pair<int,double> &pair : topAut)
        cout << pair.first << ": " << pair.second << endl;
}

void doPageRank() {
    //CSR csr = CSR("../src/test.txt");
    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute(false);

    DAAT daat = DAAT(pr.getScores());
    vector<pair<int,double>> top = daat.topK(10);

    cout << "PageRank Top k:" << endl;
    for (pair<int,double> &pair : top)
        cout << pair.first << ": " << pair.second << endl;
}

int main() {

    doHITS();

}