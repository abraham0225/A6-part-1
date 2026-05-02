#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    visited = new bool[maxVertices] {false};

    adjMatrix = new int*[maxVertices];

    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices];

        for(int j = 0; j < maxVertices; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph()
{
    delete[] visited;

    for(int i = 0; i < maxVertices; i++)
    {
        delete[] adjMatrix[i];
    }

    delete[] adjMatrix;

    vertex* tempVertex;

    while(vertices)
    {
        edge* tempEdge;

        while(vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;
        }

        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex;
    }
}

void Graph::addVertex(char data)
{
    if(numVertices >= maxVertices)
    {
        cout << "Max number of vertices reached. Can't add!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;

    vertices = newVertex;

    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }

    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't add an edge" << endl;
        return;
    }

    // Add edge from source to destination
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Add reverse edge because graph is undirected
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Add to adjacency matrix
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';

    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    vertex* temp = vertices;
    vertex* prev = nullptr;

    while(temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }

    if(!temp)
    {
        cout << "Vertex not found - can't remove" << endl;
        return;
    }

    // Save index before deleting temp
    int index = temp->data - 'A';

    // Remove this vertex from all adjacency lists
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;

        while(e)
        {
            if(e->dest->data == data)
            {
                if(prevEdge)
                {
                    prevEdge->eNext = e->eNext;
                }
                else
                {
                    v->aHead = e->eNext;
                }

                edge* deleteEdge = e;
                e = e->eNext;
                delete deleteEdge;
            }
            else
            {
                prevEdge = e;
                e = e->eNext;
            }
        }
    }

    // Remove vertex from vertex list
    if(prev)
    {
        prev->vNext = temp->vNext;
    }
    else
    {
        vertices = temp->vNext;
    }

    // Delete this vertex's own edge list
    edge* currentEdge = temp->aHead;

    while(currentEdge)
    {
        edge* deleteEdge = currentEdge;
        currentEdge = currentEdge->eNext;
        delete deleteEdge;
    }

    delete temp;

    // Remove from adjacency matrix
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;
}

void Graph::removeEdge(char src, char dest)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }

    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't remove edge" << endl;
        return;
    }

    // Remove edge from src to dest
    edge* current = srcVertex->aHead;
    edge* previous = nullptr;

    while(current)
    {
        if(current->dest->data == dest)
        {
            if(previous)
            {
                previous->eNext = current->eNext;
            }
            else
            {
                srcVertex->aHead = current->eNext;
            }

            delete current;
            break;
        }

        previous = current;
        current = current->eNext;
    }

    // Remove edge from dest to src
    current = destVertex->aHead;
    previous = nullptr;

    while(current)
    {
        if(current->dest->data == src)
        {
            if(previous)
            {
                previous->eNext = current->eNext;
            }
            else
            {
                destVertex->aHead = current->eNext;
            }

            delete current;
            break;
        }

        previous = current;
        current = current->eNext;
    }

    // Remove from adjacency matrix
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';

    adjMatrix[srcIndex][destIndex] = 0;
    adjMatrix[destIndex][srcIndex] = 0;
}

