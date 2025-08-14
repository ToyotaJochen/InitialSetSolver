#ifndef AF_H
#define AF_H

#include <iostream>
#include <vector>
#include <cstdint>     		// uncomment if boostlibs are not installed

#include "SCC.h"

class AF {
public:

AF();
bool scc = false;
uint32_t args;
std::vector<std::vector<uint32_t>> attackers;
std::vector<std::vector<uint32_t>> attacked;
std::vector<int32_t> strongly_connected_components;

int32_t accepted_var(uint32_t arg);
int32_t rejected_var(uint32_t arg);
int32_t component_var(uint32_t arg);
int32_t accepted_min_var(uint32_t arg);
int32_t rejected_min_var(uint32_t arg);
std::vector<int32_t> get_components_array();

void set_arguments(uint32_t n_args);
void add_attack(uint32_t source, uint32_t target);

void calc_scc();
std::vector<std::vector<uint32_t>>  get_components();

};

namespace std {
	inline void print_extension(const AF & af, const std::vector<uint32_t> & extension) {
		std::cout << "[";
		for (size_t i = 0; i < extension.size(); i++) {
			std::cout << extension[i]+1;
			if (i != extension.size()-1) std::cout << ",";
		}
		std::cout << "]";
  	}

  	inline void print_sequence(const AF & af, std::vector<std::vector<uint32_t> > sequence) {
		std::cout << "(";
		for (size_t i = 0; i < sequence.size(); i++) {
			print_extension(af, sequence[i]);
			if (i != sequence.size()-1) std::cout << ",";
		}
		std::cout << ")";
  	}
}

#endif