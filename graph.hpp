#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>
#include <random>
#include <chrono>

using graph_desc_t = std::vector<std::vector<bool>>;
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

class Graph {
    graph_desc_t desc_graph;

public:
    Graph() {}
    Graph(Graph& _other) : desc_graph(_other.desc_graph) {}
    Graph(Graph&& _other) : desc_graph(std::move(_other.desc_graph)) {}
    Graph(graph_desc_t& _desc_graph) : desc_graph(_desc_graph) {}
    Graph(graph_desc_t&& _desc_graph) : desc_graph(std::move(_desc_graph)) {}

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
            desc_graph.push_back(tmp);
        }
        filestream.close();
        }

    std::function<int(solution_t&)> validation_function_factory()
    {
        return [=](solution_t& _vec_vector) -> int {
            uint8_t size_set = std::count(_vec_vector.begin(), _vec_vector.end(), true); //proposed set size
            int8_t errorCount = 0;
            for(size_t i=0;i<_vec_vector.size();i++)
            {
                if(_vec_vector.at(i)==false) continue;
                for(size_t j=0;j<_vec_vector.size();j++)
                {
                    if(i==j || _vec_vector[j]==false) continue;
                    else
                    {
                        if(desc_graph.at(i).at(j)==true || desc_graph.at(j).at(i)==true)
                        {   
                            /*std::string s;
                            s.append("Given vertices ");
                            s.append(std::to_string(i));
                            s.append(" i ");
                            s.append(std::to_string(j));
                            s.append(" are adjacent!\n");
                            throw std::string(s);*/
                            errorCount--;
                        }
                    }
                }
            }
            return (errorCount<0) ? errorCount/2 : size_set;
        };
    }
    size_t getGraphSize()
    {
        return desc_graph.size();
    }
    graph_desc_t getGraphDesc()
    {
        return desc_graph;
    }

    static solution_t generateSolution(const size_t& size)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0,1);
        auto roll = std::bind (distribution, generator);

        solution_t _solution(size,false);
        for(auto&& v : _solution)
        {
            v = roll();
        }
        return _solution;
    }

    static solution_t nextSolution(const solution_t& _solution) //increment vector by a logical 1
    {
        solution_t _newSolution = _solution;
        for(auto it = _newSolution.rbegin(); it != _newSolution.rend(); it++)
        {
            *it = !*it;
            if(*it) break;
        }
        return _newSolution;
    }

    static std::vector<solution_t> allSolutionsForPoints(solution_t& initialSolution)
    {
        std::vector<solution_t> neighborhood;
        for(int i=0;i<initialSolution.size();i++)
        {
            solution_t sol(initialSolution);
            sol[i] = sol[i]^true;
            neighborhood.push_back(std::move(sol));
        }
        return neighborhood;
    }

    static graph_desc_t generateProblemGraph(size_t size, const char* filename=NULL)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0,1);
        auto roll = std::bind (distribution, generator);

        graph_desc_t newGraph;
        solution_t tmp;
        solution_t sol = std::move(generateSolution(size));
        sol[0] = false;
        newGraph.push_back(sol);
        for(int i=1;i<size;i++) 
        {
            tmp.clear();
            for(int j=0;j<i;j++)
            {
                tmp.push_back(newGraph.at(j).at(i));
            }
            tmp.push_back(false);
            solution_t tmp_rand = std::move(generateSolution(size-i-1));
            tmp.insert(tmp.end(), tmp_rand.begin(), tmp_rand.end());
            newGraph.push_back(tmp);
        }
        if(filename!=NULL)
        {
            std::ofstream ofs;
            ofs.open(filename);
            for(auto& sol_row : newGraph)
            {
                for(int i=0;i<sol_row.size();i++)
                {
                    ofs << sol_row.at(i);
                    i+1 == sol_row.size() ? ofs << ";" : ofs << ",";
                }
                ofs << std::endl;
            }
            ofs.close();
        }
        return newGraph;
    }

    static void prepareGraphVizOutput(const graph_desc_t& graph_desc, const char* filename, const solution_t& sol={}, 
        const std::chrono::duration<double> timestamp={})
    {
        std::ofstream ofs(filename, std::ios::trunc);
        if(!ofs.is_open())
        {
            throw std::string("Cannot open file for writing!\n");
        }
        ofs << "strict graph G {\n\tnode [shape=circle style=filled]\n";
        ofs << "\tlabel=\"Elapsed calculating time: " << timestamp.count() << " s\"\n";
        int v_num = graph_desc.at(0).size();
        for(int i=0;i<v_num; i++)
        {
            for(int j=0;j<v_num;j++)
            {
                if(graph_desc.at(i).at(j))
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
};
