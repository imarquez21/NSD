#include <iostream>
#include <fstream>
#include <string>
#include<list>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iterator>
#include <math.h>
#include "Graph_Class.h"

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

void computeInDegree(int *indegree, int edges, string filename){

    int nodeA;
    int nodeB;

    ifstream matrix_file(filename);

    if(matrix_file.is_open()) {
        for(int i =0;i<edges;i++){
            matrix_file>>nodeA;
            matrix_file>>nodeB;
            indegree[nodeB]++;
        }
    }
    else
    {
        cout << "File could not be opened" << '\n';
    }
}

void computeOutDegree(int *outdegree, int edges, string filename){

    int nodeA;

    ifstream matrix_file(filename);

    if(matrix_file.is_open()) {
        for(int i =0 ; i<edges;i++){
            matrix_file>>nodeA;
            outdegree[nodeA]++;
        }
    }
    else
    {
        cout << "File could not be opened" << '\n';
    }
}

void computeB(double *b, double *p, int *outdegree, int edges, string filename){

    ifstream matrix_file(filename);
    int nodeA=0;
    int nodeB=0;

    if(matrix_file.is_open()) {
        for(int i=0 ; i<100;i++){
            matrix_file>>nodeA;
            matrix_file>>nodeB;
            b[nodeB]+=double(p[nodeA])/double(outdegree[nodeA]);
        }
    }
    else
    {
        cout << "File could not be opened" << '\n';
    }
}

void normalization(double *a, int nodes){

    double norm=0;

    for (int i=0;i<nodes+1;i++){

        norm+=a[i]*a[i];
    }

    norm=1.0/sqrt(norm);

    for (int k=0;k<nodes+1;k++){
        a[k]=norm*a[k];
    }

}

void computeP(double *p, int *outdegree, int nodes,int edges, double alpha, int iterations, string filename){

    double* b=new double[nodes+1];
    //double* a=new double[nodes+1]; 1/n --> it is the same for every node, we are using
    double first_section = 1.0-alpha;
    double third_section = double(alpha)*double(1.0/nodes);

    for(int i=0; i<nodes+1;i++){
        b[i]=0.0;
        outdegree[i]=0;
        //a[i]=1.0/nodes;
        p[i]=1.0/nodes;
    }

    computeOutDegree(outdegree,edges,filename);
    //cout << "Completed Computing the out degree.\n";
        for (int i=0;i<iterations;i++){
           // cout << "Completed Computing the out degree number "<< i <<".\n";
            computeB(b,p,outdegree,edges,filename);
            for (int j=0;j<nodes+1;j++){
                p[j]=first_section*b[j]+third_section;
            }
            normalization(p,nodes);
        }

    /*
    cout << "Outdegree["<<1<<"]: " << fixed <<outdegree[1] << "\n";
    cout << "Outdegree["<<15<<"]: " << fixed <<outdegree[15] << "\n";
    cout << "Outdegree["<<625<<"]: " << fixed <<outdegree[625] << "\n";
    cout << "Outdegree["<<705<<"]: " << fixed <<outdegree[705] << "\n";
    cout << "P["<<12<<"]: " << fixed <<p[12] << "\n";
    cout << "P["<<25<<"]: " << fixed <<p[25] << "\n";
    cout << "P["<<39<<"]: " << fixed <<p[39] << "\n";
    cout << "P["<<309<<"]: " << fixed <<p[309] << "\n";
    */
}

string getSiteName(int site_index,int edges){

    ifstream file("pagename.txt");

    int current_site_index=0;
    string line="";
    string current_site_name="";
    string final_site_name="placeholder";

    if(file.is_open()) {
        while (getline(file,line)){
            file>>current_site_index;
            if (current_site_index == site_index){
                getline(file,line);
                final_site_name=line;
                return final_site_name;
            }
        }
    }
    else
    {
        cout << "File could not be opened" << '\n';
    }

    file.close();

    return final_site_name;
}

void getHighestandLowest(double *p, int* outdegree, int nodes, int edges){

    double highest=0.0;
    int highest_index=0;
    double lowest=1.0;
    int lowest_index=0;

    for (int i=0;i<nodes+1;i++){
        if (p[i]>highest){
            highest=p[i];
            highest_index=i;
        }
        if (p[i]<lowest&&outdegree[i]!=0){
            lowest=p[i];
            lowest_index=i;
        }
    }


    string highest_site=getSiteName(highest_index,edges);
    cout << "Highest: " << highest_site <<" with index "<< highest_index <<" and PR of "<< highest <<".\n";
    string lowest_site=getSiteName(lowest_index,edges);
    cout << "Lowest: " << lowest_site <<" with index "<< lowest_index <<" and PR of "<< lowest <<".\n";
}

