#ifndef __nobodyxu_wheels_algorithm_graph_indirected_path_HPP__
# define __nobodyxu_wheels_algorithm_graph_indirected_path_HPP__

# include <cstddef>
# include <iterator>
# include <vector>
# include <nxwheels/iterator/iterator.hpp>
# include "../../range/range.hpp"
# include "path_api.hpp"

namespace nxwheels {
template <class _Index_t>
class path_basic_impl {
public:
    using Index_t = _Index_t;
protected:
    Index_t rootId;
    std::vector<bool> marker;
public:
    constexpr auto& get_rootId() const noexcept { return rootId; }
    bool is_marked(const Index_t &id) const noexcept { return marker[id]; }
    void mark(const Index_t &prev_id, const Index_t &id) { marker[id] = true; }
};
template <class _Index_t>
class path_advanced_impl: path_basic_impl<_Index_t> {
public:
    using Index_t = _Index_t;
protected:
    std::vector<Index_t> path_record;

    struct iterator_end {};
    class iterator_beg: input_iterator_base<iterator_beg> {
        typename std::vector<Index_t>::const_iterator beg;
        Index_t id;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type      = Index_t;
        using reference       = Index_t&;
        using pointer         = Index_t*;
        using iterator_category = std::forward_iterator_tag;

        iterator_beg(const typename std::vector<Index_t>::const_iterator &_beg, const Index_t &_id) noexcept : beg{_beg}, id{_id} {}

        auto& operator * () const noexcept { return id; }
        auto& operator ++ () noexcept {
            id = beg[id];
            return *this;
        }
        bool operator != (const iterator_end&) const noexcept { return id != beg[id]; }
    };
public:
    void mark(const Index_t &prev_id, const Index_t &id) {
        path_basic_impl<Index_t>::mark(prev_id, id);
        path_record[id] = prev_id;
    }
    auto PathTo(const Index_t &id) const noexcept -> range<iterator_beg, iterator_end> { return {{path_record.begin(), id}}; }
};
} /* nxwheels */
#endif
