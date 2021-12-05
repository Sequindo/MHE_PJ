#include <iostream>
#include "meta.hpp"

enum metaAlgType
{
    BRUTEFORCE,
    HILL_CLIMB_STOCHASTIC,
    HILL_CLIMB_RANDOMIZED,
    TABU_SEARCH
};

enum generatedGraphSize
{
    SHORT_PROBLEM_SIZE = 15,
    MIDDLE_PROBLEM_SIZE = 22,
    LARGE_PROBLEM_SIZE = 24,
    LARGEST_PROBLEM_SIZE = 27,
    XTRALARGE_PROBLEM_SIZE = 29
};

int main(int argc, char **argv)
{
    metaAlgType algType = BRUTEFORCE;
    generatedGraphSize genSize = SHORT_PROBLEM_SIZE;
    std::string graphFilename = "";
    std::string graphVizFilenameOutput = "";
    bool generateGraphFile = false;
    bool generateOnly = false;
    unsigned int iterations = 3000;
    unsigned int burnout = 0;
    unsigned int tabuSize = 1000;
    for(int i=1;i<argc;i++)
    {
        if(argv[i]=="-hclimb")
        {
            algType = HILL_CLIMB_STOCHASTIC;
        }
        else if(argv[i]=="-hclimb_random")
        {
            algType = HILL_CLIMB_RANDOMIZED;
        }
        else if(argv[i]=="-tsearch")
        {
            algType = TABU_SEARCH;
        }
        else if(argv[i]=="-bforce")
        {
            algType = BRUTEFORCE;
        }
        else if(argv[i]=="-gfile")
        {
            graphFilename = argv[++i];
        }
        else if(argv[i]=="-ofile")
        {
            graphVizFilenameOutput = argv[++i];
        }
        else if(argv[i]=="-iter")
        {
            iterations = std::stoull(argv[++i]);
        }
        else if(argv[i]=="-tsize")
        {
            tabuSize = std::stoull(argv[++i]);
        }
        else if(argv[i]=="-burnout")
        {
            burnout = std::stoull(argv[++i]);
        }
        else if(argv[i]=="-generate")
        {
            generateGraphFile = true;
        }
        else if(argv[i]=="-size_small")
        {
            genSize = SHORT_PROBLEM_SIZE;
        }
        else if(argv[i]=="-size_middle")
        {
            genSize = MIDDLE_PROBLEM_SIZE;
        }
        else if(argv[i]=="-size_large")
        {
            genSize = LARGE_PROBLEM_SIZE;
        }
        else if(argv[i]=="-size_largest")
        {
            genSize = LARGEST_PROBLEM_SIZE;
        }
        else if(argv[i]=="-size_extralarge")
        {
            genSize = XTRALARGE_PROBLEM_SIZE;
        }
        else if(argv[i]=="-gen_only")
        {
            generateGraphFile = true;
            generateOnly = true;
        }
    }

    Graph problemGraph;
    if (graphFilename.empty()) graphFilename = "generated_graph.csv";
    if (graphFilename.empty()) graphVizFilenameOutput = "graphviz_output.csv";
    if (generateGraphFile) problemGraph.readFromFile(graphFilename.c_str());
    else problemGraph = std::move(Graph::generateProblemGraph(genSize, graphFilename.c_str()));
    if(!generateOnly)
    {
        switch(algType)
        {
            case(BRUTEFORCE):
                Meta::bruteForceMethod(problemGraph, graphVizFilenameOutput.c_str());
                break;
            case(HILL_CLIMB_STOCHASTIC):
                Meta::hillClimb(problemGraph, graphVizFilenameOutput.c_str(), iterations);
                break;
            case(HILL_CLIMB_RANDOMIZED):
                Meta::hillClimb(problemGraph, graphVizFilenameOutput.c_str(), iterations, true, burnout);
                break;
            case(TABU_SEARCH):
                Meta::tabuSearch(problemGraph, graphVizFilenameOutput.c_str(), tabuSize, iterations);
                break;
            default:
                break;
        }
    }
    return 0;
}