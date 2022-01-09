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
    uint16_t fitnessVal = this->ga_graph.getGraphSize() - this->validation_func(candidate);
    return fitnessVal;
}

void crossover(solution_t& par1, solution_t& par2) {
    std::uniform_int_distribution<size_t> distribution(0,par1.size());
    auto crosspoint = std::bind(distribution, generator);
}

solution_t GeneticAlgorithm::GA() {
    solution_t bestCandidate = std::move(Graph::generateStartPoint(ga_graph.getGraphSize()));
    return bestCandidate;
}