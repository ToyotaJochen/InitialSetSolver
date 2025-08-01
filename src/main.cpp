#include <iostream>
#include <getopt.h>             // Parser for the command-line options
#include <utility>
#include <algorithm>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <boost/graph/strong_components.hpp>

#include "AF.h"
#include "Parse.h"
#include "Main.h"
#include "CadicalSatSolver.h"




void print_info_and_version();
void print_help();

using namespace boost;

std::string solver, file;

enum task { ITERSAT, SAT, PROCEDURAL, UNKNOWN_TASK };
enum semantics { IT, UNKNOWN_SEM };


task string_to_task(std::string problem) {
	std::string tmp = problem.substr(0, problem.find("-"));
	if (tmp == "ITERSAT") return ITERSAT;
	if (tmp == "SAT") return SAT;
	if (tmp == "PROCEDURAL") return PROCEDURAL;
	return UNKNOWN_TASK;
}

semantics string_to_sem(std::string problem) {
	problem.erase(0, problem.find("-") + 1);
	std::string tmp = problem.substr(0, problem.find("-"));
	if (tmp == "IT") return IT;
	return UNKNOWN_SEM;
}

void print_problems(){
    std::cout << "[IT-ITERSAT, IT-SAT, IT-PROCEDURAL]\n";
}

void print_author_and_version(){
    std::cout << SOLVER_NAME << "\n";
    std::cout << AUTHOR << "\n";
    std::cout << VERSION <<"\n";
}

void print_help(){
    std::cout << "Usage: " << SOLVER_NAME << " -s <solver> -f <file>" << std::endl;
    std::cout << "  <solver>    For a list of available solving-methods use option -l\n";
	std::cout << "  <file>      Input the filename for the argumentation framework\n";
    std::cout << "Options:\n";
	std::cout << "  -h          Displays this help message.\n";
	std::cout << "  -v          Prints version and author information.\n";
	std::cout << "  -l          Prints available solver for computing initial sets.\n";
}

int main(int argc, char ** argv) {    
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	if (argc == 1) {
		print_author_and_version();
		return 0;
	}

	int option_index = 0;
	int opt = 0;

	while ((opt = getopt(argc, argv, "hvls:f:")) != -1) {
		switch (opt) {
			case 0:
				break;
			case 'h':
				print_help();
				break;
            case 'v':
                print_author_and_version();
                break;
            case 'l':
                print_problems();
                break;
            case 's':
                solver = optarg;
                std::cout << solver << "\n";
                break;
            case 'f':
                file = optarg;
                std::cout << file << "\n";
                break;
			default:
				return 1;
		}
    }

    AF aaf = AF();
	IterableBitSet active_arguments = parse_i23(& aaf, file);
	std::vector<std::vector<uint32_t>> result;
    aaf.calc_scc();

    switch (string_to_task(solver))
    {
    case ITERSAT:
        /* code */
        break;
    case SAT:
        break;
    case PROCEDURAL:
        break;
    default:
        return 1;
    }


    return 0;
}