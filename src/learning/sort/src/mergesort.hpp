//C++17
#ifndef __sort_mergesort_HPP__
#define __sort_mergesort_HPP__
# include "binarysort.hpp"
# include <type_traits>
# define likely(x) __builtin_expect(!!(x), 1)
# define unlikely(x) __builtin_expect(!!(x), 0)
# define BOOL static inline constexpr bool
# define CBOOL const BOOL
namespace sort {
template <class _It, class lbr = lower_bound<>, class ubr = upper_bound<>>
struct two_way_mergeable_container_impl {
    using It     = _It;
    using diff_t = It_diff_t<It>;
    using T      = It_val<It>;
    using reversed_version = two_way_mergeable_container_impl<std::reverse_iterator<It>, lbr, ubr>;

    It l_beg, r_beg, r_end;
    lbr _lower_bound;
    ubr _upper_bound;
    two_way_mergeable_container_impl(const It &beg, const It &mid, const It &end, lbr lower_bound = {}, ubr upper_bound = {}):
                                     l_beg{beg}, r_beg{mid}, r_end{end}, _lower_bound{lower_bound}, _upper_bound{upper_bound} {}

    template <class = std::enable_if_t</* type It is an bidirectional iterator */>>
    constexpr auto reverse_container() const { return reversed_version{r_end, r_beg, l_beg, _lower_bound, _upper_bound}; }

    bool runtime_assert_before_merge() const {
        assert(l_beg != r_beg);
        assert(r_beg != r_end);
        assert(l_beg != r_end);
    }
    bool does_right_reach_the_end() const { return r_beg == r_end; }

    const T& get_left() const { return *l_beg; }
    const T& get_right() const { return *r_beg; }

    template <class Cmp>
    void gallop_both_sides(Cmp &c) {
        _upper_bound({l_beg}, l_beg, r_beg, c, get_right());
        _lower_bound({r_beg}, r_beg, r_end, c, *(r_beg - 1));
    }
};

template <class Base>
struct two_way_mergeable_container: Base {
    using reversed_version = two_way_mergeable_container<typename Base::reversed_version>;
    T *tmp;
    const T * const eot;

    CBOOL is_inplace_mergeable{0};
    CBOOL has_buf{1};
    CBOOL is_O1_insertable{0};

    template <class = std::enable_if_t</* type It is an bidirectional iterator */>>
    constexpr auto reverse_container() const { return reversed_version{Base::reverse_container(), tmp, eot}; }

    bool runtime_assert_before_merge() const {
        Base::runtime_assert_before_merge();
        assert(tmp);
        assert(eot);
        assert(tmp != eot);
    }

    void prepare() {
        assert(!It_dis_is_larger_than(l_beg, r_beg, eot - tmp));
        std::move(l_beg, r_beg, tmp);
        mv_from_right_and_inc();
    }

    const T& get_left() const { return *tmp; }

    void mv_from_left_and_inc() {
        runtime_assert_before_mv();
        *l_beg = std::move(*tmp);
        ++l_beg, ++tmp;
        assert(!does_left_reach_the_end());
    }
    void mv_from_right_and_inc() {
        runtime_assert_before_mv();
        mv_from_right_and_inc_without_runtime_assert_before_mv();
    }

    auto mv_left_to_upper_bound() {
        runtime_assert_before_mv();
        auto otmp = tmp;
        l_beg = std::move(otmp, (tmp = _upper_bound(tmp, eot, get_right(), c)), l_beg);
        diff_t cnt{tmp - otmp};
        //Because right always ends first(the effect of sort::Merge::gallop_both_sides)
        assert(!does_left_reach_the_end());
        //Because right != end(promised made by operator() (void)) and the fact that this function will only
        //be called when !c(get_right(), get_left()) is true.
        assert(cnt);
        return cnt;
    }
    auto mv_right_to_lower_bound() {
        runtime_assert_before_mv();
        auto ol_beg = l_beg;
        l_beg = std::move(mid, (mid = _lower_bound(mid, end, get_left(), c)), l_beg);
        //Because right != end(promised made by operator() (void)) and the fact that this function will only
        //be called when !c(get_right(), get_left()) is true.
        auto cnt{l_beg - ol_beg};
        assert(cnt);
        return cnt;
    }

