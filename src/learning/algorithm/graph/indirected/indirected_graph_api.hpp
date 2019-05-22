#ifndef __nobodyxu_wheels_indirected_graph_api_HPP__
# define __nobodyxu_wheels_indirected_graph_api_HPP__

# include <cassert>
# include "../edge.hpp"

namespace nxwheels {
template <class Derived, class _Index_t>
class indirected_graph_api {
    /*
     * indirected_graph() = default;
     *
     * indirected_graph(const indirected_graph&) = default;
     * indirected_graph(indirected_graph&&) = default;
     *
     * indirected_graph& operator = (const indirected_graph&) = default;
     * indirected_graph& operator = (indirected_graph&&) = default;
     */
    using Index_t = _Index_t;

    constexpr auto* get_Derived() noexcept { return static_cast<Derived*>(this); }
    constexpr auto* get_Derived() const noexcept { return static_cast<const Derived*>(this); }
public:
    using edge = edge<Index_t>;

    constexpr auto V() const noexcept -> Index_t { return get_Derived()->V(); }
    constexpr auto E() const noexcept -> Index_t { return get_Derived()->E(); }

    constexpr decltype(auto) adj(Index_t index) const noexcept { return get_Derived()->adj(index); }
    constexpr decltype(auto) iter_over_nodes() const noexcept { return get_Derived()->iter_over_nodes(); }

    constexpr void addVertex(const Index_t &index = Index_t{1}) { get_Derived()->addVertex(index); }
    constexpr void addEdge(const edge &e) { get_Derived()->addEdge(e); }
    template <class Range>
    constexpr void addEdge(Range &&range) { get_Derived()->addEdge(range); }

    constexpr void clear() { get_Derived()->clear(); }

public:
    template <class Stream>
    void fromStream(Stream &&in) {
        Index_t v, e, v1, v2;

        in >> v;
        in >> e;
        if(e == 0)
            return;
        assert(e <= (v - 1) * (v - 1));
        get_Derived()->set_edges(e);

        clear();
        addVertex(v);

        for(Index_t i = 0; i != e; ++i) {
            in >> v1 >> v2;
            get_Derived()->_addEdge(edge{v1, v2});
        }
    }
    template <class Stream>
    void toStream(Stream &&out) const {
        auto Vertexs = V(), Edges = E();
        out << Vertexs;
        out << Edges;
        if(Edges == 0)
            return;

        for(Index_t i{0}; i != Vertexs; ++i)
            for(const auto &end: adj(i))
                if (end >= i)
                    out << edge{i, end};
    }
};
} /* nxwheels */
#endif
