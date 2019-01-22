//
// Martin Ethier, ID: 20660931
//

#ifndef LAB_6_GRAPH_H
#define LAB_6_GRAPH_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class graph {
private:
    int graph_matrix[10][10];
    vector<string> names;

public:
    graph(int new_graph[10][10], vector<string> new_names);
    ~graph();

    void shortest_path(string start_name);
};


#endif //LAB_6_GRAPH_H
