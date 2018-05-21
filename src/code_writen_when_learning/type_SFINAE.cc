#include <iostream>
#define MSG() __PRETTY_FUNCTION__
typedef const char* cstr;
template <int I = 0>
cstr F(char (*)[I % 2 == 0] = nullptr) noexcept { return MSG(); }
template <int I = 0>
cstr F(char (*)[I % 2 == 1] = nullptr) noexcept { return MSG(); }
int main() {
    std::cout << F() << "\n"
	      << F() << "\n";
}
