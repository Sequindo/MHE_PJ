#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>
#include <random>
#include <chrono>

using graph_desc_t = std::vector<std::vector<bool>>;
using solution_t = std::vector<bool>; //vector with values (0,1) for each vertice - telling if given vertice belongs to independent set

std::ostream& operator <<(std::ostream& os, const solution_t& sol);

class Graph {
    static std::random_device rd;
    static std::mt19937 generator;
    graph_desc_t desc_graph;

public:
    Graph();
    Graph(Graph& _other);
    Graph(Graph&& _other);
    Graph(graph_desc_t& _desc_graph);
    Graph(graph_desc_t&& _desc_graph);

    void operator=(Graph&& _other);
    void readFromFile(const char* filename);

    std::function<int(solution_t&)> validation_function_factory();
    size_t getGraphSize();
    graph_desc_t getGraphDesc();

    static solution_t generateSolution(const size_t& size);
    static solution_t nextSolution(const solution_t& _solution);

    static std::vector<solution_t> allSolutionsForPoints(solution_t& initialSolution);

    static solution_t generateStartPoint(const size_t& size);

    template<typename T>
    static T returnRandomElement(std::vector<T>& data, int size) {
        std::uniform_int_distribution<int> distribution(0,size-1);
        return data[distribution(generator)];
    }
    static graph_desc_t generateProblemGraph(size_t size, const char* filename=NULL);

    static void prepareGraphVizOutput(const graph_desc_t& graph_desc, const char* filename, const solution_t& sol={}, 
        const std::chrono::duration<double> timestamp={});
};