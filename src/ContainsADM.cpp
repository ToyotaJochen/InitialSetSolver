#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool contains_admissible(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments, int arg, SAT_Solver & solver, std::vector<std::vector<uint32_t>> result, bool first){
        std::vector<int32_t> complement_clause;
        complement_clause.resize(arguments.size());
        std::vector<uint32_t> extension;
        extension.resize(arguments.size());
        std::vector<int32_t> assumptions;
        assumptions.resize(arguments.size());
        extension.resize(arguments.size());
        if(arguments.empty()) return false;
        if(std::find(arguments.begin(), arguments.end(), arg) == arguments.end()){
            // for(uint32_t arg : arguments){
            //     complement_clause.push_back(-af.accepted_var(arg));
            // }
            // for(uint32_t arg : active_arguments._array){
            //     if(arguments.contains(arg)){
            //         assumptions.push_back(af.accepted_var(arg));
            //     } else {
            //         assumptions.push_back(-af.accepted_var(arg));
            //     }
            // }
            // for(int32_t as : assumptions){
            //     if(as != 0) solver.assume(as);
            // }
            return false;
        }
        std::set<uint32_t> charFunc = characteristicFunction(af, active_arguments, arguments);
        if(std::includes(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end())){
            // for(uint32_t arg : arguments){
            //     complement_clause.push_back(-af.accepted_var(arg));
            // }
            std::cout << "includes \n";
            for(uint32_t arg : active_arguments._array){
                if(arguments.contains(arg)){
                    assumptions.push_back(af.accepted_var(arg));
                } else {
                    assumptions.push_back(-af.accepted_var(arg));
                }
            }
            for(int32_t as : assumptions){
                if(as != 0) solver.assume(as);
            }
            return true;
        } else {
            std::set<uint32_t> intersection;
            intersection.clear();
            std::set_intersection(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end(),inserter(intersection, intersection.begin()));
            if(intersection.empty()) {
                // if(!first){
                //     for(uint32_t arg : arguments){
                //         complement_clause.push_back(-af.accepted_var(arg));
                //         extension.push_back(arg);
                //     }
                //     solver.add_clause(complement_clause);
                //     result.push_back(extension);
                // }
                return false;
            } else {
                // for(uint32_t arg : arguments){
                //         complement_clause.push_back(-af.accepted_var(arg));
                //         extension.push_back(arg);
                //     }
                // solver.add_clause(complement_clause);
                return contains_admissible(af, active_arguments, intersection, arg, solver, result, false);
            }
        }
    }
}