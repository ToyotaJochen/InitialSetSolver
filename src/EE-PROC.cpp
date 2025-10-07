/*
* The following is taken in part from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#include "Algorithms.h"

namespace Algorithms{
    /* This method implements the calculation off all initial sets, using the procedural test to check if a set is minimal*/
    std::vector<std::vector<uint32_t>> enumerate_procedural(AF & af, const IterableBitSet & active_arguments){
        if (active_arguments._array.empty()) {
            return {};
        }
        std::vector<int32_t> complement_clause;
        complement_clause.reserve(active_arguments._array.size());
        std::set<uint32_t> candidate;
        std::vector<std::vector<uint32_t>> result;
        std::vector<uint32_t> extension;
        SAT_Solver solver = SAT_Solver(af.args);
        // Create encoding for non-empty admissible sets, that lie in the same SCC in the graph.
        Encodings::admissible_nonempty_scc(af, active_arguments, solver);
        int m_count = 0;
        while (true){
            candidate.clear();
            complement_clause.clear();
            complement_clause.reserve(af.args);
            int sat = solver.solve();
            if(sat == UNSAT_V){
                //std::cout << m_count << "\n";
                break;
            } else {
                //std::cout << m_count++ << "\n";
                for (const uint32_t arg : active_arguments._array) {
                    if (solver.model[arg]) {
                        complement_clause.push_back(-af.accepted_var(arg));
                        candidate.insert(arg);
                        // std::cout << af.accepted_var(arg) << ", ";
                    }
                }
                
                // std::cout << "\n";

                // Check whether the set is initial via the procedural test.
                if(is_initial(af, active_arguments, candidate, solver, result)){
                    extension.clear();
                    extension.reserve(active_arguments._array.size());
                    for(const uint32_t arg: active_arguments._array){
                        if(candidate.contains(arg)){
                            extension.push_back(arg);
                        }

                    }
                    solver.add_clause(complement_clause);
                    result.push_back(extension);
                }
            }
        }
        

        return result;
    }
}