void printToFile(int *indegree, double *p, int nodes){

    ofstream outputFile;
    outputFile.open("PageRank_0_9.txt");


    if(outputFile.is_open()) {

        //cout << "====== Printing content to be stored in the file. ===========\n";

        for (int i=0; i <nodes+1;i++)
        {
            //if (indegree[i]!=0){
                outputFile << p[i] << "\n";
            //}
        }

        outputFile << "\n";

    }
    else
    {
        cout << "File could not be opened" << '\n';
    }

    outputFile.close();

}


int main() {

    //Variables Initialization
    string filename="wiki.txt"; //Big File
    double alpha=0.9;
    int iterations=20;

    /*
    //string filename="01_Pretty_Good_Privacy.txt";
    //string filename="googleplus.txt";
    //string filename="03_Actor_collaborations.txt";
    */
    int edges =0;
    int nodes =0;

    //Defining the number of decimals
    cout.precision(19);

    edges = getNumberofEdges(filename);
    cout << "\nNumber of Edges: "<< edges << "\n";
    nodes = getNodes(filename);
    cout << "Number of Nodes: "<< nodes << "\n";

    int *outdegree=new int[nodes+1];
    int *indegree=new int[nodes+1];
    double *p=new double[nodes+1];

    computeP(p,outdegree,nodes,edges,alpha,iterations,filename);
    getHighestandLowest(p,outdegree,nodes,edges);

    //printing to file
    //printToFile(outdegree,p,nodes);

    /*

 //Section to Define the array holding the out-degree of each node.
//Initialize the array in zero for all nodes.
int *outdegree= new int[nodes+1];
for(int i =0 ; i<nodes+1;i++){
    outdegree[i]=0;
}

cout << "Completed initializing outdegree.\n";

computeOutDegree(outdegree,edges,filename);
cout << "Completed computing outdegree.\n";

//We create array a to implement.
//Initialize the array with same probability for all nodes.
double *a=new double[nodes+1];
for(int i=0;i<nodes+1;i++){
    a[i]=double(1.0000000/double(nodes));
}
cout << "Completed initializing A.\n";

//We create array B and initialize it all in zero
double* b=new double[nodes+1];
for(int i=0;i<nodes+1;i++){
    b[i]=double(0.00000000);
}
cout << "Completed initializing B.\n";

cout << "About ot begin to compute B.\n";
//We compute B.
computeB(b,a,outdegree,edges,filename);


cout << "Completed initializing B.\n";


cout << "Value for Outdegree.\n";
cout << "Outdegree["<<1<<"]: " << fixed <<outdegree[1] << "\n";
cout << "Outdegree["<<15<<"]: " << fixed <<outdegree[15] << "\n";
cout << "Outdegree["<<625<<"]: " << fixed <<outdegree[625] << "\n";
cout << "Outdegree["<<705<<"]: " << fixed <<outdegree[705] << "\n";

cout << "Value for A.\n";
cout << "A["<<1<<"]: " << fixed <<a[1] << "\n";
cout << "A["<<15<<"]: " << fixed <<a[15] << "\n";
cout << "A["<<625<<"]: " << fixed <<a[625] << "\n";
cout << "A["<<705<<"]: " << fixed <<a[705] << "\n";


double *p=new double[nodes+1];
for(int i=0;i<nodes+1;i++){
    p[i]=double(0.00000000);
}
 */
    /*

     cout << "P["<<1<<"]: " << fixed <<p[1] << "\n";
    cout << "P["<<15<<"]: " << fixed <<p[15] << "\n";
    cout << "P["<<625<<"]: " << fixed <<p[625] << "\n";
    cout << "P["<<705<<"]: " << fixed <<p[705] << "\n";

    cout << "Value for B.\n";
    cout << "B["<<1<<"]: " << fixed <<b[1] << "\n";
    cout << "B["<<15<<"]: " << fixed <<b[15] << "\n";
    cout << "B["<<625<<"]: " << fixed <<b[625] << "\n";
    cout << "B["<<705<<"]: " << fixed <<b[705] << "\n";
    */
    return  0;
}

