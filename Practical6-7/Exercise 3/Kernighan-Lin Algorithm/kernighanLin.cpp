#include "kernighanLin.h"

KernighanLin::KernighanLin() {
    mainGraph.generateRandomGraph();
    currentGrapgh = mainGraph;
}

void KernighanLin::generateRandomA() {
    subsetA.reserve(currentGrapgh.getSize() / 2);
    for (int i = 0; i < currentGrapgh.getSize(); i += 2) {
        subsetA.push_back(currentGrapgh[i]);
    }
}

void KernighanLin::generateRandomB() {
    subsetB.reserve(currentGrapgh.getSize() / 2);
    for (int i = 1; i < currentGrapgh.getSize(); i += 2) {
        subsetB.push_back(currentGrapgh[i]);
    }
}

void KernighanLin::calculateDA() {
    for (int i = 0; i < subsetA.size(); i++) {
        int I = 0;
        int E = 0;
        for (int j = 0; j < subsetA.size(); j++) {
            if (j != i) {
                I += subsetA[i].isAdjacent(subsetA[j].getNumber());
            }
        }
        for (int j = 0; j < subsetB.size(); j++) {
            E += subsetA[i].isAdjacent(subsetB[j].getNumber());
        }
        subsetA[i].setD(E - I);
    }
}

void KernighanLin::calculateDB() {
    for (int i = 0; i < subsetB.size(); i++) {
        int I = 0;
        int E = 0;
        for (int j = 0; j < subsetB.size(); j++) {
            if (j != i) {
                I += subsetB[i].isAdjacent(subsetB[j].getNumber());
            }
        }
        for (int j = 0; j < subsetB.size(); j++) {
            E += subsetB[i].isAdjacent(subsetA[j].getNumber());
        }
        subsetB[i].setD(E - I);
    }
}

void KernighanLin::calculateD() {
    // D = Amount of external links - amount of internal links
    calculateDA();
    calculateDB();
}

int KernighanLin::calculateT() {
    int tmpT = 0;
    for (int i = 0; i < subsetA.size(); i++) {
        for (int j = 0; j < subsetB.size(); j++) {
            tmpT += subsetA[i].isAdjacent(subsetB[j].getNumber());
        }
    }
    return tmpT;
}

int KernighanLin::changeBestPair(vector<Vertex> subsetA, vector<Vertex> subsetB) {
    int bestPrice = -GRAPH_SIZE;
    int bestA = 0;
    int bestB = 0;
    Iterator rmA, rmB;

    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        int localBestPrice = -GRAPH_SIZE;
        for (Iterator j = subsetB.begin(); j < subsetB.end(); j++) {
            int price = i->getD() + j->getD();
            if (i->isAdjacent(j->getNumber())) {
                price -= 2;
            }
            if (price > localBestPrice) {
                localBestPrice = price;
                benefitPair tmp(benefitPair(localBestPrice, changePair(i->getNumber(), j->getNumber())));
                i->setChange(tmp);
            }
        }
    }
    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        if (i->getChange().first > bestPrice) {
            bestPrice = i->getChange().first;
            bestA = i->getChange().second.first;
            bestB = i->getChange().second.second;
        }
    }

    benefitPair bp = make_pair(bestPrice, make_pair(bestA, bestB));
    benefitSequential.push_back(bp);

    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        if (i->getNumber() == bp.second.first) {
            rmA = i;
            break;
        }
    }

    for (Iterator i = subsetB.begin(); i < subsetB.end(); i++) {
        if (i->getNumber() == bp.second.second) {
            rmB = i;
            break;
        }
    }

    subsetA.erase(rmA);
    subsetB.erase(rmB);

    for (int i = 0; i < subsetA.size(); i++) {
        int I = 0;
        int E = 0;
        for (int j = 0; j < subsetA.size(); j++) {
            if (j != i) {
                I += subsetA[i].isAdjacent(subsetA[j].getNumber());
            }
        }
        for (int j = 0; j < subsetB.size(); j++) {
            E += subsetA[i].isAdjacent(subsetB[j].getNumber());
        }
        subsetA[i].setD(E - I);
    }
    for (int i = 0; i < subsetB.size(); i++) {
        int I = 0;
        int E = 0;
        for (int j = 0; j < subsetB.size(); j++) {
            if (j != i) {
                I += subsetB[i].isAdjacent(subsetB[j].getNumber());
            }
        }
        for (int j = 0; j < subsetB.size(); j++) {
            E += subsetB[i].isAdjacent(subsetA[j].getNumber());
        }
        subsetB[i].setD(E - I);
    }

    if (subsetA.size() != 0) {
        changeBestPair(subsetA, subsetB);
    }

    return 0;
}

void KernighanLin::changeBestPairParallelOpenMP(vector<Vertex> subsetA, vector<Vertex> subsetB) {
    int bestPrice = -GRAPH_SIZE;
    int bestA = 0;
    int bestB = 0;
    Iterator rmA, rmB;

#pragma omp parallel for
    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        int localBestPrice = -GRAPH_SIZE;
        for (Iterator j = subsetB.begin(); j < subsetB.end(); j++) {
            int price = i->getD() + j->getD();
            if (i->isAdjacent(j->getNumber())) {
                price -= 2;
            }
            if (price > localBestPrice) {
                localBestPrice = price;
                benefitPair tmp(benefitPair(localBestPrice, changePair(i->getNumber(), j->getNumber())));
                i->setChange(tmp);
            }
        }
    }
    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        if (i->getChange().first > bestPrice) {
            bestPrice = i->getChange().first;
            rmA = i;
            bestA = i->getChange().second.first;
            bestB = i->getChange().second.second;
        }
    }
    for (Iterator i = subsetB.begin(); i < subsetB.end(); i++) {
        if (i->getNumber() == bestB) {
            rmB = i;
            break;
        }
    }
    subsetA.erase(rmA);
    subsetB.erase(rmB);
    calculateD();
    changePair cp(bestA, bestB);
    benefitPair bp(bestPrice, cp);
    benefitParallelOpenMP.push_back(bp);
    if (subsetA.size() != 0) {
        changeBestPairParallelOpenMP(subsetA, subsetB);
    }
}

