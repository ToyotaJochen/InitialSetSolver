#include "Algorithms.h"

namespace Algorithms{
    // std::vector<std::vector<uint32_t>> enumerate_initial_non_it(AF & af, const IterableBitSet & active_arguments){
    //     if (active_arguments._array.empty()) {
    //         return {};
    //     }
    //     std::vector<std::vector<uint32_t>> result;
    //     std::vector<uint32_t> extension;
    //     //std::vector<int32_t> complement_clause;
    //     //complement_clause.reserve(active_arguments._array.size());
    //     std::vector<int32_t> complement_clause;
    //     complement_clause.reserve(active_arguments._array.size());
    //     std::vector<int32_t> min_complement_clause;
    //     min_complement_clause.reserve(active_arguments._array.size());


    //     // Create encoding for non-empty admissible sets
    //     SAT_Solver solver = SAT_Solver(af.args);
    //     Encodings::admissible_nonempty_scc(af, active_arguments, solver);

    //     SAT_Solver min_solver = SAT_Solver(af.args);
    //     std::vector<uint32_t> min_args;
        
        
    //     while(true){
    //         int sat = solver.solve();
    //         if(sat == UNSAT_V){
    //             break;
    //         }
    //         complement_clause.clear();
    //         complement_clause.reserve(active_arguments._array.size());
    //         min_complement_clause.clear();
    //         min_complement_clause.reserve(active_arguments._array.size());
    //         min_args.clear();
    //         min_args.reserve(af.args);
    //         for (const uint32_t arg : active_arguments._array) {
    //             if (solver.model[arg]) {
    //                 complement_clause.push_back(-af.accepted_var(arg));
    //                 min_args.push_back(arg);
    //             }
    //         }
    //         solver.add_clause(complement_clause);

    //         std::vector<uint32_t> sub_clause;
    //         sub_clause.reserve(min_args.size());
    //         if(min_args.size() > 1){
    //             for(const uint32_t a : min_args){
    //                 for(const uint32_t b: min_args){
    //                     if(b != a){
    //                         sub_clause.push_back(b);
    //                     }
    //                 }
    //                 Encodings::not_nonempty_adm(af, sub_clause, solver);
    //             }
    //         }
    //         int sat_min = min_solver.solve();
    //         if(sat_min == UNSAT_V){
    //             for(const uint32_t arg : sub_clause){
    //                 min_complement_clause.push_back(-af.accepted_min_var(arg));
    //             }
    //         } else {
    //             extension.clear();
    //             extension.reserve(active_arguments._array.size());
    //             for(const uint32_t & arg : active_arguments._array) {
    //                 if (solver.model[arg]) { // hier muss noch die methode für das model vom sat solver auf min vars erweitert werden!
    //                     extension.push_back(arg);
    //                     min_complement_clause.push_back(-af.accepted_min_var(arg));
    //                 }
    //             }
    //         }
    //         solver.add_clause(min_complement_clause);
    //     }
    //     return result;
    // }


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
