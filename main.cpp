#include <iostream>
#include "graph.hpp"

#define SHORT_PROBLEM_SIZE 20
#define MIDDLE_PROBLEM_SIZE 22
#define LARGE_PROBLEM_SIZE 24
#define LARGEST_PROBLEM_SIZE 27
#define XTRALARGE_PROBLEM_SIZE 29

std::ostream& operator <<(std::ostream& os, const solution_t& sol)
{
    os << "Vertices with indexes: ";
    for(int i=0;i<sol.size();i++)
    {
        if(sol.at(i)) os << i+1 << " ";
    }
    return os;
}

template<typename DurationType = std::chrono::seconds>
void bruteForceMethod(Graph& graph, const char* graphvizFilenameOutput)
{
    uint8_t set_size = 0;
    solution_t pInitialSolution, pSolutionNext, pMaxSolution;
    pInitialSolution = std::move(Graph::generateSolution(graph.getGraphSize()));
    pMaxSolution = pSolutionNext = pInitialSolution;
    auto start = std::chrono::high_resolution_clock::now();
    do
    {
        try
        {
            pSolutionNext = std::move(graph.nextSolution(pSolutionNext));
            auto validation_func = graph.validation_function_factory();
            int curr_set_size = validation_func(pSolutionNext);
            //std::cout << "Passed solution " << pSolutionNext << std::endl;
            if(curr_set_size > set_size)
            {
                set_size = curr_set_size;
                pMaxSolution = pSolutionNext;
            }
        }
        catch(std::string &e)
        {
            //std::cerr << e << std::endl;
        }
    } while(pSolutionNext != pInitialSolution);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<DurationType>(end - start);
    Graph::prepareGraphVizOutput(graph.getGraphDesc(), graphvizFilenameOutput, pMaxSolution, time_span);
    return;
}

int main(int argc, char **argv)
{
    if(argc>1)
    {
        Graph problemGraph;
        problemGraph.readFromFile(argv[1]);
        bruteForceMethod<std::chrono::milliseconds>(problemGraph, "graphviz_output_custom.txt");

    } else {
        Graph problemGraphShort{std::move(Graph::generateProblemGraph(SHORT_PROBLEM_SIZE, "generated_graph_short.csv"))};
        Graph problemGraphMiddle{std::move(Graph::generateProblemGraph(MIDDLE_PROBLEM_SIZE, "generated_graph_middle.csv"))};
        Graph problemGraphLarge{std::move(Graph::generateProblemGraph(LARGE_PROBLEM_SIZE, "generated_graph_large.csv"))};
        Graph problemGraphLargest{std::move(Graph::generateProblemGraph(LARGEST_PROBLEM_SIZE, "generated_graph_largest.csv"))};
        //Graph problemGraphExtraLarge{std::move(Graph::generateProblemGraph(XTRALARGE_PROBLEM_SIZE, "generated_graph_exlarge.csv"))};
        bruteForceMethod<std::chrono::milliseconds>(problemGraphShort, "graphviz_output_short.txt");
        bruteForceMethod<std::chrono::milliseconds>(problemGraphMiddle, "graphviz_output_middle.txt");
        bruteForceMethod<std::chrono::milliseconds>(problemGraphLarge, "graphviz_output_large.txt");
        bruteForceMethod<std::chrono::milliseconds>(problemGraphLargest, "graphviz_output_largest.txt");
        //bruteForceMethod<std::chrono::milliseconds>(problemGraphExtraLarge, "graphviz_output_extralarge.txt");
    }
    return 0;
}