bool KernighanLin::compareResultsOpenMP() {
    bool flag = true;
    if (benefitSequential.size() == benefitParallelOpenMP.size()) {
        for (int i = 0; i < benefitSequential.size(); i++) {
            if (flag != false) {
                flag = (benefitSequential[i] == benefitParallelOpenMP[i]);
            }
        }
    }
    else {
        flag = false;
    }
    return flag;
}

int KernighanLin::changeBestPairParallelTBB(vector<Vertex> subsetA, vector<Vertex> subsetB) {
    int bestPrice = -GRAPH_SIZE;
    int bestA = 0;
    int bestB = 0;
    Iterator rmA, rmB;

    parallel_for(size_t(0), subsetA.size(), size_t(1), [&](size_t i) {
        int localBestPrice = -GRAPH_SIZE;
        for (Iterator j = subsetB.begin(); j < subsetB.end(); j++) {
            int price = subsetA[i].getD() + j->getD();
            if (subsetA[i].isAdjacent(j->getNumber())) {
                price -= 2;
            }
            if (price > localBestPrice) {
                localBestPrice = price;
                benefitPair tmp(benefitPair(localBestPrice, changePair(subsetA[i].getNumber(), j->getNumber())));
                subsetA[i].setChange(tmp);
            }
        }
    });

    for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
        if (i->getChange().first > bestPrice) {
            bestPrice = i->getChange().first;
            rmA = i;
            bestA = i->getChange().second.first;
            bestB = i->getChange().second.second;
        }
    }

    for (Iterator i = subsetB.begin(); i < subsetB.end(); i++) {
        if (i->getNumber() == bestB) {
            rmB = i;
            break;
        }
    }

    subsetA.erase(rmA);
    subsetB.erase(rmB);
    calculateD();
    changePair cp(bestA, bestB);
    benefitPair bp(bestPrice, cp);
    benefitParallelTBB.push_back(bp);

    if (subsetA.size() != 0) {
        changeBestPairParallelTBB(subsetA, subsetB);
    }

    int tmpT = 0;
    for (int i = 0; i < subsetA.size(); i++) {
        for (int j = 0; j < subsetB.size(); j++) {
            tmpT += subsetA[i].isAdjacent(subsetB[j].getNumber());
        }
    }
    return tmpT;
}


benefitPair KernighanLin::changeBestPairParallelMPI_TBB(vector<Vertex> subsetA, vector<Vertex> subsetB, int size, int rank) {
    int bestPrice = -GRAPH_SIZE;
    int bestA = 0;
    int bestB = 0;

    parallel_for(size_t(rank * (subsetA.size() / size)), size_t(rank * (subsetA.size() / size) + subsetA.size() / size), size_t(1), [&](size_t i) {
        int localBestPrice = -GRAPH_SIZE;
        for (Iterator j = subsetB.begin(); j < subsetB.end(); j++) {
            int price = subsetA[i].getD() + j->getD();
            if (subsetA[i].isAdjacent(j->getNumber())) {
                price -= 2;
            }
            if (price > localBestPrice) {
                localBestPrice = price;
                benefitPair tmp(benefitPair(localBestPrice, changePair(subsetA[i].getNumber(), j->getNumber())));
                subsetA[i].setChange(tmp);
            }
        }
    });

    for (Iterator i = subsetA.begin() + size_t(rank * (subsetA.size() / size)); i < subsetA.begin() + size_t(rank * (subsetA.size() / size) + subsetA.size() / size); i++) {
        if (i->getChange().first > bestPrice) {
            bestPrice = i->getChange().first;
            bestA = i->getChange().second.first;
            bestB = i->getChange().second.second;
        }
    }
    return make_pair(bestPrice, make_pair(bestA, bestB));
}


bool KernighanLin::compareResultsTBB() {
    bool flag = true;
    if (benefitSequential.size() == benefitParallelTBB.size()) {
        for (int i = 0; i < benefitSequential.size(); i++) {
            if (flag != false) {
                flag = (benefitSequential[i] == benefitParallelTBB[i]);
            }
            else {
                cout << "MISTAKE ON " << i - 1 << " ELEMENT" << endl;
                break;
            }
        }
    }
    else {
        flag = false;
    }
    return flag;
}

bool KernighanLin::compareResultsMPI_TBB() {
    bool flag = true;
    if (benefitSequential.size() == benefitParallelMPI_TBB.size()) {
        for (int i = 0; i < benefitSequential.size(); i++) {
            if (flag != false) {
                flag = (benefitSequential[i] == benefitParallelMPI_TBB[i]);
            }
            else {
                cout << "MISTAKE ON " << i << " ELEMENT" << endl;
                break;
            }
        }
    }
    else {
        flag = false;
    }
    return flag;
}
