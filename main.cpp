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
        solution_t pInitialSolution, pSolutionNext;
        pInitialSolution = std::move(problemGraph.generateSolution());
        pSolutionNext = pInitialSolution;
        do
        {
            try
            {
                pSolutionNext = std::move(problemGraph.nextSolution(pSolutionNext));
                auto validation_func = problemGraph.validation_function_factory();
                int curr_set_size = validation_func(pSolutionNext);
                if(curr_set_size > set_size)
                {
                    set_size = curr_set_size;
                    problemGraph.prepareGraphVizOutput("graphviz.txt", pSolutionNext);
                }
            }
            catch(std::string &e)
            {
                std::cerr << e << std::endl;
            }
        } while(pSolutionNext != pInitialSolution);
    }
    return 0;
}