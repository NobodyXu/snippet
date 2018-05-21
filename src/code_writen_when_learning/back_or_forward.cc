#include <iostream>
#include <cstddef>
#include <array>
std::array<int, 11> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 10};
template <const std::size_t where, class Arr>
void iterate(Arr a) {
    if constexpr(where)
	for(std::size_t i = a.size() - 1; i != -1; --i) std::cout << a[i] << std::endl;
    else
	for(std::size_t i{0}, end = a.size(); i != end; ++i) std::cout << a[i] << std::endl;
}
int main() {
    iterate<1>(arr);
    iterate<0>(arr);
}
