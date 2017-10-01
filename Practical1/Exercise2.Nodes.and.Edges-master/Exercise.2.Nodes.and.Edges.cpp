//First Exercise
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getNumberofEdges(string filename){

    ifstream matrix_file(filename);
    int lines_count=0;
    string line="";

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

int getNodes(string filename){

    ifstream matrix_file(filename);
    int current_value=0;
    int max_value=0;

    int iteration=0;

    if(matrix_file.is_open()) {

        while (matrix_file){
            matrix_file>>current_value;
            //max_value=current_value;

            /*
            cout << "======================================================\n";
            cout << "Iteration: " << iteration << "\n";
            cout << "Current Value: " << current_value << "\n";
            cout << "Max Value: " << max_value << "\n\n";
            */

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



int main() {

    string filename="matrix.txt";
    int edges =0;
    int nodes =0;

    edges = getNumberofEdges(filename);
    cout << "Number of Edges: "<< edges << "\n";

    nodes = getNodes(filename);
    cout << "Number of Nodes: "<< nodes << "\n";

    return  0;
}

