//
// Created by mbaratella on 13/07/2021.
//

#include "Utilities.h"

FILE* Utilities::openFile(const string& filename, const string& mode) {
    FILE *file = nullptr;
    file = fopen(filename.c_str(), mode.c_str());
    if (file == nullptr){
        cerr << "Cannot openFile the file" << endl;
        exit(1);
    }
    return file;
}

int* Utilities::openMMap(const string& mapFilename, const int& mapPointerSize) {
    int file_row = open(mapFilename.c_str(), O_RDONLY);
    int *pointer = (int *) mmap(nullptr, mapPointerSize * sizeof(int), PROT_READ, MAP_SHARED, file_row, 0);
    close(file_row);
    if (pointer == MAP_FAILED) {
        cerr << "Error with the mapping of the file" << endl;
        exit(1);
    }
    return pointer;
}

void Utilities::closeMMap(int *pointer, int pointerSize) {
    if (munmap(pointer, pointerSize * sizeof(int)) == -1) {
        cerr << "Error un-mmapping the file" << endl;
        exit(1);
    }
}

bool Utilities::checkTermination(const vector<double> &vector, const std::vector<double> &vectorNew, int nNodes, double errorThreshold) {
    // termination condition is defined by the case in which two consecutive iterations of the algorithm produce two almost identical vectors.
    // Compute the Euclidean distance between the vectors vector1 and vector2
    double error = 0.0;
    for(int i=0; i<nNodes; i++) {
        error =  error + fabs(vectorNew.at(i) - vector.at(i));
    }
    //if two consecutive instances of the algorithm vector are almost identical, stop
    if (error < errorThreshold){
        return false;
    }
    else
        return true;
}

double Utilities::jaccard(const vector<double> &scores1, const vector<double> &scores2, const int &nNodes) {
    double sum = 0.0;

    for(int i=0; i<nNodes; i++){
        for(int j=0; j<nNodes; j++){
            if(scores1.at(i) == scores2.at(j)){
                sum = sum + 1.0;
            }
        }
    }

    return sum / (nNodes * 2 - sum);
}
