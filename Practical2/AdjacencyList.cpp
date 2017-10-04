#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "adjacencylist.h"

/* - - - - - - - - - - - - - - - - - VARIABLES - - - - - - - - - - - - - - - - - - - - */

//Graph graph;

/* - - - - - - - - - - - - - - - - - FUNCTIONS - - - - - - - - - - - - - - - - - - - - */

/**
 * Initialize the graph
 * @param number_nodes
 * @param number_edges
 */
Graph* graph_init(long number_nodes, long number_edges, long offset){
    Graph* graph = new Graph();
    //Initialize arrays and variables
    graph->graph = new long[number_nodes];
    graph->graph_degree = new long[number_nodes];
    graph->neighbours = new long[number_edges];

    //Set default values for arrays
    memset(graph->graph, -1, sizeof(long)*number_nodes);
    memset(graph->neighbours, -1, sizeof(long)*number_edges);
    memset(graph->graph_degree, 0, sizeof(long)*number_nodes);

    //Set important data for interact with arrays
    graph->number_edges = number_edges;
    graph->number_nodes = number_nodes;
    graph->offset = offset;

    return graph;
}

/**
 * Free the memory used by the graph
 */
void graph_deinit(Graph* graph){
    //Free the memory used for arrays
    delete [] graph->graph;
    delete [] graph->graph_degree;
    delete [] graph->neighbours;

    delete graph;
}

/**
 * Configure the graph and load data from file
 * @param name file name
 * @return
 */
Graph* graph_load_file(char* name){
    fstream input;
    Graph* graph;
    long number_nodes=0;
    long number_edges=0;
    long offset = 0;

    input.open(name);

    //If the file can't be opened, return FALSE
    if(!input)
        return NULL;

    //Compute size of the graph and get the offset between the index for arrays and the ID of nodes
    graph_compute_size(input, number_nodes, number_edges, offset);

    //Initialize graph with the obtained size of the graph
    graph = graph_init(number_nodes, number_edges, offset);

    //Compute degree of each node
    graph_compute_degree_array(graph, input);

    //Set indexes of each node
    graph_set_nodes(graph);

    //Load data onto the data structure
    graph_load_data(graph, input);

    input.close();

    return graph;
}

/**
 * Add edge to the graph (in one directions A-->B, not B-->A)
 * @param node
 * @param neighbour
 * @return
 */
int graph_add_edge(Graph* graph, long node, long neighbour){
    //If arrays are not initialized or node is the same as the given neighbour, then stop the function
    if(graph->graph == NULL || graph->neighbours == NULL || node == neighbour)
        return FALSE;

    //Get correct index of the node
    long index = node;

    //Get first index of node's neighbours
    long first_neighbour = graph->graph[index];

    //Search the correct position of the given neighbour
    for(int i=first_neighbour;i<graph->graph_degree[index]+first_neighbour;i++){
        //If edge already exists, return FALSE (not added)
        if(graph->neighbours[i] == neighbour){
            graph->graph_degree[node] -= 1; //Duplicate, then I reduce the degree
            return FALSE;
        }


        //If empty spot, then assign the neighbour and stop the function
        if(graph->neighbours[i] < 0) {
            graph->neighbours[i] = neighbour;
            return TRUE;
        }

        //Keep array ordered, therefore swap the given neighbour with the least bigger neighbour node (?)
        //After that, arrays elements must be fixed to their new places
        if(graph->neighbours[i] > neighbour){
            swap(graph->neighbours[i], neighbour);
        }
    }
    //Element not inserted into the array, is space finished?
    return FALSE;
}

/**
 * Compute the array with the degree of each node
 * @param file
 * @return
 */
int graph_compute_degree_array(Graph* graph, fstream &file){
    //If array for the graph degree is not initialized, return FALSE
    if(graph->graph_degree == NULL)
        return FALSE;

    file_reset(file);

    long nodeA;
    long nodeB;

    while(file>>nodeA>>nodeB){
        nodeA -= graph->offset;
        nodeB -= graph->offset;

        //If nodeA is different from nodeB, then increase the degree of both nodes
        if(nodeA != nodeB) {
            graph->graph_degree[nodeA]++;
            graph->graph_degree[nodeB]++;
        }
    }

    return TRUE;
}

/**
 * Compute the size of the graph by looking the ID of nodes and the number of rows (without considering self loops)
 * It may count more edges, in this case some space will be allocated but not used
 * @param file
 * @return
 */
int graph_compute_size(fstream &file, long &number_nodes, long &number_edges, long &offset){
    if(!file)
        return FALSE;

    file_reset(file);

    long nodeA;
    long nodeB;

    long min_id = LONG_MAX;
    long max_id = 0;

    // Count how many couples there are in the file
    while(file>>nodeA>>nodeB){

        if(nodeA!=nodeB)
            number_edges+=2;

        nodeA < min_id ? min_id = nodeA : NULL;
        nodeB < min_id ? min_id = nodeB : NULL;

        nodeA > max_id ? max_id = nodeA : NULL;
        nodeB > max_id ? max_id = nodeB : NULL;
    }

    number_nodes = max_id - min_id + 1;
    number_edges = number_edges;
    offset = min_id;

    return TRUE;
}

/**
 * Print the edges of the graph without duplicates or self loops
 */
void graph_print(Graph* graph){
    for(int i=0;i<graph->number_nodes;i++){
        long node = i;
        long first_neighbour = graph->graph[i];

        for(int j=first_neighbour;j<graph->graph_degree[i]+first_neighbour;j++){
            if(node < graph->neighbours[j])
                cout << (node+graph->offset) << " " << (graph->neighbours[j]+graph->offset) << endl;
        }
    }
}

/* - - - - - - - - - - - - - - - - - AUXILIARY FUNCTIONS - - - - - - - - - - - - - - - - - - - - */

/**
 * Configure the indexes of each node in order to get the first neighbour on the contiguous array
 * @return
 */
int graph_set_nodes(Graph* graph){
    if(graph->graph == NULL || graph->neighbours == NULL || graph->graph_degree == NULL || graph->number_nodes<=0)
        return FALSE;

    graph->graph[0] = 0;

    for(int i=1;i<graph->number_nodes;i++){
        graph->graph[i] = graph->graph[i-1] + graph->graph_degree[i-1];
    }

    return TRUE;
}

void swap(long &a, long &b){
    long tmp = a;
    a = b;
    b = tmp;
}

/**
 * Bring the file pointer to the beginning
 * @param file
 */
void file_reset(fstream &file){
    file.clear();
    file.seekg(0, file.beg);
}

/**
 * Load the whole file into the structure
 * @param file
 * @return
 */
int graph_load_data(Graph* graph, fstream &file){
    file_reset(file);

    long nodeA;
    long nodeB;

    while(file>>nodeA>>nodeB){
        nodeA -= graph->offset;
        nodeB -= graph->offset;

        //Not direct graph --> I have to add the edge to both nodes
        graph_add_edge(graph, nodeA, nodeB);
        graph_add_edge(graph, nodeB, nodeA);
    }

    return TRUE;
}
