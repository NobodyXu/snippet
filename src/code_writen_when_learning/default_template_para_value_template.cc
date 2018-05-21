#include <iostream>
template <class T = char>
inline constexpr const T t{60};
int main() {
    std::cout << t<int> << std::endl
	      << t<> << std::endl;
}
