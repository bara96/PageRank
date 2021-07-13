#include <iostream>

#include "Models/CSR/CSR.h"

using namespace std;

int main() {
    CSR csr = CSR("../src/web-NotreDame.txt");
    csr.computeCSR();
    cout << "numero di nodi: " << csr.getNNodes() << ", numero di archi: " << csr.getNEdges() << endl;
}
