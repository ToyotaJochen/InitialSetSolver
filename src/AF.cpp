/*
* The following is largely taken from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
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

// accepted_var corresponds to the index of the inputs (i23)
int32_t AF::accepted_var(uint32_t arg) {
	return arg+1;
}

int32_t AF::rejected_var(uint32_t arg) {
	return (args + arg + 1);
}

int32_t AF::component_var(uint32_t arg){
	return strongly_connected_components[arg];
}

int32_t AF::accepted_min_var(uint32_t arg){
	return(2 * args + arg + 1);
}

int32_t AF::rejected_min_var(uint32_t arg){
	return(3 * args + arg + 1);
}

// int32_t AF::component_var(uint32_t arg){
// 	return strongly_connected_components[arg];
// }

// Calculate the strongly connected components of the AF using Tarjans Algorithm.
void AF::calc_scc(){
	strongly_connected_components = calculate_scc(attackers);
	scc = true;
}

// Returns a Vector containing the components ID of an argument.
std::vector<int32_t> AF::get_components_array(){
	return strongly_connected_components;
}

// Returns a Vector of Vectors that contain all the arguments, that belong to the same component.
std::vector<std::vector<uint32_t>> AF::get_components(){
	std::vector<std::vector<uint32_t>> components;
	components.resize(args);
	for(int i = 0; i < strongly_connected_components.size(); i++){
		components[strongly_connected_components[i]].push_back(i);
	}

	return components;
}