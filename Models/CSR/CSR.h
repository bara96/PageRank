//
// Created by mbaratella on 13/07/2021.
//

#ifndef PAGERANK_CSR_H
#define PAGERANK_CSR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <regex>
#include "../Utilities//Utilities.h"

using namespace std;

class CSR {
protected:
    string map_col_ind_filename = "./map_col_ind_filename";
    string map_row_ptr_filename = "./map_row_ptr_filename";
    string filename;
    int n_nodes = 0;
    int n_edges = 0;
    vector<double> values;
    int row_pointer_size = 0;
    int col_index_size = 0;

public:
    CSR();

    explicit CSR(string filename);

    const string &getFilename() const;

    void setFilename(const string &filenameVal);

    void setMapColIndFilename(const string &mapColIndFilename);

    void setMapRowPtrFilename(const string &mapRowPtrFilename);

    const string &getMapColIndFilename() const;

    const string &getMapRowPtrFilename() const;

    int getNNodes() const;

    void setNNodes(int nNodes);

    int getNEdges() const;

    void setNEdges(int nEdges);

    vector<double> &getValues();

    void setValues(const vector<double> &values);

    int getRowPointerSize() const;

    void setRowPointerSize(int rowPointerSize);

    int getColIndexSize() const;

    void setColIndexSize(int colIndexSize);

    /**
     * Check if transposed matrix is already generated
     */
    static void generateTransposeCSR(const string &mainFilename);

    /**
     * Generate a transposed CSR file
     */
    static void transposeCSR(const string &mainFilename, const string &transposedFilename);

    /**
     * Compute the CSR
     */
    void compute();

protected:
    /**
     * parse the file, read n° of nodes/edges and remove comments row
     * @param filenameVal
     */
    FILE* parseFile(const string &filenameVal);
};


#endif //PAGERANK_CSR_H
