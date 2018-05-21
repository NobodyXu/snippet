#include <iostream>
#define MSG() __PRETTY_FUNCTION__
typedef const char* cstr;
struct B {
    cstr F() const noexcept { return MSG(); }
};
struct D: B {
    cstr F() const noexcept { return MSG(); }
};
int main() {
    std::cout << B{}.F() << std::endl
	      << D{}.F() << std::endl;
}
