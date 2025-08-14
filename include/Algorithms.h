#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <set>
#include "Encodings.h"


namespace Algorithms {
    std::vector<std::vector<uint32_t>> enumerate_initial(AF & af, const IterableBitSet & active_arguments);
    std::set<uint32_t> characteristicFunction(AF & af, std::set<uint32_t> & arguments);
    bool contains_admissible(AF & af, std::set<uint32_t> & arguments, int arg);
    bool is_initial(AF & af, std::set<uint32_t> & arguments);
    std::vector<std::vector<uint32_t>> enumerate_initial_scc(AF & af, const IterableBitSet & active_arguments);
    std::vector<std::vector<uint32_t>> enumerate_initial_non_it(AF & af, const IterableBitSet & active_arguments);
    std::vector<std::vector<uint32_t>> enumerate_procedural(AF & af, const IterableBitSet & active_arguments);
}

#endif