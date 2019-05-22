#ifndef __sort_iterator_traits_HPP__
#define __sort_iterator_traits_HPP__
# include <iterator>
namespace sort {
template <class It>
using It_traits = std::iterator_traits<It>;

template <class It>
using It_val =    typename It_traits<It>::value_type;
template <class It>
using It_diff_t = typename It_traits<It>::difference_type;
template <class It>
using It_ref =    typename It_traits<It>::reference;
template <class It>
using It_ptr =    typename It_traits<It>::pointer;
template <class It>
using It_tag =    typename It_traits<It>::iterator_category;

template <class It>
using It_ptr_const =       It_val<It> * const;
template <class It>
using It_const_ptr =       const It_ptr<It>;
template <class It>
using It_const_ptr_const = const It_ptr_const<It>;

namespace impl {
template <class It, class = It_tag<It>>
struct It_dis_is_larger_than {
    using diff_t = It_diff_t<It>;
    bool operator () (const It &beg, const It &end, const diff_t &v) const {
        diff_t cnt{0};
        for(auto it = beg; it != end; ++it)
            if(++cnt >v)
                return 1;
        return 0;
    }
};
template <class It>
struct It_dis_is_larger_than<It, std::random_access_iterator_tag> {
    using diff_t = It_diff_t<It>;
    bool operator () (const It &beg, const It &end, const diff_t &v) const {
        return end - beg > v;
    }
};
}//namespace impl
template <class It>
bool It_dis_is_larger_than(const It &beg, const It &end, const It_diff_t<It> &v) {
    return impl::It_dis_is_larger_than<It>{}(beg, end, v);
}

template <class It>
inline constexpr const bool is_list_v = 0;
}//namespace sort
#endif
