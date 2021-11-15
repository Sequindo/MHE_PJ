#include "graph.hpp"

class Meta
{
public:
template<typename DurationType = std::chrono::seconds>
static void bruteForceMethod(Graph& graph, const char* graphvizFilenameOutput)
{
    int8_t set_size = INT8_MIN;
    solution_t pInitialSolution, pSolutionNext, pMaxSolution;
    pInitialSolution = std::move(Graph::generateSolution(graph.getGraphSize()));
    pMaxSolution = pSolutionNext = pInitialSolution;
    auto validation_func = graph.validation_function_factory();
    auto start = std::chrono::high_resolution_clock::now();
    do
    {
        pSolutionNext = std::move(graph.nextSolution(pSolutionNext));
        auto curr_set_size = validation_func(pSolutionNext);
        if(curr_set_size > set_size)
        {
            set_size = curr_set_size;
            pMaxSolution = pSolutionNext;
        }
    } while(pSolutionNext != pInitialSolution);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<DurationType>(end - start);
    Graph::prepareGraphVizOutput(graph.getGraphDesc(), graphvizFilenameOutput, pMaxSolution, time_span);
    return;
}

template<typename DurationType = std::chrono::seconds>
static void hillClimb(Graph& graph, const char* graphvizFilenameOutput, int iterations, bool randomized=false, int burnout = 0)
{
    solution_t initialSolution = std::move(Graph::generateStartPoint(graph.getGraphSize()));
    std::vector<solution_t> pointSolutions = std::move(Graph::allSolutionsForPoints(initialSolution));
    auto validation_func = graph.validation_function_factory();
    
    int8_t set_size = -INT8_MIN;
    int8_t curr_set_size = set_size;
    int8_t prev_set_size = set_size;
    auto start = std::chrono::high_resolution_clock::now();
    do
    {
        prev_set_size = set_size;
        if(!randomized)
        {
            for(solution_t& solutionFromList : pointSolutions)
            {
                curr_set_size = validation_func(solutionFromList);
                if(curr_set_size > set_size)
                {
                    set_size = curr_set_size;
                    initialSolution = solutionFromList;
                    pointSolutions = std::move(Graph::allSolutionsForPoints(initialSolution));
                    break;
                }
            }
        }
        else
        {
            for(int i=0;i<burnout;i++)
            {
                solution_t random_solution = Graph::returnRandomElement<solution_t>(pointSolutions, pointSolutions.size());
                curr_set_size = validation_func(random_solution);
                if(curr_set_size > set_size)
                {
                    set_size = curr_set_size;
                    initialSolution = random_solution;
                    pointSolutions = std::move(Graph::allSolutionsForPoints(initialSolution));
                    break;
                }
            }
        }
        if(prev_set_size == set_size) break; //no improvement
    } while(iterations--);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<DurationType>(end - start);
    Graph::prepareGraphVizOutput(graph.getGraphDesc(), graphvizFilenameOutput, initialSolution, time_span);
    return;
}

};