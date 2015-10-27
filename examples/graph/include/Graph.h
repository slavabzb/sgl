#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph
{
public:
    void readGraph(std::string fileName);
    void writeGraph(std::string fileName);

    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    int changeEdge(int from, int to, int newWeight);
    
    void transformToAdjList();
    void transformToAdjMatrix();
    void transformToListOfEdges();
};

#endif // GRAPH_H
