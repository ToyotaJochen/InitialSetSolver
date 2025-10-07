/*
* The following is largely taken from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#include "Encodings.h"

namespace Encodings {
	void admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver) {
		std::vector<int32_t> non_empty_clause(active_arguments._array.size());
		std::vector<int32_t> out_clause;
		for (size_t i = 0; i < active_arguments._array.size(); i++) {
			non_empty_clause[i] = af.accepted_var(active_arguments._array[i]);
			solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.rejected_var(active_arguments._array[i]));

			out_clause.clear();
			out_clause.reserve(af.attackers[active_arguments._array[i]].size()+1);
			for (size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++) {
				if (active_arguments._bitset[af.attackers[active_arguments._array[i]][j]]) {
					solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), af.rejected_var(af.attackers[active_arguments._array[i]][j]));
					out_clause.push_back(af.accepted_var(af.attackers[active_arguments._array[i]][j]));
				}
			}
			out_clause.push_back(-af.rejected_var(active_arguments._array[i]));
			solver.add_clause(out_clause);
		}
		solver.add_clause(non_empty_clause);
	}

	void admissible_nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver) {
		std::vector<int32_t> non_empty_clause(active_arguments._array.size());
		std::vector<int32_t> out_clause;
		std::vector<uint8_t> scc_processed_args_bitset;
		scc_processed_args_bitset.resize(active_arguments._array.size(), false);

		for (size_t i = 0; i < active_arguments._array.size(); i++) {
			non_empty_clause[i] = af.accepted_var(active_arguments._array[i]);

			// rej_1
			solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.rejected_var(active_arguments._array[i]));

		    out_clause.clear();
			out_clause.reserve(af.attackers[active_arguments._array[i]].size()+1);
		    for (size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++) {
			 	if (active_arguments._bitset[af.attackers[active_arguments._array[i]][j]]) {
					// adm
			 		solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), af.rejected_var(af.attackers[active_arguments._array[i]][j]));
			 		// rej_3
					out_clause.push_back(af.accepted_var(af.attackers[active_arguments._array[i]][j]));
			 	}
			}

			// rej_3
			out_clause.push_back(-af.rejected_var(active_arguments._array[i]));
			solver.add_clause(out_clause);

			// Add SCC encodings
			int scc_id = af.strongly_connected_components[i];
			for (size_t c = 0; c < active_arguments._array.size(); c++) {
				if(af.strongly_connected_components[active_arguments._array[c]] != scc_id){
					// Only add clauses if argument c was not already processed, otherwise every clause will be added twice.
					if(!scc_processed_args_bitset[active_arguments._array[c]]){	
						solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.accepted_var(active_arguments._array[c]));
					}
				}
			}
			scc_processed_args_bitset[i] = true;
		}
		solver.add_clause(non_empty_clause);
	}

	
	// Add non-empty, SCC encodings
	void nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
		std::vector<int32_t> non_empty_clause(active_arguments._array.size());
		std::vector<int32_t> scc_in_clause;
		std::vector<int32_t> scc_out_clause;
		for (size_t i = 0; i < active_arguments._array.size(); i++) {
			non_empty_clause[i] = af.accepted_var(active_arguments._array[i]);
			int scc_id = af.strongly_connected_components[i];
			for (size_t c = 0; c < active_arguments._array.size(); c++) {
				if(af.strongly_connected_components[active_arguments._array[c]] != scc_id){
					solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.accepted_var(active_arguments._array[c]));
					//std::cout << "SCC clause: " << -af.accepted_var(active_arguments._array[i]) << ", " << af.rejected_var(active_arguments._array[c]) << "\n";
					//std::cout << solver.check() << "\n";
				}
			}
		}
		solver.add_clause(non_empty_clause);
		
	}


}