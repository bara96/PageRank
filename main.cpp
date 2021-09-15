#include <iostream>

#include "Models/CSR/CSR.h"
#include "Models/PageRank/PageRank.h"
#include "Models/DAAT/DAAT.h"
#include "Models/PageRank_graph/PageRank_graph.h"
#include <chrono>

using namespace std;

vector<pair<int,double>> doPageRank(int topK, bool showTop) {
    //CSR csr = CSR("../Pagerank/src/web-NotreDame.txt");
    CSR csr = CSR("../Pagerank/src/web-NotreDame.txt");
    csr.compute();
    PageRank pr = PageRank(csr);
    pr.compute(false);

    DAAT daat = DAAT(pr.getScores());
    vector<pair<int,double>> top = daat.topK(topK);

    if(showTop) {
        cout << "PageRank Top k:" << endl;
        for (pair<int, double> &pair : top)
            cout << pair.first << ": " << pair.second << endl;
    }
    return top;
}

vector<pair<int, double>> doPageRank_graph(int topK, bool showTop) {
    PageRank_graph boost;
    string path = "../Pagerank/src/web-NotreDame.txt";
    std::vector<double> scores = boost.pageRankGraph(path);

    DAAT daat = DAAT(scores);
    vector<pair<int,double>> top = daat.topK(topK);

    if(showTop) {
        cout << "PageRank_graph_boost Top k:" << endl;
        for (pair<int, double> &pair : top)
            cout << pair.first << ": " << pair.second << endl;
    }
    return top;
   
}

int main() {
    int topK = 9;
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    //init page rank with CSR
    vector<pair<int, double>> topPageRank = doPageRank(topK, true);
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("\nTime measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    cout << endl;

    //init page rank with boost library
    begin = std::chrono::high_resolution_clock::now();
    vector<pair<int, double>> topPageRank_graph = doPageRank_graph(topK, true);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);   
    cout << endl;
    printf("\nTime measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}