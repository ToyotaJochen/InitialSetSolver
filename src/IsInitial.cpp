#include <algorithm>
#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool is_initial(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments, SAT_Solver & solver, std::vector<std::vector<uint32_t>> result){
        std::vector<int32_t> complement_clause;
        if(arguments.size() == 1){
            std::set<uint32_t> char_func = characteristicFunction(af, active_arguments, arguments);
            if (std::find(arguments.begin(), arguments.end(), *arguments.begin()) != arguments.end()){
                return true;
            } else {
                return false;
            }
        }
        //std::cout <<"is initial c > 1 \n";

        for(auto a : arguments){
            for(auto b: arguments){
                if(a != b){
                    std::set<uint32_t> candidate;
                    for (auto c : arguments){
                        if(c != b){
                            candidate.insert(c);
                        }
                    }
                    //std::cout << "entering contains \n";
                    if(contains_admissible(af, active_arguments, candidate, a, solver, result, true)){
                        return false;
                    }
                    //std::cout << "left contains \n";
                }
            }
        }
        return true;
    }
}