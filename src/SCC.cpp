#include "SCC.h"
#include "AF.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <boost/graph/strong_components.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Graph;

std::vector<uint32_t> calculate_scc(std::vector<std::vector<uint32_t>> attackers){
    
    uint32_t num_vertices = attackers.size();
    std::vector<uint32_t> scc;
    scc.resize(num_vertices);

    Graph G(num_vertices);

    // adding the attacks as edges to the graph
    for(auto i = 0; i < num_vertices; i++){
        for(auto j = 0; j < attackers[i].size(); j++){
            add_edge(attackers[i][j], i, G);
        }
    }

    //calculate the SCC's
    int num_components = strong_components(G, make_iterator_property_map(scc.begin(), get(vertex_index, G), scc[0]));

    // print the components of the arguments
    // for (auto i = scc.begin(); i != scc.end(); ++i)
    //     std::cout << "Vertex " << i - scc.begin() << " is in component " << *i
    //               << std::endl;
    
    return scc;
}