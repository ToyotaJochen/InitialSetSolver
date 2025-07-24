#ifndef SCC_H
#define SCC_H

#include <iostream>
#include <vector>
#include "AF.h"

class SCC {
    public:

    uint32_t num_components;
    uint32_t num_vertices;

    std::vector< uint32_t > scc;

    SCC();

    void calc_scc(AF aaf);


};

#endif