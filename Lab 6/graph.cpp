//
// Martin Ethier, ID: 20660931
//

#include "graph.h"

graph::graph(int new_graph[10][10], vector<string> new_names) {
    for (int i = 0; i < 10; i++) {
        names.push_back(new_names[i]);
        for (int j = 0; j < 10; j++) {
            graph_matrix[i][j] = new_graph[i][j];
        }
    }
}

graph::~graph() {

}

void graph::shortest_path(string start_name) {
    //initialize distance array and shortest path set array
    int dist[10];
    bool shortest_path_set[10];
    int starting_node = 10;

    //find index of starting node
    for (int i = 0; i < 10; i++) {
        if (start_name == names[i]) {
            starting_node = i;
        }
    }

    if (starting_node == 10) {
        cout << "Given node is not contained in graph.";
        return;
    }

    for (int i = 0; i < 10; i++) {
        dist[i] = INT8_MAX;
        shortest_path_set[i] = false;
    }

    dist[starting_node] = 0;

    for (int count = 0; count < 9; count ++) {
        int min = INT8_MAX, index_min;

        for (int i = 0; i < 10; i ++) {
            if (dist[i] <= min && !shortest_path_set[i]) {
                min = dist[i];
                index_min = i;
            }
        }

        shortest_path_set[index_min] = true;

        for (int i = 0; i < 10; i ++) {
            if (graph_matrix[index_min][i] != INT8_MAX && !shortest_path_set[i] && dist[index_min] != INT8_MAX
                && dist[index_min] + graph_matrix[index_min][i] < dist[i]) {
                dist[i] = dist[index_min] + graph_matrix[index_min][i];
            }
        }

    }

    // print distance array
    cout << "Node   Distance from " << start_name << endl;
    for (int i = 0; i < 10; i ++) {
        cout << names[i] << "----" << dist[i] << endl;
    }

}


int main() {
    vector<string> new_names1;
    new_names1.push_back("Darryl");
    new_names1.push_back("Andy");
    new_names1.push_back("Kelsey");
    new_names1.push_back("Nathan");
    new_names1.push_back("Greg");
    new_names1.push_back("Olive");
    new_names1.push_back("Shelley");
    new_names1.push_back("Jess");
    new_names1.push_back("Brooks");
    new_names1.push_back("Maria");

    int new_graph1[10][10] = {{0,9,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,2},
                          {9,0,1,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,3,INT8_MAX},
                          {INT8_MAX,1,0,7,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,2},
                          {INT8_MAX,INT8_MAX,7,0,INT8_MAX,6,INT8_MAX,1,8,INT8_MAX},
                          {INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,0,10,2,INT8_MAX,INT8_MAX,INT8_MAX},
                          {INT8_MAX,INT8_MAX,INT8_MAX,6,10,0,4,7,INT8_MAX,INT8_MAX},
                          {INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,2,4,0,6,INT8_MAX,INT8_MAX},
                          {INT8_MAX,INT8_MAX,INT8_MAX,1,INT8_MAX,7,6,0,5,INT8_MAX},
                          {INT8_MAX,3,INT8_MAX,8,INT8_MAX,INT8_MAX,INT8_MAX,5,0,6},
                          {2,INT8_MAX,2,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,6,0}};

    graph graph1(new_graph1, new_names1);

    graph1.shortest_path("Andy");

    vector<string> new_names2;
    new_names2.push_back("Rick");
    new_names2.push_back("James");
    new_names2.push_back("Donny");
    new_names2.push_back("Patrick");
    new_names2.push_back("Bob");
    new_names2.push_back("Chelsey");
    new_names2.push_back("Marie");
    new_names2.push_back("Logan");
    new_names2.push_back("Morty");
    new_names2.push_back("Jenny");

    int new_graph2[10][10] = {{0,3,INT8_MAX,8,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,1},
                              {3,0,1,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX},
                              {INT8_MAX,1,0,4,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX},
                              {8,INT8_MAX,4,0,4,INT8_MAX,INT8_MAX,7,INT8_MAX,INT8_MAX},
                              {INT8_MAX,INT8_MAX,INT8_MAX,4,0,2,10,INT8_MAX,INT8_MAX,INT8_MAX},
                              {INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,2,0,5,INT8_MAX,INT8_MAX,INT8_MAX},
                              {INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,10,5,0,8,6,INT8_MAX},
                              {INT8_MAX,INT8_MAX,INT8_MAX,7,INT8_MAX,INT8_MAX,8,0,INT8_MAX,10},
                              {INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,6,INT8_MAX,0,7},
                              {1,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,INT8_MAX,10,7,0}};

    graph graph2(new_graph2, new_names2);

    graph2.shortest_path("Rick");

    return 0;
}