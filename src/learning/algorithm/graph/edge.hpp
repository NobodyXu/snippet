#ifndef __nobodyxu_wheels_edge_HPP__
# define __nobodyxu_wheels_edge_HPP__

namespace nxwheels {
template <class Index_t>
struct edge {
    Index_t from, to;
};
template <class T> edge(const T&) -> edge<T>;
} /* nxwheels */
#endif
