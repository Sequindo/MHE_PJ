#include "ga.hpp"
#include <iostream>

/* TODO
    generating initial population - implemented
    fitness function - implemented
    crossover one - point - implemented
    mutate - classic AG - implemented

    crossover multi - point - TODO
    selection roulette - TODO
    selection competition - TODO
*/

bool GeneticAlgorithm::check_end_condition() {
    return false;
}

void GeneticAlgorithm::generateInitialPopulation(size_t size) {
    this->initial_population.clear();
    initial_population.resize(size);
    for(auto& p : initial_population)
    {
        p = std::move(Graph::generateSolution(ga_graph.getGraphSize()));
    }
}

uint16_t GeneticAlgorithm::fintess(solution_t& candidate) {
    uint16_t fitnessVal = this->ga_graph.getGraphSize() + this->validation_func(candidate);
    return fitnessVal;
}

void GeneticAlgorithm::crossover(solution_t& par1, solution_t& par2) {
    std::uniform_int_distribution<size_t> distribution(0,par1.size());
    for(auto crosspoint = distribution(generator); crosspoint < par1.size(); crosspoint++)
    {
        std::swap(par1.at(crosspoint), par2.at(crosspoint));
    }
}

void GeneticAlgorithm::mutate(solution_t& candidate) {
    std::discrete_distribution<> distribution({1-mutate_single_prob, mutate_single_prob});
    for(size_t i=0;i<candidate.size();i++)
    {
        if(distribution(generator)) {
            candidate.at(i)=candidate.at(i)^true;
        }
    }
}

std::vector<solution_t>& GeneticAlgorithm::selection(bool type) {
    return initial_population;
}

solution_t* GeneticAlgorithm::GA() {
    uint16_t best_fitness = 0u;
    solution_t* bestCandidate = nullptr;
    for(auto& p : initial_population)
    {
        if(this->fintess(p) >= best_fitness)
        {
            best_fitness = this->fintess(p);
            bestCandidate = &p;
        }
    }
    return bestCandidate;
}