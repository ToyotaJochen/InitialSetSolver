#include "Algorithms.h"

namespace Algorithms{
    std::vector<std::vector<uint32_t>> enumerate_procedural(AF & af, const IterableBitSet & active_arguments){
        if (active_arguments._array.empty()) {
            return {};
        }

        std::vector<int32_t> complement_clause;
        complement_clause.reserve(active_arguments._array.size());
        std::vector<std::vector<uint32_t>> result;
        std::vector<uint32_t> extension;
        SAT_Solver solver = SAT_Solver(af.args);
        Encodings::admissible_nonempty_scc(af, active_arguments, solver);

         while (true) { // iteratively compute models for the encoding
            int sat = solver.solve();
            //std::cout << sat << "\n";
            if (sat == UNSAT_V) break;

            extension.clear();
            extension.reserve(active_arguments._array.size());
            complement_clause.clear();
            complement_clause.reserve(active_arguments._array.size());
            for(const uint32_t & arg : active_arguments._array) {
                if (solver.model[arg]) {
                    extension.push_back(arg);
                    complement_clause.push_back(-af.accepted_var(arg));
                }
            }
            result.push_back(extension);
            solver.add_clause(complement_clause);


            // std::set<uint32_t> candidate;
            // for (const uint32_t arg : active_arguments._array) {
            //     if (solver.model[arg]) {
            //             candidate.insert(arg);
            //     }
            // }
            // bool initial = is_initial(af, active_arguments, candidate);
            // std::cout << initial;

            // if(initial){ 
            //     extension.clear();
            //     extension.reserve(active_arguments._array.size());
            //     complement_clause.clear();
            //     complement_clause.reserve(active_arguments._array.size());
            //     for(const uint32_t & arg : active_arguments._array) {
            //         if (solver.model[arg]) {
            //             extension.push_back(arg);
            //             complement_clause.push_back(-af.accepted_var(arg));
            //         }
            //     }
            //     result.push_back(extension);
            //     solver.add_clause(complement_clause);
            //     print_extension(af, extension);
            //     break;
            // }


        }
        return result;
    }
}