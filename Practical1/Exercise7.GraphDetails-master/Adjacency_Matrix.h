#include <iostream>
#include <cstdlib>

using namespace std;

class AdjacencyMatrix
{
    private:
        int n;
        int **adj;
        bool *visited;
        vector <pair<int,int>> nodes_degrees;

    public:
        AdjacencyMatrix(int n)
        {
            this->n = n;
            visited = new bool [n];
            adj = new int* [n];
            for (int i = 0; i < n; i++)
            {
                adj[i] = new int [n];
                for(int j = 0; j < n; j++)
                {
                    adj[i][j] = 0;
                }
            }
        }
        /*
         * Adding Edge to Graph
         */ 
        void add_edge(int origin, int destin)
        {
            if( origin > n || destin > n || origin < 0 || destin < 0)
            {   
                cout<<"Invalid edge!\n";
            }
            else
            {
                adj[origin][destin] = 1;
            }
        }
        /*
         * Print the graph
         */ 
        void display()
        {
            int i,j;
            cout << "Printing graph as an Adjacency Matrix.\n";
            for(i = 0;i < n;i++)
            {
                for(j = 0; j < n; j++)
                    cout<<adj[i][j]<<"  ";
                cout<<endl;
            }
        }


        vector <pair<int,int>> nodesDegree()
        {
            int i,j;
            int node_pos=0;
            int node_degree=0;

            for(i = 0;i < n;i++)
            {

                for(j = 0; j < n; j++)
                {
                   // cout<<adj[i][j]<<"  ";

                    if (adj[i][j]==1)
                    {
                        node_degree++;
                    }
                    else
                    {
                       // nodes_degrees[node_pos].second=node_degree;
                    }
                  // cout << "\nNode Degree within inner for: "<<node_degree << "\n";
                }
                //cout << "\nNode Position within outer for: "<< i << "\n";

                nodes_degrees.push_back(std::make_pair(i,node_degree));
                node_degree=0;
                //[node_pos].first=i;
                //nodes_degrees[i].second=node_degree;
            }


            /*
            cout << "Nodes Degree. \n";
            for (int i =0;i<n;i++){
                cout << "Node [" << nodes_degrees[i].first <<"] Degree: " << nodes_degrees[i].second << "\n";
            }
             */
            return nodes_degrees;
        }

};



 
/*
 * Adjacency List Node
 */ 
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
/*
 * Adjacency List
 */  
struct AdjList
{
    struct AdjListNode *head;
};
 
/*
 * Class Graph
 */ 
class Graph
{
    private:
        int V;
        struct AdjList* array;
    public:
        Graph(int V)
        {
            this->V = V;
            array = new AdjList [V];
            for (int i = 0; i < V; ++i)
                array[i].head = NULL;
        }
        /*
         * Creating New Adjacency List Node
         */ 
        AdjListNode* newAdjListNode(int dest)
        {
            AdjListNode* newNode = new AdjListNode;
            newNode->dest = dest;
            newNode->next = NULL;
            return newNode;
        }
        /*
         * Adding Edge to Graph
         */ 
        void addEdge(int src, int dest)
        {
            AdjListNode* newNode = newAdjListNode(dest);
            newNode->next = array[src].head;
            array[src].head = newNode;
            newNode = newAdjListNode(src);
            newNode->next = array[dest].head;
            array[dest].head = newNode;
        }
        /*
         * Print the graph
         */ 
        void printGraph()
        {
            int v;
            cout << "Printing graph as an adjacency list.\n";
            for (v = 0; v < V; ++v)
            {
                AdjListNode* pCrawl = array[v].head;
                cout<<"\nNode["<<v<<"]: " << v ;
                while (pCrawl)
                {
                    cout<<"-> "<<pCrawl->dest;
                    pCrawl = pCrawl->next;
                }
                cout<<endl;
            }
        }
};
