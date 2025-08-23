#include <set>
#include "Algorithms.h"

namespace Algorithms{
    // std::set<uint32_t> characteristicFunction(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments){
    //     std::set<uint32_t> charFunc;
    //     for(size_t i = 0; i < active_arguments._array.size(); i++){
    //         if(af.attackers[i].empty()){
    //             charFunc.insert(active_arguments._array[i]);
    //             //std::cout << "argument " << af.accepted_var(active_arguments._array[i]) << " added to D_F \n";
    //         } else {
    //             for(size_t j = 0; j < af.attackers[i].size(); j++){
    //                 for(size_t k = 0; k < af.attacked[j].size(); k++){
    //                     if(arguments.contains(af.attackers[j][k])){ // hier gehts falsch
    //                         if(!charFunc.contains(active_arguments._array[i])){
    //                             charFunc.insert(active_arguments._array[i]);
    //                             std::cout << "argument " << af.accepted_var(active_arguments._array[i]) << " added to D_F \n";
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     return charFunc;
    // }

    std::set<uint32_t> characteristicFunction(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments){
        std::set<uint32_t> charFunc;
        uint32_t counter;
        
        for(uint32_t a = 0; a < active_arguments._array.size(); a++){
            if(af.attackers[a].empty()){
                charFunc.insert(active_arguments._array[a]);
                //std::cout << "non-attacked argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
            } else {
                std::vector<uint32_t> attackers_of_a = af.attackers[a];
                counter = 0;
                for(uint32_t b : attackers_of_a){
                    std::vector<uint32_t> attackers_of_b = af.attackers[b];
                    for(uint32_t c : attackers_of_b){
                        if(arguments.contains(c)){
                            counter++;
                            break;
                        }
                    }
                    if(counter == af.attackers[a].size()){
                        if(!charFunc.contains(active_arguments._array[a])){
                            charFunc.insert(active_arguments._array[a]);
                            //std::cout << "argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
                        }
                    }
                }
            }
        }
        return charFunc;
    }
}