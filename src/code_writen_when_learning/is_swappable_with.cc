#include <iostream>
#include <type_traits>
template <class T1, class T2>
inline constexpr const bool is_swappable_with_v{std::is_swappable_with<T1, T2>::value};
int main() {
    std::cout << std::boolalpha
	      << is_swappable_with_v<int, int> << std::endl
	      << is_swappable_with_v<int, char> << std::endl;
}
