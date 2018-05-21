#include <iostream>
typedef const char* cstr;
#define MSG() __PRETTY_FUNCTION__
struct A {
    using F = cstr (*)(void);
    constexpr operator F () const noexcept { return [](){ return MSG(); }; }
};
struct B {
    cstr operator () (void) const noexcept { return MSG(); }
};
template <class type, class T, class ...Args>
auto F(const T &obj, const Args &...args) { return static_cast<type>(obj)(args...); }
int main() {
    std::cout << F<cstr(*)(void)>(A{}) << "\n"
	      << A{}() << "\n";
}
