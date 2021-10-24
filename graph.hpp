#pragma once
#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>
#include <random>

using graph_desc_t = std::vector<std::vector<bool>>;
using solution_t = std::vector<bool>; //vector with values (0,1) for each vertice - telling if given vertice belongs to independent set
class Graph {
    graph_desc_t _desc_graph;

public:
    Graph() {}
    Graph(Graph& _other) {}
    Graph(Graph&& other) {}

    void readFromFile(const char* filename)
    {
        std::ifstream filestream(filename);
        std::string line;
        if(!filestream.is_open())
        {
            throw std::string("Unable to read file\n");
        }
        while(std::getline(filestream, line))
        {
            std::vector<bool> tmp;
            for(auto c : line)
            {
                switch(c)
                {
                    case('0'):
                        tmp.push_back(false);
                        break;
                    case('1'):
                        tmp.push_back(true);
                    default:
                        break;
                }
            }
            _desc_graph.push_back(tmp);
        }
        filestream.close();
        }
    void prepareGraphVizOutput(const char* filename, const solution_t& sol={})
    {
        std::ofstream ofs(filename, std::ios::trunc);
        if(!ofs.is_open())
        {
            throw std::string("Cannot open file for writing!\n");
        }
        ofs << "strict graph G {\n\tnode [shape=circle style=filled]\n";
        int v_num = _desc_graph.at(0).size();
        for(int i=0;i<v_num; i++)
        {
            for(int j=0;j<v_num;j++)
            {
                if(_desc_graph.at(i).at(j))
                {
                    ofs << "\t" << i+1 << "--" << j+1 << "\n";
                }
            }
        }
        if(!sol.empty()) {
            for(int i=0;i<sol.size();i++)
            {
                if(sol.at(i))
                {
                    ofs << "\t" << i+1 << " [style=filled, fillcolor=lightblue]\n";
                }
            }
        }
        ofs << "}";
        ofs.close();
    }
    std::function<int(solution_t&)> validation_function_factory()
    {
        return [=](solution_t& _vec_vector) -> int {
            int size_set = std::count(_vec_vector.begin(), _vec_vector.end(), true); //proposed set size
            for(size_t i=0;i<_vec_vector.size();i++)
            {
                if(_vec_vector.at(i)==false) continue;
                for(size_t j=0;j<_vec_vector.size();j++)
                {
                    if(i==j || _vec_vector[j]==false) continue;
                    else
                    {
                        if(_desc_graph.at(i).at(j)==true || _desc_graph.at(j).at(i)==true)
                        {
                            std::string s;
                            s.append("Given vertices ");
                            s.append(std::to_string(i));
                            s.append(" i ");
                            s.append(std::to_string(j));
                            s.append(" are adjacent!\n");
                            throw std::string(s);
                        }
                    }
                }
            }
            return size_set;
        };
    }

    solution_t generateSolution()
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0,1);
        auto roll = std::bind (distribution, generator);

        solution_t _solution(_desc_graph.size(),false);
        for(auto&& v : _solution)
        {
            v = roll();
        }
        return _solution;
    }
    solution_t nextSolution(const solution_t& _solution) //increment vector by a logical 1
    {
        solution_t _newSolution = _solution;
        for(auto it = _newSolution.rbegin(); it != _newSolution.rend(); it++)
        {
            *it = !*it;
            if(*it) break;
        }
        return _newSolution;
    }
};
