#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

class Graph
{
public:
    void readGraph(string fileName);
    void writeGraph(string fileName);

    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    int changeEdge(int from, int to, int newWeight);
    
    void transformToAdjList();
    void transformToAdjMatrix();
    void transformToListOfEdges();

private:
    vector< vector< int > > adjMatrix;
};

#endif // GRAPH_H
