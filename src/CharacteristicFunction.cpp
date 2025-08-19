#include <set>
#include "Algorithms.h"

namespace Algorithms{
    std::set<uint32_t> characteristicFunction(AF & af, IterableBitSet active_arguments, std::set<uint32_t> & arguments){
        std::set<uint32_t> charFunc;
        for(size_t i = 0; i < active_arguments._array.size(); i++){
            for(size_t j = 0; j < af.attackers[i].size(); j++){
                for(size_t k = 0; k < af.attacked[j].size(); k++){
                    if(arguments.contains(af.attacked[j][k]))
                        charFunc.insert(active_arguments._array[i]);
                }
            }
        }
        return charFunc;
    }
}