#include <iostream>
#include "graph.hpp"

#define SHORT_PROBLEM_SIZE 10

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
    solution_t pInitialSolution, pSolutionNext;
    pInitialSolution = std::move(Graph::generateSolution(graph.getGraphSize()));
    pSolutionNext = pInitialSolution;
    auto start = std::chrono::high_resolution_clock::now();
    do
    {
        try
        {
            pSolutionNext = std::move(graph.nextSolution(pSolutionNext));
            auto validation_func = graph.validation_function_factory();
            int curr_set_size = validation_func(pSolutionNext);
            if(curr_set_size > set_size)
            {
                set_size = curr_set_size;
            }
        }
        catch(std::string &e)
        {
            //std::cerr << e << std::endl;
        }
    } while(pSolutionNext != pInitialSolution);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<DurationType>(end - start);
    Graph::prepareGraphVizOutput(graph.getGraphDesc(), graphvizFilenameOutput, pSolutionNext, time_span);
    return;
}

int main(int argc, char **argv)
{
    Graph problemGraphShort{std::move(Graph::generateProblemGraph(SHORT_PROBLEM_SIZE, "generated_graph.csv"))};
    bruteForceMethod<std::chrono::milliseconds>(problemGraphShort, "graphviz_output_short.txt");
    if(argc>1)
    {
        //problemGraph.readFromFile(argv[1]);
    }
    return 0;
}