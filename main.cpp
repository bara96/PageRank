#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank/PageRank.h"
#include "Models/DAAT/DAAT.h"

using namespace std;

int main() {

    //CSR csr = CSR("../src/test.txt");
    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute(false);

    Utilities::printVector(pr.getRankings());

    DAAT daat = DAAT(pr.getRankings());
    vector<pair<int,double>> top = daat.topK(10);

    cout << "Top k:" << endl;
    for (pair<int,double> &pair : top)
        cout << pair.first << ": " << pair.second << endl;
}
