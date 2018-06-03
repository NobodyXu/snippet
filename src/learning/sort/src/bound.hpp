#ifndef __sort_bound_HPP__
#define __sort_bound_HPP__
# include "iterator_traits.hpp"
# include <cstdint>
# include <utility>
# include <type_traits>
# include <algorithm>
# include <cassert>
# include <memory>
# include <functional>//std::less
# define CBOOL inline constexpr const bool
namespace sort {
namespace impl {
template <bool count_or_not, class It, class unary_F>
auto for_each_if(It &it, const It &end, unary_F f) {
    if constexpr(count_or_not) {
        It_diff_t<It> cnt{1};
        for(; ++it != end && f(*it); ++cnt);
        return cnt;
    } else
        while(++it != end && f(*it));
}
template <class T, class Cmp>
constexpr auto get_unary_F(const T &val, Cmp &c) noexcept { return [&](const T &v){ return c(v, val); }; }

template <class T>
CBOOL is_const_v{std::is_const<T>{}()};
template <class T1, class T2>
CBOOL is_same_v{std::is_same<T1, T2>{}()};
/*
 * Comparer c can only be used like this: c(*it, val).
 * When the function wants to find the upper bound, then c should return 1 when *it <= val;
 * Otherwise, c should return 0 when *it < val.
 */
template <class It, class Cmp>
struct get_bound_impl_for_random_access_it {
    using T = It_val<It>;
    It &beg;
    It &end;
    Cmp &c;
    const T &val;
    const std::size_t &branches, &min_bound;
    constexpr void operator () (void) {
        assert(min_bound >= 2 * branches);

        if (end - beg > min_bound) main_loop_for_narrowing_the_range();
        for_each_if<0>(beg, end, get_unary_F(val, c));
    }
  protected:
    constexpr void main_loop_for_narrowing_the_range() {
        It it;
        It_diff_t<It> dis;
        do {
            check_every_branch(it, dis);
        } while(end - beg > min_bound);
    }
    constexpr void check_every_branch(It &it, It_diff_t<It> &dis) {
        dis = (end - beg) / branches, it = beg + dis;
        do {
            if (c(*it, val))
                beg = it + 1;
            else {
                end = it + 1;
                break;
            }
            it += dis;
        } while(it < end);
    }
};//struct get_bound_impl_for_random_access_it
template <class It1, class It2, class Cmp, class It = std::remove_cv_t<It1>>
constexpr auto get_bound_impl(It1 &it1, It2 &it2, const It_val<It> &val, Cmp &c) {
    constexpr const bool is_It1_const{is_const_v<It1>};
    constexpr const bool is_It2_const{is_const_v<It2>};
    constexpr const bool is_rand_access_it{is_same_v<It_tag<It>, std::random_access_iterator_tag>};
    //static_assert(/* is forward it */);
    static_assert(is_same_v<std::remove_cv_t<It1>, std::remove_cv_t<It2>>);

    It_diff_t<It> cnt;
    std::conditional_t<is_It1_const, std::remove_const_t<It1>, It1&> hint{it1};
    std::conditional_t<is_It1_const, It1&, const It1> beg{it1};
    std::conditional_t<is_It2_const && is_rand_access_it, std::remove_const_t<It2>, It2&> end{it2};
    if constexpr(is_rand_access_it) {
        get_bound_impl_for_random_access_it<It, Cmp>{hint, end, c, val, 2, 10}();
        cnt = hint - beg;
    } else
        cnt = for_each_if<1>(hint, end, get_unary_F(val, c));
    if constexpr(is_It1_const && !is_It2_const) it2 = hint;
    return cnt;
}
template <class It1, class It2, class It3, class Cmp, class It = std::remove_cv_t<It1>>
constexpr auto get_bound(const It1 &beg, It2 &hint, It3 &end, const It_val<It> &val, Cmp c) {
    if (c(*hint, val)) return get_bound_impl(++hint, end, val, c);
    else               return get_bound_impl(beg, ++hint, val, c);
}
template <bool lower_bound_or_upper_bound, class Val, class Cmp>
constexpr auto get_cmp(Cmp &c) noexcept {
    if constexpr(lower_bound_or_upper_bound) return c;//lower_bound
    else                                     return [&](Val x, Val y){ return !c(y, x); };
}
}//namespace impl
struct upper_bound {
    template <class It1, class It2, class It3, class Cmp = std::less<>, class It = std::remove_cv_t<It1>>
    constexpr auto operator()(const It1 &beg, It2 &hint, const It3 &end, const It_ref<It> val, Cmp c = {}) const {
        return impl::get_bound(beg, hint, end, val, impl::get_cmp<0, const It_val<It>&>(c));
    }
    template <class It1, class It2, class It3, class Cmp = std::less<>, class It = std::remove_cv_t<It1>>
    constexpr auto operator()(const It1 &beg, It2 &hint, It3 &&end, const It_ref<It> val, Cmp c = {}) const {
        return impl::get_bound(beg, hint, end, val, impl::get_cmp<0, const It_val<It>&>(c));
    }
};
struct lower_bound {
    template <class It1, class It2, class It3, class Cmp = std::less<>, class It = std::remove_cv_t<It1>>
    constexpr auto operator()(const It1 &beg, It2 &hint, const It3 &end, const It_ref<It> val, Cmp c = {}) const {
        return impl::get_bound(beg, hint, end, val, impl::get_cmp<1, const It_val<It>&>(c));
    }
    template <class It1, class It2, class It3, class Cmp = std::less<>, class It = std::remove_cv_t<It1>>
    constexpr auto operator()(const It1 &beg, It2 &hint, It3 &&end, const It_ref<It> val, Cmp c = {}) const {
        return impl::get_bound(beg, hint, end, val, impl::get_cmp<1, const It_val<It>&>(c));
    }
};
}//namespace sort
# undef CBOOL
#endif
