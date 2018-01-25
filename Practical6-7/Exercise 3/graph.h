#pragma once

#include <vector>
#include <bitset>
#include "vertex.h"
using namespace std;



class Graph
{
	int size; //vertices amount
	vector<Vertex> vertices;
public:
	Graph() : size(GRAPH_SIZE) {
		vertices.reserve(size);
		for (int i = 0; i < size; i++) {
			Vertex tmp(i);
			vertices.push_back(tmp);
		}
	};

	int getSize() {
		return size;
	}

	Graph(const Graph& graph) {
		this->size = graph.size;
		vertices.reserve(size);
		vertices = graph.vertices;
	}

	Graph& operator=(const Graph& graph) {
		this->size = graph.size;
		this->vertices.reserve(size);
		this->vertices = graph.vertices;
		return *this;
	}

	Vertex& operator[](const int number) {
		return vertices[number];
	}

	~Graph() {};

	void generateRandomGraph() {
		while (!(this->isConncective())) {
			int first_vertex = rand() % size;
			int second_vertex = rand() % size;
			vertices[first_vertex].setAdjacency(second_vertex);
			vertices[second_vertex].setAdjacency(first_vertex);
		}
	}


	bool isConncective() {
		bool flag = true;
#pragma omp parallel for
		for (int i = 0; i < size; i++) {
			if (vertices[i].isAlone()) {
				flag = false;
			}
		}
		return flag;
	}
};

