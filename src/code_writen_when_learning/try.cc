#include <iostream>
#include <cstddef>
template <class ...T> struct type_storage {};

template <class T>
T create_T();

namespace impl {
template <std::size_t I, class T, class ...Args>
decltype(auto) element_t() noexcept {
    if constexpr(I > 0)
        return impl::element_t<I - 1, Args...>();
    else
        return create_T<T>();
}//template function element_t
}//namespace impl

template <std::size_t I, class ...Args>
decltype(auto) element_t(type_storage<Args...>) { return impl::element_t<I, Args...>(); }
template <std::size_t I, class T>
using element_T = decltype(element_t<I>(T{}));

struct A {
    int i, j, k;
};
int main() {
    element_T<2, type_storage<int, long, A>> a{1, 2, 3};
    std::cout << a.i << std::endl
	      << a.j << std::endl
	      << a.k << std::endl;
}
