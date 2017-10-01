//First Exercise
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;

void readMatrixFile(string filename, int lines){

    ifstream matrix_file(filename);
    int nodeA;
    int nodeB;

    int iteration=0;

    while(iteration<lines){
        matrix_file>>nodeA;
        matrix_file>>nodeB;
        iteration++;
        /*
        cout << "Line " << iteration << "\n";
        cout << "Node A: " << nodeA <<"\n";
        cout << "Node B: " << nodeB <<"\n";
        */
    }

}

int getLines(string filename){

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

    /*
    //Printing the Vector unsorted
    cout << "\n Printing the Vector Unsorted. \n";
    for (int i=0; i<nodes.size();i++){
        cout << "Node[" << i << "]: "<< nodes[i] <<"\n";
    }
*/

    //Sorting the Vector and removing duplicates
    std::sort(nodes.begin(),nodes.end());
    auto last_node = std::unique(nodes.begin(),nodes.end());
    nodes.erase(last_node, nodes.end());

    //Getting the number of Nodes
    return nodes.size();

    /*
    //Printing Sorted and Unique Values of the Vector
    cout << "\n Printing only the unique elements of the vector. \n";
    for (int i=0; i<nodes.size();i++){
        cout << "Node[" << i << "]: "<< nodes[i] <<"\n";
    }
    */

    /*

    for (auto i = nodes.begin();i!=nodes.end();++i){
        cout << *i <<" \n";
    }

    int iteration=0;

    while(iteration<sizeof(nodes)/sizeof(nodes[0])){
        matrix_file>>nodes[iteration];
        matrix_file>>nodes[iteration+1];


        cout << "Line " << iteration << "\n";
        cout << "Node[" << iteration << "]: " << nodes[iteration] << "\n";
        cout << "Node[" << iteration+1 << "]: " << nodes[iteration+1] << "\n\n";

        iteration+=2;
    }
      */

    /*
    cout << "Reading the Array with the Nodes Now \n\n";
    for (int i=0;i<(lines*2);i++){
        cout << "Node["<<i<<"]: " << nodes[i] << "\n";
    }
    */

}


void getNodeDegrees(string filename){

    ifstream matrix_file(filename);

    std::vector<int> nodes;
    int node;
    int total_nodes;

    int degree_counter=0;

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

    /*
    for (int i=0; i<nodes.size();i++){

        if (nodes[i]==nodes[i+1]){
            degree_counter++;
        }
        else
        {

        }
        cout << "Node[" << i << "]: "<< nodes[i] <<"\n";
    }
    */
    /*
    //Printing the Vector unsorted
    cout << "\n Printing the Vector Unsorted. \n";
    for (int i=0; i<nodes.size();i++){
        cout << "Node[" << i << "]: "<< nodes[i] <<"\n";
    }
    */

}

int main() {

    string filename="First_Sample.txt";

    int lines = getLines(filename);
    int total_nodes=0;

    /*
    //readMatrixFile(filename,lines);
    cout << "===================================================\n";
    cout << "Number of Edges: " << lines << ".\n";
    cout << "===================================================\n";
    cout << "===================================================\n";
    //total_nodes=getNodes(filename,lines);
    cout << "Number of Nodes: " << total_nodes << ".\n";
    cout << "===================================================\n";
    cout << "===================================================\n";
    */

    cout << "Nodes' Degrees \n";
    getNodeDegrees(filename);

    return  0;
}