void Graph::bfsL(char start)
{
    for(int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    vertex* startVertex = vertices;

    while(startVertex && startVertex->data != start)
    {
        startVertex = startVertex->vNext;
    }

    if(!startVertex)
    {
        cout << "Start vertex not found" << endl;
        return;
    }

    vertex** queue = new vertex*[maxVertices];
    int front = 0;
    int rear = 0;

    visited[startVertex->data - 'A'] = true;
    queue[rear] = startVertex;
    rear++;

    cout << "BFS List starting at " << start << ": ";

    while(front < rear)
    {
        vertex* current = queue[front];
        front++;

        cout << current->data << " ";

        edge* tempEdge = current->aHead;

        while(tempEdge)
        {
            int index = tempEdge->dest->data - 'A';

            if(!visited[index])
            {
                visited[index] = true;
                queue[rear] = tempEdge->dest;
                rear++;
            }

            tempEdge = tempEdge->eNext;
        }
    }

    cout << endl;

    delete[] queue;
}

void Graph::bfsM(char start)
{
    for(int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    int startIndex = start - 'A';

    if(startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Start vertex not found" << endl;
        return;
    }

    int* queue = new int[maxVertices];
    int front = 0;
    int rear = 0;

    visited[startIndex] = true;
    queue[rear] = startIndex;
    rear++;

    cout << "BFS Matrix starting at " << start << ": ";

    while(front < rear)
    {
        int current = queue[front];
        front++;

        cout << char('A' + current) << " ";

        for(int i = 0; i < maxVertices; i++)
        {
            if(adjMatrix[current][i] != 0 && !visited[i])
            {
                visited[i] = true;
                queue[rear] = i;
                rear++;
            }
        }
    }

    cout << endl;

    delete[] queue;
}

void Graph::dfsL(char start)
{
    for(int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    vertex* startVertex = vertices;

    while(startVertex && startVertex->data != start)
    {
        startVertex = startVertex->vNext;
    }

    if(!startVertex)
    {
        cout << "Start vertex not found" << endl;
        return;
    }

    vertex** stack = new vertex*[maxVertices];
    int top = 0;

    stack[top] = startVertex;
    top++;
    visited[startVertex->data - 'A'] = true;

    cout << "DFS List starting at " << start << ": ";

    while(top > 0)
    {
        top--;
        vertex* current = stack[top];

        cout << current->data << " ";

        edge* tempEdge = current->aHead;

        while(tempEdge)
        {
            int index = tempEdge->dest->data - 'A';

            if(!visited[index])
            {
                visited[index] = true;
                stack[top] = tempEdge->dest;
                top++;
            }

            tempEdge = tempEdge->eNext;
        }
    }

    cout << endl;

    delete[] stack;
}

void Graph::dfsM(char start)
{
    for(int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    int startIndex = start - 'A';

    if(startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Start vertex not found" << endl;
        return;
    }

    int* stack = new int[maxVertices];
    int top = 0;

    stack[top] = startIndex;
    top++;
    visited[startIndex] = true;

    cout << "DFS Matrix starting at " << start << ": ";

    while(top > 0)
    {
        top--;
        int current = stack[top];

        cout << char('A' + current) << " ";

        for(int i = maxVertices - 1; i >= 0; i--)
        {
            if(adjMatrix[current][i] != 0 && !visited[i])
            {
                visited[i] = true;
                stack[top] = i;
                top++;
            }
        }
    }

    cout << endl;

    delete[] stack;
}

bool Graph::detectCycle()
{
    for(int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    vertex** stack = new vertex*[maxVertices];
    vertex** parent = new vertex*[maxVertices];

    for(int i = 0; i < maxVertices; i++)
    {
        parent[i] = nullptr;
    }

    for(vertex* start = vertices; start != nullptr; start = start->vNext)
    {
        int startIndex = start->data - 'A';

        if(!visited[startIndex])
        {
            int top = 0;

            stack[top] = start;
            top++;
            visited[startIndex] = true;
            parent[startIndex] = nullptr;

            while(top > 0)
            {
                top--;
                vertex* current = stack[top];

                int currentIndex = current->data - 'A';
                edge* tempEdge = current->aHead;

                while(tempEdge)
                {
                    int neighborIndex = tempEdge->dest->data - 'A';

                    if(!visited[neighborIndex])
                    {
                        visited[neighborIndex] = true;
                        parent[neighborIndex] = current;

                        stack[top] = tempEdge->dest;
                        top++;
                    }
                    else if(parent[currentIndex] != tempEdge->dest)
                    {
                        delete[] stack;
                        delete[] parent;
                        return true;
                    }

                    tempEdge = tempEdge->eNext;
                }
            }
        }
    }

    delete[] stack;
    delete[] parent;

    return false;
}

void Graph::displayList()
{
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";

        for(edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " (" << e->weight << ") -> ";
        }

        cout << "null" << endl;
    }

    cout << endl;
}

void Graph::displayMatrix()
{
    cout << "     ";

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " ";
    }

    cout << endl;
    cout << "   ";

    for(int i = 0; i < maxVertices; i++)
    {
        cout << "-----";
    }

    cout << endl;

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " |";

        for(int j = 0; j < maxVertices; j++)
        {
            cout << setw(3) << adjMatrix[i][j] << " ";
        }

        cout << endl;
    }
}