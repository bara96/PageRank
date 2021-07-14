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
