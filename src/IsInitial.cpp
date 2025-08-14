#include <algorithm>
#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool is_initial(AF & af, std::set<uint32_t> & arguments){
        if(arguments.size() == 1){
            std::set<uint32_t> char_func = characteristicFunction(af, arguments);
            if (includes(arguments.begin(), arguments.end(), char_func.begin(), char_func.end())){
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
                    std::cout << "entering contains \n";
                    if(contains_admissible(af, candidate, a)){
                        return false;
                    }
                    std::cout << "left contains \n";
                }
            }
        }
        return true;
    }
}