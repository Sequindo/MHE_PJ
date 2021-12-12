#include "graph.hpp"
#include <set>
#include <list>

class Meta
{
public:
template<typename DurationType = std::chrono::seconds>
static std::pair<std::chrono::duration<double>, int16_t> bruteForceMethod(Graph& graph, const char* graphvizFilenameOutput)
{
    int16_t set_size = INT16_MIN;
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
    return std::make_pair(time_span, set_size);
}

template<typename DurationType = std::chrono::seconds>
static std::pair<std::chrono::duration<double>, int16_t> hillClimb(Graph& graph, const char* graphvizFilenameOutput, int iterations, bool randomized=false, int burnout = 0)
{
    solution_t initialSolution = std::move(Graph::generateStartPoint(graph.getGraphSize()));
    std::vector<solution_t> pointSolutions = std::move(Graph::allSolutionsForPoints(initialSolution));
    auto validation_func = graph.validation_function_factory();
    
    int16_t set_size = INT16_MIN;
    auto curr_set_size = set_size;
    auto prev_set_size = set_size;
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
    return std::make_pair(time_span, set_size);
}

template<typename DurationType = std::chrono::seconds>
static std::pair<std::chrono::duration<double>, int16_t> tabuSearch(Graph& graph, const char* graphvizFilenameOutput, int tabooSize, int iterations)
{
    auto start = std::chrono::high_resolution_clock::now();
    solution_t bestSolution = std::move(Graph::generateStartPoint(graph.getGraphSize()));
    auto validation_func = graph.validation_function_factory();
    std::set<decltype(bestSolution)> tabooSet;
    std::list<decltype(bestSolution)> tabooList;

    auto isInTaboo = [&](auto e) {
        return tabooSet.count(e);
    };
    auto addToTaboo = [&](auto e) {
        tabooSet.insert(e);
        tabooList.push_back(e);
    };
    auto shrinkTaboo = [&]() {
        if(tabooSet.size() > tabooSize)
        {
            tabooSet.erase(tabooList.front());
            tabooList.pop_front();
        }
    };

    auto v = bestSolution;
    do {
        auto neighbours = std::move(Graph::allSolutionsForPoints(bestSolution));
        neighbours.erase(std::remove_if(neighbours.begin(),
                             neighbours.end(),
                             [&](auto e) { return isInTaboo(e); }),
            neighbours.end());
        if (neighbours.size() == 0) break;
        v = *std::max_element(neighbours.begin(), neighbours.end(), [&](auto a, auto b) {
            return validation_func(a) < validation_func(b);
        });
        addToTaboo(v);
        auto const size_set = validation_func(v);
        if (validation_func(v) > validation_func(bestSolution)) {
            bestSolution = v;
        }
        shrinkTaboo();
    } while(--iterations);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<DurationType>(end - start);
    Graph::prepareGraphVizOutput(graph.getGraphDesc(), graphvizFilenameOutput, bestSolution, time_span);
    return std::make_pair(time_span, std::count(bestSolution.begin(), bestSolution.end(), true));
}
};