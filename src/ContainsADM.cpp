#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool contains_admissible(AF & af, std::vector<uint32_t> & arguments, int arg){
        if(std::find(arguments.begin(), arguments.end(), arg) == arguments.end()){
            return false;
        }
        std::set<uint32_t> charFunc = characteristicFunction(af, arguments);
        for(auto i : arguments){
            if(std::find(charFunc.begin(), charFunc.end(), i) == charFunc.end()){
                std::vector<uint32_t> def_arguments;
                def_arguments.resize(arguments.size());
                for(auto j: arguments){
                    if(std::find(charFunc.begin(), charFunc.end(), j) != charFunc.end()){
                        def_arguments.push_back(j);
                    }
                }
                return contains_admissible(af, def_arguments, arg);
            }
        }
        return true;
    }
}