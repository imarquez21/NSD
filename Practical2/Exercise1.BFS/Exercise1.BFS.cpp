#include<iostream>
#include<list>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iterator>
#include "Graph_Class.h"

using namespace std;

int getNodes(string filename){

    ifstream matrix_file(filename);
    int current_value=0;
    int max_value=0;

    int iteration=0;

    if(matrix_file.is_open()) {

        while (matrix_file){
            matrix_file>>current_value;

            if (current_value>max_value){
                max_value=current_value;
            }
            iteration++;
        }

    }
    else
    {
        cout << "File could not be opened" << '\n';
    }

    matrix_file.close();

    return max_value;

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

vector<pair<int, int>> storeEdgesPair(string filename, int lines){
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

void populateGraph(Graph graph, vector<pair<int,int>> nodes){

    //cout << "Adding Edges to the graph.\n";
    for (int i=0; i<nodes.size();i++){
        //cout << "Iteration: " << i << ".\n";
        //cout << "Adding pair[" << i << "]: [" << nodes[i].first << ", " << nodes[i].second << "]\n";
        graph.addEdge(nodes[i].first,nodes[i].second);
    }

    //cout << "Populating the graph completed.\n";
}

void implementBFSinAllNodes(Graph graph, int number_of_nodes){

    int size_counter;
    vector<int>size_of_BFS_paths;
    int BFS_path_max_size=0;

    for (int i =0; i < number_of_nodes; i++)
    {
        cout << "BFS starting from node: " << i << ".\n";
        size_counter = graph.BFS(i);

        cout << "\n";
        cout << "Size of the BFS path " << size_counter << ".\n";
        size_of_BFS_paths.push_back(size_counter);
    }

    BFS_path_max_size = *max_element(size_of_BFS_paths.begin(),size_of_BFS_paths.end());

    cout << "\n\n";
    cout << "The Max Value is: " << BFS_path_max_size << ".\n";
    cout << "Based on approximation the diameter is: " << BFS_path_max_size*2 << ".\n";

}


int main()
{
    //"List_of_Edges_2.txt"
    //01_Pretty_Good_Privacy.txt
    //amazon.txt --> Careful, with this one the computer hangs --> Need to improve the calculation of D.
    string filename = "List_of_Edges_2.txt";
    vector<pair<int,int>> edges_pairs;

    int number_of_edges =0;
    number_of_edges = getEdges(filename);
    cout << "\n";
    cout << "The number of edges is: " << number_of_edges << ".\n";

    int number_of_nodes=0;
    number_of_nodes = getNodes(filename)+1;
    cout << "The number of nodes is: " << number_of_nodes << ".\n";

    edges_pairs = storeEdgesPair(filename,number_of_edges);
    //cout << "Storing edges pairs completed.\n";

    Graph graph(number_of_nodes);
    //cout << "Creating graph completed.\n";

    populateGraph(graph,edges_pairs);
    //cout << "Populating graph completed.\n";

    cout << "Implementing BFS in all nodes \n";
    implementBFSinAllNodes(graph,number_of_nodes);
    
    return 0;
}