    void cleanup() {
        runtime_assert_before_mv_back();
        std::move(tmp, eot, l_beg);
    }
  protected:
    //This assertion should only be tested in the main loop
    void runtime_assert_before_mv() const {
        //Because right always ends first, so does_left_reach_the_end() should returns true in the main loop
        assert(!does_left_reach_the_end());
        //When right == end, the operator () (void) should call cleanup and return.
        assert(!does_right_reach_the_end());
    }
    void runtime_assert_before_mv_back() const {
        assert(std::distance(r_end, r_beg) == 1);
        auto sizeof_tmp = eot - tmp;
        assert(sizeof_tmp >= 1);
        assert(sizeof_tmp == std::distance(l_beg, r_beg));
    }
    bool does_left_reach_the_end() const { return tmp == eot; }
    void mv_from_right_and_inc_without_runtime_assert_before_mv() {
        *l_beg = std::move(*r_beg);
        ++l_beg, ++r_beg;
    }
};//struct mergeable_container_base
template <class B> two_way_mergeable_container(B, typename B::T*, const typename B::T * const) -> two_way_mergeable_container<B>;

template <class Base, class Inserter = inserter<typename Base::It>>
struct two_way_inplace_mergeable_container: Base {
    using reversed_version = two_way_inplace_mergeable_container<typename Base::reversed_version>;
    Inserter _insert;

    CBOOL is_inplace_mergeable{1};
    CBOOL has_buf{0};
    CBOOL is_O1_insertable{1};

    template <class = std::enable_if_t</* type It is an bidirectional iterator */>>
    constexpr auto reverse_container() const { return reversed_version{Base::reverse_container(), _insert}; }

    void prepare() { mv_from_right_and_inc_without_runtime_assert_before_mv(); }

    void mv_from_left_and_inc() {
        runtime_assert_before_mv();
        ++l_beg;
        //Because right always ends first(the effect of sort::Merge::gallop_both_sides)
        assert(!does_left_reach_the_end());
    }
    void mv_from_right_and_inc() {
        runtime_assert_before_mv();
        mv_from_right_and_inc_without_runtime_assert_before_mv();
    }

    auto mv_left_to_upper_bound() {
        assert(runtime_assert_before_mv());
        auto cnt{_upper_bound(l_beg, r_beg, get_right(), c)};
        //Because right always ends first(the effect of sort::Merge::gallop_both_sides)
        assert(!does_left_reach_the_end());
        //Because right != end(promised made by operator() (void)) and the fact that this function will only
        //be called when !c(get_right(), get_left()) is true.
        assert(cnt);
        return cnt;
    }
    auto mv_right_to_lower_bound() {
        assert(runtime_assert_before_mv());
        auto o_r_beg{r_beg};
        auto cnt{_lower_bound(r_beg, r_end, get_left(), c)};
        assert(cnt);
        _insert(l_beg, o_r_beg, r_beg);
        return cnt;
    }

    void cleanup() { runtime_assert_before_mv_back(); }
  protected:
    bool does_left_reach_the_end() const { return beg == mid; }
    void runtime_assert_before_mv() const {
        //Because right always ends first, so does_left_reach_the_end() should returns true in the main loop
        assert(!does_left_reach_the_end());
        //When right == end, the operator () (void) should call cleanup and return.
        assert(!does_right_reach_the_end());
    }
    void runtime_assert_before_mv_back() const { assert(std::distance(end, mid) == 1); }
    void mv_from_right_and_inc_without_runtime_assert_before_mv() {
        auto omid{mid};
        ++mid;
        _insert(beg, omid);
    }
};//struct inplace_mergeable_container_base
template <class B, class Ins> two_way_inplace_mergeable_container(B, Ins) -> two_way_inplace_mergeable_container<B, Ins>;
template <class B> two_way_inplace_mergeable_container(B) -> two_way_inplace_mergeable_container<B>;

/*
 * class template sort::Merge_impl provides the main logic of algorithm merge
 * @ container  It provides the logic of whether left is copied and how and where it is copied to
 *            , how to get the value of dereferenced left and right, how to test whether right reaches the end,
 *              how to move one element/a range of element from left/right and inc the iterator, and how to cleanup after the main loop.
 *
 * @ c  It provides the logic of how T is compared.
 *
 * @ min_gallop  It provides the logic of how many times left/right should be chosen continuously before the main loop enters gallop_mode.
 */
template <class C, class Cmp>
struct two_way_Merge_impl: C {
    Cmp &c;
    diff_t &min_gallop;

