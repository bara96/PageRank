#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank/PageRank.h"
#include "Models/DAAT/DAAT.h"

using namespace std;

int main() {

    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute();

    DAAT daat = DAAT(pr.getRankings());
    Utilities::printVector(daat.topK(5));

}
