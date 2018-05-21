#include <iostream>
typedef const char* cstr;
template <class ...Args> constexpr cstr F(Args&&...) noexcept { return __PRETTY_FUNCTION__; }
int main() {
    int i;
    std::cout << F(int{}) << std::endl
	      << F(i) << std::endl;
}
