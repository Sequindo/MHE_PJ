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
/*
void test_if_it_works(Graph& test_graph)
{
    auto validation_func = test_graph.validation_function_factory();
    std::vector<solution_t> solutions;
    solutions.push_back(solution_t{1, 0, 1, 0, 0, 1});
    solutions.push_back(solution_t{1, 0, 1, 0, 1, 1});
    for(auto sol : solutions)
    {
        try
        {
            bool ret = validation_func(sol);
            if(ret) std::cout << sol <<  "describes an independent set\n";
        } catch(std::string &str)
        {
            std::cout << str << std::endl;
        };
    }
}
*/
int main(int argc, char **argv)
{
    Graph problemGraph;
    if(argc>1)
    {
        try
        {
            problemGraph.readFromFile(argv[1]);
            solution_t pSolution = problemGraph.generateSolution();
            auto validation_func = problemGraph.validation_function_factory();
            validation_func(pSolution);
            problemGraph.prepareGraphVizOutput("graphviz.txt", pSolution);
        }
        catch(std::string &e)
        {
            std::cerr << e << std::endl;
        }
    }
    return 0;
}