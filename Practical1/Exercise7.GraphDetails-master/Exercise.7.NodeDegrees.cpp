//First Exercise
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include "Adjacency_Matrix.h"

using namespace std;

void readMatrixFile(string filename, int lines){

    ifstream matrix_file(filename);
    int nodeA;
    int nodeB;

    int iteration=0;

    while(iteration<lines) {
        matrix_file >> nodeA;
        matrix_file >> nodeB;
        iteration++;
    }

    matrix_file.close();

}

int getEdges(string filename){

    int lines_count=0;
    string line;
    ifstream matrix_file(filename);

    if(matrix_file.is_open()) {
        while (getline(matrix_file,line)){
            lines_count++;
        }

    }
    else
    {
        cout << "File could not be opened" << '\n';
    }

    matrix_file.close();

    return lines_count;
}

int getNodes(string filename, int lines){

    ifstream matrix_file(filename);

    std::vector<int> nodes;
    int node;
    int total_nodes;
    while (matrix_file>>node){
        nodes.push_back(node);
    }

    //Sorting the Vector and removing duplicates
    std::sort(nodes.begin(),nodes.end());
    auto last_node = std::unique(nodes.begin(),nodes.end());
    nodes.erase(last_node, nodes.end());

    //Getting the number of Nodes
    matrix_file.close();

    return nodes.size();

}

void getNodeDegrees(string filename){

    ifstream matrix_file(filename);

    std::vector<int> nodes;
    int node;

    while (matrix_file>>node){
        nodes.push_back(node);
    }

    std::sort(nodes.begin(),nodes.end());

    map<int, int> nodesMap;

    vector<int>::iterator position;

    for (position=nodes.begin();position<nodes.end();++position){
        nodesMap[*position] +=1;
    }

    map<int, int>::iterator nodesPositionMap;
    for (nodesPositionMap=nodesMap.begin();nodesPositionMap!=nodesMap.end();++nodesPositionMap){
        cout << "Node: " << nodesPositionMap->first << "\t";
        cout << "Degree: " << nodesPositionMap->second << "\n";
    }

    matrix_file.close();

}

vector<pair<int, int>> storeNodesVector(string filename, int lines){
	ifstream matrix_file(filename);

    vector<pair<int, int>>nodes;
    pair<int,int> nodePair;
    int counter=0;

    while (matrix_file && counter<lines){
        matrix_file>>nodePair.first;
        matrix_file>>nodePair.second;
        nodes.push_back(nodePair);
        counter++;
    }
    /*
    //Printing the Vector unsorted
    cout << "\n Printing the Vector Unsorted. \n";
    for (int i=0; i<nodes.size();i++){
        cout << "Pair[" << i << "]: "<< nodes[i].first << ", " << nodes[i].second << "\n";
    }
    */
     matrix_file.close();

    return nodes;
    /*
    //Sorting the Vector and removing duplicates
    std::sort(nodes.begin(),nodes.end());
    auto last_node = std::unique(nodes.begin(),nodes.end());
    nodes.erase(last_node, nodes.end());

    //Getting the number of Nodes
    return nodes.size();
	*/
}

vector<pair<int, int>> removeDuplicatedEdges(vector<pair<int, int>>nodes){

    auto it = nodes.begin();
    for (; it != nodes.end(); ++it) {
        auto pit = nodes.begin();
        for (; pit != nodes.end();) {
            if (((it->first == pit->first && it->second == pit->second) || (it->first == pit->second && it->second == pit->first)) && (pit != it)) {
                //Printing to validate which edges are being seen as duplicated.
                //std::cout << "found pair " << it->first << "," << it->second << " with " << pit->first << "," << pit->second << std::endl;
                pit = nodes.erase(pit);
            } else {
                ++pit;
            }
        }

    }

    /*
    for (int i=0; i<nodes.size();i++){
        cout << "Pair[" << i << "]: "<< nodes[i].first << ", " << nodes[i].second << "\n";
    }
    */
    return nodes;
    /*
    std::set<std::pair<int, int>, custom_comparator> unique;

    for (const auto& p : nodes) {
        unique.insert(p);
    }

    for (const auto& p : unique) {
        std::cout << p.first << ", " << p.second << "\n";
    }
    */
}

vector<pair<int, int>> removeSelfLoops(vector<pair<int, int>>nodes){

    for (int i=0;i<=nodes.size();i++){

        //cout << "Node[" << i << "]" << "["<< nodes[i].first << "]" << "[" << nodes[i].second << "] \n";
        if(nodes[i].first == nodes[i].second){
            nodes.erase(nodes.begin()+i);
        }
    }

    /*
    //Printing the Vector unsorted
    for (int i=0; i<nodes.size();i++){
        cout << "Pair[" << i << "]: "<< nodes[i].first << ", " << nodes[i].second << "\n";
    }
    */

    return nodes;

}

void printListofEdges(vector<pair<int,int>> nodes){

    cout << "Printing graph as a list of edges.\n";
    for (int i=0; i<nodes.size();i++){
        cout << "Edge[" << i << "]: "<< nodes[i].first << ", " << nodes[i].second << "\n";
    }

}

AdjacencyMatrix populateMatrix(AdjacencyMatrix matrix,vector<pair<int,int>> clean_graph){
    for (int i =0; i<clean_graph.size();i++){

        matrix.add_edge(clean_graph[i].first,clean_graph[i].second);
    }

    return matrix;
}

void populateGraph(Graph graph, vector<pair<int,int>> nodes){

    for (int i=0; i<nodes.size();i++){
        graph.addEdge(nodes[i].first,nodes[i].second);
    }

}

