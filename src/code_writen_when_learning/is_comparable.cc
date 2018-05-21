#include <iostream>
struct A {
    int obj;
    constexpr operator const int &() const noexcept { return obj; }
    constexpr operator int() noexcept { return obj; }
};
int main() {
    std::cout << std::boolalpha
	      << (A{110} < A{2222})
	      << std::endl;
}
