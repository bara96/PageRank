#include "PageRank_graph.h"



float PageRank_graph::getDampingFactor() const{
    return this->dampingFactor;
}

void PageRank_graph::setDampingFactor(float dampingFactor){
    this->dampingFactor = dampingFactor;
}

const string &PageRank_graph::getPath() const {
    return this->path;

}
void PageRank_graph::setPath(const string &pathval) {
     this->path = pathval;

}
int PageRank_graph::getNNodes() const {
    return n_nodes;
}

void PageRank_graph::setNNodes(int nNodes) {
    n_nodes = nNodes;
}

int PageRank_graph::getNEdges() const {
    return n_edges;
}

void PageRank_graph::setNEdges(int nEdges) {
    n_edges = nEdges;
}

FILE* PageRank_graph::parseFile(const string &filenameVal) {
    FILE *f = nullptr;
    char character;
    char str[100];

    f = Utilities::openFile(filenameVal, "r");
    character = getc(f);
    while (character == '#'){
        fgets(str, 100 - 1, f);
        sscanf(str, "%*s %d %*s %d", &n_nodes, &n_edges);
        character = getc(f);
    }
    ungetc(character, f);

    cout << "N° of Nodes: " << n_nodes << ", N° of Edges:: " << n_edges << endl;

    return f;
}

PageRank_graph::Graph PageRank_graph::getGraph() {
    return this->g;
}

void PageRank_graph::setGraph() {
    
    int fromNode = 0, toNode = 0;
    int currentRow=0;
   // Elements for row
    int elemRow = 0;
    // Cumulative numbers of elements
    int currentElem = 0;
    //temporary row
    int tempRow;
    //values, initially set to 1.0 as default
    int temprow=0;
    FILE *f = nullptr;
    string s = this->getPath();
    typedef typename boost::graph_traits<Graph>::vertex_iterator Viter;
    Viter v, vend;

    f = parseFile(s);

    //read all values from the main file and create edges and nodes
    while(!feof(f)){
        fscanf(f, "%d%d", &fromNode, &toNode);
        add_edge(fromNode, toNode, g);
    }
   //The property map interface provides a generic method for accessing properties from graphs
   //fullfill vertex with his property (out degree)
   int i = 0;
    for (boost::tie(v, vend) = vertices(g); v != vend; ++v) {
        std::cout << "Vertex descriptor # " << *v 
             << "degree: " << (boost::in_degree(*v, g))
             << "\n";
          g[i].degree_out = (boost::in_degree(*v, g));
          i++;
             
    }
    //read from file and insert nodes on the graph
    
}

void PageRank_graph::computeVertexRank(Graph &g,Vertex &the_vertex, std::map<int, float> &rank_map){
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    //  Viter v, vend;
    //     for (boost::tie(v, vend) = vertices(g); v != vend; ++v) {
            float total_rank = (1 - dampingFactor)/n_nodes;
            float part_rank = 0;
            //define iterators and descriptor to get informations about edges connecting the_vertex and other vertex
            typename graph_traits<Graph>::edge_descriptor e;
            typename graph_traits<Graph>::in_edge_iterator in_i, in_end;
            //get all nodes with arc enetring in the_vertex anc compute their rank. at the end 
            //the sum of these ranks will be the rank of the_vertex
            for (boost::tie(in_i, in_end) = in_edges(the_vertex, g); in_i != in_end; ++in_i)
            {
            e = *in_i;
            //we are interested only on source (since is the node that is connected to the target that's the_vertex)
            Vertex src = source(e, g), targ = target(e, g);
            int src_name = src;
            float rank = rank_map[src_name];

            //divide the rank by the out edges num to do the normalization
            rank = rank / float(out_degree(src, g));
            part_rank += rank;

            std::cout << "(" << src
                        << "," << targ << ") ";
            }
            std::cout << std::endl;
            total_rank += part_rank * dampingFactor;

            //update
            PageRank_graph::update_map[the_vertex] = total_rank;
            std::cout << "update rank value for node: " << the_vertex << ", and value:" << total_rank << std::endl;
                
        // }
}
    
void PageRank_graph::pageRankGraph(string &str){
    typedef typename boost::graph_traits<Graph>::vertex_iterator Viter;
    Viter v, vend;
    std::map<int, float> node_rank_map;
    setPath(str);
    setGraph();
    Graph g= getGraph();
    
    for(int i=0; i < n_nodes+1; i++) {
        node_rank_map[i] = 1.0 / float(n_nodes);
    }
    const int max_iter = 39;

    for (int i=0; i<max_iter; ++i) {
        std::cout << "=====The " << i << " th iter=======" << std::endl;

         for (boost::tie(v, vend) = vertices(g); v != vend; ++v) {
              typename graph_traits<Graph>::vertex_descriptor vtx;
              vtx=*v;
              PageRank_graph::computeVertexRank(g,vtx,node_rank_map);
         }
        
        // print rank value:
        // std::map<int, float>::iterator it(node_rank_map.begin());
        // for(; it != node_rank_map.end(); ++it) {
        //     std::cout << it->first << "--->" << it->second << std::endl;
        // }

        node_rank_map.swap(update_map);
        update_map.clear();
        
    }
       // print rank value:
    std::map<int, float>::iterator it(node_rank_map.begin());
        for(; it != node_rank_map.end(); ++it) {
            std::cout << it->first << "--->" << it->second << std::endl;
        }
    std::cout << "FINISH" << endl;
 
};