#include "AF.h"
#include "SCC.h"

AF::AF() : args(0) {}

void AF::set_arguments(uint32_t n_args) {
	args = n_args;
	attackers.resize(args);
	attacked.resize(args);
}

void AF::add_attack(uint32_t source, uint32_t target) {
	attackers[target].push_back(source);
	attacked[source].push_back(target);
}

int32_t AF::accepted_var(uint32_t arg) {
	return arg+1;
}

int32_t AF::rejected_var(uint32_t arg) {
	return (args + arg + 1);
}

void AF::calc_scc(){
	strongly_connected_components = calculate_scc(attackers);
	scc = true;
}

std::vector<std::vector<uint32_t>> AF::get_components(){
	std::vector<std::vector<uint32_t>> components;
	components.resize(args);
	for(int i = 0; i < strongly_connected_components.size(); i++){
		components[strongly_connected_components[i]].push_back(i);
	}

	return components;
}