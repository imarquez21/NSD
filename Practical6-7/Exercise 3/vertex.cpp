#include "vertex.h"

Vertex::Vertex(int number) : D(0), number(number) {
    setAdjacency(number);
    change = benefitPair(-GRAPH_SIZE, changePair(-GRAPH_SIZE, -GRAPH_SIZE));
}

void Vertex::setChange(benefitPair change) {
    this->change = change;
}

benefitPair Vertex::getChange() {
    return this->change;
}

void Vertex::setNumber(int number) {
    this->number = number;
}
int Vertex::getNumber() {
    return number;
}
void Vertex::setD(int D) {
    this->D = D;
}
int Vertex::getD() {
    return this->D;
}
void Vertex::setAdjacency(int vertex_num) {
    if (!(adjacency_list[vertex_num]))
        adjacency_list.set(vertex_num);
}
bool Vertex::isAdjacent(int vertex_num) {
    return adjacency_list[vertex_num];
}
bool Vertex::isAlone() {
    for (int i = 0; i < GRAPH_SIZE; i++) {
        if (i != number) {
            if (adjacency_list[i])
                return false;
        }
    }
    return true;
}