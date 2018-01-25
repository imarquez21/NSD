#pragma once
#include "graph.h"
#include <ctime>
#include <time.h>
#include <iostream>
#include <tbb\parallel_for.h>
#include <tbb\concurrent_vector.h>
typedef vector<Vertex>::iterator Iterator;
typedef pair<int, int> changePair;
typedef pair<int, changePair> benefitPair;
using namespace std;
using namespace tbb;

class KernighanLin
{
	Graph mainGraph, currentGrapgh;
public:
	int TOld, TNew;
	vector<benefitPair> benefitSequential;
	vector<benefitPair> benefitParallelOpenMP;
    vector<benefitPair> benefitParallelTBB;
    vector<benefitPair> benefitParallelMPI_TBB;
	vector<Vertex> subsetA, subsetB;

    KernighanLin();

    void generateRandomA();

    void generateRandomB();

    void calculateDA();

    void calculateDB();

    void calculateD();

    int calculateT();

    int changeBestPair(vector<Vertex> subsetA, vector<Vertex> subsetB);

    void changeBestPairParallelOpenMP(vector<Vertex> subsetA, vector<Vertex> subsetB);

    int changeBestPairParallelTBB(vector<Vertex> subsetA, vector<Vertex> subsetB);

    benefitPair changeBestPairParallelMPI_TBB(vector<Vertex> subsetA, vector<Vertex> subsetB, int size, int rank);

    bool compareResultsOpenMP();

    bool compareResultsTBB();

    bool compareResultsMPI_TBB();

	~KernighanLin() {};
};

