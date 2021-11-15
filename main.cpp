#include <iostream>
#include "meta.hpp"

#define SHORT_PROBLEM_SIZE 15
#define MIDDLE_PROBLEM_SIZE 22
#define LARGE_PROBLEM_SIZE 24
#define LARGEST_PROBLEM_SIZE 27
#define XTRALARGE_PROBLEM_SIZE 29

int main(int argc, char **argv)
{
    if(argc>1)
    {
        Graph problemGraph;
        problemGraph.readFromFile(argv[1]);
        // to be added in next commit

    } else {
        //Graph problemGraphShort{std::move(Graph::generateProblemGraph(SHORT_PROBLEM_SIZE, "generated_graph_short.csv"))};
        //Graph problemGraphMiddle{std::move(Graph::generateProblemGraph(MIDDLE_PROBLEM_SIZE, "generated_graph_middle.csv"))};
        //Graph problemGraphLarge{std::move(Graph::generateProblemGraph(LARGE_PROBLEM_SIZE, "generated_graph_large.csv"))};
        //Graph problemGraphLargest{std::move(Graph::generateProblemGraph(LARGEST_PROBLEM_SIZE, "generated_graph_largest.csv"))};
        //Graph problemGraphExtraLarge{std::move(Graph::generateProblemGraph(XTRALARGE_PROBLEM_SIZE, "generated_graph_exlarge.csv"))};
        Graph problemGraphShort;
        problemGraphShort.readFromFile("generated_graph_short.csv");

        Meta::bruteForceMethod<std::chrono::nanoseconds>(problemGraphShort, "graphviz_output_short_bruteforce.txt");
        Meta::hillClimb<std::chrono::nanoseconds>(problemGraphShort, "graphviz_output_short_hillclimb_classic.txt", 1000);
        Meta::hillClimb<std::chrono::nanoseconds>(problemGraphShort, "graphviz_output_short_hillclimb_randomized.txt", 1000, true, 45);
    }
    return 0;
}