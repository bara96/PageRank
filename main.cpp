#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank//PageRank.h"

using namespace std;

int main() {
    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute();
}
