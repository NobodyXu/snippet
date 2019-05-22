#ifndef __type_erasure_any_basic_storage_any_base_HPP__
# define __type_erasure_any_basic_storage_any_base_HPP__
# include <cstdint>
# include <type_traits>
# include <boost/smart_ptr/intrusive_ref_counter.hpp>
# include <boost/smart_ptr/intrusive_pointer.hpp>
namespace type_erasure {
template <class T, class ...Args> void construct_on(void *ptr, Args ...args) noexcept(new (ptr) T(args...)) { new (ptr) T(args...); }
template <
        /*
         * @ option describe what function ptr you want to get.
         *          When opton == 0, get cp ctor
         *          When opton == 1, get mv ctor
         *          When opton == 2, get dtor
         */
        char option,
        class T
    >
constexpr auto generater() noexcept {
    if constexpr(option < 2) return &construct_on<T, std::conditional_t<option, T&&, const T&>>;
    else                     return static_cast<void (*)(const T&)>([](const T &t) noexcept(t.~T()) { t.~T(); });
}
} /* type_erasure */

namespace type_erasure::vtable {
struct group_base: boost::intrusive_ref_counter<group_base> {};
typedef boost::intrusive_pointer<group_base> group_base_ptr_t;

//group1 records the fundemental information about the type being erased.
struct group1: group_base {
    struct bitset_t {
        enum :char16_t {
            is_cp_trival      = 1 << 0;
            has_mv_ctor       = 1 << 1;
            has_cp_ctor       = 1 << 2;
            is_fundemental_t  = 1 << 3;
        } bitset;
        template <class T> constexpr bitset_t(T*) noexcept {
            if constexpr(std::is_trivially_copy_constructible<T>{}()) bitset |= is_cp_trival;
        }
    } bitset;
    void (*fptr[0])(void);
};
} /* type_erasure::vtable */

#endif
