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

    typedef std::pair<int,int> Edge;

    f = Utilities::openFile(s,"r");

   

    //read all values from the main file
    while(!feof(f)){
        fscanf(f, "%d%d", &fromNode, &toNode);
        auto v1 = add_vertex(VertexProperty { fromNode }, g);
        auto v2 = add_vertex(VertexProperty { toNode }, g);
        add_edge(v1, v2, g);  
      
    }
    
   
    //read from file and insert nodes on the graph
    
}

    
    
    void PageRank_graph::pageRankGraph(string &str){
        setPath(str);
        setGraph();
    };