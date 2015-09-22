#include "Graph.h"
#include <fstream>
#include <stdexcept>

void Graph::readGraph(string fileName)
{
    ifstream file(fileName.c_str());

    if(!file.is_open())
    {
        throw invalid_argument("Can't open file");
    }

    adjMatrix.clear();

    char type = ' ';
    file >> type;

    if(type == 'C')
    {
        int N = 0;
        file >> N;

        bool W = false;
        file >> W;

        for(int i = 0; i < N; i++)
        {
            vector<int> row;

            for(int j = 0; j < N; j++)
            {
                int a;
                file >> a;

                row.push_back(a);
            }

            adjMatrix.push_back(row);
        }
    }
}

void Graph::addEdge(int from, int to, int weight)
{

}

void Graph::removeEdge(int from, int to)
{

}

int Graph::changeEdge(int from, int to, int newWeight)
{

}

void Graph::transformToAdjList()
{

}

void Graph::transformToAdjMatrix()
{

}

void Graph::transformToListOfEdges()
{

}

void Graph::writeGraph(string fileName)
{

}
