#ifndef ENCODINGS_H
#define ENCODINGS_H

#include "AF.h"
#include "IterableBitSet.h"

#include "CadicalSatSolver.h"
typedef CadicalSatSolver SAT_Solver;

namespace Encodings {
    void admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void admissible_nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void min(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver);
    void and_bin_clause_tseitin(AF & af, uint32_t a, uint32_t b, bool la, bool lb, SAT_Solver & solver);
    void or_bin_clause_tseitin(AF & af, uint32_t a, uint32_t b, bool la, bool lb, SAT_Solver & solver);
    void not_nonempty_adm(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver);

    
    void nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void admissible_nonempty_vec(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver);
    void add_rejected(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_conflict_free(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_admissible(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);

    

}
 #endif