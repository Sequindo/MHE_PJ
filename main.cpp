#include <iostream>
#include <cstring>
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
        if(strcmp(argv[i],"-hclimb")==0)
        {
            algType = HILL_CLIMB_STOCHASTIC;
        }
        else if(strcmp(argv[i],"-hclimb_random")==0)
        {
            algType = HILL_CLIMB_RANDOMIZED;
        }
        else if(strcmp(argv[i],"-tsearch")==0)
        {
            algType = TABU_SEARCH;
        }
        else if(strcmp(argv[i],"-bforce")==0)
        {
            algType = BRUTEFORCE;
        }
        else if(strcmp(argv[i],"-gfile")==0)
        {
            graphFilename = argv[++i];
        }
        else if(strcmp(argv[i],"-ofile")==0)
        {
            graphVizFilenameOutput = argv[++i];
        }
        else if(strcmp(argv[i],"-iter")==0)
        {
            iterations = std::stoull(argv[++i]);
        }
        else if(strcmp(argv[i],"-tsize")==0)
        {
            tabuSize = std::stoull(argv[++i]);
        }
        else if(strcmp(argv[i],"-burnout")==0)
        {
            burnout = std::stoull(argv[++i]);
        }
        else if(strcmp(argv[i],"-generate")==0)
        {
            generateGraphFile = true;
        }
        else if(strcmp(argv[i],"-size_small")==0)
        {
            genSize = SHORT_PROBLEM_SIZE;
        }
        else if(strcmp(argv[i],"-size_middle")==0)
        {
            genSize = MIDDLE_PROBLEM_SIZE;
        }
        else if(strcmp(argv[i],"-size_large")==0)
        {
            genSize = LARGE_PROBLEM_SIZE;
        }
        else if(strcmp(argv[i],"-size_largest")==0)
        {
            genSize = LARGEST_PROBLEM_SIZE;
        }
        else if(strcmp(argv[i],"-size_extralarge")==0)
        {
            genSize = XTRALARGE_PROBLEM_SIZE;
        }
        else if(strcmp(argv[i],"-gen_only")==0)
        {
            generateGraphFile = true;
            generateOnly = true;
        }
    }

    Graph problemGraph;
    if (graphFilename.empty()) graphFilename = "generated_graph.csv";
    if (graphFilename.empty()) graphVizFilenameOutput = "graphviz_output.csv";
    if (!generateGraphFile && !generateOnly) problemGraph.readFromFile(graphFilename.c_str());
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