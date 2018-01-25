#pragma once
#include <bitset>
#include <omp.h>
#define GRAPH_SIZE 1500
using namespace std;

typedef pair<int, int> changePair;
typedef pair<int, changePair> benefitPair;

class Vertex
{
	bitset<GRAPH_SIZE> adjacency_list;
	int D; //D - is a parameter needed for algorithm - difference in amount of external and internal adjencies
	int number;
	benefitPair change;
public:
    Vertex(int number);

	~Vertex() {};

    void setChange(benefitPair change);

    benefitPair getChange();

    void setNumber(int number);

    int getNumber();

    void setD(int D);

    int getD();

    void setAdjacency(int vertex_num);

    bool isAdjacent(int vertex_num);

    bool isAlone();
};

