#ifndef __nobodyxu_wheels_algorithm_graph_indirected_path_HPP__
# define __nobodyxu_wheels_algorithm_graph_indirected_path_HPP__

# include <vector>
# include <limits>
# include <stdexcept>
# include <cassert>

# include <nxwheels/iterator/iterator.hpp>
# include <Ints/Ints.hpp>

# include "../edge.hpp"
# include "../../range/range.hpp"

namespace nxwheels {
template <class _Index_t>
class path_basic {
    std::vector<bool> marker;
public:
    using Index_t = _Index_t;
    using self    = path_basic;

    path_basic() = default;

    path_basic(const _Index_t &hint): marker(hint) {}

    path_basic(const self&) = default;
    path_basic(      self&&) = default;

    self& operator = (const self&) = default;
    self& operator = (      self&&) = default;

    constexpr const static inline bool record_path = false;
    bool is_marked(const Index_t &id) const noexcept { return id < marker.size() && marker[id]; }
    void mark(const Index_t &v) {
        if (v >= marker.size())
            marker.resize(v + 1);

        marker[v] = true;
    }
};
template <class _Index_t>
class path_advanced {
    using underlying_Index_t = underlying_type<_Index_t>;
    static_assert(std::is_unsigned<underlying_Index_t>{}());

    constexpr const static inline _Index_t placeholder_impl_v = std::numeric_limits<underlying_Index_t>::max();
    constexpr const static inline _Index_t max_impl_v = placeholder_impl_v - 1;
public:
    struct Index_t: public wrap_over_t<_Index_t> {
        using base = wrap_over_t<_Index_t>;

        using base::base;
        constexpr Index_t() noexcept : base{placeholder_impl_v} {}
        template <class U>
        constexpr Index_t(const U &t, std::enable_if_t<std::is_same<underlying_Index_t, U>{}()>* = nullptr) noexcept : base{t} {
            assert(t <= max_impl_v);
        }
    };

    constexpr const static inline Index_t placeholder_v = Index_t{};
    constexpr const static inline Index_t max_v = Index_t{max_impl_v};
private:
    std::vector<Index_t> path_record;

    struct iterator_end {};
    class iterator_beg: input_iterator_base<iterator_beg> {
        typename std::vector<Index_t>::const_iterator beg;
        Index_t id;
    public:
        using value_type      = Index_t;
        using reference       = const Index_t&;
        using pointer         = const Index_t*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        constexpr iterator_beg(const typename std::vector<Index_t>::const_iterator &_beg, const Index_t &_id) noexcept : beg{_beg}, id{_id} {}

        constexpr auto& operator * () const noexcept { return id; }
        auto& operator ++ () noexcept {
            id = beg[id.get_value()];
            return *this;
        }
        constexpr bool operator != (const iterator_end&) const noexcept { return id != beg[id.get_value()]; }
    };
public:
    constexpr const static inline bool record_path = true;
    using self = path_advanced;

    path_advanced() = default;

    constexpr path_advanced(const Index_t &hint): path_record(hint.get_value()) {}

    path_advanced(const self&) = default;
    path_advanced(      self&&) = default;

    self& operator = (const self&) = default;
    self& operator = (      self&&) = default;

    void mark(const edge<Index_t> &e) {
        if (e.to >= path_record.size())
            path_record.resize(e.to.get_value() + 1);

        path_record[e.to.get_value()] = e.from;
    }
    bool is_marked(const Index_t &id) const noexcept {
        return id < path_record.size() && path_record[id.get_value()] != placeholder_v;
    }
    /*!
     * PathTo returns an iterable which denotes the path from id to rootId.
     * It is in reverse order and excludes the root node.
     */
    auto PathTo(const Index_t &id) const noexcept -> range<iterator_beg, iterator_end> { return {{path_record.begin(), id}}; }
};
} /* nxwheels */
#endif
