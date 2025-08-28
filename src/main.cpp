#include <iostream>
#include <getopt.h>             
#include <utility>
#include <algorithm>
#include <boost/config.hpp>

#include "AF.h"
#include "Parse.h"
#include "Main.h"
#include "Algorithms.h"
#include "CadicalSatSolver.h"

using namespace boost;

static int version_flag = 0;
static int usage_flag = 0;
static int formats_flag = 0;
static int problems_flag = 0;

enum task { ITERSATSCC, ITSAT, NITSAT, PROCEDURAL, UNKNOWN_TASK };
enum semantics { IT, UNKNOWN_SEM };

task string_to_task(std::string problem) {
	problem.erase(0, problem.find("-") + 1);
	std::string tmp = problem.substr(0, problem.find("-"));
	if (tmp == "IT") return ITSAT;
	if (tmp == "ITSCC") return ITERSATSCC;
	if (tmp == "NIT") return NITSAT;
	if (tmp == "PROC") return PROCEDURAL;
	return UNKNOWN_TASK;
}

void print_problems(){
    std::cout << "[EE-IT, EE-ITSCC, EE-NIT, EE-PROC]\n";
}

void print_version(){
    std::cout << SOLVER_NAME << "\n";
    std::cout << AUTHOR << "\n";
    std::cout << VERSION <<"\n";
}

void print_formats(){
    std::cout << "[i23] \n";
}

void print_usage(){
    std::cout << "Usage: " << SOLVER_NAME << " -p <task> -f <file> -fo <format> \n\n";
    std::cout << "  <task>      For a list of available solving-methods use option --problems\n";
    std::cout << "  <file>      input argumentation framework\n";
	std::cout << "  <format>    file format for input AF; for a list of available formats use option --formats\n\n";
    std::cout << "Options:\n";
	std::cout << "  --help      Displays this help message.\n";
	std::cout << "  --version   Prints version and author information.\n";
	std::cout << "  --problems  Prints available solver for computing initial sets.\n";
    std::cout << "  --formats   Prints available file formats\n";
}

int main(int argc, char ** argv) {    
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	if (argc == 1) {
		print_version();
		return 0;
	}

	const struct option longopts[] = {
		{"help", no_argument, &usage_flag, 1},
		{"version", no_argument, &version_flag, 1},
		{"formats", no_argument, &formats_flag, 1},
		{"problems", no_argument, &problems_flag, 1},
		{"p", required_argument, 0, 'p'},
		{"f", required_argument, 0, 'f'},
		{"fo", required_argument, 0, 'o'},
		{"a", required_argument, 0, 'a'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int opt = 0;
	std::string task, file, fileformat, query;

	while ((opt = getopt_long_only(argc, argv, "", longopts, &option_index)) != -1) {
		switch (opt) {
			case 0:
				break;
			case 'p':
				task = optarg;
				//std::cout << task;
				break;
			case 'f':
				file = optarg;
				break;
			case 'o':
				fileformat = optarg;
				break;
			case 'a':
				query = optarg;
				break;
			default:
				return 1;
		}
	}

	if (version_flag) {
		print_version();
		return 0;
	}

	if (usage_flag) {
		print_usage();
		return 0;
	}

	if (formats_flag) {
		print_formats();
		return 0;
	}

	if (problems_flag) {
		print_problems();
		return 0;
	}

	if (task.empty()) {
		std::cerr << argv[0] << ": Task must be specified via -p flag\n";
		return 1;
	}

	if (file.empty()) {
		std::cerr << argv[0] << ": Input file must be specified via -f flag\n";
		return 1;
	}

	if (fileformat.empty()) {
		//std::cerr << argv[0] << ": File format must be specified via -fo flag\n";
		fileformat = "i23";
		//return 1;
	}

    AF aaf = AF();
	IterableBitSet active_arguments = parse_i23(& aaf, file);
	std::vector<std::vector<uint32_t>> result;

    aaf.calc_scc();
	// std::cout<< " scc done \n";
	// std::vector<std::vector<uint32_t>> com = aaf.get_components();
	// for(int i = 0; i < com.size(); i++){
	// 	for(int j = 0; j < com[i].size(); j++){
	// 		std::cout << "Vertex " << aaf.accepted_var(active_arguments._array[com[i][j]]) << " is in component " << i << "\n"; 
	// 	}
	// }

    switch (string_to_task(task))
    {
	case ITSAT:
		result = Algorithms::enumerate_initial(aaf, active_arguments);
		for (const std::vector<uint32_t> & ext : result) {
				print_extension(aaf, ext);
				std::cout << ",";
		}
		break;
    case ITERSATSCC:
        result = Algorithms::enumerate_initial_scc(aaf, active_arguments);
		for (const std::vector<uint32_t> & ext : result) {
				print_extension(aaf, ext);
				std::cout << ",";
		}
		break;
    case NITSAT:
		result = Algorithms::enumerate_initial_non_it(aaf, active_arguments);
			for (const std::vector<uint32_t> & ext : result) {
				print_extension(aaf, ext);
				std::cout << ",";
			}
        break;
    case PROCEDURAL:
		result = Algorithms::enumerate_procedural(aaf, active_arguments);
		for (const std::vector<uint32_t> & ext : result) {
			print_extension(aaf, ext);
			std::cout << ",";
		}
        break;
    default:
		std::cout << "Task not supported! \n";
        return 1;
    }


    return 0;
}