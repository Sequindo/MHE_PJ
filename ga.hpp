#include "graph.hpp"

class GeneticAlgorithm {
    Graph& ga_graph;
    std::vector<solution_t> initial_population;
    std::function<int (solution_t &)> validation_func;

public:
    void generateInitialPopulation(size_t size);
    
    GeneticAlgorithm(Graph& _graph) : ga_graph(_graph) {
        validation_func = ga_graph.validation_function_factory();
    }

    uint16_t fintess(solution_t& candidate);

    bool check_end_condition();
    solution_t GA();

};