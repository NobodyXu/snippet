#include <iostream>
#include <type_traits>
typedef const char* cstr;
struct Base {
    cstr F() const noexcept { return __PRETTY_FUNCTION__; }
    cstr F2() const noexcept { return __PRETTY_FUNCTION__; }
    static cstr F1() noexcept { return __PRETTY_FUNCTION__; }
};
struct Derived1: Base {
    cstr F() const noexcept { return __PRETTY_FUNCTION__; }
    cstr F2(char (*)[0] = 0) const noexcept { return __PRETTY_FUNCTION__; }
    static cstr F1() noexcept { return __PRETTY_FUNCTION__; }
};
int main() {
    std::cout << Base{}.F() << "\n" 
	      << Base::F1() << "\n"
	      << Base{}.F2() << "\n"
	      << Derived1{}.F() << "\n"
	      << Derived1::F1() << "\n"
	      << Derived1{}.F2() << "\n";
}
