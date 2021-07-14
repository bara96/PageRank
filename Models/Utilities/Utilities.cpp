//
// Created by mbaratella on 13/07/2021.
//

#include <cstdio>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "Utilities.h"

FILE* Utilities::openFile(const string& filename, const string& mode) {
    FILE *file;
    file = fopen(filename.c_str(), mode.c_str());
    if (file == nullptr){
        throw (runtime_error("Cannot openFile the file"));
    }
    return file;
}

int* Utilities::openMMap(const string& mapFilename, const int& mapPointerSize) {
    int file_row = open(mapFilename.c_str(), O_RDONLY);
    int *pointer = (int *) mmap(nullptr, mapPointerSize * sizeof(int), PROT_READ, MAP_SHARED, file_row, 0);
    close(file_row);
    if (pointer == MAP_FAILED) {
        throw (runtime_error("Error with the mapping of the file"));
    }
    return pointer;
}
