#include <iostream>
#include "KernighanLin.h"
#include <ctime>
#include <time.h>
#include "mpi.h"
using namespace std;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);
    int rank = 0;
    int size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;


    clock_t time = clock();
    KernighanLin kernighanLin;
    kernighanLin.generateRandomA();
    kernighanLin.generateRandomB();
    kernighanLin.calculateD();

    int* bestchangeA = new int(size);
    int* bestchangeB = new int(size);
    int* bestchangeVal = new int(size);


    vector<Vertex> subsetA(kernighanLin.subsetA);
    vector<Vertex> subsetB(kernighanLin.subsetB);
    benefitPair change;
    Iterator rmA;
    Iterator rmB;

    time = clock();

    time = clock();
    kernighanLin.changeBestPair(kernighanLin.subsetA, kernighanLin.subsetB);
    time = clock() - time;
    if (rank == 0) {
        cout << "Finding pairs to change via sequential method: " << float(time) / CLOCKS_PER_SEC << endl;
    }
    time = clock();

    int counter = 0;

    while (subsetA.size() > 0) {

        change = kernighanLin.changeBestPairParallelMPI_TBB(subsetA, subsetB, size, rank);

        MPI_Gather(&(change.second.first), 1, MPI_INT, bestchangeA, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Gather(&(change.second.second), 1, MPI_INT, bestchangeB, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Gather(&(change.first), 1, MPI_INT, bestchangeVal, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            for (int i = 0; i < size; i++) {
                if (bestchangeVal[i] > change.first) {
                    change.first = bestchangeVal[i];
                    change.second.first = bestchangeA[i];
                    change.second.second = bestchangeB[i];
                }
            }
            int additional = subsetA.size() % size;
            if (additional != 0) {
                vector<Vertex> additional_subsetA(subsetA.end() - additional, subsetA.end());
                benefitPair additional_change = kernighanLin.changeBestPairParallelMPI_TBB(additional_subsetA, subsetB, 1, rank);
                if (additional_change.first > change.first) {
                    change.first = additional_change.first;
                    change.second.first = additional_change.second.first;
                    change.second.second = additional_change.second.second;
                }
            }
            /*cout << counter << " step change pair first " << change.second.first << endl;
            cout << counter << " step change pair second " << change.second.second << endl;*/
        }


        MPI_Bcast(&change.second.first, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&change.second.second, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&change.first, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for (Iterator i = subsetA.begin(); i < subsetA.end(); i++) {
            if (i->getNumber() == change.second.first) {
                rmA = i;
                break;
            }
        }

        for (Iterator i = subsetB.begin(); i < subsetB.end(); i++) {
            if (i->getNumber() == change.second.second) {
                rmB = i;
                break;
            }
        }

        /*cout << rank << " I would remove from A " << rmA->getNumber() << " on step " << counter << endl;
        cout << rank << " I would remove from B " << rmB->getNumber() << " on step " << counter << endl;
*/
        int price = rmA->getD() + rmB->getD();
        if (rmA->isAdjacent(rmB->getNumber())) {
            price -= 2;
        }
        kernighanLin.benefitParallelMPI_TBB.push_back(make_pair(price, make_pair(rmA->getNumber(), rmB->getNumber())));
  
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
        counter++;
    }

    if (rank == 0) {
        time = clock() - time;
        cout << "Finding pairs to change via mpi_tbb: " << float(time) / CLOCKS_PER_SEC << endl;
        cout << "COMPARE PROCESS seq VS mpi_tbb RESULT: " << kernighanLin.compareResultsMPI_TBB() << "." << endl;
    }



    MPI_Finalize();

    return 0;
}