#include <iostream>
#include <type_traits>
template <class F, class T>
inline constexpr const bool is_convertible_v{std::is_convertible<F, T>::value};
template <class T>
inline constexpr const bool is_convertible_ref_to_T_v{is_convertible_v<T&, T>};
int main()
