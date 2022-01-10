#include "graph.hpp"

class GeneticAlgorithm {
    Graph& ga_graph;
    std::vector<solution_t> initial_population;
    std::function<int (solution_t &)> validation_func;
    int iterations;
    uint16_t threshold;
    double mutate_prob;
    double mutate_single_prob;
public:
    void generateInitialPopulation(size_t size);
    
    GeneticAlgorithm(Graph& _graph, uint16_t _threshold, double _mutate_prob, double _mutate_single_prob) 
        : ga_graph(_graph), threshold(_threshold), mutate_prob(_mutate_prob), mutate_single_prob(_mutate_single_prob) {
        validation_func = ga_graph.validation_function_factory();
    }

    uint16_t fintess(solution_t& candidate);
    void crossover(solution_t& par1, solution_t& par2);
    void mutate(solution_t& candidate);
    std::vector<solution_t>& selection(bool type);
    bool check_end_condition();
    solution_t* GA();
};