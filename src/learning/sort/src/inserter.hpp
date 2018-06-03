#ifndef __sort_inserter_HPP__
#define __sort_inserter_HPP__
# include <cassert>
# include <algorithm>
# include <utility>
# include "iterator_traits.hpp"
namespace sort {
/*
 * Given type It, T = It_val<It>, tag = It_tag<It>
 * this class template serve the purpose of insert a/a range of T (identified by It(s)) into
 * the place before where another iterator points to.
 *
 * There are two overloaded member functions, one insert one element, another
 * insert a range of elements.
 *
 * To use inserter with It whose tag is std::forward_iterator_tag,
 * an iterator adapter is required.
 * The behavior of it will be equivalent to as if its tag is std::forward_iterator_tag.
 */
template <class It, class = It_tag<It>>
struct inserter {
    void operator () (It &out, It &in) const;
    void operator () (It &out, It &f_in, It &l_in) const;
};
template <class It>
struct inserter<It, std::forward_iterator_tag> {
};
template <class It>
struct inserter<It, std::random_access_iterator_tag> {
    void operator () (It out, It in) const {
        assert(in - out > 0);
        auto temp = std::move(*in);
        std::move_backward(out, in, in + 1);
        *out = std::move(temp);
    }
    void operator () (const It &out, const It &f_in, const It &l_in, It_ptr<It> tmp) const {
        auto num_to_mv = l_in - f_in;
        assert(num_to_mv > 0);
        assert(f_in - out > 0);
        assert(tmp);
        std::move(f_in, l_in, tmp);
        std::move_backward(out, f_in, l_in);
        out = std::move(tmp, tmp + num_to_mv, out);
    }
};
}//namespace sort
#endif
