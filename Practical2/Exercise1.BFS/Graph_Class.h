using namespace std;

class Graph
{
    int nodes;
    list<int> *adj;
    list<int> *BFS_path;
    
    public:
    Graph(int nodes)
    {
		this->nodes = nodes; // We set the number of nodes in the graph
		adj = new list<int>[nodes]; //for each node we have we have an adjacency list
	}
	
	void addEdge(int source, int dest)
	{
		adj[source].push_back(dest); // As we are neighbors to each one of the nodes to its corresponding pointer
	}
	
	int BFS(int starting_node)
	{
        //Current node will hold the index of the node we are using as the starting point for BFS
        int current_node=starting_node;

        //The FIFO stack that holds which node is to be reviewed.
        list<int> FIFO_stack;

        //For each of the nodes we need to go through their neighbors, we use a list to keep track of the neighboring nodes.
        list<int>::iterator neighbor_nodes;

        //We start from scratch, no node has been visited, this is the flag that we set a node to be visited or not.
		bool *visited = new bool[nodes];
		for(int i = 0; i < nodes; i++)
		{
			visited[i] = false;
		}

        // We begin with the node that has been defined as the starting node, as it is the first we set the "visited" flag to true
        visited[starting_node] = true;
        FIFO_stack.push_back(starting_node);

        int size_counter=0;
            while(!FIFO_stack.empty())
            {
                //Take out the node that has been visited from the FIFO_Stack and print
                starting_node = FIFO_stack.front();
                cout << starting_node << " ";
                //cout << "The value stored in BFS Path for node: "<< current_node  << " is: " << starting_node << ".\n";
                FIFO_stack.pop_front();

                //We go through the neighbors of teh node we are currently on, if the node has not been visited we set the flag to visited as
                //we have now visited, finally we removed from the FIFO_stack as it has been already visited.
                for(neighbor_nodes = adj[starting_node].begin();  neighbor_nodes != adj[starting_node].end(); neighbor_nodes++)
                {
                    if(!visited[*neighbor_nodes])
                    {
                        visited[*neighbor_nodes] = true;
                        FIFO_stack.push_back(*neighbor_nodes);
                    }
                }
                size_counter++;
            }//Closing While
        return size_counter;
        cout << "\n";
    }


};
 
 
 

