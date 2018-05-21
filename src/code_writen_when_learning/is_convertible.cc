#include <iostream>
#include <type_traits>
template <class F, class T>
inline constexpr const bool is_convertible_v{std::is_convertible<F, T>::value};
int main() {
    std::cout << std::boolalpha
	      << is_convertible_v<int, int> << std::endl;
}
