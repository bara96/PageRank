cmake_minimum_required(VERSION 3.19)
enable_language(CXX)
set(Boost_INCLUDE_DIR /usr/local/include/boost/)
set(Boost_LIBRARY_DIR /usr/local/include/boost/)
find_package(Boost 1.76.0 COMPONENTS system filesystem graph iostreams)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

project(PageRank)

set(CMAKE_CXX_STANDARD 14)

add_executable(PageRank main.cpp  
                Models/CSR/CSR.cpp
                Models/CSR/CSR.h 
                Models/Utilities/Utilities.cpp 
                Models/Utilities/Utilities.h 
                Models/PageRank/PageRank.cpp 
                Models/PageRank/PageRank.h
                Models/PageRank_graph/PageRank_graph.cpp 
                Models/PageRank_graph/PageRank_graph.h
                Models/DAAT/DAAT.cpp
                Models/DAAT/DAAT.h 
                Models/MinHeap/MinHeap.cpp 
                Models/MinHeap/MinHeap.h 
                Models/HITS/HITS.cpp 
                Models/HITS/HITS.h 
                Models/InDegree/InDegree.cpp 
                Models/InDegree/InDegree.h)
target_link_libraries( PageRank ${Boost_LIBRARIES} )