cmake_minimum_required(VERSION 3.19)
project(PageRank)

set(CMAKE_CXX_STANDARD 14)

add_executable(PageRank main.cpp  Models/CSR/CSR.cpp Models/CSR/CSR.h Models/Utilities/Utilities.cpp Models/Utilities/Utilities.h Models/PageRank/PageRank.cpp Models/PageRank/PageRank.h Models/DAAT/DAAT.cpp Models/DAAT/DAAT.h Models/MinHeap/MinHeap.cpp Models/MinHeap/MinHeap.h Models/HITS/HITS.cpp Models/HITS/HITS.h Models/InDegree/InDegree.cpp Models/InDegree/InDegree.h)