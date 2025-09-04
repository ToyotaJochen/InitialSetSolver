#include <set>
#include "Algorithms.h"

namespace Algorithms{
    std::set<uint32_t> characteristicFunction(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments){
        std::set<uint32_t> charFunc;
        uint32_t counter;

        // for(uint32_t a : arguments){
        //     // argument is unsattacked
        //     if(af.attackers[a].empty()){
        //         charFunc.insert(active_arguments._array[a]);
        //         //std::cout << "non-attacked argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
        //     } else {
        //         std::vector<uint32_t> attackers_of_a = af.attackers[a];
        //         counter = 0;
        //         // iterate over the attackers of argument a
        //         for(uint32_t b : attackers_of_a){
        //             std::vector<uint32_t> attackers_of_b = af.attackers[b];
        //             // iterate over the attackers of argument b and check if they are present in the set
        //             for(uint32_t c : attackers_of_b){
        //                 if(arguments.contains(c)){
        //                     counter++;
        //                     break;
        //                 }
        //             }
        //             // check if every attacker of b is defended by the set
        //             if(counter == af.attackers[a].size()){
        //                 if(!charFunc.contains(active_arguments._array[a])){
        //                     charFunc.insert(active_arguments._array[a]);
        //                     //std::cout << "argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
        //                 }
        //             }
        //         }
        //     }
        // }

        for(uint32_t a = 0; a < active_arguments._array.size(); a++){
            // argument is unsattacked
            if(af.attackers[a].empty()){
                charFunc.insert(active_arguments._array[a]);
                std::cout << "non-attacked argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
            } else {
                std::vector<uint32_t> attackers_of_a = af.attackers[a];
                counter = 0;
                // iterate over the attackers of argument a
                for(uint32_t b : attackers_of_a){
                    std::vector<uint32_t> attackers_of_b = af.attackers[b];
                    // iterate over the attackers of argument b and check if they are present in the set
                    for(uint32_t c : attackers_of_b){
                        if(arguments.contains(c)){
                            counter++;
                            break;
                        }
                    }
                    // check if every attacker of b is defended by the set
                    if(counter == af.attackers[a].size()){
                        if(!charFunc.contains(active_arguments._array[a])){
                            charFunc.insert(active_arguments._array[a]);
                            std::cout << "argument " << af.accepted_var(active_arguments._array[a]) << " added to D_F \n";
                        }
                    }
                }
            }
        }
        return charFunc;
    }
}