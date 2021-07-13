//
// Created by mbaratella on 13/07/2021.
//

#include "CSR.h"

#include <utility>

CSR::CSR() = default;

CSR::CSR(string filename) : filename(std::move(filename)) {}

const string &CSR::getFilename() const {
    return filename;
}

void CSR::setFilename(const string &filenameVal) {
    CSR::filename = filenameVal;
}

const string &CSR::getMapColInd() const {
    return map_col_ind;
}

const string &CSR::getMapRowPtr() const {
    return map_row_ptr;
}

int CSR::getNNodes() const {
    return n_nodes;
}

void CSR::setNNodes(int nNodes) {
    n_nodes = nNodes;
}

int CSR::getNEdges() const {
    return n_edges;
}

void CSR::setNEdges(int nEdges) {
    n_edges = nEdges;
}

const vector<float> &CSR::getValues() const {
    return values;
}

void CSR::setValues(const vector<float> &values) {
    CSR::values = values;
}

int CSR::getRowPointerSize() const {
    return row_pointer_size;
}

void CSR::setRowPointerSize(int rowPointerSize) {
    row_pointer_size = rowPointerSize;
}

int CSR::getColIndexSize() const {
    return col_index_size;
}

void CSR::setColIndexSize(int colIndexSize) {
    col_index_size = colIndexSize;
}

FILE* CSR::parseFile(const string &filenameVal) {
    cout << "PARSER BEGIN" << endl;

    FILE *f = Utilities::openFile(filenameVal, "r");
    char character;
    char str[100];
    character = getc(f);
    while (character == '#'){
        fgets(str, 100 - 1, f);
        sscanf(str, "%*s %d %*s %d", &n_nodes, &n_edges);
        character = getc(f);
    }
    ungetc(character, f);

    cout << "PARSER END" << endl;

    return f;
}

void CSR::computeCSR() {
    int fromnode, tonode;
    int current_row = 0;
    int i = 0;
    // Elements for row
    int elem_row = 0;
    // Cumulative numbers of elements
    int current_elem = 0;
    int temp_r;
    //values
    values = vector<float>();

    FILE *mainFile, *column_index_file, *row_pointer_file;

    mainFile = parseFile(filename);
    column_index_file = fopen(map_col_ind.c_str(), "w+");
    row_pointer_file = fopen(map_row_ptr.c_str(), "w+");

    // The first row always starts at position 0
    temp_r = 0;
    fwrite(&temp_r, sizeof(int), 1, row_pointer_file);

    while(!feof(mainFile)){
        fscanf(mainFile,"%d%d",&fromnode,&tonode);

        // CHECK IF WE NEED TO CHANGE THE ROW
        if (fromnode > current_row) {
            current_elem = current_elem + elem_row;
            for (int k = current_row + 1; k <= fromnode; k++) {
                fwrite(&current_elem, sizeof(int), 1, row_pointer_file);
            }
            elem_row = 0;
            current_row = fromnode;
        }
        values.insert(values.begin() + i, 1.0);
        fwrite(&tonode, sizeof(int), 1, column_index_file);
        elem_row++;
        i++;
    }
    
    temp_r = current_elem + elem_row - 1;
    fwrite(&temp_r, sizeof(int), 1, row_pointer_file);
    fclose(row_pointer_file);
    fclose(column_index_file);
    row_pointer_size = current_row+2;
    col_index_size = i;
}
