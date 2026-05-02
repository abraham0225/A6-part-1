#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <iomanip>
//#include sqll.h  // for traversals

using namespace std;

struct edge
{
    struct vertex* dest;
    edge* eNext;

    int weight;
};

struct vertex
{
    char data;
    vertex* vNext;
    edge* aHead;
};

class Graph
{
    private:
        vertex* vertices; // list of vertices
        int** adjMatrix;
        bool* visited;
        int maxVertices;
        int numVertices;

    public:
        Graph(int maxV);
        ~Graph();

        //core operations
        void addVertex(char data);
        void addEdge(char src, char dest, int weight);
        void removeVertex(char data);
        void removeEdge(char src, char dest);

        // traversal algorithms
        void bfsL(char start);
        void bfsM(char start);
        void dfsL(char start);
        void dfsM(char start);

        // display
        void displayList();
        void displayMatrix();

};

#endif