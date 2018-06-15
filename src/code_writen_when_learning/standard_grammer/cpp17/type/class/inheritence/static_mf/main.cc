#include <iostream>
struct A {
    static int F() { return 97; }
    operator char() const noexcept { return static_cast<char>(F()); }
};
struct B: A {
};
struct C: A {
    using A::F;
    static int F(int) { return 1; }
};
struct D: A {
    static int F() { return 98; }
};
int main() {
    std::cout << A::F()  << std::endl
	      << B::F()  << std::endl
	      << C::F()  << std::endl
	      << C::F(1) << std::endl
	      << D::F()  << std::endl
	      << A{} << std::endl
	      << D{} << std::endl;
}
