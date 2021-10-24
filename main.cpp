#include <iostream>

#include "graph.hpp"


std::ostream& operator <<(std::ostream& os, const solution_t& sol)
{
    os << "Vertices with indexes: ";
    for(int i=0;i<sol.size();i++)
    {
        if(sol.at(i)) os << i+1 << " ";
    }
    return os;
}

int main(int argc, char **argv)
{
    Graph problemGraph;
    int set_size = 0;
    if(argc>1)
    {
        problemGraph.readFromFile(argv[1]);
        while(true)
        {
            try
            {
                solution_t pSolution = problemGraph.generateSolution();
                solution_t pSolutionNext = std::move(problemGraph.nextSolution(pSolution));
                auto validation_func = problemGraph.validation_function_factory();
                set_size = validation_func(pSolutionNext);
                problemGraph.prepareGraphVizOutput("graphviz.txt", pSolutionNext);
                break;
            }
            catch(std::string &e)
            {
                std::cerr << e << std::endl;
            }
        }
    }
    return 0;
}