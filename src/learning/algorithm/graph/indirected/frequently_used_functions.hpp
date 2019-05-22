#ifndef __nobodyxu_wheels_frequently_used_functions_HPP__
# define __nobodyxu_wheels_frequently_used_functions_HPP__

# include <cassert>
# include "indirected_graph.hpp"

namespace nxwheels::id_graph {
constexpr auto degree(const indirected_graph &g, typename indirected_graph::Index_t Vertex) noexcept {
    return g.adj(Vertex).size();
}
constexpr auto MaxDegree(const indirected_graph &g) noexcept {
    auto V = g.V();
    decltype(V) max{0};

    for(decltype(V) i{0}; i != V; ++i) {
        auto Degree = degree(g, i);
        max = max < Degree ? Degree : max;
    }

    return max;
}
constexpr auto CountSelfLoops(const indirected_graph &g) noexcept {
    auto V = g.V();
    decltype(V) count{0};

    for(decltype(V) i{0}; i != V; ++i)
        for(const auto &u: g.adj(i))
            count = u == i ? count + 1 : count ;

    assert(count % 2 == 0);
    return count >> 1;
}
constexpr auto AvgDegree(const indirected_graph &g) noexcept {
    return (g.E() << 1) / g.V();
}
} /* nxwheels::id_graph */
#endif
