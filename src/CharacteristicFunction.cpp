#include <set>
#include "Algorithms.h"

namespace Algorithms{
    std::set<uint32_t> characteristicFunction(AF & af, std::vector<uint32_t> & arguments){
        std::set<uint32_t> charFunc;
        bool attacked = false;
        int arg = 0;
        for(auto it = begin(af.attackers); it != end(af.attackers); ++it){
            arg++;
            for(auto at = begin(*it); at != end(*it); ++at){
                for(auto di = begin(af.attackers[*at]); di != end(af.attackers[*at]); ++di){
                    if (std::find(arguments.begin(), arguments.end(), *di) != arguments.end()){
                        charFunc.insert(arg);
                    }
                }
            }
        }
        return charFunc;
    }
}