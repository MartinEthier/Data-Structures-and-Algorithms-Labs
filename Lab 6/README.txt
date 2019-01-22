Martin Ethier, ID: 20660931

MTE 140 Lab 6 - Graph ADT

The graph ADT was implemented using the adjacency matrix structure. The class had 2 private attributes:
-A string vector to contain the names of the nodes, called "names"
-The adjacency matrix itself, A 10X10 2d array called "graph_matrix"

The "names" vector contains the names of the nodes in the same order as they appear in the adjacency matrix.

Included is a constructor which assigns the given matrix and vector to their respective variables. There is also an empty default 
destructor since there was no need for dynamic memory in this ADT.

Finally, there is the "shortest_path" method which computes the shortest path to each node starting from the node given as the 
parameter. The method implements dijkstra's shortest path algorithm to find the paths.

Execution:
In the main function, prepare a 10x10 array as the adjacency matrix, and along with it populate a 10 element vector with the names 
of the nodes in the order that they appear in the matrix. Initialize a new graph with the created matrix and vector and apply the 
shortest_path method on the new graph.
