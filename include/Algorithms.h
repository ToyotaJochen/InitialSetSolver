#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Encodings.h"


namespace Algorithms {
    std::vector<std::vector<uint32_t>> enumerate_initial(AF & af, const IterableBitSet & active_arguments);
    std::vector<std::vector<uint32_t>> characteristicFunction(AF & af, std::vector<uint32_t> & arguments);
    bool contains_admissible(AF & af, std::vector<uint32_t> & arguments);
    bool is_initial(AF & af, std::vector<uint32_t> & arguments);
}

#endif