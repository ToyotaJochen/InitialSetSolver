#include <algorithm>
#include <set>
#include "Algorithms.h"

namespace Algorithms{
    /* This method implements the test, whether a given set of arguments is an initial set. */
    bool is_initial(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments, SAT_Solver & solver, std::vector<std::vector<uint32_t>> result){
        // If the set is a singleton set, check if its able to defend itself.
        if(arguments.size() == 1){
            std::set<uint32_t> char_func = characteristicFunction(af, active_arguments, arguments);
            if (std::find(arguments.begin(), arguments.end(), *arguments.begin()) != arguments.end()){
                // The set cannot be reduced and its admissible, therefore it is an initial set.
                return true;
            } else {
                return false;
            }
        }
        //std::cout <<"is initial c > 1 \n";

        /* Check for every pair of arguments a,b in the set arguments, whether arguments\{b} contains an admissible, non-empty set S, 
        that contains a. If such a pair of arguments a,b exist such that arguments\{b} contains a non-empty, admisible set, that 
        contains a, the set cannot be an initial set. 
        */
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