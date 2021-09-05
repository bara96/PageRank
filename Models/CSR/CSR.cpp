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

const string &CSR::getIntroduction() const {
    return introduction;
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
    char string[100];
    f = Utilities::openFile(filenameVal, "r");
    character = getc(f);
    while (character == '#'){
        //Reads characters from stream and stores them as a C string into str until (num-1)
        //characters have been read or either a newline or the end-of-file is reached, whichever happens first.
        fgets(string, 100 - 1, f);
       
        introduction += "#"+std::string(string);
        //Reads data from s and stores them according to parameter format into the locations given by the additional arguments,
        //as if scanf was used, but reading from s instead of the standard input (stdin).
        sscanf(string, "%*s %d %*s %d", &n_nodes, &n_edges);
        //Returns the character currently pointed by the internal file position indicator of the specified stream.
        character = getc(f);
    }
    ungetc(character, f);

    cout << "N° of Nodes: " << n_nodes << ", N° of Edges:: " << n_edges << endl;

    return f;
}


void CSR::transposeCSR(){
    int fromNode = 0, toNode = 0;
    FILE *mainFile, *column_index_file, *row_pointer_file;
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

    //define tuple namespace and a vector of tuple
   
    typedef vector<tuple<int,int>> tuple_list;
    
    
    namespace filesys = boost::filesystem;
    

    filesys::path filepath(getFilename()); 
    auto filename1 = filepath.filename();
    
    
    
    auto parentPath = filepath.parent_path();
    //build path of new file
    char *copyfilename = strdup(filename1.c_str());
    string copyParentdir = strdup(parentPath.c_str());
    std::string s1 ("/");
    std::string new_filename = std::strtok(copyfilename,".") ;
    new_filename.insert(0,s1);
    std::string s2="-transposed-1.txt";

    //create new file transposed
    std::string final_str=copyParentdir.append(new_filename).append(s2);
    auto dest = ofstream (final_str);
    mainFile = parseFile(filename); 

    dest << introduction;
    tuple_list edges;
    while(!feof(mainFile)){
        fscanf(mainFile, "%d%d", &fromNode, &toNode);
        edges.push_back(tuple<int,int>(toNode,fromNode));
                 
    }
    fclose(mainFile);

    std::sort(edges.begin(), edges.end());
     for (tuple_list::const_iterator i = edges.begin(); i != edges.end(); ++i){
        // cout << "from: " << std::get<0>(*i)<< "   ";
        // cout << "to: " << std::get<1>(*i) << endl;
        dest << std::get<0>(*i)<< "   "<< std::get<1>(*i) << endl;
    }
    dest.close();
    setFilename(final_str);
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

