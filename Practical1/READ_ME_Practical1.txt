~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Networks : Structure and dynamics
NSD: Practical 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Authors:
- MUTIAH BINTI ABDUL HAMID
- ISRAEL MARQUEZ SALINAS

Content:
This folder contains the 8 exercises submitting Practical 1 in the NSD Laboratory (Autumn 2017/18). Every directory is contain a README.txt file, along with the required codes deployed for solving the proposed exercises.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Exercise 1 - Reading the graph from a text file with format x y, where each lines represents an edge between x and y nodes.

The coding language has been defined as c++, we have used the operator >> which reads the entry in a file until it find an space or break line.

Exercise 2 - Size of a graph.

We have used the mechanism of readline, with this option we read the file and calculate the  number of edges.

To calculate the nodes the we use again >>, this time we fall in a loop for each entry that is being read and compare with the previous one to identify if it is the greates value so far, as the format is non-directed graph with x and y being numbered this approach is implemented to idedntify the greatest node number.

Exercise 3 - Node Degree

For this exercise the nodes are being stored in a vector and sorted, from lowest to greates. With the unique operation we collect only one node from the list of edges, this as a node migth have more that one node.

For the node degree we have created a vector pair, on the first element we hold the node number, on the second element we hold the degree of that vector.

To do so we create an iterator that cycles through the vector of nodes and the proceeds on a second comparisson to store the number of recurrences of the node number in the txt file. With this iterator we add the second element of the node - degree vector pair and get the degree of the node.

Exercise 4 - Clean Graph
We continue to use a vector pair to keep the edeges in the file. With this managemnet it is possible to compare of the vector pair's first element is same the second, if it is then we remove the pair from the vector pair holding the edges, with this operation we remove self-loops.

For the duplicated edges, the process is implemented with a structure called custom_comparator, this structre allows to create an object that compars the element being held in the first element with the elements in the vector of nodes, whether if the order is x y or y z. By adpating this structure to the vector pair we have chosen to manage the list of edges x y the duplicated edges are removed.


Exercise 5 - Graph Structues.
The first item, storing it as as list of edges has been implemented using a vector pair, a structure in c in which in allows to hold a pair of int or string, based on the file format we have been working with this has been the approach implemented.

Adjacency Matrix, we have a library in which it is possible to use the struct that defines the nodes and edges of a matrix. Based on our first method of managing the file in x y format we have fed the structure with nodes and edges to create the adjacency matrix, this struct is in the Ajacency_Matrix.h header file.

Scalacibility --> We are ware that our code still taking a considerable amount of time, we consider that most of the time is being taken by the function in which we count the nodes as we are reading line by line, which denotes an edge. Therefore the more the edges the more the time it to process the calculations.


Exercise 7 - Number of Isolated Nodes
For this exercise the combiantion of using adjacency list and adjacency matrxi was implement to create custom functions to calculate the degree of the graph and for each node.

In order to do this we took samples of undirected graphs, then we implemented the calculation for number of nodes and edges. This for the average node degree.

For the nodes with zero degree we look for the nodes with no edges associated to them, this before cleanig the graph, otherwise we would have removed the self-loops and then we won't have nodes with zero edges.

For the minimum and max we implememted once again a vector pair to match the node with its degrees, then we go through the vector pair to identify the smallest or greates second element in the pair which holds the degree of the node and then we return the first element of that pair which is the node associated to the degree.


Exercice 8 - Degree Distribution.

Based on the previous exercies in which already have the degree per node we use the vector pair in which the relationship node - degree is created. We go through the vector and count the recurrences of the value for a degree, then we store those values on a second vector pair, in which the first element is number of nodes with a certain degree and the second item is the degree of those nodes.

Finally we go over the vector pair and print to a file, "degree_dist.txt", as a final step we use GNUplot script Fig.degree.dist.plt file to create the Degree_Dist.eps file illustrating the degree distribution.
