#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <sgl/sgl.h>

class Graph
{
public:
    Graph()
    {
        this->view = std::make_shared<sgl::view::adjacency_matrix>();
    }

    void readGraph(std::string fileName)
    {
        std::ifstream file(fileName);
        sgl::io::simple_reader reader(file);
        this->view = reader.read();
    }

    void writeGraph(std::string fileName)
    {
        std::ofstream file(fileName);
        sgl::io::simple_writer writer(file);
        writer.write(this->view);
    }

    void addEdge(unsigned int from, unsigned int to, unsigned int weight)
    {
        this->view->add_edge(sgl::core::edge(from, to, weight));
    }

    void removeEdge(unsigned int from, unsigned int to)
    {
        auto edges = this->view->get_edges();
        auto it = std::find_if(edges.begin(), edges.end(), [&](const sgl::core::edge& edge)
        {
            if(edge.get_first().get_id() == from && edge.get_second().get_id() == to)
            {
                return true;
            }

            return false;
        });

        this->view->remove_edge(*it);
    }

    unsigned int changeEdge(unsigned int from, unsigned int to, unsigned int newWeight)
    {
        auto edges = this->view->get_edges();
        auto it = std::find_if(edges.begin(), edges.end(), [&](const sgl::core::edge& edge)
        {
            if(edge.get_first().get_id() == from && edge.get_second().get_id() == to)
            {
                return true;
            }

            return false;
        });

        int oldWeight = it->get_weight();

        this->removeEdge(from, to);
        this->addEdge(from, to, newWeight);

        return oldWeight;
    }

    void transformToAdjList()
    {
        this->view = std::make_shared<sgl::view::adjacency_list>(*this->view);
    }

    void transformToAdjMatrix()
    {
        this->view = std::make_shared<sgl::view::adjacency_matrix>(*this->view);
    }

    void transformToListOfEdges()
    {
        this->view = std::make_shared<sgl::view::edge_list>(*this->view);
    }

private:
    sgl::view::view_t view;
};

int main()
{
    Graph graph;
    graph.readGraph("file.txt");

    graph.addEdge(1, 2, 3);
    int weight = graph.changeEdge(0, 1, 5);
    std::cout << "Previous weight was " << weight << "\n";
    graph.writeGraph("changed.txt");

    graph.transformToAdjList();
    graph.writeGraph("adjlist.txt");

    graph.transformToAdjMatrix();
    graph.writeGraph("matrix.txt");

    graph.transformToListOfEdges();
    graph.writeGraph("edgelist.txt");

    return 0;
}
