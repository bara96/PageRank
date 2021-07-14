//
// Created by mbaratella on 14/07/2021.
//

#include "PageRank.h"

PageRank::PageRank(const CSR &csr) : csr(csr) {
    row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    col_index = Utilities::openMMap(csr.getMapColIndFilename(), csr.getColIndexSize());
}

void PageRank::stochastization() {
    int i=0, j=0;
    int row_elem = 0;
    int current_col = 0;
    vector<int> out_link;

    //initialize out_links
    for(i=0; i < csr.getNNodes(); i++) {
        out_link.push_back(0);
    }

    //get out_links from mmap file
    for(i=0; i < csr.getNNodes(); i++) {
        if (row_pointer[i+1] != 0) {
            row_elem = row_pointer[i+1] - row_pointer[i];
            out_link[i] = row_elem;
        }
    }

    //get values from mmap file
    for(i=0; i < csr.getNNodes(); i++) {
        row_elem = row_pointer[i+1] - row_pointer[i];
        for (j=0; j<row_elem; j++) {
            csr.getValues().at(current_col) = csr.getValues().at(current_col) / out_link[i];
            current_col++;
        }
    }

}

void PageRank::compute() {
    cout << "COMPUTING PAGERANK START" << endl;

    cout << "- Stochastization Start" << endl;
    stochastization();
    cout << "- Stochastization End" << endl;

    

    cout << "COMPUTING PAGERANK END" << endl;
}
