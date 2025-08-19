#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool contains_admissible(AF & af, IterableBitSet active_arguments, std::set<uint32_t> & arguments, int arg){
        if(std::find(arguments.begin(), arguments.end(), arg) == arguments.end()){
            return false;
        }
        std::set<uint32_t> charFunc = characteristicFunction(af, active_arguments, arguments);
        if(std::includes(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end())){
            return true;
        } else {
            std::set<uint32_t> intersection;
            intersection.clear();
            std::set_intersection(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end(),inserter(intersection, intersection.begin()));
            if(intersection.empty()) {
                return false;
            } else {
                return contains_admissible(af, active_arguments, arguments, arg);
            }
        }
    }
}