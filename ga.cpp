#include "ga.hpp"
#include <iostream>

bool GeneticAlgorithm::check_end_condition() {
    return false;
}

void GeneticAlgorithm::generateInitialPopulation(size_t size) {
    this->initial_population.clear();
    initial_population.resize(size);
    for(auto& p : initial_population)
    {
        p = std::move(Graph::generateStartPoint(ga_graph.getGraphSize()));
    }
}


uint16_t GeneticAlgorithm::fintess(solution_t& candidate) {
    uint16_t fitnessVal = this->ga_graph.getGraphSize();
    return fitnessVal;
}

solution_t GeneticAlgorithm::GA() {
    solution_t bestCandidate = std::move(Graph::generateStartPoint(ga_graph.getGraphSize()));
    return bestCandidate;
}