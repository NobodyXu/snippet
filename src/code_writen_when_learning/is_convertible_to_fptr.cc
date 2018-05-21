#include <iostream>
#include <type_traits>
#define MSG() __PRETTY_FUNCTION__
typedef const char* cstr;
using fptr_t = cstr (*)(void);
struct A {
    constexpr operator fptr_t() const noexcept { return [](){ return MSG(); }; }
};
int main() {
    std::cout << std::boolalpha
	      << std::is_convertible<A, fptr_t>{}() << "\n"
	      << std::is_convertible<A&, fptr_t>{}() << "\n";
}
