#include <set>
#include "Algorithms.h"

namespace Algorithms{
    bool contains_admissible(AF & af, const IterableBitSet & active_arguments, std::set<uint32_t> & arguments, int arg, SAT_Solver & solver){
        std::vector<int32_t> complement_clause;
        complement_clause.resize(arguments.size());
        if(arguments.empty()) return false;
        if(std::find(arguments.begin(), arguments.end(), arg) == arguments.end()){
            for(const uint32_t arg: arguments){
                complement_clause.push_back(-af.accepted_var(arg));
            }
            solver.add_clause(complement_clause);
            return false;
        }
        std::set<uint32_t> charFunc = characteristicFunction(af, active_arguments, arguments);
        if(std::includes(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end())){
            for(const uint32_t arg: arguments){
                complement_clause.push_back(-af.accepted_var(arg));
            }
            solver.add_clause(complement_clause);
            return true;
        } else {
            std::set<uint32_t> intersection;
            intersection.clear();
            std::set_intersection(charFunc.begin(), charFunc.end(), arguments.begin(), arguments.end(),inserter(intersection, intersection.begin()));
            if(intersection.empty()) {
                for(const uint32_t arg: arguments){
                    complement_clause.push_back(-af.accepted_var(arg));
                }
                solver.add_clause(complement_clause);
                return false;
            } else {
                for(const uint32_t arg: arguments){
                    complement_clause.push_back(-af.accepted_var(arg));
                }
                solver.add_clause(complement_clause);
                return contains_admissible(af, active_arguments, intersection, arg, solver);
            }
        }
    }
}