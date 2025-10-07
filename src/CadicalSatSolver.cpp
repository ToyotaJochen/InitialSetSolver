/*
* The following is largely taken from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#include "CadicalSatSolver.h"

CadicalSatSolver::CadicalSatSolver(int32_t n_args) {
    solver = new CaDiCaL::Solver;
	decision_vars = n_args;
	model = std::vector<bool>(decision_vars);
	extension = std::vector<uint32_t>(decision_vars);
}

 // Here are functions simplifying clause addition. The given literals
  // should all be valid (different from 'INT_MIN' and different from '0').
  //
  //   require (VALID)
  //   ensure (STEADY )
void CadicalSatSolver::add_clause(const std::vector<int32_t> & clause) {
	for (int32_t i : clause) {
		solver->add(i);
	}
	solver->add(0);
}

void CadicalSatSolver::add_clause(const std::vector<int64_t> & clause) {
	for (int32_t i : clause) {
		solver->add(i);
	}
	solver->add(0);
}

void CadicalSatSolver::add_clause_1(int32_t lit) {
	solver->add(lit);
	solver->add(0);
}

void CadicalSatSolver::add_clause_2(int32_t lit1, int32_t lit2) {
	solver->add(lit1);
	solver->add(lit2);
	solver->add(0);
}

void CadicalSatSolver::add_clause_2(int64_t lit1, int64_t lit2) {
	solver->add(lit1);
	solver->add(lit2);
	solver->add(0);
}

void CadicalSatSolver::add_clause_3(int32_t lit1, int32_t lit2, int32_t lit3) {
	solver->add(lit1);
	solver->add(lit2);
	solver->add(lit3);
	solver->add(0);
}

  // Assume valid non zero literal for next call to 'solve'.  These
  // assumptions are reset after the call to 'solve' as well as after
  // returning from 'simplify' and 'lookahead.
  //
  //   require (READY)
  //   ensure (STEADY )
void CadicalSatSolver::assume(int32_t lit) {
	solver->assume(lit);
}

// Try to solve the current formula.  Returns
  //
  //    0 = UNKNOWN      (limit reached or interrupted through 'terminate')
  //   10 = SATISFIABLE
  //   20 = UNSATISFIABLE
  //
  //   require (READY)
  //   ensure (STEADY  | SATISFIED | UNSATISFIED)
  //
  // Note, that while in this call the solver actually transitions to state
  // 'SOLVING', which however is only visible from a different context,
  // i.e., from a different thread or from a signal handler.  Only right
  // before returning from this call it goes into a 'READY' state.
int CadicalSatSolver::solve() {
	int sat = solver->solve();

	if ( !( (sat == SAT_V) || (sat == UNSAT_V) ) ) {
		std::cerr << "Problem" << std::endl;
		exit(1);
	}

    // Get value (-lit=false, lit=true) of valid non-zero literal.
    //
    //   require (SATISFIED)
    //   ensure (SATISFIED)

	if (sat == SAT_V) {
		model.clear();
		for (int32_t i = 1; i <= decision_vars; i++)
			model.push_back(solver->val(i) > 0 ? true : false);
	}
	return sat;
}

int CadicalSatSolver::solve_extension() {
	int sat = solver->solve();

	if ( !( (sat == SAT_V) || (sat == UNSAT_V) ) ) {
		std::cerr << "Problem" << std::endl;
		exit(1);
	}

	if (sat == SAT_V) {
		model.clear();
		extension.clear();
		for (int32_t i = 1; i <= decision_vars; i++) {
			if (solver->val(i) > 0) {
				model.push_back(true);
				extension.push_back(i-1);
			} else {
				model.push_back(false);
			}
		}
	}
	return sat;
}

int CadicalSatSolver::solve(const std::vector<int32_t> assumptions) {
	for (auto const& ass: assumptions) {
		assume(ass);
	}
	return solve();
}

bool CadicalSatSolver::check(){
	return solver->inconsistent();
}