//
// Created by mbaratella on 13/07/2021.
//

#ifndef PAGERANK_CSR_H
#define PAGERANK_CSR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../Utilities//Utilities.h"

using namespace std;

class CSR {
private:
    const string map_col_ind = "./map_col_ind";
    const string map_row_ptr = "./map_row_ptr";
    string filename;
    int n_nodes = 0;
    int n_edges = 0;
    vector<float> values;
    int row_pointer_size = 0;
    int col_index_size = 0;

public:
    CSR();

    explicit CSR(string filename);

    const string &getFilename() const;

    void setFilename(const string &filenameVal);

    const string &getMapColInd() const;

    const string &getMapRowPtr() const;

    int getNNodes() const;

    void setNNodes(int nNodes);

    int getNEdges() const;

    void setNEdges(int nEdges);

    const vector<float> &getValues() const;

    void setValues(const vector<float> &values);

    int getRowPointerSize() const;

    void setRowPointerSize(int rowPointerSize);

    int getColIndexSize() const;

    void setColIndexSize(int colIndexSize);

    /**
     * Compute the CSR
     */
    void computeCSR();

private:
    /**
     * parse the file, read n° of nodes/edges and remove comments row
     * @param filenameVal
     */
    FILE* parseFile(const string &filenameVal);
};


#endif //PAGERANK_CSR_H
