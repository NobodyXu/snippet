#ifndef __concept_check_is_swappable_with_HPP__
#define __concept_check_is_swappable_with_HPP__
# include "impl/macro/define_fn_check.hpp"
# include "impl/macro/define_CONCEPT_T.hpp"
# include "impl/type_storage.hpp"
# include "impl/helper_function_declarations.hpp"
# include <utility>
namespace concept_check {
namespace impl {
namespace _impl_ {
using std::swap;
# define test_swap(T, a, b) swap(type_storage_element<a>(T{}), type_storage_element<b>(T{}))

template <class T> using decltype_swap = type_storage<decltype(test_swap(T, 0, 1)), decltype(test_swap(T, 1, 0))>;

DEF_CONCEPT_1(is_swap_nothrow_v, noexcept(test_swap(T, 0, 1)) && noexcept(test_swap(T, 1, 0)), DEF_CONCEPT_V);

# undef test_swap
}//namespace _impl_

create_check_fn_ret_t_test_fn_test(swap, _impl_::decltype_swap<T>, type_storage<void, void>, void)

template <class T> CONCEPT_T is_nothrow_swappable_with() noexcept {
    if constexpr(has_swap_v<T>) return 0;
    //return _impl_::is_swap_nothrow_v<T>;
    else                        return 0;
}
}//namespace impl

template <class T1, class T2 = T1> DEF_CONCEPT_V(is_swappable_with_v, (impl::has_swap_v<type_storage<T1, T2>>));
template <class T1, class T2 = T1> DEF_CONCEPT_V(is_nothrow_swappable_with_v, (impl::is_nothrow_swappable_with<type_storage<T1, T2>>));
DEF_CONCEPT_1(is_swappable_v, is_swappable_with_v<T>, DEF_CONCEPT_V);
DEF_CONCEPT_1(is_nothrow_swappable_v, is_nothrow_swappable_with_v<T>, DEF_CONCEPT_V);
}
# include "impl/macro/undef_fn_check.hpp"
# include "impl/macro/undef_CONCEPT_T.hpp"
#endif
