#include <iostream>
#include "frequently_used_functions.hpp"
using namespace nxwheels;

int main() {
    indirected_graph g;
    g.fromStream(std::cin);

    std::cout << id_graph::MaxDegree(g) << " \n"
              << id_graph::CountSelfLoops(g) << " \n";
}
