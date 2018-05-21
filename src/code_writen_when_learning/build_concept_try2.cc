#include <iostream>
#include <type_traits>

template <class T>
using __T = T;

template <class F, class T>
inline constexpr const bool is_convertible_v{std::is_convertible<F, T>::value};

template <class F, class T>
inline constexpr const bool is_same_v{std::is_same<F, T>::value};

#include "disambiguation_types.hpp"
using namespace concept_check;
namespace impl {
template <class T>
auto is_pre_incrementable(disambiguation_t1) -> __T<decltype(++( *__T<T*>(nullptr) ))>;
template <class T>
void is_pre_incrementable(disambiguation_t2);
}

template <class T>
constexpr const  bool is_pre_incrementable() noexcept {
    if constexpr(is_same_v<decltype(impl::is_pre_incrementable<T>(disambiguation_t1{})), void>)
	return 0;
    else
	return is_convertible_v<decltype(++( *__T<T*>(nullptr) )), T&>;
}

template <class T>
inline constexpr const bool is_pre_incrementable_v{is_pre_incrementable<T>()};

struct A {};

int main() {
    std::cout << std::boolalpha
	      << is_pre_incrementable_v<int> << std::endl
	      << is_pre_incrementable_v<A> << std::endl;
}
