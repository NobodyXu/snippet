#include <iostream>
template <class T>
struct A {
    bool F();
};
template <class Ret, class ...Args>
struct A<Ret (*)(Args...)> {
    bool F() noexcept { return 0; }
};
template <class Ret, class ...Args>
struct A<Ret (*)(Args...) noexcept> {
    bool F() noexcept { return 1; }
};
int main() {
    std::cout << std::boolalpha
	      << A<void (*)(void)>{}.F() << "\n"
	      << A<void (*)(void) noexcept>{}.F() << "\n";
}
