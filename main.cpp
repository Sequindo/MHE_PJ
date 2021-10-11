#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <string>

using graph_t = std::vector<std::vector<bool>>;
using solution_t = std::vector<bool>; //vector with values (0,1) for each vertice - telling if given vertice belongs to independent set

std::ostream& operator <<(std::ostream& os, const solution_t& sol)
{
    os << "Vertices with indexes: ";
    for(int i=0;i<sol.size();i++)
    {
        if(sol.at(i)) os << i+1 << " ";
    }
    return os;
}

std::function<bool(solution_t&)> validation_function_factory(graph_t _graph)
{
    return [=](solution_t& _vec_vector) -> bool {
        for(int i=0;i<_vec_vector.size();i++)
        {
            if(_vec_vector.at(i)==false) continue;
            for(int j=0;j<_vec_vector.size();j++)
            {
                if(i==j || _vec_vector[j]==false) continue;
                else
                {
                    if(_graph.at(i).at(j)==true || _graph.at(j).at(i)==true)
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
        return true;
    };
}

void test_if_it_works()
{
    graph_t test_graph = {
        {0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    auto validation_func = validation_function_factory(test_graph);
    std::vector<solution_t> solutions;
    solutions.push_back(solution_t{1, 0, 1, 0, 0, 1});
    solutions.push_back(solution_t{1, 0, 1, 0, 1, 1});
    for(auto sol : solutions)
    {
        try
        {
            bool ret = validation_func(sol);
            if(ret) std::cout << sol <<  "describes an independent set\n";
        } catch(std::string &str)
        {
            std::cout << str << std::endl;
        };
    }
}

int main(int argc, char **argv)
{
    test_if_it_works();
    return 0;
}