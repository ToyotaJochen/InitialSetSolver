#ifndef ENCODINGS_H
#define ENCODINGS_H

#include "AF.h"
#include "IterableBitSet.h"

#include "CadicalSatSolver.h"
typedef CadicalSatSolver SAT_Solver;

namespace Encodings {
    void admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void admissible_nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void initial(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);

    void add_rejected(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_conflict_free(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_admissible(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    void add_admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver);
    

}
 #endif