//First Exercise
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readMatrixFile(string filename){

    int iteration=0;
    int nodeA;
    int nodeB;

    ifstream matrix_file(filename);

    if(matrix_file.is_open()) {

        while (matrix_file){

            matrix_file>>nodeA;
            matrix_file>>nodeB;
            /*
            cout << "Iteration :"<< iteration   << "\n";
            cout << "Number of Node A:"<< nodeA << "\n";
            cout << "Number of Node B:"<< nodeB << "\n\n";
            ++iteration;
            */
        }
    }
    else
    {
        cout << "File could not be opened" << '\n';
    }
}

int main() {

    string filename="matrix.txt";
    readMatrixFile(filename);

    return  0;
}

