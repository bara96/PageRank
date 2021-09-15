#ifndef PAGERANK_PAGERANK_GRAPH_H
#define PAGERANK_PAGERANK_GRAPH_H

#include <cmath>
#include <string>
#include <utility>
#include "../Utilities/Utilities.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>

using namespace boost;


class PageRank_graph
{
protected:
    typedef boost::adjacency_list<vecS,
                                  vecS,
                                  bidirectionalS,
                                  no_property,
                                  property<edge_weight_t, float>> Graph;

    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    Graph g;
    string path;
    vector<double> p;
    float dampingFactor = 0.85;
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
    std::vector<double> update_vec; 

    float getDampingFactor() const;

    void setDampingFactor(float dampingFactor);

    void setPath(const string &s) ;

    const string &getPath() const;

    int getNNodes() const;

    void setNNodes(int nNodes);

    int getNEdges() const;

    void setNEdges(int nEdges);

    void initGraph();

    Graph getGraph();

    void computeVertexRank(Graph &g,Vertex &v, std::vector<double> &rank_vector);
    
    std::vector<double> pageRankGraph(string &str);

};



#endif 