#include "Algorithms.h"

namespace Algorithms{
    std::vector<std::vector<uint32_t>> enumerate_procedural(AF & af, const IterableBitSet & active_arguments){
        if (active_arguments._array.empty()) {
            return {};
        }

        //std::vector<int32_t> complement_clause;
        //complement_clause.reserve(active_arguments._array.size());
        std::vector<std::vector<uint32_t>> result;
        std::vector<uint32_t> extension;
        SAT_Solver solver = SAT_Solver(af.args);
        Encodings::admissible_nonempty(af, active_arguments, solver);

         while (true) { // iteratively compute models for the encoding
            int sat = solver.solve();
            if (sat == UNSAT_V) break;

            std::set<uint32_t> candidate;
            for (const uint32_t arg : active_arguments._array) {
                if (solver.model[arg]) {
                        candidate.insert(arg);
                }
            }

            if(is_initial(af, candidate)){ 
                extension.clear();
                extension.reserve(active_arguments._array.size());
                //complement_clause.clear();
                //complement_clause.reserve(active_arguments._array.size());
                for(const uint32_t & arg : active_arguments._array) {
                    if (solver.model[arg]) {
                        extension.push_back(arg);
                        //complement_clause.push_back(-af.accepted_var(arg));
                    }
                }
                result.push_back(extension);
                //solver.add_clause(complement_clause);
            } else {
                break;
            }
            
        }
        return result;
    }
}