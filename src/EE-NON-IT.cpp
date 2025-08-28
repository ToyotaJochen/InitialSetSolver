#include "Algorithms.h"

namespace Algorithms{
    std::vector<std::vector<uint32_t>> enumerate_initial_non_it(AF & af, const IterableBitSet & active_arguments){
        if (active_arguments._array.empty()) {
            return {};
        }
        std::vector<std::vector<uint32_t>> result;
        std::vector<uint32_t> extension;
        //std::vector<int32_t> complement_clause;
        //complement_clause.reserve(active_arguments._array.size());
        std::vector<int32_t> minimization_clause;
        minimization_clause.reserve(active_arguments._array.size());

        // Create encoding for non-empty admissible sets
        SAT_Solver solver = SAT_Solver(af.args);
        Encodings::min(af, active_arguments, solver);

        while(true){
            int sat = solver.solve();
            if(sat == UNSAT_V){
                break;
            }

            
        }
        return result;
    }
}