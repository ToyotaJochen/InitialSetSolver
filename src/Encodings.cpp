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

			// SCC
			int scc_id = af.strongly_connected_components[i];
			for (size_t c = 0; c < active_arguments._array.size(); c++) {
				if(af.strongly_connected_components[active_arguments._array[c]] != scc_id){
					// only add clauses if argument c was not already processed, otherwise every clause will added twice.
					if(!scc_processed_args_bitset[active_arguments._array[c]]){	
						solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.accepted_var(active_arguments._array[c]));
					}
				}
			}
			scc_processed_args_bitset[i] = true;
		}
		solver.add_clause(non_empty_clause);
	}

	

	// void nonempty_scc(AF & af, const IterableBitSet & active_arguments, SAT_Solver & solver){
	// 	std::vector<int32_t> non_empty_clause(active_arguments._array.size());
	// 	std::vector<int32_t> scc_in_clause;
	// 	std::vector<int32_t> scc_out_clause;
	// 	for (size_t i = 0; i < active_arguments._array.size(); i++) {
	// 		non_empty_clause[i] = af.accepted_var(active_arguments._array[i]);
	// 		int scc_id = af.strongly_connected_components[i];
	// 		for (size_t c = 0; c < active_arguments._array.size(); c++) {
	// 			if(af.strongly_connected_components[active_arguments._array[c]] != scc_id){
	// 				solver.add_clause_2(-af.accepted_var(active_arguments._array[i]), -af.accepted_var(active_arguments._array[c]));
	// 				//std::cout << "SCC clause: " << -af.accepted_var(active_arguments._array[i]) << ", " << af.rejected_var(active_arguments._array[c]) << "\n";
	// 				//std::cout << solver.check() << "\n";
	// 			}
	// 		}
	// 	}
	// 	solver.add_clause(non_empty_clause);
		
	// }

	// adding nonempty admissible clauses for a subset of arguments
	void admissible_nonempty_vec(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver) {
		std::vector<int32_t> non_empty_clause(active_arguments.size());
		std::vector<int32_t> out_clause;
		for (size_t i = 0; i < active_arguments.size(); i++) {
			non_empty_clause[i] = af.accepted_min_var(active_arguments[i]);
			solver.add_clause_2(-af.accepted_min_var(active_arguments[i]), -af.rejected_min_var(active_arguments[i]));

			out_clause.clear();
			out_clause.reserve(af.attackers[active_arguments[i]].size()+1);
			for (size_t j = 0; j < af.attackers[active_arguments[i]].size(); j++) {
				solver.add_clause_2(-af.accepted_min_var(active_arguments[i]), af.rejected_min_var(af.attackers[active_arguments[i]][j]));
				out_clause.push_back(af.accepted_min_var(af.attackers[active_arguments[i]][j]));	
			}
			out_clause.push_back(-af.rejected_min_var(active_arguments[i]));
			solver.add_clause(out_clause);
		}
		solver.add_clause(non_empty_clause);
	}

	void min(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver){
		Encodings::admissible_nonempty_vec(af, active_arguments, solver);
		for(uint32_t a : active_arguments){
			for(uint32_t b : active_arguments){
				if(a != b){
					solver.add_clause_2(-af.accepted_min_var(a), -af.accepted_min_var(b));
				}
			}
		}
					
	}

	void and_bin_clause_tseitin(AF & af, uint32_t a, uint32_t b, bool la, bool lb, SAT_Solver & solver, std::vector<int64_t> tseitin_vars){
		int64_t tseitin_var = af.current_tseitin_var();
		tseitin_vars.push_back(tseitin_var);
		if(la && lb){
			solver.add_clause_3(-a,-b,tseitin_var);
			solver.add_clause_2(a,-tseitin_var);
			solver.add_clause_2(b,-tseitin_var);
		} else {
			if(!la && lb){
				solver.add_clause_3(a,-b,tseitin_var);
				solver.add_clause_2(-a,-tseitin_var);
				solver.add_clause_2(b,-tseitin_var);
			} else { 
				if(la && !lb){
					solver.add_clause_3(-a,b,tseitin_var);
					solver.add_clause_2(a,-tseitin_var);
					solver.add_clause_2(-b,-tseitin_var);
				} else {
					solver.add_clause_3(-a,b,tseitin_var);
					solver.add_clause_2(a,-tseitin_var);
					solver.add_clause_2(-b,-tseitin_var);
				}
			}
		}
	}

	void or_bin_clause_tseitin(AF & af, uint32_t a, uint32_t b, bool la, bool lb, SAT_Solver & solver, std::vector<int64_t> tseitin_vars){
		int64_t tseitin_var = af.current_tseitin_var();
		tseitin_vars.push_back(tseitin_var);
		if(la && lb){
			solver.add_clause_3(a,b,-tseitin_var);
			solver.add_clause_2(-a,tseitin_var);
			solver.add_clause_2(-b,tseitin_var);
		} else {
			if(!la && lb){
				solver.add_clause_3(-a,b,-tseitin_var);
				solver.add_clause_2(a,tseitin_var);
				solver.add_clause_2(-b,tseitin_var);
			} else { 
				if(la && !lb){
					solver.add_clause_3(a,-b,-tseitin_var);
					solver.add_clause_2(-a,tseitin_var);
					solver.add_clause_2(b,tseitin_var);
				} else {
					solver.add_clause_3(-a,-b,tseitin_var);
					solver.add_clause_2(a,-tseitin_var);
					solver.add_clause_2(b,-tseitin_var);
				}
			}
		}
	}

	int64_t or_clause_tseitin(AF & af, SAT_Solver solver, std::vector<int64_t> tseitin_vars){
		int64_t current_tseitin_var = af.current_tseitin_var();
		// tseitin_vars.push_back(current_tseitin_var);
		std::vector<int64_t> t_clause;
		t_clause.reserve(tseitin_vars.size()- 1);
		for(int64_t t = 0; t < tseitin_vars.size() - 2; t++){
			solver.add_clause_2(-tseitin_vars[t], current_tseitin_var);
			t_clause.push_back(tseitin_vars[t]);
		}
		t_clause.push_back(-current_tseitin_var);
		solver.add_clause(t_clause);
		return current_tseitin_var;
	}
	

	void not_nonempty_adm(AF & af, const std::vector<uint32_t> & active_arguments, SAT_Solver & solver){
		// 
		std::vector<int64_t> tseitin_vars_A;
		// tseitin_vars.reserve(af.args);
		for (size_t i = 0; i < active_arguments.size(); i++) {
		    for (size_t j = 0; j < af.attackers[active_arguments[i]].size(); j++) {
				and_bin_clause_tseitin(af, af.accepted_min_var(active_arguments[i]), af.rejected_min_var(af.attackers[active_arguments[i]][j]), true, false, solver, tseitin_vars_A);
			}
		}
		int64_t tseitin_var_A = or_clause_tseitin(af, solver, tseitin_vars_A);

		std::vector<std::vector<int64_t>> out_clauses;
		std::vector<int64_t> out_clause;
		for (size_t i = 0; i < active_arguments.size(); i++) {
			out_clause.clear();
			out_clause.push_back(af.rejected_min_var(active_arguments[i]));
		    for (size_t j = 0; j < af.attackers[active_arguments[i]].size(); j++) {
				out_clause.push_back(-af.accepted_min_var(af.attackers[active_arguments[i]][j]));
			}
			out_clauses.push_back(out_clause);
		}

		std::vector<std::vector<int64_t>> tseitin_out_clauses;
		std::vector<int64_t> tseitin_vars_B;
		for(std::vector<int64_t> clause : out_clauses){
			int64_t current_tseitin_var = af.current_tseitin_var();
			std::vector<int64_t> tseitin_clause;
			tseitin_clause.reserve(clause.size() + 1);
			tseitin_clause.push_back(-clause[0]); 
			for(size_t i = 1; i < clause.size(); i++){
				tseitin_clause.push_back(std::abs(clause[i]));
			}
			tseitin_clause.push_back(current_tseitin_var);
			tseitin_vars_B.push_back(current_tseitin_var);
			tseitin_out_clauses.push_back(tseitin_clause);
		}

		for(std::vector<int64_t> clause : tseitin_out_clauses){
			solver.add_clause(clause);
		}

		int64_t tseitin_var_B = or_clause_tseitin(af, solver, tseitin_vars_B);

		std::vector<int64_t> tseitin_out_clauses_C;
		tseitin_out_clauses_C.reserve(af.args);
		int64_t tseitin_var_C = af.current_tseitin_var();
		for (size_t i = 0; i < active_arguments.size(); i++) {
			tseitin_out_clauses_C.push_back(af.accepted_min_var(active_arguments[i]));
			solver.add_clause_2((int64_t) -af.accepted_min_var(active_arguments[i]), -tseitin_var_C);
		}
		tseitin_out_clauses_C.push_back(tseitin_var_C);
		solver.add_clause(tseitin_out_clauses_C);

		std::vector<int64_t> tseitin_clause;
		int64_t tseitin_complete_var = af.current_tseitin_var();
		tseitin_clause.push_back(-tseitin_complete_var);
		tseitin_clause.push_back(tseitin_var_A);
		tseitin_clause.push_back(tseitin_var_B);
		tseitin_clause.push_back(tseitin_var_C);
		solver.add_clause(tseitin_clause);
		solver.add_clause_2(-tseitin_var_A, tseitin_complete_var);
		solver.add_clause_2(-tseitin_var_B, tseitin_complete_var);
		solver.add_clause_2(-tseitin_var_C, tseitin_complete_var);
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
