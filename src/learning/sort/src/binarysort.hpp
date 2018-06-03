#ifndef __sort_binarysort_HPP__
#define __sort_binarysort_HPP__
//C++17
# include <cassert>
# include <algorithm>
# include "iterator_traits.hpp"
# include "bound.hpp"
# include "inserter.hpp"
# include "concept_check.hpp"
namespace sort {
template <class It, class Cmp, class upbd_f, class Insert_f>
void binarysort_impl(const It &beg, It it, const It &end, Cmp &c, upbd_f &upbd, Insert_f &_insert) {
    auto get_upbd = [&upbd, &c](const It &beg, const &oit){};
    do {
        auto oit{it};
        ++it;
		    if(c(*oit, *(oit - 1)))
            _insert(upbd(beg, oit, *oit, c), oit);
    } while(it != end);
}
template <class It, class Cmp = std::less<>, class upbd_f = upper_bound<It, Cmp>, class Insert_f = inserter<It>>
void binarysort(const It &beg, const It &it, const It &end, Cmp c = {}, upbd_f upbd = {}, Insert_f _Insert = {}) {
    using namespace concept_check;
    using T = It_val<It>;
    static_assert(is_base_of_v<std::forward_iterator_tag, It_tag<It>>);
    static_assert(is_same_v<decltype(it + 1), It>);
    static_assert(is_same_v<decltype(it - 1), It>);
    static_assert(is_same_v<decltype(*it), T&>);
    static_assert(is_same_v<decltype(beg != end), bool>);
    static_assert(is_same_v<decltype(c(beg, beg)), bool>);
    static_assert(is_same_v<decltype(upbd(beg, end, *beg, c)), It>);
    static_assert(is_same_v<decltype(_Insert(const_cast<It&>(beg), const_cast<It&>(end))), void>);
    assert(sort::It_dis_is_larger_than(beg, it, 0));
    assert(sort::It_dis_is_larger_than(it, end, -1));
    assert(std::is_sorted(beg, it, c));
    if(it != end) {
		    binarysort_impl<It>(beg, it, end, c, upbd, _Insert);
        assert(std::is_sorted(beg, end, c));
    }
}
}//namespace sort
#endif
