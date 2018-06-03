#ifndef __concept_check_type_storage_HPP__
#define __concept_check_type_storage_HPP__

# include <cstddef>
# include "impl/helper_function_declarations.hpp"

//All funcs defined here can't be used in evaluation context
namespace concept_check {
template <class ...T> struct type_storage {};

namespace impl {
template <std::size_t I, class T, class ...Args>
decltype(auto) element() noexcept {
    if constexpr(I > 0)
        return element<I - 1, Args...>();
    else
        return create_T<T>();
}//template function element
}
template <std::size_t I, class ...Args>
using element_T = decltype(impl::element<I, Args...>());

template <std::size_t I, class ...Args>
auto type_storage_element(type_storage<Args...>) noexcept -> element_T<I, Args...>;
template <std::size_t I, class T>
using type_storage_element_T = decltype(type_storage_element<I>(T{}));
}//namespace concept_check::impl
#endif
