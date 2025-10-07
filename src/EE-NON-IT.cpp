/*
* The following is taken in part from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#include "Algorithms.h"

namespace Algorithms{
    /* This method implements the non-iterative calculation off all initial sets. */
    std::vector<std::vector<uint32_t>> enumerate_initial_non_it(AF & af, const IterableBitSet & active_arguments){
        if (active_arguments._array.empty()) {
            return {};
        }
        std::vector<std::vector<uint32_t>> result;
        std::vector<uint32_t> extension;
        std::vector<int32_t> complement_clause;
        complement_clause.reserve(active_arguments._array.size());
        std::vector<int32_t> min_complement_clause;
        min_complement_clause.reserve(active_arguments._array.size());

        // Create encoding for non-empty admissible sets
        SAT_Solver solver = SAT_Solver(af.args);
        Encodings::admissible_nonempty_scc(af, active_arguments, solver);

        while(true){
            int sat = solver.solve();
            if(sat == UNSAT_V){
                break;
            }
            SAT_Solver min_solver = SAT_Solver(af.args);
            complement_clause.clear();
            complement_clause.reserve(active_arguments._array.size());
            for (const uint32_t arg : active_arguments._array) {
                if (solver.model[arg]) {
                    complement_clause.push_back(-af.accepted_var(arg));
                } else {
                    min_solver.assume(-af.accepted_var(arg));
                }
            }
            solver.add_clause(complement_clause);
            
            Encodings::admissible_nonempty(af, active_arguments, min_solver);
            min_solver.add_clause(complement_clause);
            int sat_min = min_solver.solve();
            if(sat_min == UNSAT_V){
                extension.clear();
                extension.reserve(active_arguments._array.size());
                for(const uint32_t & arg : active_arguments._array) {
                    if (solver.model[arg]) {
                        extension.push_back(arg);
                    }
                }
                result.push_back(extension);
            }
        }
        return result;
    }
}
