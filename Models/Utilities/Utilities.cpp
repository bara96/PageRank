//
// Created by mbaratella on 13/07/2021.
//

#include <cstdio>
#include "Utilities.h"

FILE *Utilities::openFile(const string& filename, const string& mode) {
    FILE *file;
    file = fopen(filename.c_str(), mode.c_str());
    if (file == nullptr){
        throw (runtime_error("Cannot openFile the file"));
    }
    return file;
}