double computeGraphDensity(double edges, double nodes){

    double graph_density = (2*edges)/(nodes * (nodes-1));

    /*
    int upper_part = 2*edges;
    int lower_part = nodes * (nodes-1);
    cout << "Upper Part" << upper_part << "\n";
    cout << "Lower Part" << lower_part << "\n";

    graph_density = double (upper_part)/lower_part;
    cout << "Graph density within fucntion.";
    std::cout << std::fixed << graph_density << "\n";
    */

    return graph_density;
}

double computeAverageDegree(vector<pair<int,int>> nodes_degrees, double total_nodes){

    double average_degree=0.0000000000;
    double nodes_degree_sum=0;

    for (int i=0; i<nodes_degrees.size();i++){
        nodes_degree_sum+=nodes_degrees[i].second;
    }

    average_degree = nodes_degree_sum/total_nodes;

    return average_degree;
}

vector<pair<int, int>> computeMinimumDegree(vector<pair<int,int>> nodes_degrees){

    int minimum_degree=0;
    int node_with_min_degree=0;
    vector<pair<int, int>> min_degree_node;

    minimum_degree=nodes_degrees[0].second;

    for (int i =0;i < nodes_degrees.size();i++){

        if (nodes_degrees[i].second<minimum_degree){
            minimum_degree = nodes_degrees[i].second;
            node_with_min_degree = i;
        }
    }

    min_degree_node.push_back(std::make_pair(node_with_min_degree,minimum_degree));
    return min_degree_node;
}


vector<pair<int, int>> computeMaximumDegree(vector<pair<int,int>> nodes_degrees){

    int maximum_degree=0;
    int node_with_max_degree=0;
    vector<pair<int, int>> max_degree_node;

    maximum_degree=nodes_degrees[0].second;

    for (int i =0;i < nodes_degrees.size();i++){

        if (nodes_degrees[i].second>maximum_degree){
            maximum_degree = nodes_degrees[i].second;
            node_with_max_degree = i;
        }
    }

    max_degree_node.push_back(std::make_pair(node_with_max_degree,maximum_degree));
    return max_degree_node;
}


int computeNodesWithZeroDegree(vector<pair<int,int>> nodes_degrees){


    int nodes_with_zero_degree =0;

    for (int i =0;i < nodes_degrees.size();i++){

        if (nodes_degrees[i].second==0){
            nodes_with_zero_degree++;
        }
    }

    return nodes_with_zero_degree;
}


int main() {

    /*Please change "matrix.txt" to the value of the file name containing the data to be working with.
     *
     * The options of file to choose from are:
     * 01_Pretty_Good_Privacy.txt
     * 02_Brightkite.txt
     * 03_Actor_collaborations.txt
     *
     * */

    string filename="01_Pretty_Good_Privacy.txt";

    int edges = 0;
    int total_nodes=0;
    int size_of_matrix = 0;
    double graph_density = 0.0000000000;
    vector<pair<int, int>>nodes;
    vector<pair<int, int>>nodes_clean;
    vector<pair<int, int>>clean_graph;
    vector<pair<int, int>>nodes_degrees;

    vector<pair<int, int>>min_degree_node;
    vector<pair<int, int>>max_degree_node;

    ///* We read the File that contains the x - y, in which each

    // We count the lines in the file, this can be considered as the number of edges
    // due to the fact that file is format on a relationship in which each line is x y
    // denoting that an edge exists between x and y
    edges = getEdges(filename);

    // We get the number of nodes in the graph.
    total_nodes=getNodes(filename,edges);

    // Storing Values from txt file into a vector pair.
    nodes = storeNodesVector(filename, edges);

    // Removing duplicated edges from the vector.
    nodes_clean = removeDuplicatedEdges(nodes);

    //cout << "Graph after removing duplicated edges";
    //printVector(nodes_clean);

    // Removing Self-Loops after the duplicated edges have been removed.
    clean_graph = removeSelfLoops(nodes_clean);

    /*
     *
     * Section associated to testing the result of graph management
     * 1.- List of Edges
     * 2.- Adjacency Matrix
     * 3.- Adjacency List
     *
     * //Section to manage graph as list of edges.
    printListofEdges(clean_graph);
    cout << "\n";

    //Section to manage graph as an adjacency matrix.
    AdjacencyMatrix matrix(total_nodes);
    matrix = populateMatrix(matrix,clean_graph);
    matrix.display();
    cout << "\n";

    //Section to manage the graph as an adjacency list
    Graph graph(total_nodes);
    populateGraph(graph,clean_graph);
    graph.printGraph();

     printListofEdges(nodes);
    cout << "\n";
    cout << "\n";

    */


    AdjacencyMatrix matrix(total_nodes);
    matrix = populateMatrix(matrix,nodes);
    //matrix.display();

    nodes_degrees = matrix.nodesDegree();

    cout << "Number of Edges: "<< edges <<"\n";
    cout << "Number of Nodes: "<< total_nodes <<"\n";
    graph_density = computeGraphDensity(edges,total_nodes);
    cout << "Graph Fill (KONECT): ";
    std::cout << std::fixed << graph_density << "\n";
    //cout << "Graph Average Degree: " << computeAverageDegree(nodes_degrees,total_nodes) <<"\n";
    cout << "Graph Average Degree: " << double (edges*2.0000000)/total_nodes <<"\n";
    min_degree_node = computeMinimumDegree(nodes_degrees);
    cout << "Minimum Degree: " << min_degree_node[0].second << " associated to node: [" << min_degree_node[0].first << "]\n";
    max_degree_node = computeMaximumDegree(nodes_degrees);
    cout << "Maximum Degree: " << max_degree_node[0].second << " associated to node: [" << max_degree_node[0].first << "]\n";

    cout << "Number of Nodes with zero degree: "<< computeNodesWithZeroDegree(nodes) <<"\n";

    return  0;
}
