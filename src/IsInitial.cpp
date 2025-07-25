#include <algorithm>
#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool is_initial(AF & af, std::vector<uint32_t> & arguments){
        if(arguments.size() == 1){
            std::set<uint32_t> char_func = characteristicFunction(af, arguments);
            if (std::find(arguments.begin(), arguments.end(), arguments[0]) != arguments.end()){
                return true;
            } else {
                return false;
            }
        }

        for(auto a : arguments){
            for(auto b: arguments){
                if(a != b){
                    std::set<uint32_t> candidate;
                    for (auto c : arguments){
                        if(c != b){
                            candidate.insert(c);
                        }
                    }
                    if(Algorithms::contains_admissible(af, candidate, a)){
                        return false;
                    }
                }
            }
        }
        return true;
    }
}