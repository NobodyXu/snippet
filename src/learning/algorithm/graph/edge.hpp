#ifndef __nobodyxu_wheels_edge_HPP__
# define __nobodyxu_wheels_edge_HPP__

namespace nxwheels {
template <class Index_t>
struct edge {
    Index_t from, to;
};
template <class T> edge(const T&) -> edge<T>;

template <class OutStream, class Index_t>
auto& operator << (OutStream &os, const edge<Index_t> &e) { return os << e.from << " " << e.to; }
} /* nxwheels */
#endif
