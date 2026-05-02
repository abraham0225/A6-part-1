#include "graph.h"

int main()
{
    Graph g(10);

    // Add vertices
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');
    g.addVertex('G');
    g.addVertex('H');
    g.addVertex('I');
    g.addVertex('J');

    // Add edges
    g.addEdge('A', 'B', 1);
    g.addEdge('A', 'C', 2);
    g.addEdge('B', 'D', 3);
    g.addEdge('C', 'E', 4);
    g.addEdge('C', 'D', 5);
    g.addEdge('E', 'D', 6);
    g.addEdge('A', 'H', 7);
    g.addEdge('B', 'G', 8);
    g.addEdge('F', 'I', 9);
    g.addEdge('F', 'J', 10);
    g.addEdge('I', 'J', 11);
    g.addEdge('C', 'F', 12);
    g.addEdge('D', 'F', 13);
    g.addEdge('C', 'H', 14);

    cout << "Original Adjacency List:" << endl;
    g.displayList();

    cout << "Original Adjacency Matrix:" << endl;
    g.displayMatrix();

    cout << endl;

    // Test BFS and DFS
    cout << "Traversal Tests:" << endl;
    g.bfsL('A');
    g.bfsM('A');
    g.dfsL('A');
    g.dfsM('A');

    cout << endl;

    // Test cycle detection
    cout << "Cycle Test:" << endl;

    if(g.detectCycle())
    {
        cout << "Cycle detected" << endl;
    }
    else
    {
        cout << "No cycle detected" << endl;
    }

    cout << endl;

    // Test removeEdge
    cout << "Removing edge C-H..." << endl;
    g.removeEdge('C', 'H');

    cout << endl;

    cout << "Adjacency List After Removing C-H:" << endl;
    g.displayList();

    cout << "Adjacency Matrix After Removing C-H:" << endl;
    g.displayMatrix();

    cout << endl;

    // Test traversals again after removing edge
    cout << "Traversal Tests After Removing Edge:" << endl;
    g.bfsL('A');
    g.bfsM('A');
    g.dfsL('A');
    g.dfsM('A');

    cout << endl;

    return 0;
}