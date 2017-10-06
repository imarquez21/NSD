
===========================================
Networks : Structure and dynamics
NSD: Practical 2
===========================================

********************************************
Authors:
- MUTIAH BINTI ABDUL HAMID
- ISRAEL MARQUEZ SALINAS
********************************************

To compile g++-7 Exercise1.BFS.cpp -o Exercise1.BFS
To run ./Exercise1.BFS


The algorithm implement BFS on a graph.

The input is a txt file with format u v, each line denotes an edge.

Based on the input file the graph is created as an adjacency list.

With the adjacency list the BFS path is calcualted, as it is calcualted the max size of BFS path is obtained.

This value is stored in a vector and from this vector the max is obtained, to define an upper limit.

NOTE: Diameter calculation is innacurate for the moment while testing with the Amazon dataset.

https://snap.stanford.edu/data/com-Amazon.html

PLEASE BE CAREFUL AS ALGORITHM NEEDS TO BE IMPROVED TO PREVENT COMPUTER FROM HANGING.

Currently working on improving it, it can be used with graphs like the one described in following link.

http://konect.uni-koblenz.de/networks/arenas-pgp

File prints the BFS path for each one of the nodes in the graph.
