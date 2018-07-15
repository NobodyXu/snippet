#ifndef __nobodyxu_wheels_indirected_graph_api_HPP__
# define __nobodyxu_wheels_indirected_graph_api_HPP__

# include "../edge.hpp"

namespace nxwheels {
template <class Derived, class _Index_t>
struct indirected_graph_api {
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
    using edge = edge<Index_t>;

    constexpr auto V() const noexcept -> Index_t { return get_Derived()->V(); }
    constexpr auto E() const noexcept -> Index_t { return get_Derived()->E(); }
    constexpr auto adj(Index_t index) { return get_Derived()->adj(index); }

    template <class Stream>
    constexpr void fromStream(Stream &&in) {
        Index_t v{0}, e{0}, v1{0}, v2{0};

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
    constexpr void toStream(Stream &&out) const {
        auto Vertexs = V(), Edges = E();
        out << Vertexs;
        out << Edges;
        if(Edges == 0)
            return;

        for(Index_t i{0}; i != Vertexs; ++i)
            for(const auto &Edge: adj(i))
                out << Edge.beg << Edge.end;
    }

    constexpr void addVertex(const Index_t &index = Index_t{1}) { get_Derived()->addVertex(index); }
    constexpr void addEdge(const edge &e) { get_Derived()->addEdge(e); }
    template <class Range>
    constexpr void addEdge(Range &&range) { get_Derived()->addEdge(range); }

    constexpr void clear() { get_Derived()->clear(); }
 private:
    constexpr auto* get_Derived() noexcept { return static_cast<Derived*>(this); }
    constexpr auto* get_Derived() const noexcept { return static_cast<const Derived*>(this); }
};
} /* nxwheels */
#endif