    template <bool switch_for_gallop_mode>
  	void main() {
        diff_t accl{0}, accr{1};
        prepare();
        for( ; ; ) {//the main loop
            if(comp_right_and_left()) {
                mv_from_right_and_inc();
                accl = 0, ++accr;
            } else {
                mv_from_left_and_inc();
                accr = 0, ++accl;
            }
            if(unlikely(does_right_reach_the_end())) break;
            if constexpr(siwtch_for_gallop_mode)
                if(unlikely((accl | accr) == min_gallop)) {
                    diff_t cnt;
                    if(comp_right_and_left())
                        do {
                            min_gallop = min_gallop > 3 ? min_gallop - 2 : 3;
                            cnt = mv_right_to_lower_bound();
                            if(unlikely(does_right_reach_the_end())) goto eor;
                            cnt += mv_left_to_upper_bound();
                        } while (cnt >= min_gallop);
                    else
                        do {
                            min_gallop = min_gallop > 3 ? min_gallop - 2 : 3;
                            cnt  = mv_left_to_upper_bound();
                            cnt += mv_right_to_lower_bound();
                            if(unlikely(does_right_reach_the_end())) goto eor;
                        } while (cnt >= min_gallop);
                    min_gallop += 3;
                }//gallop mode
        }//for loop
      eor:
        cleanup();
    }

    bool comp_right_and_left() const { return c(get_right(), get_left()); }
};//struct Merge
template <class C, class Cmp> Merge(C, Cmp, typename C::diff_t) -> Merge<C, Cmp>;

template <class C, class Cmp = std::less>
struct Binary_two_way_Merge {
    using T      = typename C::T;
    using diff_t = typename C::diff_t;
    using It     = typename C::It;
    C container;
    diff_t &min_gallop;
    const diff_t &min_merge;
    Cmp c;

    bool default_switch_for_gallop_mode{1};
    using concept_check::is_same_v;
    CBOOL is_random_access_iterator{is_same_v<It_tag<It>, std::random_access_iterator_tag>};
    CBOOL is_bidirectional_iterator{is_same_v<It_tag<It>, std::bidirectional_iterator_tag>};

    void operator () (void) {
        runtime_assert_before_merge();
        if(c(*r_beg, *(r_beg - 1))) merge_impl();
    }
    void merge_impl() {
        container.gallop_both_sides();
        if(It_dis_is_larger_than(l_beg, r_beg, min_merge) && It_dis_is_larger_than(r_beg, r_end, min_merge)) merge();
        else                                                                                                 binarysort();
    }
  protected:
    constexpr auto get_reversed_cmp() noexcept { return [&c](const T &x, const T &y){ return c(y, x); }; }

    void runtime_assert_before_merge() const {
        assert(container.runtime_assert_before_merge());
        assert(std::is_sorted(container.l_beg, container.r_beg, c));
        assert(std::is_sorted(container.r_beg, container.r_end, c));
    }

    void merge() {
        auto f = [this](){
            if(r_beg - l_beg < min_gallop && r_end - r_beg < min_gallop) _merge<0>();
            else                                                         _merge<default_switch_for_gallop_mode>();
        };
        if constexpr(is_random_access_iterator) f();
        else                                    _merge<default_switch_for_gallop_mode>();
    }
    template <bool switch_for_gallop_mode>
    void _merge() {
        if constexpr(is_random_access_iterator/* the cost of accessing an element */)
            if(r_beg - l_beg > r_end - r_beg)
                _merge<switch_for_gallop_mode>(container.reverse_container(), get_reversed_cmp(), min_gallop);
            else
                _merge<switch_for_gallop_mode>(container, c, min_gallop);
        else
            _merge<switch_for_gallop_mode>(container, c, min_gallop);
    }

    //These two followimg functions decide whether to compare the left and right and reverse the container and c
    void _binarysort() {
        if constexpr(is_random_access_iterator/* the cost of accessing an element */)
            if(r_beg - l_beg > r_end - r_beg)
                __binarysort(container.reverse_container(), get_reversed_cmp());
            else
                __binarysort(container, c);
        else
            __binarysort(container, c);
    }
    template <class _C, class _Cmp>
    static void __binarysort(_C _container, _Cmp _c) {
        if constexpr(_C::is_inplace_mergeable)
            binarysort(_container.l_beg, _container.r_beg, _container.r_end, _c, _container._upper_bound, _container._insert);
        else
            binarysort(_container.l_beg, _container.r_beg, _container.r_end, _c, _container._upper_bound);
    }
};
template <class C, class Cmp> Merge(C, typename C::diff_t, typename C::diff_t, Cmp) -> Merge<C, Cmp>;
template <class C> Merge(C, typename C::diff_t, typename C::diff_t) -> Merge<C>;
}//namespace sort
# undef likely
# undef unlikely
# undef BOOL
# undef CBOOL
#endif
