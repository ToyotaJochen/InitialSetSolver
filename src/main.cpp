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

void print_solver(){
    std::cout << "iterative SAT [itSAT], SAT [nitSAT], Procedural Test [procTEST]\n";
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
	std::cout << "  -l          Prints available Solver for computing initial sets.\n";
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
                print_solver();
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
	IterableBitSet active_arguments = parse_i23(&aaf, file);
	std::vector<std::vector<uint32_t>> result;

    int num_args = aaf.args;

    typedef adjacency_list<vecS, vecS, directedS> Graph;

    Graph G(num_args);

    for(auto i = 0; i < aaf.attackers.size(); i++){
        for(auto j = 0; j < aaf.attackers[i].size(); j++){
            add_edge(j, i, G);
        }
    }

    std::vector< int > c(num_args);
    int num = strong_components(
        G, make_iterator_property_map(c.begin(), get(vertex_index, G), c[0]));

    std::cout << "Total number of components: " << num << std::endl;
    for (auto i = c.begin(); i != c.end(); ++i)
        std::cout << "Vertex " << i - c.begin() << " is in component " << *i
                  << std::endl;
    return 0;
}