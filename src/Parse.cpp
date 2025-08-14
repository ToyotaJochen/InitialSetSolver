#include <fstream>
#include <sstream>

#include "IterableBitSet.h"
#include "AF.h"
#include "Parse.h"

// The arguments of an AF with n arguments are indexed consecutively with positive 
// integers from 1 to n. The first line of the input file is the unique "p-line" of the form

// p af <n>

// where <n> is the number of arguments n, ending with the newline character. An attack a → b, 
// where a has index i and b has index j, is expressed as the line

// i j

// ending with the newline character. In addition to the p-line and lines expressing attacks, 
// lines starting with the '#' character are allowed. These lines are interpreted as comment lines 
// unrelated to the syntax of the input AF, and end with the newline character. No other lines are allowed.

// Example. 
// The AF with five arguments a,b,c,d,e and attacks a → b, b → d, d → e, e → d, e → e is specified as follows, 
// assuming the indexing a=1, b=2, c=3, d=4, e=5 :

// p af 5
// # this is a comment
// 1 2
// 2 4
// 4 5
// 5 4
// 5 5

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