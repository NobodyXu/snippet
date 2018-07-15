#ifndef __nobodyxu_wheels_indirected_graph_HPP__
# define __nobodyxu_wheels_indirected_graph_HPP__

# include <boost/cstdint.hpp>
# include <vector>
# include "indirected_graph_api.hpp"

namespace nxwheels {
struct indirected_graph: indirected_graph_api<indirected_graph, boost::uint64_t> {
    using Index_t = boost::uint64_t;
    friend indirected_graph_api<indirected_graph, Index_t>;

    indirected_graph() = default;

    indirected_graph(const indirected_graph&) = default;
    indirected_graph(indirected_graph&&) = default;

    indirected_graph& operator = (const indirected_graph&) = default;
    indirected_graph& operator = (indirected_graph&&) = default;

    constexpr auto V() const noexcept { return VertexVector.size(); }
    constexpr auto E() const noexcept { return edges; }
    auto& adj(Index_t N) noexcept { return VertexVector[N]; }
    auto& adj(Index_t N) const noexcept { return VertexVector[N]; }

    void addVertex(Index_t N = 1) { VertexVector.resize(VertexVector.size() + N); }
    void addEdge(const edge &e) {
        ++edges;
        _addEdge(e);
    }
    template <class Range>
    void addEdge(Range &&range) {
        // This can be optimized if concept check is available.
        for(auto &&e: range)
            addEdge(e);
    }

    constexpr void clear() noexcept {
        VertexVector.clear();
    }

protected:
    void _addEdge(const edge &e) {
        VertexVector[e.beg].push_back(e.end);
    }
    constexpr void set_edges(Index_t _edges) noexcept { edges = _edges; }

    uint64_t edges{0};
    std::vector<std::vector<Index_t>> VertexVector;
};
} /* nxwheels */
#endif
