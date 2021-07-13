//
// Created by mbaratella on 13/07/2021.
//

#ifndef PAGERANK_UTILITIES_H
#define PAGERANK_UTILITIES_H

#include <iostream>
#include <cerrno>
#include <cstdio>

using namespace std;

class Utilities {
public:

    static FILE *openFile(const string& filename, const string &mode);

};


#endif //PAGERANK_UTILITIES_H
