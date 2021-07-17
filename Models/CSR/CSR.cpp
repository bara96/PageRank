//
// Created by mbaratella on 13/07/2021.
//

#include "CSR.h"

CSR::CSR() = default;

CSR::CSR(string filename) : filename(std::move(filename)) {}

const string &CSR::getFilename() const {
    return filename;
}

void CSR::setFilename(const string &filenameVal) {
    CSR::filename = filenameVal;
}

void CSR::setMapColIndFilename(const string &mapColIndFilename) {
    map_col_ind_filename = mapColIndFilename;
}

void CSR::setMapRowPtrFilename(const string &mapRowPtrFilename) {
    map_row_ptr_filename = mapRowPtrFilename;
}

const string &CSR::getMapColIndFilename() const {
    return map_col_ind_filename;
}

const string &CSR::getMapRowPtrFilename() const {
    return map_row_ptr_filename;
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

vector<double> &CSR::getValues() {
    return values;
}

void CSR::setValues(const vector<double> &valuesVal) {
    CSR::values = valuesVal;
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
    FILE *f = nullptr;
    char character;
    char str[100];

    f = Utilities::openFile(filenameVal, "r");
    character = getc(f);
    while (character == '#'){
        //TODO convert into C++
        fgets(str, 100 - 1, f);
        sscanf(str, "%*s %d %*s %d", &n_nodes, &n_edges);
        character = getc(f);
    }
    ungetc(character, f);

    cout << "N° of Nodes: " << n_nodes << ", N° of Edges:: " << n_edges << endl;

    return f;
}

void CSR::compute() {
    int fromNode = 0, toNode = 0;
    int currentRow = 0;
    // Elements for row
    int elemRow = 0;
    // Cumulative numbers of elements
    int currentElem = 0;
    //temporary row
    int tempRow;
    //values, initially set to 1.0 as default
    values = vector<double>();
    //files
    FILE *mainFile, *column_index_file, *row_pointer_file;

    cout << "COMPUTING CSR START" << endl;

    mainFile = parseFile(filename);     //main file with values
    column_index_file = fopen(map_col_ind_filename.c_str(), "w+");  //col_ind file pointer
    row_pointer_file = fopen(map_row_ptr_filename.c_str(), "w+");   //row_ptr file pointer

    // The first row always starts at position 0
    tempRow = 0;
    fwrite(&tempRow, sizeof(int), 1, row_pointer_file);

    //read all values from the main file
    while(!feof(mainFile)){
        fscanf(mainFile, "%d%d", &fromNode, &toNode);

        // Chek if we need to change row
        if (fromNode > currentRow) {
            currentElem = currentElem + elemRow;
            for (int k = currentRow + 1; k <= fromNode; k++) {  //store on file the row
                fwrite(&currentElem, sizeof(int), 1, row_pointer_file);
            }
            elemRow = 0;
            currentRow = fromNode;
        }
        values.push_back(1.0);  //add row value as 1.0 (we'll need stochatization later)
        fwrite(&toNode, sizeof(int), 1, column_index_file); //store on file the col
        elemRow++;
    }
    tempRow = currentElem + elemRow - 1;
    fwrite(&tempRow, sizeof(int), 1, row_pointer_file);

    fclose(row_pointer_file);
    fclose(column_index_file);
    fclose(mainFile);

    //save pointer sizes, for mmap
    row_pointer_size = currentRow + 2;
    col_index_size = (int) values.size();

    cout << "COMPUTING CSR START END" << endl;
}

