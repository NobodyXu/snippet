#ifndef __algorithm_Container_Container_traits_container_traits_HPP__
# define __algorithm_Container_Container_traits_container_traits_HPP__
namespace algorithm {
namespace container_traits::impl {
struct Disambiguation2 {
    static inline constexpr const bool is_first = 0;
};
struct Disambiguation1 {
    static inline constexpr const bool is_first = 1;
    constexpr operator Disambiguation2() { return {}; }
};

# define DEF_TEMP template <template <class...> class C>
# define DEF_F static constexpr auto
template <class D>
struct Base {
    DEF_F has(Disambiguation2 d) -> decltype(d);
    static inline constexpr const bool is_true = decltype(D::has(Disambiguation1{}))::is_first;
    constexpr bool operator () () const noexcept { return is_true; }
};

DEF_TEMP struct has_emplace_front: Base<has_emplace_front> {
    using Base::has;
    DEF_F has(Disambiguation1 d) -> decltype(&C<int>::emplace_front, d);
};
DEF_TEMP struct has_emplace_back: Base<has_emplace_back> {
    using Base::has;
    DEF_F has(Disambiguation1 d) -> decltype(&C<int>::emplace_back, d);
};

DEF_TEMP struct has_resize: Base<has_emplace_back> {
    using Base::has;
    DEF_F has(Disambiguation1 d) -> decltype(&C<int>::resize, d);
};
DEF_TEMP struct has_reserve: Base<has_emplace_back> {
    using Base::has;
    DEF_F has(Disambiguation1 d) -> decltype(&C<int>::reserve, d);
};
# undef DEF_F
# undef DEF_TEMP
} /* container_traits::impl */
template <template <class...> class Container>
struct container_traits {};
} /* algorithm */
#endif
