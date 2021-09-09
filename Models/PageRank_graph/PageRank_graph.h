#ifndef PAGERANK_PAGERANK_GRAPH_H
#define PAGERANK_PAGERANK_GRAPH_H

#include <cmath>
#include <string>
#include <utility>
#include "../Utilities/Utilities.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;

struct VertexProperty {
        int id;
};

class PageRank_graph
{
protected:
    typedef boost::adjacency_list<listS, vecS, undirectedS, VertexProperty> Graph;
    Graph g;
    float dampingFactor = 0.85;
    string path;
    vector<double> p;
    int n_nodes = 0;
    int n_edges = 0;

    /**
     * Initialize the stochastization of the matrix
     *
     * 
     */
    void stochastization(Graph *g);

     /**
     * parse the file, read n° of nodes/edges and remove comments row
     * @param filenameVal
     */
    FILE* parseFile(const string &filenameVal);
public:
    
    float getDampingFactor() const;

    void setDampingFactor(float dampingFactor);

    void setPath(const string &s) ;

    const string &getPath() const;

    int getNNodes() const;

    void setNNodes(int nNodes);

    int getNEdges() const;

    void setNEdges(int nEdges);

    void setGraph();

    Graph getGraph();
    
    void pageRankGraph(string &str);

    void compute(Graph *g);

};



#endif 