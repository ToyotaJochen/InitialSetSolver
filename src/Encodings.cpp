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
		//std::vector<std::vector<uint32_t>> components = af.get_components();
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

			// SCC
			int scc_id = af.strongly_connected_components[i];
			for (size_t c = 0; c < active_arguments._array.size(); c++) {
				if(af.strongly_connected_components[active_arguments._array[c]] != scc_id){
					solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.accepted_var(active_arguments._array[c]));
					//std::cout << "SCC clause: " << -af.accepted_var(active_arguments._array[i]) << ", " << af.rejected_var(active_arguments._array[c]) << std::endl;
					//std::cout << solver.check() << "\n";
				}
			}

			// std::cout << "OUT CLAUSE: \n";
			// for(auto c : out_clause){
			// 	std::cout << c << "\n";
			// }
			//std::cout << solver.check() << "\n";

		}
		// std::cout << "non_empt CLAUSE: \n";
		// 	for(auto c : non_empty_clause){
		// 		std::cout << c << "\n";
		// 	}
		solver.add_clause(non_empty_clause);
		// std::cout << "Non empty clause: " << solver.check() << "\n";
		// std::cout << solver.check() << "\n";
	}

	// Niskanen, A.
	// Encodings from Mu-Toksia Solver
	
	// void add_rejected(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		solver.add_clause_2(-af.rejected_var(i), -af.accepted_var(i));

	// 	}
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		for(size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++){
	// 			solver.add_clause_2(af.rejected_var(active_arguments._array[i]), -af.accepted_var(af.attackers[active_arguments._array[i]][j]));
	// 		}
	// 	}
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		std::vector<int> clause = {-af.rejected_var(active_arguments._array[i])};
	// 		for(size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++){
	// 			clause.push_back(af.accepted_var(af.attackers[active_arguments._array[i]][j]));
	// 		}
	// 		solver.add_clause(clause);
	// 	}
	// }

	// void add_conflict_free(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		for(size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++){
	// 			if(active_arguments._array[i] != af.attackers[active_arguments._array[i]][j]){
	// 				std::vector<int> clause = {-af.accepted_var(active_arguments._array[i]), -af.accepted_var(af.attackers[active_arguments._array[i]][j])};
					
	// 				solver.add_clause(clause);
	// 			} else {
	// 				std::vector<int> clause = {-af.accepted_var(active_arguments._array[i])};
	// 				solver.add_clause(clause);
	// 			}
	// 		}
	// 	}
	// }

	// void add_admissible(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
	// 	add_rejected(af, active_arguments, solver);
	// 	add_conflict_free(af, active_arguments, solver);
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		for(size_t j = 0; j < af.attackers[active_arguments._array[i]].size(); j++){
	// 			std::vector<int> clause = {-af.accepted_var(active_arguments._array[i]), af.rejected_var(af.attackers[active_arguments._array[i]][j])};
	// 			solver.add_clause(clause);
	// 		}
	// 	}

	// }

	// void add_admissible_nonempty(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
	// 	add_admissible(af, active_arguments, solver);
	// 	std::vector<int> clause(active_arguments._array.size());
	// 	for(size_t i = 0; i < active_arguments._array.size(); i++ ){
	// 		clause[i] = af.accepted_var(active_arguments._array[i]);
	// 	}
	// 	solver.add_clause(clause);
	// }


}