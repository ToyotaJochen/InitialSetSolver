/*
* The following is taken from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#include <fstream>
#include <sstream>

#include "IterableBitSet.h"
#include "AF.h"
#include "Parse.h"


IterableBitSet parse_i23(AF* aaf, std::string file) {
    std::ifstream input;
	input.open(file);

	if (!input.good()) {
		std::cerr << file << ": Cannot open input file\n";
		exit(1);
	}

	std::vector<uint32_t> active_array;
	std::vector<uint8_t> active_bitset;
	std::string line;
    uint32_t n_args, source, target;
		
    while (!input.eof()) {
        getline(input, line);
        if (line.length() == 0 || line[0] == '#') continue;
        std::istringstream iss(line);
        if (line[0] == 'p') {
            std::string p, af;
            iss >> p >> af >> n_args;
            active_bitset.resize(n_args, true);
            active_array.reserve(n_args);
            aaf->set_arguments(n_args);
            for (int i = 1; i <= n_args; i++) {
                active_array.push_back(i-1);
            }
        } else {
            iss >> source >> target;
            aaf->add_attack(source-1, target-1); // vector index startet bei 0!
        }
    }
    input.close();

    return IterableBitSet(active_array, active_bitset);
}