#include "SCC.h"
#include "AF.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <boost/graph/strong_components.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Graph;

SCC::SCC() : num_components(0), num_vertices(0) {}

void SCC::calc_scc(AF & af){
    num_vertices = af.args;

    scc.resize(num_vertices);

    Graph G(num_vertices);

    // adding the attacks as edges to the graph
    for(auto i = 0; i < af.attackers.size(); i++){
        for(auto j = 0; j < af.attackers[i].size(); j++){
            add_edge(af.attackers[i][j], i, G);
        }
    }

    //calculate the SCC's
    num_components = strong_components(G, make_iterator_property_map(scc.begin(), get(vertex_index, G), scc[0]));

    // print the components of the arguments
    // for (auto i = scc.begin(); i != scc.end(); ++i)
    //     std::cout << "Vertex " << i - scc.begin() << " is in component " << *i
    //               << std::endl;

}